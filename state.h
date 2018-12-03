#ifndef STATE_H
#define STATE_H
#include "branch.h"
#include <map>
#include <QChar>

class State
{
public:
    State(int id);
    ~State();

    int getId();
    std::map<QChar, Branch*> getBranchs();
    State* getPreviousState();
    QChar getValue();

    void setBranchs(std::map<QChar, Branch*> branchs);
    void setPrevious(State* state);
    void setValue(QChar value);


private :
    int id;
    QChar value;
    std::map<QChar, Branch*> branchs;
    State* previousState;
};

#endif // STATE_H
