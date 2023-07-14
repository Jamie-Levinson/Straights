#ifndef CARD_H
#define CARD_H
#include <string>
class Card {
	public:
		Card(std::string card);
		char  getSuit() const;
		int getRank() const;
		std::string getType() const;
	private:
		char suit;
		int rank;
		std::string type;
};

bool operator==(const Card & a, const Card & b);

#endif
