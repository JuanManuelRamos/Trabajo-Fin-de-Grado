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
    ui->tableWidget_PLAND_Especiales->setColumnWidth(0, 50);
    ui->tableWidget_PLAND_Especiales->setColumnWidth(1, 236);
    ui->tableWidget_PLAND_Especiales->setColumnWidth(2, 238);
    ui->tableWidget_PLAND_Especiales->setColumnWidth(3, 215);
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
    ui->label_PLAND_varR->setText(QString::number(numDiasPlan));

    if(planesEspeciales.size() > 0)
    {
        for(int i = 0; i < numDiasPlan; i++)
        {
            ui->tableWidget_PLAND_Especiales->insertRow(1+i);
            ui->tableWidget_PLAND_Especiales->setItem(1+i, 0, new QTableWidgetItem(QString::number(1+i)));
            ui->tableWidget_PLAND_Especiales->setItem(1+i, 1, new QTableWidgetItem(db1->queryMostrarNombrePlatoPorID(QString::number(planesEspeciales[plan].get_idPlatoPP(i)))));
            ui->tableWidget_PLAND_Especiales->setItem(1+i, 2, new QTableWidgetItem(db1->queryMostrarNombrePlatoPorID(QString::number(planesEspeciales[plan].get_idPlatoSP(i)))));
            ui->tableWidget_PLAND_Especiales->setItem(1+i, 3, new QTableWidgetItem(db1->queryMostrarNombrePlatoPorID(QString::number(planesEspeciales[plan].get_idPlatoP(i)))));
        }
    }

    ui->listWidget_PLAND_alerg->clear();
    ui->listWidget_2_PLAND_inc->clear();

    if(ui->checkBox_cereales_2->isChecked())
        ui->listWidget_PLAND_alerg->addItem("Cereales");
    if(ui->checkBox_frutos_secos_2->isChecked())
        ui->listWidget_PLAND_alerg->addItem("Frutos secos");
    if(ui->checkBox_legumbres_2->isChecked())
        ui->listWidget_PLAND_alerg->addItem("Legumbres");
    if(ui->checkBox_marisco_2->isChecked())
        ui->listWidget_PLAND_alerg->addItem("Marisco");
    if(ui->checkBox_pescado_2->isChecked())
        ui->listWidget_PLAND_alerg->addItem("Pescado");
    if(ui->checkBox_huevo_2->isChecked())
        ui->listWidget_PLAND_alerg->addItem("Proteína de huevo");
    if(ui->checkBox_leche_2->isChecked())
        ui->listWidget_PLAND_alerg->addItem("Proteína de leche de vaca");


    if(ui->checkBox_celiaco_2->isChecked())
        ui->listWidget_2_PLAND_inc->addItem("Celiaquía");
    if(ui->checkBox_diabetico_2->isChecked())
        ui->listWidget_2_PLAND_inc->addItem("Diabetes");
    if(ui->checkBox_semivegetariano_2->isChecked())
        ui->listWidget_2_PLAND_inc->addItem("Semivegetarianismo");
    if(ui->checkBox_vegetariano_2->isChecked())
        ui->listWidget_2_PLAND_inc->addItem("Vegetarianismo");
    if(ui->checkBox_vegano_2->isChecked())
        ui->listWidget_2_PLAND_inc->addItem("Veganismo");
}


