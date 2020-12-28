#include "keyfilter.h"


KeyFilter::KeyFilter(QObject *parent) : QObject(parent)
{

}

bool KeyFilter::eventFilter(QObject *obj, QEvent *event)
{
    if (event->type() == QEvent::KeyPress)
    {
        MainWindow* ptrObj = static_cast<MainWindow*>(obj);
        QKeyEvent* ptrEvent = static_cast<QKeyEvent*>(event);
        //если не назначаем клавиши, то стандартная обработка события
        if(!ptrObj->ui->actExitAssign->isChecked() && !ptrObj->ui->actSaveAssign->isChecked() && !ptrObj->ui->actOpenAssign->isChecked() && !ptrObj->ui->actCreateAssign->isChecked())
        {
            return false;
        }
        else if(ptrObj->ui->actCreateAssign->isChecked())    //если назначаем "Создать"
        {
            if(checkKeys(ptrEvent->modifiers(), ptrEvent->key(), ptrObj))
            {
                ptrObj->createButton = ptrEvent->modifiers() + ptrEvent->key();
                ptrObj->ui->actCreateAssign->setChecked(false);    //сброс галочки назначения клавиши
                ptrObj->ui->actCreate->setShortcut(ptrObj->createButton);   //назначение новой комбинации
                return true;
            }
            else
            {
                return true;
            }
        }
        else if(ptrObj->ui->actOpenAssign->isChecked())    //если назначаем "Открыть"
        {
            if(checkKeys(ptrEvent->modifiers(), ptrEvent->key(), ptrObj))
            {
                ptrObj->openButton = ptrEvent->modifiers() + ptrEvent->key();
                ptrObj->ui->actOpenAssign->setChecked(false);    //сброс галочки назначения клавиши
                ptrObj->ui->actOpen->setShortcut(ptrObj->openButton);   //назначение новой комбинации
                return true;
            }
            else
            {
                return true;
            }
        }
        else if(ptrObj->ui->actSaveAssign->isChecked())    //если назначаем "Сохранить"
        {
            if(checkKeys(ptrEvent->modifiers(), ptrEvent->key(), ptrObj))
            {
                ptrObj->saveButton = ptrEvent->modifiers() + ptrEvent->key();
                ptrObj->ui->actSaveAssign->setChecked(false);    //сброс галочки назначения клавиши
                ptrObj->ui->actSave->setShortcut(ptrObj->saveButton);   //назначение новой комбинации
                return true;
            }
            else
            {
                return true;
            }
        }
        else if(ptrObj->ui->actExitAssign->isChecked())    //если назначаем "Выход"
        {
            if(checkKeys(ptrEvent->modifiers(), ptrEvent->key(), ptrObj))
            {
                ptrObj->quitButton = ptrEvent->modifiers() + ptrEvent->key();
                ptrObj->ui->actExitAssign->setChecked(false);    //сброс галочки назначения клавиши
                ptrObj->ui->actExit->setShortcut(ptrObj->quitButton);   //назначение новой комбинации
                return true;
            }
            else
            {
                return true;
            }
        }

    }
    return false;
}

bool KeyFilter::checkKeys(unsigned int typeModifier, int key, MainWindow* ptr)
{
    if(key == Qt::Key_Control || key == Qt::Key_Alt || key == Qt::Key_Shift)    //чтобы CNTRL, ALT, SHIFT использовались только как модификаторы
    {
        return false;
    }
    QKeySequence temp;
    temp = typeModifier + key;
    if (temp == ptr->createButton || temp == ptr->openButton || temp == ptr->saveButton || temp == ptr->quitButton)
    {
        return false;
    }
    return true;
}
