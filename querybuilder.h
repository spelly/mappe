#ifndef QUERYBUILDER_H
#define QUERYBUILDER_H

#include <QObject>
#include <QtGui>
#include <QStringList>
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlQuery>
#include "qcustomplot.h"
#include "graph.h"

class QueryBuilder : public QObject
{
    Q_OBJECT
public:
    explicit QueryBuilder(QObject *parent = 0);

    QString getQuery();
    int getCounter();
    QStringList getTableList();
    QStringList getT_RigList();
    QStringList getT_LogList();
    QString getTBValue();
    QString getFBValue();
    QComboBox* fieldBox;
    QComboBox* tableBox;

signals:
    void setQuery(QString);
    void alreadyContains(QString);

public slots:
    void setFieldBox(QString s);
    void setTableBox(QString s);
    void setFBValue(QString s);
    void makeQuery();
    void setBoxes();
    void enableBtn();

private:
    QStringList tableList;
    QStringList T_RigList;
    QStringList T_LogList;
    QString tableSelction;
    QString query;
    QString select;
    QString from;
    QStringList querysDone;
    QString TBValue;
    QString FBValue;

    
};

#endif // QUERYBUILDER_H
