#include "gamemodel.h"
#include <algorithm>
#include <iostream>

GameModel::GameModel(unsigned seed) : seed{seed} {
	deck = std::make_shared<Deck>(seed);
}

std::vector<std::shared_ptr<Player>> GameModel::getPlayers() const { return players; }

std::shared_ptr<Deck> GameModel::getDeck() const { return deck; }

std::deque<std::shared_ptr<Card>> GameModel::getTableClubs() const { return tableClubs; }

std::deque<std::shared_ptr<Card>> GameModel::getTableDiamonds() const { return tableDiamonds; }

std::deque<std::shared_ptr<Card>> GameModel::getTableHearts() const { return tableHearts; }

std::deque<std::shared_ptr<Card>> GameModel::getTableSpades() const { return tableSpades; }

int GameModel::getCurrentPlayer() const { return currentPlayer; }

void GameModel::addPlayer(char playerType) {
	bool computer = false;
	if (playerType == 'c') {
		computer = true;
	}
	std::shared_ptr<Player> newPlayer = std::make_shared<Player>(computer);
	players.push_back(newPlayer);
}

void GameModel::resetRound() {
	for (int i = 0; i < 4; ++i) {
		players[i]->endRound();
	}
	tableClubs.clear();
	tableDiamonds.clear();
	tableHearts.clear();
	tableSpades.clear();
	deck->shuffle();
	int j = 0;
	for (int i = 0; i < 52; ++i) {
		if (i != 0 && i % 13 == 0) {
			++j;
		}
		players[j]->addToHand(deck->getDeck()[i]);
		if (deck->getDeck()[i]->getType() == "7S") {
			currentPlayer = j;
		}
	}
}

std::vector<std::shared_ptr<Card>> GameModel::getLegalPlays() const {
	std::vector<std::shared_ptr<Card>> playerHand = players[currentPlayer]->getHand();
	std::vector<std::shared_ptr<Card>> legalPlays;
	for (auto card: playerHand) {
		int rank = card->getRank();
                char suit = card->getSuit();
		if (rank == 7) {
			if (suit == 'S') {
				legalPlays.clear();
				legalPlays.push_back(card);
				break;
			} else {
				legalPlays.push_back(card);
			}
		} else if (suit == 'C' && !tableClubs.empty() && (rank == tableClubs.front()->getRank() - 1 || rank == tableClubs.back()->getRank() + 1)) {
			legalPlays.push_back(card);
		} else if (suit == 'D' && !tableDiamonds.empty() && (rank == tableDiamonds.front()->getRank() - 1 || rank == tableDiamonds.back()->getRank() + 1)) {
                        legalPlays.push_back(card);
                } else if (suit == 'H' && !tableHearts.empty() && (rank == tableHearts.front()->getRank() - 1 || rank == tableHearts.back()->getRank() + 1)) {
                        legalPlays.push_back(card);
                } else if (suit == 'S' && !tableSpades.empty() && (rank == tableSpades.front()->getRank() - 1 || rank == tableSpades.back()->getRank() + 1)) {
                        legalPlays.push_back(card);
                }
	}
	return legalPlays;
}

bool GameModel::isLegalPlay(std::string card) {
	auto legalPlays = getLegalPlays();
	if (card == "10C") {
		std::cout << "10C legal? plays: " << std::endl;
		for (auto c: legalPlays) {
			std::cout << c->getType() << std::endl;
		}
	}
	for (auto c: legalPlays) {
		if (card == c->getType()) {
			return true;
		}
	}
	return false;
}

void GameModel::playedCard(std::string card) {
	std::shared_ptr<Player> player = players[currentPlayer];
	auto cardPlayed = player->removeFromHand(card);
	int rank = cardPlayed->getRank();
	char suit = cardPlayed->getSuit();
	if (suit == 'C') {
	       	if (tableClubs.empty() || rank == tableClubs.front()->getRank() - 1) {
			tableClubs.push_front(cardPlayed);
		} else {
			tableClubs.push_back(cardPlayed);
		}
	} else if (suit == 'D') {
		if (tableDiamonds.empty() || rank == tableDiamonds.front()->getRank() - 1) {
                        tableDiamonds.push_front(cardPlayed);
                } else {
                        tableDiamonds.push_back(cardPlayed);
                }
	} else if (suit == 'H') {
		if (tableHearts.empty() || rank == tableHearts.front()->getRank() - 1) {
                        tableHearts.push_front(cardPlayed);
                } else {
                        tableHearts.push_back(cardPlayed);
                }
	} else {
		if (tableSpades.empty() || rank == tableSpades.front()->getRank() - 1) {
                        tableSpades.push_front(cardPlayed);
                } else {
                        tableSpades.push_back(cardPlayed);
                }
	}
	if (currentPlayer == 3) {
                currentPlayer = 0;
        } else { 
                currentPlayer++;
        }
	notifyObservers();
}

void GameModel::discardedCard(std::string card) {
	std::shared_ptr<Player> player = players[currentPlayer];
        player->addToDiscards(player->removeFromHand(card));
	if (currentPlayer == 3) {
		currentPlayer = 0;
	} else { 
		currentPlayer++;
	}
        notifyObservers();
}

void GameModel::rageQuit() {
	players[currentPlayer]->setPlayerType(true);
	notifyObservers();
}

std::vector<int> GameModel::getWinners() const {
	std::vector<int> winners;
	for (auto p: players) {
		p->endRound();
	};
	int lowestScore = players[0]->getGameScore();
	for (int i = 0; i < 4; ++i) {
		if (lowestScore > players[i]->getGameScore()) {
			winners.clear();
			winners.push_back(i);
			lowestScore = players[i]->getGameScore();
		} else if ((lowestScore == players[i]->getGameScore())) {
			winners.push_back(i);
		}
        }
	return winners;
}
