#ifndef TESTGUI_H
#define TESTGUI_H

#include <QObject>

#include <QObject>
#include <QtTest>

class TestGui : public QObject
{
    Q_OBJECT
public:
    explicit TestGui(QObject *parent = nullptr);

signals:

private slots:
    void testGui();

};

#endif // TESTGUI_H
