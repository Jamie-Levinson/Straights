#ifndef GAMEVIEW_H
#define GAMEVIEW_H

#include "observer.h"
#include <string>
#include <memory>

class GameModel;
//constructor is main file, invites players, calls update
//update is each turn, takes in input, calls handleFunctions
//
class GameView : public Observer {
	public:
		GameView(std::shared_ptr<GameModel> gm);
		virtual void update();
		void beginNewRound();
		void handleDeck();
		void handleLegalPlay(std::string cardPlayed);
		void handleLegalDiscard(std::string cardDiscarded);
		void handleRageQuit();
		void handleQuit();
		void handleWinners();
	private:
		std::shared_ptr<GameModel> gm;
		void nextInput();
};

#endif
