#include "keyfilter.h"
#include "mainwindow.h"
#include "ui_mainwindow.h"

KeyFilter::KeyFilter(QObject *parent) : QObject(parent)
{

}

bool KeyFilter::eventFilter(QObject *obj, QEvent *event)
{
    if (event->type() == QEvent::KeyPress)
    {
        //если не назначаем клавиши, то стандартная обработка события
        if(!static_cast<MainWindow*>(obj)->ui->actExitAssign->isChecked() && !static_cast<MainWindow*>(obj)->ui->actSaveAssign->isChecked() && !static_cast<MainWindow*>(obj)->ui->actOpenAssign->isChecked() && !static_cast<MainWindow*>(obj)->ui->actCreateAssign->isChecked())
        {
            return false;
        }
        else if(static_cast<MainWindow*>(obj)->ui->actCreateAssign->isChecked())    //если назначаем "Создать"
        {

        }

    }
    return false;
}
