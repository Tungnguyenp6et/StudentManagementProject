#ifndef LOWEREDIT_H
#define LOWEREDIT_H

#include <QLineEdit>

class LowerEdit : public QLineEdit
{
public:
    LowerEdit();
    LowerEdit(QWidget *parent);
    void keyPressEvent(QKeyEvent *event) override;
};

#endif // LOWEREDIT_H
