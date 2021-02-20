#ifndef WINDOWTEXTEDITOR_H
#define WINDOWTEXTEDITOR_H
#include <QMainWindow>
#include <documenttextedit.h>


class WindowTextEditor : public QMainWindow
{
    Q_OBJECT
public:
    explicit WindowTextEditor(QWidget *parent = nullptr);
    documentTextEdit* pDocument;
protected:
    void closeEvent(QCloseEvent* event);    //переопределяем для вопроса о сохранении перед закрытием
signals:
    void saveDocument();
};

#endif // WINDOWTEXTEDITOR_H
