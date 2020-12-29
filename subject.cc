#include <set>
#include "subject.h"
#include "observer.h"

void Subject::subscribe(Observer *obs)
{
    observers_.insert(obs);
}

void Subject::unsubscribe(Observer *formerObs)
{
    observers_.erase(formerObs);
}

void Subject::notify()
{
    for (auto i : observers_)
        i->update();
}
