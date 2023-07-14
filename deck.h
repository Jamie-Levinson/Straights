#ifndef DECK_H
#define DECK_H
#include "card.h"
#include <memory>
#include <vector>

class Deck {
	public:
		Deck(unsigned seed);
		void shuffle();
		std::vector<std::shared_ptr<Card>> getDeck() const;
	private:
		unsigned seed;
		std::vector<std::shared_ptr<Card>> deck;
};

std::ostream &operator<<(std::ostream & out, const Deck & deck);

#endif
