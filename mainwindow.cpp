#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFile>
#include <QFileDialog>
#include <QTextStream>
#include <QLocale>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_actWhite_triggered()    //выбор белой темы
{
    application = "";
    qApp->setStyleSheet(application);
    ui->actWhite->setChecked(true);
    ui->actDark->setChecked(false);
}

void MainWindow::on_actDark_triggered()     //выбор темной темы
{
    QFile file1(":/new/steels/style.qss");
    if (file1.open(QFile::ReadOnly))
    {
        QTextStream stream(&file1);
        stream.setCodec("UTF-8");    //ДЛЯ ОТОБРАЖЕНИЯ РУССКИХ БУКВ
        application = stream.readAll();
        file1.close();
        qApp->setStyleSheet(application);
        ui->actWhite->setChecked(false);
        ui->actDark->setChecked(true);
    }
}
