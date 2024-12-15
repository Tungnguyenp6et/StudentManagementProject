#include "numberdelegate.h"

NumberDelegate::NumberDelegate(QObject *parent)
    : QStyledItemDelegate{parent}
{}
QWidget *NumberDelegate::createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const{
    QLineEdit *editor = new QLineEdit(parent);
    QDoubleValidator *validator = new QDoubleValidator(0,10,2,editor);
    validator->setNotation(QDoubleValidator::StandardNotation);
    editor->setValidator(validator);
    return editor;
}
void NumberDelegate::setEditorData(QWidget *editor, const QModelIndex &index) const{

    QLineEdit *LineEdit = static_cast <QLineEdit*>(editor);
    LineEdit->setText(index.data().toString());
}
void NumberDelegate::setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const{
    QLineEdit *LineEdit = static_cast<QLineEdit*>(editor);
    model->setData(index,LineEdit->text().toDouble());
}
