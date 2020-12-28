#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtWidgets>
#include <QTranslator>
#include <QEvent>
#include "documenttextedit.h"
#include "keyfilter.h"
//#include <QMap>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

    friend class KeyFilter;
private:
    Ui::MainWindow *ui;
    QString filter;  //фильтр форматов файлов
    QTextEdit* help; //для создания окна справки
    QTranslator translator; //для переключения переводов

    QString application = 0;    //хранит текущее имя файла

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

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
    void on_actExit_triggered();
    void on_actPrint_triggered();
};

#endif // MAINWINDOW_H
