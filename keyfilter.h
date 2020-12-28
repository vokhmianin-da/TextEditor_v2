#ifndef KEYFILTER_H
#define KEYFILTER_H

#include <QObject>
#include <QEvent>

class KeyFilter : public QObject
{
protected:
    virtual bool eventFilter(QObject *obj, QEvent *event);

public:
    explicit KeyFilter(QObject *parent = nullptr);

};

#endif // KEYFILTER_H
