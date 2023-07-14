#include "card.h"
#include <iostream>
#include <string>
Card::Card(std::string card) {
	type = card;
	if (card[0] == 'J') {
		rank = 11; 
	} else if (card[0] == 'Q') {
		rank = 12;
	} else if (card[0] == 'K') {
		rank = 13; 
	} else if (card[0] == 'A') {
		rank = 1; 
	} else if (card.substr(0,2) == "10") {
		rank = 10;
	} else {
		rank = card[0] - '0';
	}
	if (card.substr(0, 2) == "10") {
		suit = card[2];
	} else {
		suit = card[1];
	}
}

char  Card::getSuit() const { return suit; }

int Card::getRank() const { return rank; }

std::string Card::getType() const { return type; }

bool operator==(const Card & a, const Card & b) {
	return (a.getType() == b.getType() && a.getSuit() == b.getSuit());
}
