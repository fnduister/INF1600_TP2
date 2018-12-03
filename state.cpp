#include "State.h"

State::State(int id)
{
    if(id == 0){
        previousState = nullptr;
    }
}


State::~State()
{
}

int State::getId()
{
    return id;
}

std::map<QChar, Branch*> State::getBranchs() {
    return branchs;
}

State* State::getPreviousState() {
    return previousState;
}

QChar State::getValue()
{
    return value;
}

void State::setBranchs(std::map<QChar, Branch*> branchs)
{
    this->branchs = branchs;
}

void State::setPrevious(State * state)
{
    this->previousState = state;
}

void State::setValue(QChar value)
{
    this->value = value;
}
