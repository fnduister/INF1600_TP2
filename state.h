#ifndef STATE_H
#define STATE_H
#include <map>

class Branch;

class State
{
public:
    State();
private:
    std::map<char, Branch*> branchs;
    State* previousState;
};

#endif // STATE_H
