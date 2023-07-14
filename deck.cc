#include "deck.h"
#include <chrono>
#include <random>
#include <algorithm>
#include <iostream>

Deck::Deck(unsigned seed) : seed{seed} {
	std::string suits[4] = {"C", "D", "H", "S"};
	std::string ranks[13] = {"A", "2", "3", "4", "5", "6", "7", "8", "9", "10", "J", "Q", "K"};
	for(auto suit: suits) {
		for (auto rank: ranks) {
			std::string card = rank + suit;
			std::shared_ptr<Card> newCard = std::make_shared<Card>(card);
			deck.push_back(newCard);
		}
	}
}

void Deck::shuffle() {
	if (seed == 0) {
		seed = std::chrono::system_clock::now().time_since_epoch().count();
	}
	std::default_random_engine rng{seed};
	std::shuffle(deck.begin(), deck.end(), rng);
}

std::vector<std::shared_ptr<Card>> Deck::getDeck() const { return deck; };

std::ostream &operator<<(std::ostream & out, const Deck & deck) {
	int i = 0;
	for (auto card: deck.getDeck()) {
		out << card->getType();
		if (i != 12) {
			out << " ";
			i++;
		} else {
			out << std::endl;
			i = 0;
		}
	}
	return out;
}
