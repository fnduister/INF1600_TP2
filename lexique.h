#ifndef LEXIQUE_H
#define LEXIQUE_H

#include <vector>
#include <string>
#include "state.h"
#include <QTextStream>

class Lexique
{
public:
    Lexique();
    ~Lexique();
    void loadItems(QTextStream& in);
private:
    std::vector<State*> states;
    State* currentState;
    std::vector<QString> items;
};

#endif // LEXIQUE_H
