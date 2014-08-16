#include "diffmatchpatch.h"
#include "ui_diffmatchpatch.h"

#include <QApplication>
#include <QPushButton>
#include <QVBoxLayout>

#include <QFileDialog>
#include <QFile>
#include <QMessageBox>
#include <QTextStream>

#include <tagtoken.h>
#include <logwindow.h>


DiffMatchPatch::DiffMatchPatch(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::DiffMatchPatch)
{
    ui->setupUi(this);
}

//important!  Global variables for Forms!***
PatchOutputWindow *patchOutput;
LogWindow *logWindow;

DiffMatchPatch::~DiffMatchPatch()
{
    delete ui;
}

QString returnQstring(QString *parent = 0)
{
    return *parent;
}

void DiffMatchPatch::on_actionOpen_Left_triggered()
{
    QString fileName = QFileDialog::getOpenFileName(this, tr("Open File"), QString(),
                                                    tr("Text Files (*.txt);;C++ Files (*.cpp *.h)"));

    if (!fileName.isEmpty()) {
        QFile file(fileName);
        if (!file.open(QIODevice::ReadOnly)) {
            QMessageBox::critical(this, tr("Error"), tr("Could not open file"));
            return;
        }
        QTextStream in(&file);
        //ui->plainTextEditLeft->setText(in.readAll());

        //set font to ASCII
        //http://qt-project.org/forums/viewthread/7943
        //ui->plainTextEditLeft->setStyleSheet("font: 9pt \"Courier\";");

        //no wrap
        //http://qt-project.org/doc/qt-4.8/qtextedit.html#LineWrapMode-enum
        //http://qt-project.org/doc/qt-4.8/qtextedit.html#lineWrapMode-prop
        //how to use
        //http://www.qtcentre.org/threads/8188-bug-setLineWrapMode
        //setLineWrapMode(QTextEdit::NoWrap)

        //plainTextEditLeft.setLineWrapMode(plainTextEdit::NoWrap);
        ui->plainTextEditLeft->setLineWrapMode(QPlainTextEdit::NoWrap);

        ui->plainTextEditLeft->setPlainText(in.readAll());
        //ui->textEditLeft->setText(in.readAll());
        file.close();
    }
}

void DiffMatchPatch::on_actionOpen_Right_triggered()
{
    QString fileName = QFileDialog::getOpenFileName(this, tr("Open File"), QString(),
                                                    tr("Text Files (*.txt);;C++ Files (*.cpp *.h)"));

    if (!fileName.isEmpty()) {
        QFile file(fileName);
        if (!file.open(QIODevice::ReadOnly)) {
            QMessageBox::critical(this, tr("Error"), tr("Could not open file"));
            return;
        }
        QTextStream in(&file);

        ui->plainTextEditRight->setStyleSheet("font: 9pt \"Courier\";");

        ui->plainTextEditRight->setLineWrapMode(QPlainTextEdit::NoWrap);

        ui->plainTextEditRight->setPlainText(in.readAll());

        file.close();
    }
}

void DiffMatchPatch::on_actionSave_Left_triggered()
{
    QString fileName = QFileDialog::getSaveFileName(this, tr("Save File"), QString(),
                                                    tr("Text Files (*.txt);;C++ Files (*.cpp *.h)"));

    if (!fileName.isEmpty()) {
        QFile file(fileName);
        if (!file.open(QIODevice::WriteOnly)) {
            // error message
        } else {
            QTextStream stream(&file);
            stream << ui->plainTextEditLeft->toPlainText();
            stream.flush();
            file.close();
        }
    }
}

void DiffMatchPatch::on_actionSave_Right_triggered()
{
    QString fileName = QFileDialog::getSaveFileName(this, tr("Save File"), QString(),
                                                    tr("Text Files (*.txt);;C++ Files (*.cpp *.h)"));

    if (!fileName.isEmpty()) {
        QFile file(fileName);
        if (!file.open(QIODevice::WriteOnly)) {
            // error message
        } else {
            QTextStream stream(&file);
            stream << ui->plainTextEditRight->toPlainText();
            stream.flush();
            file.close();
        }
    }
}

