#ifndef SUBJECT_H
#define SUBJECT_H
#include <vector>

class Observer;

class Subject {
  public:
    void attach( Observer* o);
    void detach( Observer* o);
    void notifyObservers();

  private:
    std::vector<Observer*> observers;
   
};


#endif
