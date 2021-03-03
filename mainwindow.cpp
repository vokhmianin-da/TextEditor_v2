#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFile>
#include <QFileDialog>
#include <QTextStream>
#include <QLocale>
#include <QList>
#include <QPrinter>
#include <QPrintDialog>
#include <QFont>
#include <QFontDialog>
#include <QDate>
#include <QTime>
#include <windowtexteditor.h>



MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    //QKeySequence x = ui->actOpen->shortcut();
    filter = trUtf8("Текстовый файл(*.txt)");
    installEventFilter(new KeyFilter);
    ptrStatusBar = statusBar();
    dataLbl = new QLabel;
    timeLbl = new QLabel;

    dataLbl->setText("Время: " + QTime::currentTime().toString("h:mm"));
    timeLbl->setText("Дата: " +QDate::currentDate().toString("dd.MM.yyyy"));

    this->setMinimumSize(640, 480); //минимальный размер окна

    ptrStatusBar->addWidget(dataLbl);
    ptrStatusBar->addWidget(timeLbl);
    this->startTimer(1000); //обновление текущих даты и времени каждые 1 сек
}


void MainWindow::timerEvent(QTimerEvent *)
{
    dataLbl->setText("Время: " + QTime::currentTime().toString("h:mm"));
    timeLbl->setText("Дата: " +QDate::currentDate().toString("dd.MM.yyyy"));
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
    WindowTextEditor* tempWindow = new WindowTextEditor;
    connect (tempWindow, SIGNAL(saveDocument()), this, SLOT(on_actSave_triggered()));   //соединяем сигнал сохранения нового окна с слотом сохранения главного окна

    tempWindow->pDocument = new documentTextEdit; //создание нового текстового окна
    tempWindow->pDocument->setName(QFileDialog::getSaveFileName(this, tr("Создать документ"), QDir::current().path(), filter));
    tempWindow->setCentralWidget(tempWindow->pDocument);
    tempWindow->setWindowTitle(tempWindow->pDocument->getName());   //установка имени вкладки

    if (tempWindow->pDocument->getName().length() > 0)
    {
        QString ext = QString(&(tempWindow->pDocument->getName().data()[tempWindow->pDocument->getName().length() - 4]));
        if (ext == ".txt")
        {
            QList <QMdiSubWindow*>tempList = ui->documentViewer->subWindowList();   //проверяем, открыт ли уже такой файл
            for(int i = 0; i < tempList.size(); i++)
            {
               if(tempList[i]->widget()->windowTitle() == tempWindow->windowTitle())
               {
                   //Эта конструкция очищает окно, если такое уже было открыто (удивительно, но конструкция работает!!!)
                   documentTextEdit* ptr = static_cast<documentTextEdit*>(static_cast<QMainWindow*>(tempList[i]->widget())->centralWidget());
                   //documentTextEdit* ptr2 = static_cast<documentTextEdit*>(ptr->centralWidget());
                   ptr->clear();
                   return;
               }
            }

            QFile file(tempWindow->pDocument->getName());
            if (file.open(QFile::WriteOnly))
            {
                QTextStream stream(&file);
                stream.setCodec("UTF-8");    //ДЛЯ ОТОБРАЖЕНИЯ РУССКИХ БУКВ
                ui->documentViewer->addSubWindow(tempWindow);    //добавление нового текстового окна в QMdiArea
                stream << tempWindow->pDocument->toPlainText();
                tempWindow->pDocument->setOldFileContent(tempWindow->pDocument->toHtml()); //запись содержимого для последующего сравнения при закрытии документа
                tempWindow->pDocument->setHtml(tempWindow->pDocument->getOldFileContent());
                file.close();
            }
        }
    }
}

void MainWindow::on_actOpen_triggered() //открыть документ
{    
    WindowTextEditor* tempWindow = new WindowTextEditor;
    connect (tempWindow, SIGNAL(saveDocument()), this, SLOT(on_actSave_triggered()));   //соединяем сигнал сохранения нового окна с слотом сохранения главного окна

    tempWindow->pDocument = new documentTextEdit; //создание нового текстового окна
    if(ui->actReadOnly->isChecked())
    {
        tempWindow->pDocument->readOnlyMode = true; //только для чтения
    }
    else
    {
        tempWindow->pDocument->readOnlyMode = false;
    }
    tempWindow->pDocument->setName(QFileDialog::getOpenFileName(this, tr("Открыть документ"), QDir::current().path(), filter));
    tempWindow->setCentralWidget(tempWindow->pDocument);
    tempWindow->setWindowTitle(tempWindow->pDocument->getName());   //установка имени вкладки

    if (tempWindow->pDocument->getName().length() > 0)
    {
        int index = tempWindow->pDocument->getName().indexOf(".txt");              // определяем, есть ли в
        // названии строка ".txt"
        if (index != -1 && tempWindow->pDocument->getName().length() - 4 == index) // если это текстовый файл,
            // выполняются 2 условия:
            // строка ".txt" есть
            // в названии, и она
            // находится в конце
            // строки названия файла
        {
            QList <QMdiSubWindow*>tempList = ui->documentViewer->subWindowList();   //проверяем, открыт ли уже такой файл
            for(int i = 0; i < tempList.size(); i++)
            {
               if(tempList[i]->widget()->windowTitle() == tempWindow->windowTitle())
               {
                   return;
               }
            }

            QFile file(tempWindow->pDocument->getName());
            if (file.open(QFile::ReadOnly))
            {
                QTextStream stream(&file);
                stream.setCodec("UTF-8");    //ДЛЯ ОТОБРАЖЕНИЯ РУССКИХ БУКВ
                //ui->plainTextEdit->setPlainText(stream.readAll());
                ui->documentViewer->addSubWindow(tempWindow);    //добавление нового текстового окна в QMdiArea
                tempWindow->pDocument->setOldFileContent(stream.readAll()); //запись содержимого для последующего сравнения при закрытии документа
                tempWindow->pDocument->setHtml(tempWindow->pDocument->getOldFileContent());
                file.close();

            }
        }
    }
}

