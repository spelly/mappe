#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlQuery>
#include <QtGui>
#include <QObject>
#include <QInputDialog>
#include <QFileDialog>
#include <QMessageBox>
#include <QDebug>
#include <QMenu>
#include "graph.h"

Graph::Graph(QMainWindow *parent) :
    QMainWindow(parent)
{
    customPlot = new QCustomPlot;
    customPlot->setEnabled(false);

    srand(QDateTime::currentDateTime().toTime_t());

    customPlot->setInteractions(QCustomPlot::iRangeDrag | QCustomPlot::iRangeZoom | QCustomPlot::iSelectAxes |
                                    QCustomPlot::iSelectLegend | QCustomPlot::iSelectPlottables | QCustomPlot::iSelectTitle);
    customPlot->setRangeDrag(Qt::Horizontal|Qt::Vertical);
    customPlot->setRangeZoom(Qt::Horizontal|Qt::Vertical);
    customPlot->xAxis->setRange(0, 1);
    customPlot->yAxis->setRange(0, 1);
    customPlot->yAxis->setRangeReversed(true);
    customPlot->setupFullAxesBox();
    customPlot->xAxis->setLabel("x Axis");
    customPlot->yAxis->setLabel("y Axis");
    customPlot->legend->setVisible(true);
    QFont legendFont = font();
    legendFont.setPointSize(10);
    customPlot->legend->setFont(legendFont);
    customPlot->legend->setSelectedFont(legendFont);
    customPlot->legend->setSelectable(QCPLegend::spItems); // legend box shall not be selectable, only legend items


    // connect slot that ties some axis selections together (especially opposite axes):
    connect(customPlot, SIGNAL(selectionChangedByUser()), this, SLOT(selectionChanged()));
    // connect slots that takes care that when an axis is selected, only that direction can be dragged and zoomed:
    connect(customPlot, SIGNAL(mousePress(QMouseEvent*)), this, SLOT(mousePress()));
    connect(customPlot, SIGNAL(mouseWheel(QWheelEvent*)), this, SLOT(mouseWheel()));

    // make bottom and left axes transfer their ranges to top and right axes:
    connect(customPlot->xAxis, SIGNAL(rangeChanged(QCPRange)), customPlot->xAxis2, SLOT(setRange(QCPRange)));
    connect(customPlot->yAxis, SIGNAL(rangeChanged(QCPRange)), customPlot->yAxis2, SLOT(setRange(QCPRange)));

    // connect some interaction slots:
    connect(customPlot, SIGNAL(titleDoubleClick(QMouseEvent*)), this, SLOT(titleDoubleClick()));
    connect(customPlot, SIGNAL(axisDoubleClick(QCPAxis*,QCPAxis::SelectablePart,QMouseEvent*)), this, SLOT(axisLabelDoubleClick(QCPAxis*,QCPAxis::SelectablePart)));
    connect(customPlot, SIGNAL(legendDoubleClick(QCPLegend*,QCPAbstractLegendItem*,QMouseEvent*)), this, SLOT(legendDoubleClick(QCPLegend*,QCPAbstractLegendItem*)));

    // connect slot that shows a message in the status bar when a graph is clicked:
    connect(customPlot, SIGNAL(plottableClick(QCPAbstractPlottable*,QMouseEvent*)), this, SLOT(graphClicked(QCPAbstractPlottable*)));

    // setup policy and connect slot for context menu popup:
    customPlot->setContextMenuPolicy(Qt::CustomContextMenu);
    connect(customPlot, SIGNAL(customContextMenuRequested(QPoint)), this, SLOT(contextMenuRequest(QPoint)));






    // Oppretter databasen med databasedriver QODBC
    db = QSqlDatabase::addDatabase("QODBC");

    // Setter maksverdiene for x og y aksene til -1 for å være sikker på at de blir overskrevet
    xMax = -1;
    yMax = -1;

    // Setter startverdi for fargevelger variabelen
    colorCounter = 0;
}

