#include "word.h"

Word::Word(QString word, int id):word(word), id(id)
{
    occurrence = 0;
    usedRecently = false;
}

bool Word::toggleUsed(){
    usedRecently = !usedRecently;
    return usedRecently;
}

bool Word::getUsed() const{
    return usedRecently;
}


QString Word::getWord() const{
    return word;
}
void Word::setWord(QString word){
    this->word = word;
}

int Word::getOccurrence() const{
    return  occurrence;
}
void Word::increaseOccurrence(){
    occurrence++;
}
