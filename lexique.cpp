#include "lexique.h"

Lexique::Lexique()
{

}
Lexique::~Lexique(){

};


void Lexique::loadItems(QTextStream& in){
    while(!in.atEnd()){
        items.push_back(in.readLine());
    }
}