void DiffMatchPatch::on_actionPatch_Compute_triggered()
{
    diff_match_patch dmp;

    QString str1 = ui->plainTextEditLeft->toPlainText();
    QString str2 = ui->plainTextEditRight->toPlainText();

    patchOutput = new PatchOutputWindow(this);

    //parent window can be in front of child window
    //childForm = new PatchOutputWindow();

    QString strPatch = dmp.patch_toText(dmp.patch_make(str1, str2));
    QTextStream out(&strPatch);

    patchOutput->setOutputWindowText(strPatch);

    patchOutput->show();

    //emit patchOutputWindowData(&strPatch);

    //manually create a new window
    /*
    QWidget* win = new QWidget();
    QVBoxLayout* layout = new QVBoxLayout(win);
    QPlainTextEdit* plainTextEditPatchOutput = new QPlainTextEdit();

    layout->addWidget(plainTextEditPatchOutput);

    //Load up patch file into a string
    QString strPatch = dmp.patch_toText(dmp.patch_make(str1, str2));
    QTextStream out(&strPatch);

    plainTextEditPatchOutput->setStyleSheet("font: 9pt \"Courier\";");
    plainTextEditPatchOutput->setLineWrapMode(QPlainTextEdit::NoWrap);

    //load patch file into plainTextEdit.
    plainTextEditPatchOutput->setPlainText(out.readAll());;

    //show window with patch file loaded
    win->show();
    */
}

void DiffMatchPatch::log_window()
{

}

void DiffMatchPatch::on_actionPatch_Apply_triggered()
{

    //VARS
    diff_match_patch dmp;

    QString fileName = QFileDialog::getOpenFileName(this, tr("Open File"), QString(),
                                                    tr("Text Files (*.txt);;C++ Files (*.cpp *.h)"));

    if (!fileName.isEmpty()) {
        QFile file(fileName);
        if (!file.open(QIODevice::ReadOnly)) {
            QMessageBox::critical(this, tr("Error"), tr("Could not open file"));
            return;
        }

        //load left plainTextEdit as str1
        QString str1 = ui->plainTextEditLeft->toPlainText();

        //load file into patch object
        QTextStream in(&file);
        QString strPatch = file.readAll();

        //QString strPatch = dmp.patch_toText(dmp.patch_make(str1, str2));

        //Creating Temp patch var manually
        QList<Patch> heldPatch = dmp.patch_fromText(strPatch);

        //original suggested use of code that wouldn't work.
        //QPair<QString, QVector<bool> > out = dmp.patch_apply(dmp.patch_fromText(strPatch), str1);

        //I think it breaks assigning this part?
        //for each?
        //output patch to test if it was imported correctly
        //outputted patch file is empty.

        //QPair<QString, QVector<bool> > out = dmp.patch_apply(dmp.patch_fromText(strPatch), str1);
        //QPair<QString, QVector<bool> > out = dmp.patch_apply(heldPatch, str1);

        //childForm = new PatchOutputWindow(this);
        //childForm->show();


        //why not create a new patch object in memory based

        //?
        //QString outPut;
        //QTextStream out(&outPut);

        //QString strResult = out.first;

        //childForm->setOutputWindowText(outPut);
        patchOutput = new PatchOutputWindow(this);

        //breaks if I enable this
        //childForm->setOutputWindowText(outPut);

        patchOutput->show();

        //causes my exec to delete itself...?
        //ui->plainTextEditRight->setStyleSheet("font: 9pt \"Courier\";");

        //ui->plainTextEditRight->setLineWrapMode(QPlainTextEdit::NoWrap);

        //ui->plainTextEditRight->setPlainText(strResult);

        file.close();

        /*
    diff_match_patch dmp;
    QString str1 = QString("First string in diff");
    QString str2 = QString("Second string in diff");

    QString strPatch = dmp.patch_toText(dmp.patch_make(str1, str2));
    QPair<QString, QVector<bool> > out
            = dmp.patch_apply(dmp.patch_fromText(strPatch), str1);
    QString strResult = out.first;
    */
    }

}

