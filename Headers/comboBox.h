#ifndef COMBOBOX_H
#define COMBOBOX_H
#include<Headers/database.h>
#include <QAbstractListModel>
#include <QVector>
#include <QString>
#include <QAbstractListModel>

enum table{AUTHOR=1,GENRE=2};
class comboBox : public QAbstractListModel
{

private:
    database *db;
    QVector<QString> datalist;

public:
    explicit comboBox(int dataMask, database *Db,QObject *parent = nullptr);
    int rowCount(const QModelIndex& parent = QModelIndex()) const override;
    QVariant data(const QModelIndex& index, int role = Qt::DisplayRole)const override;

};

#endif // COMBOBOX_H
