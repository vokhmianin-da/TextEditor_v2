#ifndef KEYFILTER_H
#define KEYFILTER_H

#include <QObject>
#include <QEvent>
#include "mainwindow.h"
#include "ui_mainwindow.h"

class MainWindow;

class KeyFilter : public QObject
{
protected:
    virtual bool eventFilter(QObject *obj, QEvent *event);

public:
    explicit KeyFilter(QObject *parent = nullptr);
    bool checkKeys(unsigned int typeModifier, int key, MainWindow* ptr);

    bool shortcutCreate(MainWindow* ptr, QKeyEvent *ptrEvent);
    bool shortcutOpen(MainWindow* ptr, QKeyEvent *ptrEvent);
    bool shortcutSave(MainWindow* ptr, QKeyEvent *ptrEvent);
    bool shortcutExit(MainWindow* ptr, QKeyEvent *ptrEvent);

};

#endif // KEYFILTER_H