Qt::GlobalColor Graph::getColor()
{
    // Oppretter en tabell av farger, og legger inn noen farger
    Qt::GlobalColor colorArray[7] = {Qt::red, Qt::green, Qt::cyan, Qt::magenta, Qt::yellow, Qt::gray, Qt::darkRed};
    int temp;

    // Om telleren har nådd maks, nullstill teller og return. Hvis ikke, øk teller og return
    if (colorCounter == 6) {
        temp = colorCounter;
        colorCounter = 0;
        return colorArray[temp];
    }
    else {
        temp = colorCounter;
        colorCounter ++;
        return colorArray[temp];
    }

}

void Graph::exportGraph()
{
    // Oppretter et QPixmap objekt, og "grabber" customPlot widgeten
    QPixmap pm = QPixmap::grabWidget(customPlot);
    // Åpner en lagre fil dialog
    QString filename = QFileDialog::getSaveFileName(this, tr("Save File"), "", tr("Images (*.jpg)"));
    // Lagre QPixMap objektet til disk
    pm.save(filename);
}

void Graph::addGraph(QString q)
{
    //Bruker access driver for å åpne filen direkte. Ikke nødvendig å kjøre mot access sin database motor
    db.setDatabaseName("DRIVER={Microsoft Access Driver (*.mdb)};FIL={MS Access};DBQ=" + databaseSti);

    // Oppretter en tabell av vector med lengde 2. En for hver akse
    QVector<double> *graphTabell[2];
    for (int i = 0; i < 2; i++) {
        graphTabell[i] = new QVector<double>;
    }

    // Hvis databasen er åpen....
    if (db.open()) {
        qDebug("Database opened");

        //Opprett query object, og kjør queryen.
        QSqlQuery sqlQuery;
        sqlQuery.exec(q);

        // Så lenge det er flere tuples i queryen, pushback i vector, og  evt overskriv maks x, y verdier
        while (sqlQuery.next()) {

            for (int i = 0; i < 2; i++) {
                graphTabell[i]->push_back(sqlQuery.value(i).toDouble());
            }

            if (sqlQuery.value(0).toInt() > xMax) {
                xMax = sqlQuery.value(0).toInt();
            }

            if (sqlQuery.value(1).toInt() > yMax) {
                yMax = sqlQuery.value(1).toInt();
            }
        }

        // Lukker databasen
        db.close();

        // create graph and assign data to it:
        customPlot->addGraph(customPlot->yAxis, customPlot->xAxis);
        customPlot->graph(customPlot->graphCount() -1)->setData(*graphTabell[0] , *graphTabell[1]);
        customPlot->graph(customPlot->graphCount() -1)->setPen(QPen(getColor()));

        // set axes ranges, so we see all data:
        customPlot->xAxis->setRange(0, yMax);
        customPlot->yAxis->setRange(0, xMax);

        // Kjør en replot på grafvinduet og plusser counteren
        customPlot->replot();

    }
    else {
        QMessageBox::warning(this, "Error", "Database could not be opened!");
        //qDebug("ouch!.. shit not working");
    }
}

void Graph::setXValue(int x)
{
    xMax = x;
    customPlot->xAxis->setRange(0, xMax);
    customPlot->replot();
}

void Graph::setYValue(int y)
{
    yMax = y;
    customPlot->yAxis->setRange(0, yMax);
    customPlot->replot();
}

void Graph::setDatabaseSti()
{
    // Henter filbanen til databasen
    databaseSti = QFileDialog::getOpenFileName();
    // Sender signal om at filbanen er satt
    emit fileOpened();
}

void Graph::enableBtn()
{
    customPlot->setEnabled(true);
}

void Graph::titleDoubleClick()
{
  // Set the plot title by double clicking on it

  bool ok;
  QString newTitle = QInputDialog::getText(this, "QCustomPlot example", "New plot title:", QLineEdit::Normal, customPlot->title(), &ok);
  if (ok)
  {
    customPlot->setTitle(newTitle);
    customPlot->replot();
  }
}

void Graph::axisLabelDoubleClick(QCPAxis *axis, QCPAxis::SelectablePart part)
{
  // Set an axis label by double clicking on it

  if (part == QCPAxis::spAxisLabel) // only react when the actual axis label is clicked, not tick label or axis backbone
  {
    bool ok;
    QString newLabel = QInputDialog::getText(this, "QCustomPlot example", "New axis label:", QLineEdit::Normal, axis->label(), &ok);
    if (ok)
    {
      axis->setLabel(newLabel);
      customPlot->replot();
    }
  }
}

