#ifndef PERCENTAGEDELEGATE_H
#define PERCENTAGEDELEGATE_H

#include <QObject>
#include <QLineEdit>
#include <QStyledItemDelegate>

class PercentageDelegate : public QStyledItemDelegate
{
public:
    explicit PercentageDelegate(QObject *parent = nullptr);
    QWidget *createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const override;
    void setEditorData(QWidget *editor, const QModelIndex &index) const;
    void setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const;
private:
};

#endif // PERCENTAGEDELEGATE_H
