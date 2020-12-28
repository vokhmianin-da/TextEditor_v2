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

};

#endif // KEYFILTER_H
