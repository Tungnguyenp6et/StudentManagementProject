#include "studentdialog.h"
#include "ui_studentdialog.h"

StudentDialog::StudentDialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::StudentDialog)
{
    ui->setupUi(this);
    AddButton->setText("ADD");
    RemoveButton->setText("REMOVE");
    StudentLabel->setText("<b>YOUR STUDENT</b>");
    StudentLabel->setAlignment(Qt::AlignCenter);
    Layout->addWidget(StudentLabel, 0, 0, 1, 4);
    Layout->addWidget(StudentView, 1, 0, 6, 4);
    Layout->addWidget(AddButton, 7,0, 1, 1);
    Layout->addWidget(RemoveButton,7,3,1,1);
    this->setLayout(Layout);
    this->adjustSize();
}

StudentDialog::~StudentDialog()
{
    delete ui;
}
