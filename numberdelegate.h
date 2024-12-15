#ifndef NUMBERDELEGATE_H
#define NUMBERDELEGATE_H

#include <QStyledItemDelegate>
#include <QWidget>
#include <QLineEdit>

class NumberDelegate : public QStyledItemDelegate
{
public:
    explicit NumberDelegate(QObject *parent = nullptr);
    QWidget *createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const override;
    void setEditorData(QWidget *editor, const QModelIndex &index) const override;
    void setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const override;
};

#endif // NUMBERDELEGATE_H
