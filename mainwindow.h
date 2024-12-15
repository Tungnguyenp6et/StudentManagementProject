#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtCore>
#include <QSqlDatabase>
#include <QFile>
#include <QDir>
#include <QSql>
#include <QSqlQuery>
#include <QSqlError>
#include "login.h"
#include "registerform.h"
#include <QMessageBox>
#include "classviewlayout.h"
#include <iostream>
QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    void SetUpTheDatabase();
    ~MainWindow();
private slots:
    void OnSubmitButtonClicked();
    void OnRegisterButtonClicked();
private:
    Ui::MainWindow *ui;
    QSqlDatabase db;
    QFile *MyForm = new QFile(this);
    bool IsLogedIn{false};
    QString WriteablePath;
    QString TargetFilePath;
    QFile *MyFile = new QFile(this);
    LogIn *LogInWidget = new LogIn(this);
    ClassViewLayout *ClassLayout;

};
#endif // MAINWINDOW_H
