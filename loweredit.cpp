#include "loweredit.h"

LowerEdit::LowerEdit() {}

LowerEdit::LowerEdit(QWidget *parent) : QLineEdit(parent){}

void LowerEdit::keyPressEvent(QKeyEvent *event){
    QString Value = this->text();
    QString NewValue = Value.toLower();
    this->setText(NewValue);
    QLineEdit::keyPressEvent(event);
}
