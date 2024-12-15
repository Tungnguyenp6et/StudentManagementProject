#include "login.h"

LogIn::LogIn(QWidget *parent)
    : QWidget{parent}
{
    this->setWindowTitle("LOG IN");
    Username->setText("Username: ");
    Password->setText("Password: ");
    Register->setText("<a href=\"internal_link\">Haven't got an accout, Click me!</a>");
    SubmitButton->setText("SUBMIT");
    Register->setTextFormat(Qt::RichText);
    Register->setOpenExternalLinks(false);
    Layout->addWidget(Username, 0, 0, 1, 1);
    Layout->addWidget(UsernameSpace, 0, 1, 1, 4);
    Layout->addWidget(Password, 1, 0, 1, 1);
    Layout->addWidget(PasswordSpace, 1, 1, 1, 4);
    Layout->addWidget(SubmitButton, 2, 4, 1, 1);
    Layout->addWidget(Register, 3, 1, 1, 4);
    this->setLayout(Layout);
    this->adjustSize();
}
