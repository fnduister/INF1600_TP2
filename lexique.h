#ifndef LEXIQUE_H
#define LEXIQUE_H

#include "state.h"
#include <iostream>
#include <QString>
#include <QTextStream>
#include <set>
#include "word.h"

struct SortByOccurences
{
    bool operator ()(const Word *a, const Word *b)
    {
        return a->getOccurrence() < b->getOccurrence();
    }
};

class Lexique
{
public:
    Lexique();
    ~Lexique();

    std::vector<Word*>  getItems() const;
    std::vector<State*> getStates();

    void setItem(std::vector<Word*> items);
    void setState(std::vector<State*> states);
    void initialiserLexique();
    void addState(State* state);
    void setCurrentState(State* state);
    void sortItems();
    State* getCurrentState();
    void loadItems(QTextStream& in);
    std::map<QChar, Branch*> createBranchs(int index, std::vector<int> previous_branch_outputs);
    void buildAutomate();
    int getBiggerItemCount();
    int getNumberShowedOccurrences()const;
    std::vector<Word*> getSortedItems() const;


private:
    bool sortbysec(const std::pair<QString,int> &a,
                       const std::pair<QString,int> &b);
    std::vector<Word*> items;
    std::vector<Word*> SortedItems;
    std::vector<State*> states;
    int nb_state = 0;
    State* currentState;
    int numberShowedOccurrences = 5;
};

#endif // LEXIQUE_H
