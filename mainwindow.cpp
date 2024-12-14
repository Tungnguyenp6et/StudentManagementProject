#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    SetUpTheDatabase();


}
void MainWindow::SetUpTheDatabase(){
    MyForm->setFileName(":/Database/DatabaseForm.accdb");
    WriteablePath = QStandardPaths::writableLocation(QStandardPaths::AppDataLocation);
    TargetFilePath = WriteablePath + QDir::separator() + "MyDatabase.accdb";
    MyFile->setFileName(TargetFilePath);

    if (QFile::exists(TargetFilePath)) {
        goto open;
    }
    QDir().mkdir(WriteablePath);
    if (!MyForm->open(QIODevice::ReadOnly)){
        qDebug() << "Open form unsuccessfully";
    }
    if (!MyFile->open(QIODevice::WriteOnly)){
        qDebug() << "Open file unsuccessfully";
    }
    MyFile->write(MyForm->readAll());
    MyFile->close();
    MyForm->close();

    open:
    qDebug() << "Successfully extract the file";
    qDebug() << TargetFilePath;
    db = QSqlDatabase::addDatabase("QODBC", "accdb_connection");
    db.setDatabaseName("Driver={Microsoft Access Driver (*.mdb, *.accdb)};DBQ=" + TargetFilePath);
    if(!db.open()) qDebug()<< db.lastError().text();
    else qDebug() << "Open!";


}
MainWindow::~MainWindow()
{
    delete ui;
}
