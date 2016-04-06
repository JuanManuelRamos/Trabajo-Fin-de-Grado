#include "mainwindowmenuplan.h"
#include "ui_mainwindowmenuplan.h"



/*-----------------------------------------------------------------*/
/*------ HABILITAR LOS BOTONES DE LA SECCION PLANIFICADOR ---------*/
/*-----------------------------------------------------------------*/
void MainWindowMenuPlan::enablePLANElements()
{
    ui->pushButton_PLAN_der->setEnabled(true);
    ui->pushButton_PLAN_der2->setEnabled(true);
    ui->pushButton_PLAN_izq->setEnabled(true);
    ui->pushButton_PLAN_izq2->setEnabled(true);
}


/*-----------------------------------------------------------------*/
/*------ DESHABILITAR LOS BOTONES DE LA SECCION PLANIFICADOR ------*/
/*-----------------------------------------------------------------*/
void MainWindowMenuPlan::disablePLANElements()
{
    ui->pushButton_PLAN_der->setEnabled(false);
    ui->pushButton_PLAN_der2->setEnabled(false);
    ui->pushButton_PLAN_izq->setEnabled(false);
    ui->pushButton_PLAN_izq2->setEnabled(false);
    ui->label_PLAN_PlatosTotal->setText("");
    ui->label_PLAN_PP->setText("");
    ui->label_PLAN_SP->setText("");
    ui->label_PLAN_P->setText("");
}



/*-----------------------------------------------------------------*/
/*------------------ EVENTO CLICK DE BOTON > ----------------------*/
/*-----------------------------------------------------------------*/
void MainWindowMenuPlan::on_pushButton_PLAN_der_clicked()
{
    ACTION A = controllSelectionElement(*ui->listView_PLAN_Platos);                  //Comprueba si hay un plato seleccionado


    if(A == ACCEPT)
    {
        for(int i = 0; i < ui->listWidget_PLAN_PlatosSelec->model()->rowCount(); i++)       //Comprobar que no se añade dos veces el mismo plato
        {
            if(ui->listView_PLAN_Platos->currentIndex().data(Qt::DisplayRole).toString() == ui->listWidget_PLAN_PlatosSelec->model()->index(i, 0).data(Qt::DisplayRole).toString())
            {
                QMessageBox::information(this,"Información","El plato seleccionado ya ha sido previamente añadido a la lista.");
                A = DENY;
                break;
            }
        }

        if(A == ACCEPT)
            ui->listWidget_PLAN_PlatosSelec->addItem(ui->listView_PLAN_Platos->currentIndex().data(Qt::DisplayRole).toString());    //Añadir el elemento del listview platos al listwidget platos seleccionados
    }
}


/*-----------------------------------------------------------------*/
/*------------------ EVENTO CLICK DE BOTON >> ---------------------*/
/*-----------------------------------------------------------------*/
void MainWindowMenuPlan::on_pushButton_PLAN_der2_clicked()
{
    ui->listWidget_PLAN_PlatosSelec->clear();                           //Borrar todos los elementos del listwidget

    for(int i = 0; i < ui->listView_PLAN_Platos->model()->rowCount(); i++)
    {
        ui->listWidget_PLAN_PlatosSelec->addItem(ui->listView_PLAN_Platos->model()->index(i, 0).data(Qt::DisplayRole).toString());  //Seleccionar uno a uno los platos del listview y añadirlos al listwidget
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


/*-----------------------------------------------------------------*/
/*------------------ EVENTO CLICK DE BOTON << ---------------------*/
/*-----------------------------------------------------------------*/
void MainWindowMenuPlan::on_pushButton_PLAN_izq2_clicked()
{
    ui->listWidget_PLAN_PlatosSelec->clear();                           //Borrar todos los elementos del listwidget
}



/*-----------------------------------------------------------------*/
/*--------------- INFORMACION DE NUMERO DE PLATOS -----------------*/
/*-----------------------------------------------------------------*/
void MainWindowMenuPlan::infoPLANPlatos()
{
    ui->label_PLAN_PlatosTotal->setText(db1->queryNumPlatos());
    ui->label_PLAN_PP->setText(db1->queryNumPriPlato());
    ui->label_PLAN_SP->setText(db1->queryNumSegPlato());
    ui->label_PLAN_P->setText(db1->queryNumPostre());
}




