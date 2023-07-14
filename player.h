#ifndef PLAYER_H
#define PLAYER_H
#include "card.h"
#include <vector>
#include <memory>
#include <string>
class Player {
	public:
		Player(bool computer);
		bool isComputer() const;
		std::vector<std::shared_ptr<Card>> getHand() const;
		std::vector<std::shared_ptr<Card>> getDiscards() const;
		void addToHand(std::shared_ptr<Card> card);
		std::shared_ptr<Card> removeFromHand(std::string card);
		void addToDiscards(std::shared_ptr<Card> card);
		int getGameScore() const;
		int getRoundScore() const;
		void endRound();
		void setPlayerType(bool comp);
	private:
		std::vector<std::shared_ptr<Card>> hand;
		std::vector<std::shared_ptr<Card>> discards;
		int gameScore;
		int roundScore;
		bool computer;
};

#endif
