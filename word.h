#ifndef WORD_H
#define WORD_H

#include <QString>

class Word
{
public:
    Word(QString value, int id);
    bool toggleUsed();
    QString getWord() const;
    void setWord(QString value);
    bool getUsed() const;

    int getOccurrence() const;
    void increaseOccurrence();
private:
    int id;
    QString word;
    int occurrence;
    bool usedRecently;
};

#endif // WORD_H
