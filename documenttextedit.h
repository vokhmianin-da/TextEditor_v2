#ifndef DOCUMENTTEXTEDIT_H
#define DOCUMENTTEXTEDIT_H
#include <QTextEdit>
#include <QString>
#include <QFont>

class documentTextEdit : public QTextEdit
{
    Q_OBJECT
private:
   QString currentFileName = 0;    //хранит текущее имя файла
   QString oldFileContent = 0;  //содержимое файла при открытии

public:
    documentTextEdit();
    documentTextEdit(const QString);

    void setName(QString str);  //установить имя документа
    QString getName();  //получить имя документа
    void setOldFileContent(QString str);  //здесь будет содержимое файла на момент открытия
    QString getOldFileContent();  //здесь будет содержимое файла на момент открытия
    bool readOnlyMode = false;  //состояние флага "Только для чтения" для данного документа
    QFont currentFont;  //текущий шрифт документа
    QFont tempFont; //для копирования/вставки шрифта
};

#endif // DOCUMENTTEXTEDIT_H
