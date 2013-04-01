/****************************************************************************
** Meta object code from reading C++ file 'graph.h'
**
** Created: Mon 25. Mar 23:55:18 2013
**      by: The Qt Meta Object Compiler version 63 (Qt 4.8.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../graph.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'graph.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_Graph[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
      20,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: signature, parameters, type, tag, flags
       7,    6,    6,    6, 0x05,

 // slots: signature, parameters, type, tag, flags
      20,    6,    6,    6, 0x0a,
      36,   34,    6,    6, 0x0a,
      56,   54,    6,    6, 0x0a,
      73,   71,    6,    6, 0x0a,
      88,    6,    6,    6, 0x0a,
     105,    6,    6,    6, 0x0a,
     117,    6,    6,    6, 0x08,
     146,  136,    6,    6, 0x08,
     213,  201,    6,    6, 0x08,
     266,    6,    6,    6, 0x08,
     285,    6,    6,    6, 0x08,
     298,    6,    6,    6, 0x08,
     311,    6,    6,    6, 0x08,
     328,    6,    6,    6, 0x08,
     350,    6,    6,    6, 0x08,
     372,  368,    6,    6, 0x08,
     399,    6,    6,    6, 0x08,
     422,  412,    6,    6, 0x08,
     458,    6,    6,    6, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_Graph[] = {
    "Graph\0\0fileOpened()\0exportGraph()\0q\0"
    "addGraph(QString)\0x\0setXValue(int)\0y\0"
    "setYValue(int)\0setDatabaseSti()\0"
    "enableBtn()\0titleDoubleClick()\0axis,part\0"
    "axisLabelDoubleClick(QCPAxis*,QCPAxis::SelectablePart)\0"
    "legend,item\0"
    "legendDoubleClick(QCPLegend*,QCPAbstractLegendItem*)\0"
    "selectionChanged()\0mousePress()\0"
    "mouseWheel()\0addRandomGraph()\0"
    "removeSelectedGraph()\0removeAllGraphs()\0"
    "pos\0contextMenuRequest(QPoint)\0"
    "moveLegend()\0plottable\0"
    "graphClicked(QCPAbstractPlottable*)\0"
    "hideLegend()\0"
};

void Graph::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        Graph *_t = static_cast<Graph *>(_o);
        switch (_id) {
        case 0: _t->fileOpened(); break;
        case 1: _t->exportGraph(); break;
        case 2: _t->addGraph((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 3: _t->setXValue((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 4: _t->setYValue((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 5: _t->setDatabaseSti(); break;
        case 6: _t->enableBtn(); break;
        case 7: _t->titleDoubleClick(); break;
        case 8: _t->axisLabelDoubleClick((*reinterpret_cast< QCPAxis*(*)>(_a[1])),(*reinterpret_cast< QCPAxis::SelectablePart(*)>(_a[2]))); break;
        case 9: _t->legendDoubleClick((*reinterpret_cast< QCPLegend*(*)>(_a[1])),(*reinterpret_cast< QCPAbstractLegendItem*(*)>(_a[2]))); break;
        case 10: _t->selectionChanged(); break;
        case 11: _t->mousePress(); break;
        case 12: _t->mouseWheel(); break;
        case 13: _t->addRandomGraph(); break;
        case 14: _t->removeSelectedGraph(); break;
        case 15: _t->removeAllGraphs(); break;
        case 16: _t->contextMenuRequest((*reinterpret_cast< QPoint(*)>(_a[1]))); break;
        case 17: _t->moveLegend(); break;
        case 18: _t->graphClicked((*reinterpret_cast< QCPAbstractPlottable*(*)>(_a[1]))); break;
        case 19: _t->hideLegend(); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData Graph::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject Graph::staticMetaObject = {
    { &QMainWindow::staticMetaObject, qt_meta_stringdata_Graph,
      qt_meta_data_Graph, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &Graph::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *Graph::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *Graph::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_Graph))
        return static_cast<void*>(const_cast< Graph*>(this));
    return QMainWindow::qt_metacast(_clname);
}

int Graph::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 20)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 20;
    }
    return _id;
}

// SIGNAL 0
void Graph::fileOpened()
{
    QMetaObject::activate(this, &staticMetaObject, 0, 0);
}
QT_END_MOC_NAMESPACE
