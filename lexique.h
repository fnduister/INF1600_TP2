#ifndef LEXIQUE_H
#define LEXIQUE_H

#include "state.h"
#include <iostream>
#include <QString>
#include <QTextStream>

class Lexique
{
public:
    Lexique();
    ~Lexique();

    std::vector<QString>  getItems();
    std::vector<State*> getStates();

    void setItem(std::vector<QString> items);
    void setState(std::vector<State*> states);

    void addState(State* state);
    void setCurrentState(State* state);
    State* getCurrentState();
    void loadItems(QTextStream& in);


    std::map<QChar, Branch*> createBranchs(int index, std::vector<int> previous_branch_outputs);

    void buildAutomate();

    int getBiggerItemCount();

private:
    std::vector<QString> items;
    std::vector<State*> states;
    int nb_state = 0;
    State* currentState;
};

#endif // LEXIQUE_H
