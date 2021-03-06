#ifndef TAGTOKEN_H
#define TAGTOKEN_H

#include <QtCore>

class tagToken
{
public:
    tagToken();

    //this works, but the recieving has to have the same struct, might as well make it a class.
    //tokenInfo getBooleans();

    void setString(QString string);

    void setBooleans(bool closingBrc, bool openBrc, bool isComment);

    void setRow(int row) {rowNumber = row;}

    void setColumn(int col) {colNumber = col;};

private:
    QString stringOfTagToken;

    //line # of file token was on
    int rowNumber = 0;

    //colNumber token started at
    int colNumber = 0;

    //Either an identifier such as Object:
    //or What is specified after Object: such as creature
    QString objectInstance ="";

    //is tagToken "Object:" ?
    bool objectIdentifier = 0;

    struct tokenBooleanInfo
    {
        bool openBrace = 0;
        bool closingBrace = 0;

        //never going to use this one, because... if their's whitespace, it's stored as a comment
        bool whiteSpace = 0;

        //it's a comment if there is no nearby [ or ]
        bool comment = 0;

        //are there newLines in this token?
        //I'm never going to use this because i'm going to store the newline as a new token
        bool newLines = 0;
    };

    tokenBooleanInfo myTokenBooleans;

    //struct's are like classes, but all member's are public :)

};

#endif // TAGTOKEN_H
