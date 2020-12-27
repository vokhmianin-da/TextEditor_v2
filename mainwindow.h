#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtWidgets>
#include <QTranslator>
#include <QEvent>
#include "documenttextedit.h"
//#include <QMap>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

private:
    Ui::MainWindow *ui;
    QString filter;  //фильтр форматов файлов
    QTextEdit* help; //для создания окна справки
    QTranslator translator; //для переключения переводов
    //QMap <QString,documentTextEdit> fileDocuments;   //map для хранения текущих документов

    QString application = 0;    //хранит текущее имя файла

    /*Для хранения текущих горячих клавиш*/
    int saveKey = Qt::Key_S;
    int openKey = Qt::Key_O;
    int quitKey = Qt::Key_Q;
    int newFileKey = Qt::Key_N;
    unsigned int typeModifierSave = Qt::ControlModifier; //наличие и тип модификатора (CNTRL, SHIFT, ALT)
    unsigned int typeModifierOpen = Qt::ControlModifier; //наличие и тип модификатора (CNTRL, SHIFT, ALT)
    unsigned int typeModifierQuit = Qt::ControlModifier; //наличие и тип модификатора (CNTRL, SHIFT, ALT)
    unsigned int typeModifierNewFile = Qt::ControlModifier; //наличие и тип модификатора (CNTRL, SHIFT, ALT)

    bool checkKeys(unsigned int typeModifier, int key); //определяет, используется ли уже данная клавиша (сочетание клавиш)

    /*Для проверки нажатия горячих клавиш*/
    static void openIsPressed(MainWindow*, QKeyEvent *);
    static void saveIsPressed(MainWindow*, QKeyEvent *);
    static void newKeyIsPressed(MainWindow*, QKeyEvent *);
    static void quitIsPressed(MainWindow*, QKeyEvent *);
    using funcMap = std::map <int, void (*)(MainWindow *, QKeyEvent *)>;
    funcMap keyPressedFunc;

    /*Для обновления комбинации горячих клавиш*/
    void updateCombination(int &key, unsigned int &typeModifier, void (*functPressed)(MainWindow *, QKeyEvent *), QKeyEvent * event);

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

signals:
    void setReadOnlyMode(bool); //сигнал с значением флага "Только для чтения"

private slots:
    void on_actWhite_triggered();

    void on_actDark_triggered();
    void on_actEn_triggered();
    void on_actRu_triggered();
    void on_actHelp_triggered();
    void on_actCreate_triggered();
    void on_actOpen_triggered();
    void on_documentViewer_subWindowActivated(QMdiSubWindow *arg1);
    void on_actSaveAs_triggered();
    void on_actSave_triggered();
};

#endif // MAINWINDOW_H
