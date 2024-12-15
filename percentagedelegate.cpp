#include "percentagedelegate.h"

PercentageDelegate::PercentageDelegate(QObject *parent)
    : QStyledItemDelegate{parent}
{}
QWidget *PercentageDelegate::createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const{

        QLineEdit *editor = new QLineEdit(parent);
        QDoubleValidator *validator = new QDoubleValidator(0,1,2,editor);
        validator->setNotation(QDoubleValidator::StandardNotation);
        editor->setValidator(validator);
        return editor;

}
void PercentageDelegate::setEditorData(QWidget *editor, const QModelIndex &index) const{

    QLineEdit *LineEdit = static_cast <QLineEdit*>(editor);
    LineEdit->setText(index.data().toString());
}
void PercentageDelegate::setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const{
    QLineEdit *LineEdit = static_cast<QLineEdit*>(editor);
    model->setData(index,LineEdit->text().toDouble());
}
