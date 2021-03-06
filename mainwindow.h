#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QWidget>
#include <QObject>
#include <QtGui>
#include <QtDebug>
#include <QVBoxLayout>
#include <QPushButton>
#include "qcustomplot.h"
#include "graph.h"
#include "querybuilder.h"



class MainWindow : public QWidget
{
    Q_OBJECT
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    QVBoxLayout* mainLayout;
    QHBoxLayout* selectionGroup;
    QHBoxLayout* graph;
    QHBoxLayout* bottom;
    QPushButton* velgDB;
    QPushButton* addGraph;
    QPushButton* exportButton;

signals:
    
public slots:
    void enableBtn();

private:
    QueryBuilder QB;
    Graph GO;
    
};

#endif // MAINWINDOW_H
