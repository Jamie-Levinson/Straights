#include "gameview.h"
#include "gamemodel.h"
#include <iostream>
#include <string>
//model is sent to constructor from main already constructed with deck, empty players array, etc.
GameView::GameView(std::shared_ptr<GameModel> gm) : gm{gm} {
	std::cout << "Welcome to Straights!" << std::endl;
	gm->attach(this);
	char input;
	for(int i = 0; i < 4; ++i) {
		std::cout << "Is Player" << i+1 << " a human (h) or a computer (c) ?" << std::endl;
		std::cin >> input;
		gm->addPlayer(input);
	
	}
	beginNewRound();
}

void GameView::beginNewRound() {
	gm->resetRound();
	std::cout << "A New Round Begins. It's Player" << gm->getCurrentPlayer()+1 << "'s turn to play." << std::endl;
	update();

}

void GameView::update() {
	std::vector<std::shared_ptr<Player>> players = gm->getPlayers();
	if (players[0]->getHand().empty() && players[1]->getHand().empty() && players[2]->getHand().empty() && players[3]->getHand().empty()) {
		bool gameOver = false;
		for (int i = 0; i < 4; i++) {
			std::vector<std::shared_ptr<Card>> discards = players[i]->getDiscards();
			int game = players[i]->getGameScore();
			int round = players[i]->getRoundScore();
			int total = game + round;
			std::cout << "Player" << i+1 << "'s discards:";
			for (auto card: discards) {
				std::cout << " " << card->getType();
			}
			std::cout << std::endl << "Player" << i+1 << "'s score: " << game << " + " << round << " = " << total << std::endl;
			if (total >= 80) { 
				gameOver = true; 
			}
		}
		if (gameOver) {
			handleWinners();
		} else {
			beginNewRound();
		}
		return;	
	}

	std::shared_ptr<Player> currentPlayer = players[gm->getCurrentPlayer()];
	std::deque<std::shared_ptr<Card>> tableClubs = gm->getTableClubs();
	std::deque<std::shared_ptr<Card>> tableDiamonds = gm->getTableDiamonds();
	std::deque<std::shared_ptr<Card>> tableHearts = gm->getTableHearts();
	std::deque<std::shared_ptr<Card>> tableSpades = gm->getTableSpades();
	std::vector<std::shared_ptr<Card>> playerHand = currentPlayer->getHand();
	std::vector<std::shared_ptr<Card>> legalPlays = gm->getLegalPlays();
	
	if (currentPlayer->isComputer()) {
		if (legalPlays.empty()) {
			handleLegalDiscard(playerHand[0]->getType());
		} else {
			handleLegalPlay(legalPlays[0]->getType());
		}
	
	} else {
		std::cout << "Cards on the table:" << std::endl;
		std::cout << "Clubs:";
		for(auto c: tableClubs) {
			std::cout << " " << c->getType().substr(0, c->getType().size()-1);
		}
		std::cout << std::endl;
		std::cout << "Diamonds:";
		for(auto c: tableDiamonds) {
			std::cout << " " << c->getType().substr(0, c->getType().size()-1);
                }
                std::cout << std::endl;
		std::cout << "Hearts:";
		for(auto c: tableHearts) {
			std::cout << " " << c->getType().substr(0, c->getType().size()-1);
                }
                std::cout << std::endl;
		std::cout << "Spades:";
		for(auto c: tableSpades) {
                        std::cout << " " << c->getType().substr(0, c->getType().size()-1);
                }
                std::cout << std::endl;
		std::cout << "Your hand:";
		for(auto c: playerHand) {
			std::cout << " " << c->getType();
		}
		std::cout << std::endl;
                std::cout << "Legal Plays:";
                for(auto c: legalPlays) {
                        std::cout << " " << c->getType();
                }
		std::cout << std::endl;
		nextInput();
	}
}

void GameView::nextInput() {
	std::string input;
	std::string card;
	if (!(std::cin >> input)) {
		return;
	}
	if (input == "play") {
		std::cin >> card;
		if (gm->isLegalPlay(card)) {
			handleLegalPlay(card);
		} else {
			std::cout << "This is not a legal play." << std::endl;
			nextInput();
		}
	} else if (input == "discard") {
		std::cin >> card;
		if (gm->getLegalPlays().empty()) {
			handleLegalDiscard(card);
		} else {
			std::cout << "You have a legal play. You may not discard." << std::endl;
			nextInput();
		}
	} else if (input == "deck") {
		handleDeck();
	} else if (input == "ragequit") {
		handleRageQuit();
	} else if (input != "quit") {
		std::cout << "Invalid Command, please retry." << std::endl;
		nextInput();
	} else {
		std::cout << "Goodbye! Thanks for playing Straights!" << std::endl;
	}
	
}

void GameView::handleDeck() {
	std::cout << *gm->getDeck();
	nextInput();
}

void GameView::handleLegalPlay(std::string cardPlayed) {
	std::cout << "Player" << gm->getCurrentPlayer() + 1 << " plays " << cardPlayed << std::endl;
	gm->playedCard(cardPlayed); 
}

void GameView::handleLegalDiscard(std::string cardDiscarded) {
	std::cout << "Player" << gm->getCurrentPlayer() + 1 << " discards " << cardDiscarded << std::endl;
	gm->discardedCard(cardDiscarded);
}

void GameView::handleRageQuit() {
	std::cout << "Player" << gm->getCurrentPlayer() + 1 << " ragequits. A computer will now take over." << std::endl;
	gm->rageQuit(); 
}

void GameView::handleWinners() {
	std::vector<int> winners = gm->getWinners();
	for (int player: winners) {
		std::cout << "Player" << player + 1 << " wins!" << std::endl;
	}
}
