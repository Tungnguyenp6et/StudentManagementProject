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

private:
    Ui::MainWindow *ui;
    QSqlDatabase db;
    QFile *MyForm = new QFile(this);
    QString WriteablePath;
    QString TargetFilePath;
    QFile *MyFile = new QFile(this);

};
#endif // MAINWINDOW_H