void MainWindow::on_documentViewer_subWindowActivated(QMdiSubWindow *arg1)  //обработка подокна при активации
{
    if(!arg1) return;   //если нет подокон, то сразу выходим

    //Обработка флага "Только для чтения"
    if(static_cast<documentTextEdit*>(static_cast<QMainWindow*>(arg1->widget())->centralWidget())->readOnlyMode)
    {
        static_cast<documentTextEdit*>(static_cast<QMainWindow*>(arg1->widget())->centralWidget())->setReadOnly(true);
        ui->actSave->setEnabled(false);
        ui->actSaveAs->setEnabled(false);
    }
    else
    {
        static_cast<documentTextEdit*>(static_cast<QMainWindow*>(arg1->widget())->centralWidget())->setReadOnly(false);
        ui->actSave->setEnabled(true);
        ui->actSaveAs->setEnabled(true);
    }
}

void MainWindow::on_actSaveAs_triggered()   //сохранить как
{
    if(!ui->documentViewer->currentSubWindow())
    {
        return;
    }
    documentTextEdit* documentPtr = static_cast<documentTextEdit*>(static_cast<QMainWindow*>(ui->documentViewer->currentSubWindow()->widget())->centralWidget());
    QString currentFileName;
    currentFileName = QFileDialog::getSaveFileName(this, tr("Сохранить как"), documentPtr->getName(), filter);
    if (currentFileName.length() > 0)
    {
        QString ext = QString(&(currentFileName.data()[currentFileName.length() - 4]));
        if (ext == ".txt")
        {
            QFile file(currentFileName);
            if (file.open(QFile::WriteOnly))
            {
                QTextStream stream(&file);
                stream.setCodec("UTF-8");    //ДЛЯ ОТОБРАЖЕНИЯ РУССКИХ БУКВ
                ext = documentPtr->toHtml();
                stream << ext;
                file.close();
                documentPtr->setName(currentFileName);  //установка нового имени файла в виджете
                static_cast<QMainWindow*>(ui->documentViewer->currentSubWindow()->widget())->setWindowTitle(currentFileName);  //установка нового имени в заголовке окна
            }
        }
    }
}

void MainWindow::on_actSave_triggered() //сохранить
{
    if(!ui->documentViewer->currentSubWindow())
    {
        return;
    }
    documentTextEdit* documentPtr = static_cast<documentTextEdit*>(static_cast<QMainWindow*>(ui->documentViewer->currentSubWindow()->widget())->centralWidget());
    QString currentFileName = documentPtr->getName();
    if (currentFileName.length() > 0)
    {
        QString ext = QString(&(currentFileName.data()[currentFileName.length() - 4]));
        if (ext == ".txt")
        {
            QFile file(currentFileName);
            if (file.open(QFile::WriteOnly))
            {
                QTextStream stream(&file);
                stream.setCodec("UTF-8");    //ДЛЯ ОТОБРАЖЕНИЯ РУССКИХ БУКВ
                ext = documentPtr->toHtml();
                stream << ext;
                file.close();
            }
        }
    }
}

void MainWindow::on_actExit_triggered() //выход
{
    qApp->exit();
}


void MainWindow::on_actPrint_triggered()    //печать
{
    QPrinter printer;
    QPrintDialog dlg(&printer, this);

    dlg.setWindowTitle("Печать");
    if(!ui->documentViewer->currentSubWindow())
    {
        QMessageBox::information(0, tr("Печать"), tr("Нет открытых документов"));
        return;
    }
    if(dlg.exec() == QDialog::Accepted)
    {
        static_cast<documentTextEdit*>(static_cast<QMainWindow*>(ui->documentViewer->currentSubWindow()->widget())->centralWidget())->print(&printer);
    }
}

