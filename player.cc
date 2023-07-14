#include "player.h"

Player::Player(bool computer) : computer{computer} {
	gameScore = 0;
	roundScore = 0;
}

bool Player::isComputer() const { return computer; }

std::vector<std::shared_ptr<Card>> Player::getHand() const { return hand; }

std::vector<std::shared_ptr<Card>> Player::getDiscards() const { return discards; }

void Player::addToHand(std::shared_ptr<Card> card) { hand.push_back(card); }

std::shared_ptr<Card> Player::removeFromHand(std::string card) {
	std::shared_ptr<Card> toRemove;
	for (size_t i = 0; i < hand.size(); i++) {
		if (hand[i]->getType() == card) {
			toRemove = hand[i];
			hand.erase(hand.begin() + i);
			break;
		}
	}
	return toRemove;
}

void Player::addToDiscards(std::shared_ptr<Card> card) {
	discards.push_back(card);
	roundScore += card->getRank();
}

int Player::getGameScore() const { return gameScore; }

int Player::getRoundScore() const { return roundScore; }

void Player::setPlayerType(bool comp) { computer = comp; }

void Player::endRound() {
	hand.clear();
	discards.clear();
	gameScore += roundScore;
	roundScore = 0;
}
