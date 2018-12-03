#include "Branch.h"

Branch::Branch()
{
}


Branch::~Branch()
{
}

std::vector<int> Branch::getOutput()
{
    return output;
}

State * Branch::getNextState()
{
    return nextState;
}

void Branch::addOutput(int output)
{
    this->output.push_back(output);
}

void Branch::setNextState(State * state)
{
    this->nextState = state;
}
