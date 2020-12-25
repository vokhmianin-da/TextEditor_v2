#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFile>
#include <QFileDialog>
#include <QTextStream>
#include <QLocale>
#include <QList>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    filter = trUtf8("Текстовый файл(*.txt)");
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

void MainWindow::on_actEn_triggered()   //установить английский язык
{
    translator.load(":/new/translations/QtLanguage_en.qm");
    qApp->installTranslator(&translator);
    ui->retranslateUi(this);
    ui->actEn->setChecked(true);
    ui->actRu->setChecked(false);
}

void MainWindow::on_actRu_triggered()   //установить русский язык
{
    qApp->removeTranslator(&translator);
    ui->retranslateUi(this);
    ui->actEn->setChecked(false);
    ui->actRu->setChecked(true);
}

void MainWindow::setOpenMode(bool mode) //обработка режима "Только для чтения"
{
    ui->actSave->setEnabled(!mode);
    ui->actSaveAs->setEnabled(!mode);

}

void MainWindow::on_actHelp_triggered() //вызов справки
{
    QFile fileHelp(":/new/res/help.txt");
    if (fileHelp.open(QFile::ReadOnly))
    {
        QTextStream stream(&fileHelp);
        static int n = 0;   //чтобы не создавать лишние объекты QTextEdit ("справка")
        if(n)
        {
            delete help;    //удалить прошлое окно справки
        }
        help = new QTextEdit;
        n = 1;

        help->setWindowTitle(tr("Справка"));
        help->setReadOnly(true);
        help->insertPlainText(stream.readAll());
        help->resize(400, 400);
        help->show();
    }
}

void MainWindow::on_actCreate_triggered()   //создание документа
{
    documentTextEdit* pDocument = new documentTextEdit; //создание нового текстового окна
    pDocument->setName(QFileDialog::getSaveFileName(this, tr("Создать документ"), QDir::current().path(), filter));

    QMainWindow* tempWindow = new QMainWindow;
    tempWindow->setCentralWidget(pDocument);
    tempWindow->setWindowTitle(pDocument->getName());   //установка имени вкладки

    QList <QMdiSubWindow*>tempList = ui->documentViewer->subWindowList();   //проверяем, открыт ли уже такой файл
    for(int i = 0; i < tempList.size(); i++)
    {
       if(tempList[i]->widget()->windowTitle() == tempWindow->windowTitle())
       {
           //Эта конструкция очищает окно, если такое уже было открыто (удивительно, но конструкция работает!!!)
           QMainWindow* ptr = static_cast<QMainWindow*>(tempList[i]->widget());
           documentTextEdit* ptr2 = static_cast<documentTextEdit*>(ptr->centralWidget());
           ptr2->clear();
           return;
       }
    }

    if (pDocument->getName().length() > 0)
    {
        QString ext = QString(&(pDocument->getName().data()[pDocument->getName().length() - 4]));
        if (ext == ".txt")
        {
            QFile file(pDocument->getName());
            if (file.open(QFile::WriteOnly))
            {
                QTextStream stream(&file);
                stream.setCodec("UTF-8");    //ДЛЯ ОТОБРАЖЕНИЯ РУССКИХ БУКВ
                ui->documentViewer->addSubWindow(tempWindow);    //добавление нового текстового окна в QMdiArea
                stream << pDocument->toPlainText();
                file.close();
            }
        }
    }
}
