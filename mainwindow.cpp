#include "mainwindow.h"
#include "qcustomplot.h"
#include "querybuilder.h"
#include <QObject>
#include <QtGui>


MainWindow::MainWindow(QWidget *parent) :
    QWidget(parent)
{
    // Oppretter layouts
    mainLayout = new QVBoxLayout(this);
    selectionGroup = new QHBoxLayout;
    graph = new QHBoxLayout;
    bottom = new QHBoxLayout;

    // Oppretter knapper, labels og SignalMapper
    velgDB = new QPushButton("Open database...");
    addGraph = new QPushButton("Add graph");
    addGraph->setEnabled(false);
    exportButton = new QPushButton("Export");
    exportButton->setEnabled(false);

    // Legger widgets til layouts
    selectionGroup->addWidget(velgDB, 1, Qt::AlignLeft);
    bottom->addWidget(exportButton, 0, Qt::AlignRight);
    selectionGroup->addWidget(QB.tableBox);
    selectionGroup->addWidget(QB.fieldBox);
    selectionGroup->addWidget(addGraph);
    graph->addWidget(GO.customPlot);

    // Legger sublayouts til mainLayout
    mainLayout->addLayout(selectionGroup);
    mainLayout->addLayout(graph);
    mainLayout->addLayout(bottom);

    // Connects på knapper og dropdown menyer
    QObject::connect(velgDB, SIGNAL(clicked()), &GO, SLOT(setDatabaseSti()));
    QObject::connect(velgDB, SIGNAL(clicked()), &QB, SLOT(setBoxes()));
    QObject::connect(QB.tableBox, SIGNAL(currentIndexChanged(QString)), &QB, SLOT(setFieldBox(QString)));
    QObject::connect(QB.tableBox, SIGNAL(currentIndexChanged(QString)), &QB, SLOT(setTableBox(QString)));
    QObject::connect(QB.fieldBox, SIGNAL(currentIndexChanged(QString)), &QB, SLOT(setFBValue(QString)));
    QObject::connect(addGraph, SIGNAL(clicked()), &QB, SLOT(makeQuery()));
    QObject::connect(&QB, SIGNAL(setQuery(QString)), &GO, SLOT(addGraph(QString)));
    QObject::connect(exportButton, SIGNAL(clicked()), &GO, SLOT(exportGraph()));

    QObject::connect(&GO, SIGNAL(fileOpened()), &GO, SLOT(enableBtn()));
    QObject::connect(&GO, SIGNAL(fileOpened()), &QB, SLOT(enableBtn()));
    QObject::connect(&GO, SIGNAL(fileOpened()), this, SLOT(enableBtn()));

}

MainWindow::~MainWindow()
{
}



void MainWindow::enableBtn()
{
    addGraph->setEnabled(true);
    exportButton->setEnabled(true);
}


