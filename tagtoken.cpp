#include "tagtoken.h"

tagToken::tagToken()
{


}

void tagToken::setString(QString string)
{
    stringOfTagToken = string;
}

void tagToken::setBooleans(bool closingBrc, bool openBrc, bool isComment)
{
    //I plan on removing the opening and closing braces
    myTokenBooleans.closingBrace = closingBrc;
    myTokenBooleans.openBrace = openBrc;

    myTokenBooleans.comment = isComment;
    //tokenInfo.whiteSpace
    //bool openBrace = 0;
    //bool closingBrace = 0;
    //bool whiteSpace = 0;

    //it's a comment if there is no nearby [ or ]
    // seems redundant to check for openBrace and closingBrace if I can just store as a comment.
    // need to test if tag is broken, if broken, it's a comment

    //bool comment = isComment;

    //are there newLines in this token?
    //bool newLines = 0;

}
