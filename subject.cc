#include "subject.h"
#include "observer.h"
#include <vector>

void Subject::attach ( Observer *newView ) {
    observers.emplace_back(newView);
}


void Subject::detach( Observer *formerView ) {
	for (auto it = observers.begin(); it != observers.end(); ) {
		if (*it == formerView) it = observers.erase(it);
		else ++it;
	}
}


void Subject::notifyObservers() {
    for (auto &ob : observers) ob->update();
}
