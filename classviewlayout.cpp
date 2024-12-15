#include "classviewlayout.h"

ClassViewLayout::ClassViewLayout(QWidget *parent)
    : QWidget{parent}
{
    AddButton->setText("ADD");
    RemoveButton->setText("REMOVE");
    StudentButton->setText("STUDENT");
    ClassLabel->setText("<b>YOUR CLASS</b>");
    ClassLabel->setAlignment(Qt::AlignCenter);
    Layout->addWidget(ClassLabel, 0, 0, 1, 4);
    Layout->addWidget(ClassView, 1, 0, 6, 4);
    Layout->addWidget(AddButton, 7,0, 1, 1);
    Layout->addWidget(RemoveButton,7,3,1,1);
    Layout->addWidget(StudentButton,7,1,2,1);
    this->setLayout(Layout);
    this->adjustSize();
}
