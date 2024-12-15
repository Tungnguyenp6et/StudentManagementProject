#ifndef CLASSVIEWLAYOUT_H
#define CLASSVIEWLAYOUT_H

#include <QWidget>
#include <QTableView>
#include <QPushButton>
#include <QLabel>
#include <QGridLayout>
class ClassViewLayout : public QWidget
{
    Q_OBJECT
public:
    explicit ClassViewLayout(QWidget *parent = nullptr);
    QTableView *ClassView = new QTableView(this);
    QPushButton *AddButton = new QPushButton(this);
    QPushButton *RemoveButton = new QPushButton(this);
    QPushButton *StudentButton = new QPushButton(this);
    QGridLayout *Layout = new QGridLayout(this);
    QLabel *ClassLabel = new QLabel(this);
signals:
};

#endif // CLASSVIEWLAYOUT_H
