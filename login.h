#ifndef LOGIN_H
#define LOGIN_H

#include <QWidget>
#include <QGridLayout>
#include <QPushButton>
#include <QLabel>
#include <QLineEdit>
#include "loweredit.h"

class LogIn : public QWidget
{
    Q_OBJECT
public:
    explicit LogIn(QWidget *parent = nullptr);
    QPushButton *SubmitButton = new QPushButton(this);
    QLabel *Username = new QLabel(this);
    LowerEdit *UsernameSpace = new LowerEdit(this);
    QLabel *Password = new QLabel(this);
    LowerEdit *PasswordSpace = new LowerEdit(this);
    QGridLayout *Layout = new QGridLayout(this);
    QLabel *Register = new QLabel(this);
signals:
};

#endif // LOGIN_H
