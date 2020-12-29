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
        else    //если назначаем
        {
            if(ptrObj->ui->actCreateAssign->isChecked())
            {
                return shortcutCreate(ptrObj, ptrEvent);
            } else if (ptrObj->ui->actOpenAssign->isChecked())
            {
               return  shortcutOpen(ptrObj, ptrEvent);
            } else if (ptrObj->ui->actSaveAssign->isChecked())
            {
               return  shortcutSave(ptrObj, ptrEvent);
            } else if (ptrObj->ui->actExitAssign->isChecked())
            {
                return shortcutExit(ptrObj, ptrEvent);
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

bool KeyFilter::shortcutCreate(MainWindow *ptr, QKeyEvent *ptrEvent)    //назначаем "Создать"
{
    if(checkKeys(ptrEvent->modifiers(), ptrEvent->key(), ptr))
    {
        ptr->createButton = ptrEvent->modifiers() + ptrEvent->key();
        ptr->ui->actCreateAssign->setChecked(false);    //сброс галочки назначения клавиши
        ptr->ui->actCreate->setShortcut(ptr->createButton);   //назначение новой комбинации
        ptr->ptrStatusBar->showMessage("Комбинация клавиш \"Создать\" изменена");
        return true;
    }
    ptr->ptrStatusBar->showMessage("Изменение не удалось");
    return true;
}

bool KeyFilter::shortcutOpen(MainWindow *ptr, QKeyEvent *ptrEvent)  //назначаем "Открыть"
{
    if(checkKeys(ptrEvent->modifiers(), ptrEvent->key(), ptr))
    {
        ptr->openButton = ptrEvent->modifiers() + ptrEvent->key();
        ptr->ui->actOpenAssign->setChecked(false);    //сброс галочки назначения клавиши
        ptr->ui->actOpen->setShortcut(ptr->openButton);   //назначение новой комбинации
        ptr->ptrStatusBar->showMessage("Комбинация клавиш \"Открыть\" изменена");
        return true;
    }
    ptr->ptrStatusBar->showMessage("Изменение не удалось");
    return true;
}

bool KeyFilter::shortcutSave(MainWindow *ptr, QKeyEvent *ptrEvent)  //назначаем "Сохранить"
{
    if(checkKeys(ptrEvent->modifiers(), ptrEvent->key(), ptr))
    {
        ptr->saveButton = ptrEvent->modifiers() + ptrEvent->key();
        ptr->ui->actSaveAssign->setChecked(false);    //сброс галочки назначения клавиши
        ptr->ui->actSave->setShortcut(ptr->saveButton);   //назначение новой комбинации
        ptr->ptrStatusBar->showMessage("Комбинация клавиш \"Сохранить\" изменена");
        return true;
    }
    ptr->ptrStatusBar->showMessage("Изменение не удалось");
    return true;
}

bool KeyFilter::shortcutExit(MainWindow *ptr, QKeyEvent *ptrEvent)  //назначаем "Выход"
{
    if(checkKeys(ptrEvent->modifiers(), ptrEvent->key(), ptr))
    {
        ptr->quitButton = ptrEvent->modifiers() + ptrEvent->key();
        ptr->ui->actExitAssign->setChecked(false);    //сброс галочки назначения клавиши
        ptr->ui->actExit->setShortcut(ptr->quitButton);   //назначение новой комбинации
        ptr->ptrStatusBar->showMessage("Комбинация клавиш \"Выход\" изменена");
        return true;
    }
    ptr->ptrStatusBar->showMessage("Изменение не удалось");
    return true;
}