void MainWindow::on_actCreateAssign_triggered(bool checked)
{
    if(checked)
    {
        ui->actExitAssign->setChecked(!checked);    //сброс галочки назначения клавиши
        ui->actSaveAssign->setChecked(!checked);    //сброс галочки назначения клавиши
        ui->actOpenAssign->setChecked(!checked);    //сброс галочки назначения клавиши
    }
}

void MainWindow::on_actOpenAssign_triggered(bool checked)
{
    if(checked)
    {
        ui->actExitAssign->setChecked(!checked);    //сброс галочки назначения клавиши
        ui->actSaveAssign->setChecked(!checked);    //сброс галочки назначения клавиши
        ui->actCreateAssign->setChecked(!checked);    //сброс галочки назначения клавиши
    }
}

void MainWindow::on_actSaveAssign_triggered(bool checked)
{
    if(checked)
    {
        ui->actExitAssign->setChecked(!checked);    //сброс галочки назначения клавиши
        ui->actCreateAssign->setChecked(!checked);    //сброс галочки назначения клавиши
        ui->actOpenAssign->setChecked(!checked);    //сброс галочки назначения клавиши
    }
}

void MainWindow::on_actExitAssign_triggered(bool checked)
{
    if(checked)
    {
        ui->actCreateAssign->setChecked(!checked);    //сброс галочки назначения клавиши
        ui->actSaveAssign->setChecked(!checked);    //сброс галочки назначения клавиши
        ui->actOpenAssign->setChecked(!checked);    //сброс галочки назначения клавиши
    }
}

void MainWindow::on_actLeft_triggered() //выравнивание по левому краю
{
    if(!ui->documentViewer->currentSubWindow())
    {
        return;
    }
    static_cast<documentTextEdit*>(static_cast<QMainWindow*>(ui->documentViewer->currentSubWindow()->widget())->centralWidget())->setAlignment(Qt::AlignLeft);

}

void MainWindow::on_actCenter_triggered()   //выравнивание по центру
{
    if(!ui->documentViewer->currentSubWindow())
    {
        return;
    }
    static_cast<documentTextEdit*>(static_cast<QMainWindow*>(ui->documentViewer->currentSubWindow()->widget())->centralWidget())->setAlignment(Qt::AlignCenter);

}

void MainWindow::on_actRight_triggered()    //выравнивание по правому краю
{
    if(!ui->documentViewer->currentSubWindow())
    {
        return;
    }
    static_cast<documentTextEdit*>(static_cast<QMainWindow*>(ui->documentViewer->currentSubWindow()->widget())->centralWidget())->setAlignment(Qt::AlignRight);

}

void MainWindow::on_actFont_triggered() //установка шрифта
{
    if(!ui->documentViewer->currentSubWindow())
    {
        return;
    }
    documentTextEdit* documentPtr = static_cast<documentTextEdit*>(static_cast<QMainWindow*>(ui->documentViewer->currentSubWindow()->widget())->centralWidget());
    QFontDialog dlg(documentPtr->currentFont,this);
    bool b[] = {true};
    documentPtr->currentFont = dlg.getFont(b, documentPtr->currentFont);
    documentPtr->setCurrentFont(documentPtr->currentFont);
}

void MainWindow::on_actCopyFont_triggered() //копировать шрифт
{
    if(!ui->documentViewer->currentSubWindow())
    {
        return;
    }
    documentTextEdit* documentPtr = static_cast<documentTextEdit*>(static_cast<QMainWindow*>(ui->documentViewer->currentSubWindow()->widget())->centralWidget());

    documentPtr->tempFont = documentPtr->textCursor().charFormat().font();
}

void MainWindow::on_actPasteFont_triggered() //вставить шрифт
{
    if(!ui->documentViewer->currentSubWindow())
    {
        return;
    }
    documentTextEdit* documentPtr = static_cast<documentTextEdit*>(static_cast<QMainWindow*>(ui->documentViewer->currentSubWindow()->widget())->centralWidget());
    QTextCharFormat fmt = documentPtr->textCursor().charFormat();
    fmt.setFont(documentPtr->tempFont);
    documentPtr->textCursor().setCharFormat(fmt);
}

void MainWindow::on_actCurrentDate_triggered()  //вставка текущей даты
{
    if(!ui->documentViewer->currentSubWindow())
    {
        return;
    }
    documentTextEdit* documentPtr = static_cast<documentTextEdit*>(static_cast<QMainWindow*>(ui->documentViewer->currentSubWindow()->widget())->centralWidget());
    QDate date = QDate::currentDate();

    documentPtr->textCursor().insertText(date.toString("dd.MM.yyyy"));
}

void MainWindow::on_actCurrentTime_triggered()  //вставка текущего времени
{
    if(!ui->documentViewer->currentSubWindow())
    {
        return;
    }
    documentTextEdit* documentPtr = static_cast<documentTextEdit*>(static_cast<QMainWindow*>(ui->documentViewer->currentSubWindow()->widget())->centralWidget());
    QTime time = QTime::currentTime();

    documentPtr->textCursor().insertText(time.toString("h:m:s"));
}