void DiffMatchPatch::on_actionObjects_Read_triggered()
{
    //open log window instance

    logWindow = new LogWindow(this);

    logWindow->show();

    QVector<tagToken> tags(0);

    QString holderString = ui->plainTextEditLeft->toPlainText();

    //figured since QTextStream was made for reading in text... and it worked!
    QTextStream in(&holderString);

    //recommend counting lines first and separately.

    //Then trying to count 1st row's # of char's.
    //Then first two rows



    //used merely for one loop
    int lineCounter = 0;

    int tagTokenCounter = 0;

    //thanks stack
    //http://stackoverflow.com/questions/15115571/reading-a-txt-file-using-qtextstream-c
    QString line = "";

    //update lineCounter
    do
    {
        line = in.readLine();
        lineCounter++;
    } while (!in.atEnd());

    in.resetStatus();

    int linePosition = 1;
    //start to parse file

    QString stringOfToken = "";

    //I thought about putting this inside a loop and then transformgin to a string
    QVector<QChar> tempCharactersForTokenName;

    bool insideBracket = 0;
    bool leftBracket = 0;

    do
    {
        line = in.readLine();

        int lineLength = line.length();

        int column = 0;

        do
        {
            //check if '['
            QChar character = line[column];

            if (character == '[')
            {
                //if left Bracket is already tracked
                if (leftBracket == 1)
                {//reset tempCharactersForTokenName if we encounter another '['
                    tempCharactersForTokenName.clear();
                }
                leftBracket = 1;
                insideBracket = 1;
            }

            if (character == ']')
            {
                insideBracket = 0;
                leftBracket = 0;

                int sizeOfPhrase = tempCharactersForTokenName.size();

                int tempCount = 0;

                do
                {
                    stringOfToken.append(character);

                }while (tempCount <= sizeOfPhrase);

                //commit word to string

                QVector<tagToken> temp(0);

                //errors fixed: http://stackoverflow.com/questions/25332771/c-qvector-vector-issues-const-discards-qualifiers
                temp[0].setString(stringOfToken);
                temp[0].setBooleans(1, 1, 0);

                //broken
                //temp.at(0).setString("test");

                //tags.at(0).setString(line);

                tags.push_back(temp[0]);

                tagTokenCounter++;


                //reset string
                stringOfToken = "";
            }

            if (insideBracket)
            {
                if ((character != ']') && (column == lineLength))
                {
                    //if reach end of line, and haven't found closing bracket.
                    tempCharactersForTokenName.append(character);
                }


            }
            column++;

        } while (column <= lineLength);

        column = 0;



        //I need to parse everything as a token or a comment.
        //1st and foremost.

        //then do followup conditions on the array to backfill other information based on readings just the tokens.

        //Listing the starting x,y.
        //Once I have the vector of comments/tags, I can do other things like backupdate a 3rd variable that specifies dependencies?

        //if first line, store as special comment as filename
        //assumes file is setup correct,
        //should also check if there is a [ or ] in the 1st line and set a flag for the user to correct.

        /*
        if (linePosition == 1)
        {
            QVector<tagToken> temp(0);

            //errors fixed: http://stackoverflow.com/questions/25332771/c-qvector-vector-issues-const-discards-qualifiers
            temp[0].setString(line);
            temp[0].setBooleans(0, 0, 1);

            //broken
            //temp.at(0).setString("test");

            //tags.at(0).setString(line);

            tags.push_back(temp[0]);

            tagTokenCounter++;
        }
        */



        //test if line has a [

        // need to test if tag is broken
        // do so by counting until end of line.length() if a nearby ] is found before [ or ' ';
        // if so, then test is token, else comment

        //test if char is a '['

        //how about starting recording first line at 1st char.
        //If a [ is found, then do the test to see if an unbroken ] exists, then store as token.

        /*
        if (line.contains('['))
        {
            //contains a token
            tagTokenCounter++;

        }
        else //store as string
        {
            //tags.

        }

        //somewhere I need to update a tagToken using [tagTokenCouter];
        */

        linePosition++;

    } while (linePosition <= lineCounter);


    /*  self derived example on how to parse
    //count lines
    int charCount = 1;

    int lineCount = 0;

    int numOfChars = 0;

    int bracketCount = 0;

    numOfChars = line.length();

    do
    {
        line = in.readLine();
        charCount = line.length();

        //Read Character's if length !=0
        int charPosition = 0;
        numOfChars = numOfChars + line.length();
        //while (line.length())
        //not going through the length of string properly...

        //length I don't think is working, but my debugger isn't working.
        while (charPosition <= line.length())
        {
            charCount = charCount + line.length();
            QChar character = line[charPosition];

            char character2 = character.toLatin1();

            if (character2 == '[')
            {
                bracketCount++;
            };
            charPosition++;
        }

        lineCount++;
    } while (!in.atEnd());

    in.resetStatus();
    */



    //logWindow->readInt(lineCount);

    //logWindow->readInt(numOfChars);

    //logWindow->readInt(bracketCount);

    logWindow->readInt(tagTokenCounter);
    //separate concept, now to read objects
    /*
    int numOfLines = ui->plainTextEditLeft->blockCount();

    //read until end of line, if end of line is not token, did I just read a [?  If I did, mark as broken token.  If run into another [, then finish reading token

    //min numOfLines is 1
    int counterOfLines = 1;

    while (counterOfLines<=numOfLines)
    {//
        //get a Qstring of the line

        //QString line = ui->plainTextEditLeft->AnchorAt(counterOfLines);
        QString line = "test";

        //test if line is blank
        if(line=="")
        {

        }

        counterOfLines++;
    }
    */

}
