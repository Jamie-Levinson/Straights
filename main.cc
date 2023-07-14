#include "gamemodel.h"
#include "gameview.h"

int main( int argc, char * argv[] ) {
	unsigned seed = 0;
	if (argc > 1) {
		seed = std::stoul(argv[1]);
	}
	std::shared_ptr<GameModel> gm = std::make_shared<GameModel>(seed);
	std::shared_ptr<GameView> gc = std::make_shared<GameView>(gm);
}
