#ifndef GAMEMODEL_H
#define GAMEMODEL_H
#include "subject.h"
#include "deck.h"
#include "player.h"
#include <vector>
#include <memory>
#include <string>
#include <deque>

class GameModel : public Subject {
	public:
		GameModel(unsigned seed);
		std::vector<std::shared_ptr<Player>> getPlayers() const;
		std::shared_ptr<Deck> getDeck() const;
		std::deque<std::shared_ptr<Card>> getTableClubs() const;
		std::deque<std::shared_ptr<Card>> getTableDiamonds() const;
		std::deque<std::shared_ptr<Card>> getTableHearts() const;
		std::deque<std::shared_ptr<Card>> getTableSpades() const;
		int getCurrentPlayer() const;
		void addPlayer(char playerType);
		void resetRound();
		std::vector<std::shared_ptr<Card>> getLegalPlays() const;
		bool isLegalPlay(std::string card);
		void playedCard(std::string card);
		void discardedCard(std::string card);
		void rageQuit();
		std::vector<int> getWinners() const;
	private:
		std::vector<std::shared_ptr<Player>> players;
		std::shared_ptr<Deck> deck;
		std::deque<std::shared_ptr<Card>> tableClubs;
		std::deque<std::shared_ptr<Card>> tableDiamonds;
		std::deque<std::shared_ptr<Card>> tableHearts;
		std::deque<std::shared_ptr<Card>> tableSpades;
		int currentPlayer;
		unsigned seed;
};

#endif
