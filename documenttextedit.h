#ifndef DOCUMENTTEXTEDIT_H
#define DOCUMENTTEXTEDIT_H
#include <QPlainTextEdit>
#include <QString>

class documentTextEdit : public QPlainTextEdit
{
    Q_OBJECT
private:
   QString currentFileName = 0;    //хранит текущее имя файла
public:
    documentTextEdit();
    documentTextEdit(const QString);

    void setName(QString str);  //установить имя документа
    QString getName();  //получить имя документа
    bool readOnlyMode = false;  //состояние флага "Только для чтения" для данного документа
};

#endif // DOCUMENTTEXTEDIT_H
