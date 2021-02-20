#include "windowtexteditor.h"
#include <QCloseEvent>
#include <QMessageBox>

WindowTextEditor::WindowTextEditor(QWidget *parent) : QMainWindow(parent)
{

}

void WindowTextEditor::closeEvent(QCloseEvent *event)
{
    QString a = this->pDocument->toHtml();
    if(this->pDocument->getOldFileContent() != a)   //если были изменения файла
    {
        QMessageBox mBox(QMessageBox::Information, "", tr("Сохранить изменения?"), QMessageBox::Yes | QMessageBox::No | QMessageBox::Cancel);
        int n = mBox.exec();
        if(n == QMessageBox::Yes)   //сохранить изменения
        {
            emit saveDocument();
            event->accept();
        }
        else if (n == QMessageBox::No)  //не сохранять изменения
        {
            event->accept();
        }
        else    //отмена выхода
        {
            event->ignore();
        }

    }
    else
    {
        event->accept();    //если не было изменений, то просто выход
    }
}
