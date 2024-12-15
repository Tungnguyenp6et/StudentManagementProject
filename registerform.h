#ifndef REGISTERFORM_H
#define REGISTERFORM_H

#include <QWidget>
#include <QGridLayout>
#include <QPushButton>
#include <QLabel>
#include <QLineEdit>
#include "loweredit.h"
class RegisterForm : public QWidget
{
    Q_OBJECT
public:
    explicit RegisterForm(QWidget *parent = nullptr);

    QPushButton *SubmitButton = new QPushButton(this);
    QLabel *Username = new QLabel(this);
    LowerEdit *UsernameSpace = new LowerEdit(this);
    QLabel *Password = new QLabel(this);
    LowerEdit *PasswordSpace = new LowerEdit(this);
    QLabel *ClassID = new QLabel(this);
    LowerEdit *ClassIDSpace = new LowerEdit(this);
    QLabel *ClassName = new QLabel(this);
    LowerEdit *ClassNameSpace = new LowerEdit(this);
    QGridLayout *Layout = new QGridLayout(this);

signals:
};

#endif // REGISTERFORM_H
