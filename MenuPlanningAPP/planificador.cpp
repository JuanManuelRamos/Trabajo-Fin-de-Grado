#include "mainwindowmenuplan.h"
#include "ui_mainwindowmenuplan.h"



void MainWindowMenuPlan::on_tabWidget_tabBarClicked(int index)
{
    if(index == 3)
        qDebug() << "ola k ase";
}


/*-----------------------------------------------------------------*/
/*------------------ EVENTO CLICK DE BOTON > ----------------------*/
/*-----------------------------------------------------------------*/
void MainWindowMenuPlan::on_pushButton_PLAN_der_clicked()
{
    ACTION A = controllSelectionElement(*ui->listView_PLAN_Platos);                  //Comprueba si hay un plato seleccionado

    if(A == ACCEPT)
    {
        ui->listWidget_PLAN_PlatosSelec->addItem(ui->listView_PLAN_Platos->currentIndex().data(Qt::DisplayRole).toString());    //Añadir el elemento del listview platos al listwidget platos seleccionados
    }
}


/*-----------------------------------------------------------------*/
/*------------------ EVENTO CLICK DE BOTON < ----------------------*/
/*-----------------------------------------------------------------*/
void MainWindowMenuPlan::on_pushButton_PLAN_izq_clicked()
{
    QList<QListWidgetItem *> ql = ui->listWidget_PLAN_PlatosSelec->selectedItems();

    if(ql.size() == 1)
    {
        foreach(QListWidgetItem * item, ql)
        {
            delete ui->listWidget_PLAN_PlatosSelec->takeItem(ui->listWidget_PLAN_PlatosSelec->row(item));
        }
    }
    else
    {
        QMessageBox::information(this,"Información","Debe seleccionar un elemento de la lista.");
    }
}

