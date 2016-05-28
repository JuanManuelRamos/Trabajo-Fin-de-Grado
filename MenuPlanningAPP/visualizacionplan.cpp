#include "mainwindowmenuplan.h"
#include "ui_mainwindowmenuplan.h"


void MainWindowMenuPlan::inicializarTablas()
{
    ui->tableWidget_PLAND_Recomendados->setRowCount(1);
    ui->tableWidget_PLAND_Recomendados->setColumnCount(4);
    ui->tableWidget_PLAND_Recomendados->setHorizontalHeaderLabels(QString("Día;Primer plato;Segundo plato;Postre").split(";"));
    ui->tableWidget_PLAND_Recomendados->verticalHeader()->hide();
    ui->tableWidget_PLAND_Recomendados->setColumnWidth(0, 50);
    ui->tableWidget_PLAND_Recomendados->setColumnWidth(1, 236);
    ui->tableWidget_PLAND_Recomendados->setColumnWidth(2, 238);
    ui->tableWidget_PLAND_Recomendados->setColumnWidth(3, 215);

    ui->tableWidget_PLAND_Especiales->setRowCount(1);
    ui->tableWidget_PLAND_Especiales->setColumnCount(4);
    ui->tableWidget_PLAND_Especiales->setHorizontalHeaderLabels(QString("Día;Primer plato;Segundo plato;Postre").split(";"));
    ui->tableWidget_PLAND_Especiales->verticalHeader()->hide();
}

void MainWindowMenuPlan::limpiarTablas()
{
    ui->tableWidget_PLAND_Recomendados->clear();
    ui->tableWidget_PLAND_Especiales->clear();
}

void MainWindowMenuPlan::visualizarPlanes()
{
    QString n;

    for(int i = 0; i < planesRecomendados.size(); i++)
    {
        n = "Plan alimenticio ";
        n.append(QString::number(1+i));
        ui->listWidget_PLAND_Recomendados->addItem(n);
    }
}



void MainWindowMenuPlan::on_listWidget_PLAND_Recomendados_clicked(const QModelIndex &index)
{
    int plan = index.row();

    limpiarTablas();
    inicializarTablas();

    for(int i = 0; i < numDiasPlan; i++)
    {
        ui->tableWidget_PLAND_Recomendados->insertRow(1+i);
        ui->tableWidget_PLAND_Recomendados->setItem(1+i, 0, new QTableWidgetItem(QString::number(1+i)));
        ui->tableWidget_PLAND_Recomendados->setItem(1+i, 1, new QTableWidgetItem(db1->queryMostrarNombrePlatoPorID(QString::number(planesRecomendados[plan].get_idPlatoPP(i)))));
        ui->tableWidget_PLAND_Recomendados->setItem(1+i, 2, new QTableWidgetItem(db1->queryMostrarNombrePlatoPorID(QString::number(planesRecomendados[plan].get_idPlatoSP(i)))));
        ui->tableWidget_PLAND_Recomendados->setItem(1+i, 3, new QTableWidgetItem(db1->queryMostrarNombrePlatoPorID(QString::number(planesRecomendados[plan].get_idPlatoP(i)))));
    }

    ui->label_PLAND_precioR->setText(QString::number(planesRecomendados[plan].get_objPrecio()));
    ui->label_PLAND_varR->setText(get_variedad(planesRecomendados[plan].get_objGradoRepeticion()));
}


QString MainWindowMenuPlan::get_variedad(double var)
{
    if(var >= 10)
        return "Muy baja";
    else if(var < 10 && var >= 8)
        return "Baja";
    else if(var < 8 && var >= 6)
        return "Media";
    else if(var < 6 && var >= 4)
        return "Moderada";
    else if(var < 4 && var >= 2)
        return "Alta";
    else
        return "Muy Alta";
}
