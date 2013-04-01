#include "querybuilder.h"
#include "graph.h"
#include <QObject>
#include <QtGui>
#include <QDebug>
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlQuery>

QueryBuilder::QueryBuilder(QObject *parent) :
    QObject(parent)
{
    // Oppretter listene som går i comboBoxene og comboBoxene, og legger til innholdet i comboBoxene
    tableList << "T_Rig" << "T_Log";
    T_RigList << "Pump_in" << "Boost_Rates" << "ROP" << "Surface_RPM" << "Mud_w_in" << "Mud_w_out" << "Mud_w_man" << "BHP" << "TVD" << "MD" << "Hook_pos" << "Well_head_p" << "Delta_flow" << "APL" << "Calcmode" << "MudSelect" << "InnerD" << "OuterD" << "LastShoepos" << "Deluge" << "DepthOutlet" << "DepthOut_Man" << "TVD_Man" << "ShoeHeight" << "Apl_a" << "Apl_b" << "Apl_c" << "Apl_d";
    T_LogList << "Net_A" << "Net_V" << "Net_f" << "Net_Cos" << "Net_kVA" << "Motor_temp1" << "Motor_temp2" << "Motor_temp3" << "Flowmeter" << "Saiv" << "Pin" << "Pout" << "Riser1A" << "Riser1B" << "Riser2A" << "Riser2B" << "Pid_p" << "Pid_i" << "Pid_d" << "Setpoint";
    fieldBox = new QComboBox();
    fieldBox->setSizeAdjustPolicy(QComboBox::AdjustToContents);
    fieldBox->setEnabled(false);
    tableBox = new QComboBox();
    tableBox->setSizeAdjustPolicy(QComboBox::AdjustToContents);
    tableBox->setEnabled(false);

    select = "SELECT Log_index";

}

void QueryBuilder::makeQuery() {

    query = "";
    // Henter verdier fra comboBoxene
    QString s = this->getFBValue();
    QString f = this->getTBValue();

    // Sjekker om SELECT delen av denne spørringen er blitt utført før
    if (querysDone.contains(s)) {
        emit alreadyContains(s);
    }
    else {
        //querysDone << s;

        // Lager FROM strengen
        from = "FROM " + f;

        // Setter sammen query strengen fra SELECT og FROM
        query = (select + ", " + s + " " + from);
        emit setQuery(query);
    }

}

void QueryBuilder::setBoxes()
{

    tableBox->clear();
    fieldBox->clear();
    tableBox->addItems(tableList);
    fieldBox->addItems(T_RigList);

    // Setter startverdier for comboBoxene
    TBValue = "T_Rig";
    FBValue = "Pump_in";
}

void QueryBuilder::enableBtn()
{
    fieldBox->setEnabled(true);
    tableBox->setEnabled(true);
}





QString QueryBuilder::getQuery()
{
    return query;
}

/*int QueryBuilder::getCounter()
{
    return counter;
}*/



QStringList QueryBuilder::getTableList()
{
    return tableList;
}

QStringList QueryBuilder::getT_RigList()
{
    return T_RigList;
}

QStringList QueryBuilder::getT_LogList()
{
    return T_LogList;
}

QString QueryBuilder::getTBValue()
{
    return TBValue;
}

QString QueryBuilder::getFBValue()
{
    return FBValue;
}

void QueryBuilder::setFieldBox(QString s)
{
    // Oppdaterer innholdet i felt boksen etter hvilken tabell som er valgt i tabell boksen

    //her blir det av en eller annen merkelig grunn omvendt
    //om jeg prøver == eller != etter compare, virker det ikke
    if (s.compare("T_Log")) {
        fieldBox->clear();
        fieldBox->addItems(T_RigList);
        TBValue = s;
    }
    else {
        fieldBox->clear();
        fieldBox->addItems(T_LogList);
        TBValue = s;
    }
}

void QueryBuilder::setTableBox(QString s)
{
    TBValue = s;
}

void QueryBuilder::setFBValue(QString s)
{
    FBValue = s;
}

