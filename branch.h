#ifndef BRANCH_H
#define BRANCH_H

#include <vector>


class State;

class Branch
{
public:
    Branch();
    ~Branch();

    std::vector<int> getOutput();
    State* getNextState();
    void addOutput(int output);

    void setNextState(State* state);

private:
    std::vector<int> output;
    State *nextState;

};

#endif // BRANCH_H
