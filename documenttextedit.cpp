#include "documenttextedit.h"

documentTextEdit::documentTextEdit()
{

}

documentTextEdit::documentTextEdit(const QString str): currentFileName(str)
{

}

void documentTextEdit::setName(QString str)
{
    currentFileName = str;
}

QString documentTextEdit::getName()
{
    return currentFileName;
}
