#ifndef BRANCH_H
#define BRANCH_H

#include <vector>

class State;
class Branch
{
public:
    Branch();
    State* getNextState() const;
    std::vector<int> getOutputs() const;
private:
    int id;
    std::vector<int> outputs;
    State* nextState;
};

#endif // BRANCH_H
