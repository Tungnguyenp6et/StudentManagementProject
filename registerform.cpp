#include "registerform.h"

RegisterForm::RegisterForm(QWidget *parent)
    : QWidget{parent}
{
    this->setWindowTitle("Register");
    Username->setText("Username: ");
    Password->setText("Password: ");
    SubmitButton->setText("SUBMIT");
    ClassID->setText("CLassroomID: ");
    ClassName->setText("Classroom name: ");
    Layout->addWidget(Username, 0, 0, 1, 1);
    Layout->addWidget(UsernameSpace, 0, 1, 1, 4);
    Layout->addWidget(Password, 1, 0, 1, 1);
    Layout->addWidget(PasswordSpace, 1, 1, 1, 4);
    Layout->addWidget(ClassID, 2,0,1,1);
    Layout->addWidget(ClassIDSpace, 2, 1, 1, 4);
    Layout->addWidget(ClassName, 3,0,1,1);
    Layout->addWidget(ClassNameSpace, 3, 1, 1, 4);
    Layout->addWidget(SubmitButton, 4, 4, 1, 1);
    this->setLayout(Layout);
    this->adjustSize();
}