void Graph::legendDoubleClick(QCPLegend *legend, QCPAbstractLegendItem *item)
{
  // Rename a graph by double clicking on its legend item

  Q_UNUSED(legend)
  if (item) // only react if item was clicked (user could have clicked on border padding of legend where there is no item, then item is 0)
  {
    QCPPlottableLegendItem *plItem = qobject_cast<QCPPlottableLegendItem*>(item);
    bool ok;
    QString newName = QInputDialog::getText(this, "QCustomPlot example", "New graph name:", QLineEdit::Normal, plItem->plottable()->name(), &ok);
    if (ok)
    {
      plItem->plottable()->setName(newName);
      customPlot->replot();
    }
  }
}

void Graph::selectionChanged()
{
  /*
   normally, axis base line, axis tick labels and axis labels are selectable separately, but we want
   the user only to be able to select the axis as a whole, so we tie the selected states of the tick labels
   and the axis base line together. However, the axis label shall be selectable individually.

   The selection state of the left and right axes shall be synchronized as well as the state of the
   bottom and top axes.

   Further, we want to synchronize the selection of the graphs with the selection state of the respective
   legend item belonging to that graph. So the user can select a graph by either clicking on the graph itself
   or on its legend item.
  */

  // make top and bottom axes be selected synchronously, and handle axis and tick labels as one selectable object:
  if (customPlot->xAxis->selected().testFlag(QCPAxis::spAxis) || customPlot->xAxis->selected().testFlag(QCPAxis::spTickLabels) ||
      customPlot->xAxis2->selected().testFlag(QCPAxis::spAxis) || customPlot->xAxis2->selected().testFlag(QCPAxis::spTickLabels))
  {
    customPlot->xAxis2->setSelected(QCPAxis::spAxis|QCPAxis::spTickLabels);
    customPlot->xAxis->setSelected(QCPAxis::spAxis|QCPAxis::spTickLabels);
  }
  // make left and right axes be selected synchronously, and handle axis and tick labels as one selectable object:
  if (customPlot->yAxis->selected().testFlag(QCPAxis::spAxis) || customPlot->yAxis->selected().testFlag(QCPAxis::spTickLabels) ||
      customPlot->yAxis2->selected().testFlag(QCPAxis::spAxis) || customPlot->yAxis2->selected().testFlag(QCPAxis::spTickLabels))
  {
    customPlot->yAxis2->setSelected(QCPAxis::spAxis|QCPAxis::spTickLabels);
    customPlot->yAxis->setSelected(QCPAxis::spAxis|QCPAxis::spTickLabels);
  }

  // synchronize selection of graphs with selection of corresponding legend items:
  for (int i=0; i<customPlot->graphCount(); ++i)
  {
    QCPGraph *graph = customPlot->graph(i);
    QCPPlottableLegendItem *item = customPlot->legend->itemWithPlottable(graph);
    if (item->selected() || graph->selected())
    {
      item->setSelected(true);
      graph->setSelected(true);
    }
  }
}

void Graph::mousePress()
{
  // if an axis is selected, only allow the direction of that axis to be dragged
  // if no axis is selected, both directions may be dragged

  if (customPlot->xAxis->selected().testFlag(QCPAxis::spAxis))
    customPlot->setRangeDrag(customPlot->xAxis->orientation());
  else if (customPlot->yAxis->selected().testFlag(QCPAxis::spAxis))
    customPlot->setRangeDrag(customPlot->yAxis->orientation());
  else
    customPlot->setRangeDrag(Qt::Horizontal|Qt::Vertical);
}

void Graph::mouseWheel()
{
  // if an axis is selected, only allow the direction of that axis to be zoomed
  // if no axis is selected, both directions may be zoomed

  if (customPlot->xAxis->selected().testFlag(QCPAxis::spAxis))
    customPlot->setRangeZoom(customPlot->xAxis->orientation());
  else if (customPlot->yAxis->selected().testFlag(QCPAxis::spAxis))
    customPlot->setRangeZoom(customPlot->yAxis->orientation());
  else
    customPlot->setRangeZoom(Qt::Horizontal|Qt::Vertical);
}

