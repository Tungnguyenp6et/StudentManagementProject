#ifndef STUDENTDIALOG_H
#define STUDENTDIALOG_H

#include <QDialog>

#include <QTableView>
#include <QPushButton>
#include <QLabel>
#include <QGridLayout>

namespace Ui {
class StudentDialog;
}

class StudentDialog : public QDialog
{
    Q_OBJECT

public:
    explicit StudentDialog(QWidget *parent = nullptr);
    ~StudentDialog();

private:
    Ui::StudentDialog *ui;
    QTableView *StudentView = new QTableView(this);
    QPushButton *AddButton = new QPushButton(this);
    QPushButton *RemoveButton = new QPushButton(this);
    QGridLayout *Layout = new QGridLayout(this);
    QLabel *StudentLabel = new QLabel(this);
};

#endif // STUDENTDIALOG_H
