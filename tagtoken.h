#ifndef TAGTOKEN_H
#define TAGTOKEN_H

#include <QtCore>

class tagToken
{
public:
    tagToken();

private:
    QString nameOftagToken;

    //line # of file token was on
    int rowNumber = 0;

    //colNumber token started at
    int colNumber = 0;

    //Either an identifier such as Object:
    //or What is specified after Object: such as creature
    QString objectInstance ="";

    //is tagToken "Object:" ?
    bool objectIdentifier = 0;

    struct tokenInfo
    {
        bool openBrace = 0;
        bool closingBrace = 0;
        bool whiteSpace = 0;

        //it's a comment if there is no nearby [ or ]
        bool comment = 0;

        //are there newLines in this token?
        bool newLines = 0;
    };
};

#endif // TAGTOKEN_H