void Graph::addRandomGraph()
{
  int n = 100; // number of points in graph
  double xScale = (rand()/(double)RAND_MAX + 0.5)*2;
  double yScale = (rand()/(double)RAND_MAX + 0.5)*2;
  double xOffset = (rand()/(double)RAND_MAX - 0.5)*4;
  double yOffset = (rand()/(double)RAND_MAX - 0.5)*5;
  double r1 = (rand()/(double)RAND_MAX - 0.5)*2;
  double r2 = (rand()/(double)RAND_MAX - 0.5)*2;
  double r3 = (rand()/(double)RAND_MAX - 0.5)*2;
  double r4 = (rand()/(double)RAND_MAX - 0.5)*2;
  QVector<double> x(n), y(n);
  for (int i=0; i<n; i++)
  {
    x[i] = (i/(double)n-0.5)*10.0*xScale + xOffset;
    y[i] = (sin(x[i]*r1*5)*sin(cos(x[i]*r2)*r4*3)+r3*cos(sin(x[i])*r4*2))*yScale + yOffset;
  }

  customPlot->addGraph();
  customPlot->graph()->setName(QString("New graph %1").arg(customPlot->graphCount()-1));
  customPlot->graph()->setData(x, y);
  customPlot->graph()->setLineStyle((QCPGraph::LineStyle)(rand()%5+1));
  if (rand()%100 > 75)
    customPlot->graph()->setScatterStyle((QCP::ScatterStyle)(rand()%9+1));
  QPen graphPen;
  graphPen.setColor(QColor(rand()%245+10, rand()%245+10, rand()%245+10));
  graphPen.setWidthF(rand()/(double)RAND_MAX*2+1);
  customPlot->graph()->setPen(graphPen);
  customPlot->replot();
}

void Graph::removeSelectedGraph()
{
  if (customPlot->selectedGraphs().size() > 0)
  {
    customPlot->removeGraph(customPlot->selectedGraphs().first());
    customPlot->replot();
  }
}

void Graph::removeAllGraphs()
{
  customPlot->clearGraphs();
  customPlot->replot();
}

void Graph::contextMenuRequest(QPoint pos)
{
  QMenu *menu = new QMenu(this);
  menu->setAttribute(Qt::WA_DeleteOnClose);

  if (customPlot->legend->selectTestLegend(pos)) // context menu on legend requested
  {
    menu->addAction("Move to top left", this, SLOT(moveLegend()))->setData((int)QCPLegend::psTopLeft);
    menu->addAction("Move to top center", this, SLOT(moveLegend()))->setData((int)QCPLegend::psTop);
    menu->addAction("Move to top right", this, SLOT(moveLegend()))->setData((int)QCPLegend::psTopRight);
    menu->addAction("Move to bottom right", this, SLOT(moveLegend()))->setData((int)QCPLegend::psBottomRight);
    menu->addAction("Move to bottom left", this, SLOT(moveLegend()))->setData((int)QCPLegend::psBottomLeft);
  } else  // general context menu on graphs requested
  {
    if (customPlot->selectedGraphs().size() > 0)
      menu->addAction("Remove selected graph", this, SLOT(removeSelectedGraph()));
    if (customPlot->graphCount() > 0)
      menu->addAction("Remove all graphs", this, SLOT(removeAllGraphs()));
    menu->addAction("Hide/show legend", this, SLOT(hideLegend()));
  }

  menu->popup(customPlot->mapToGlobal(pos));
}

void Graph::moveLegend()
{
  if (QAction* contextAction = qobject_cast<QAction*>(sender())) // make sure this slot is really called by a context menu action, so it carries the data we need
  {
    bool ok;
    int dataInt = contextAction->data().toInt(&ok);
    if (ok)
    {
      customPlot->legend->setPositionStyle((QCPLegend::PositionStyle)dataInt);
      customPlot->replot();
    }
  }
}

void Graph::graphClicked(QCPAbstractPlottable *plottable)
{
    //this->statusBar->showMessage(QString("Clicked on graph '%1'.").arg(plottable->name()), 1000);
}

void Graph::hideLegend()
{
    if (customPlot->legend->visible() == true) {
        customPlot->legend->setVisible(false);
        customPlot->replot();
    }
    else {
        customPlot->legend->setVisible(true);
        customPlot->replot();
    }

}


