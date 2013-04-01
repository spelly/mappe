#ifndef GRAPH_H
#define GRAPH_H

#include <QWidget>
#include <QtGui>
#include <QDebug>
#include <QtCore>
#include <QtSql>
#include "qcustomplot.h"


class Graph : public QMainWindow
{
    Q_OBJECT
public:
    explicit Graph(QMainWindow *parent = 0);
    QCustomPlot* customPlot;
private:
    Qt::GlobalColor getColor();
    int xMax;
    int yMax;
    int counter;
    int colorCounter;
    QString databaseSti;
    QSqlDatabase db;


    
signals:
    void fileOpened();
    
public slots:
    void exportGraph();
    void addGraph(QString q);
    void setXValue(int x);
    void setYValue(int y);
    void setDatabaseSti();
    void enableBtn();

private slots:
  void titleDoubleClick();
  void axisLabelDoubleClick(QCPAxis* axis, QCPAxis::SelectablePart part);
  void legendDoubleClick(QCPLegend* legend, QCPAbstractLegendItem* item);
  void selectionChanged();
  void mousePress();
  void mouseWheel();
  void addRandomGraph();
  void removeSelectedGraph();
  void removeAllGraphs();
  void contextMenuRequest(QPoint pos);
  void moveLegend();
  void graphClicked(QCPAbstractPlottable *plottable);
  void hideLegend();
};

#endif // GRAPH_H
