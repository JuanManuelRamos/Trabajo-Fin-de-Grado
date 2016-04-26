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
    ui->calendarWidget->setEnabled(true);
    ui->radioButton_PLAN_desde->setEnabled(true);
    ui->radioButton_PLAN_hasta->setEnabled(true);
    ui->dateEdit_desde->setEnabled(true);
    ui->dateEdit_hasta->setEnabled(true);
    ui->pushButton_PLAN_Modificar->setEnabled(true);
    ui->pushButton_PLAN_GenerarPlan->setEnabled(true);

    QList<QCheckBox *> allcheckbox = ui->tabWidget_PLAN_alerg_incomp->findChildren<QCheckBox *>();     //habilita todos los checkbox
    for(int i = 0; i < allcheckbox.size(); i++)
        allcheckbox.at(i)->setEnabled(true);
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
    disablePLANLabelsSelec();
    ui->calendarWidget->setEnabled(false);
    ui->radioButton_PLAN_desde->setEnabled(false);
    ui->radioButton_PLAN_hasta->setEnabled(false);
    ui->dateEdit_desde->setEnabled(false);
    ui->dateEdit_hasta->setEnabled(false);
    ui->pushButton_PLAN_Modificar->setEnabled(false);
    ui->pushButton_PLAN_GenerarPlan->setEnabled(false);

    QList<QCheckBox *> allcheckbox = ui->tabWidget_PLAN_alerg_incomp->findChildren<QCheckBox *>();     //habilita todos los checkbox
    for(int i = 0; i < allcheckbox.size(); i++)
        allcheckbox.at(i)->setEnabled(false);
}


/*-----------------------------------------------------------------*/
/*-------- DESHABILITAR LOS LABELS DE PLATOS SELECCIONADOS --------*/
/*-----------------------------------------------------------------*/
void MainWindowMenuPlan::disablePLANLabelsSelec()
{
    ui->label_PLAN_PlatosSel->setText("0");
    ui->label_PLAN_PP_2->setText("0");
    ui->label_PLAN_SP_2->setText("0");
    ui->label_PLAN_P_2->setText("0");
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
        {
            ui->listWidget_PLAN_PlatosSelec->addItem(ui->listView_PLAN_Platos->currentIndex().data(Qt::DisplayRole).toString());    //Añadir el elemento del listview platos al listwidget platos seleccionados
            infoPLANPlatosSelec();                                                                                                  //Actualiza la informacion de platos seleccionados
        }
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
    infoPLANPlatosSelec();                                                                                                          //Actualiza la informacion de platos seleccionados
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
            delete ui->listWidget_PLAN_PlatosSelec->takeItem(ui->listWidget_PLAN_PlatosSelec->row(item));       //Elimina de la lista el plato seleccionado
        }
        infoPLANPlatosSelec();                                                                                  //Actualiza la informacion de platos seleccionados
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
    disablePLANLabelsSelec();                                           //Borra los labels de platos seleccionados
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


/*-----------------------------------------------------------------*/
/*------- INFORMACION DE NUMERO DE PLATOS SELECCIONADOS -----------*/
/*-----------------------------------------------------------------*/
void MainWindowMenuPlan::infoPLANPlatosSelec()
{
    int pp = 0, sp = 0, p = 0, tipo = 0;
    int rows = ui->listWidget_PLAN_PlatosSelec->model()->rowCount();

    ui->label_PLAN_PlatosSel->setText(QString::number(rows));

    for(int i = 0; i < rows; i++)
    {
        tipo = db1->queryMostrarTipoPlatoNombre(ui->listWidget_PLAN_PlatosSelec->model()->index(i, 0).data(Qt::DisplayRole).toString()).toInt();

        switch(tipo)
        {
            case 1:
                pp++;
            break;

            case 2:
                sp++;
            break;

            case 3:
                p++;
            break;
        }
    }

    ui->label_PLAN_PP_2->setText(QString::number(pp));
    ui->label_PLAN_SP_2->setText(QString::number(sp));
    ui->label_PLAN_P_2->setText(QString::number(p));
}


/*-----------------------------------------------------------------*/
/*------------- EVENTO CLICK DEL RADIOBUTTON DESDE ----------------*/
/*-----------------------------------------------------------------*/
void MainWindowMenuPlan::on_radioButton_PLAN_desde_clicked()
{
   if(ui->radioButton_PLAN_desde->isChecked())
       ui->radioButton_PLAN_hasta->setChecked(false);
   else
      ui->radioButton_PLAN_desde->setChecked(true);
}


/*-----------------------------------------------------------------*/
/*-------------- EVENTO CLICK DEL RADIOBUTTON HASTA ---------------*/
/*-----------------------------------------------------------------*/
void MainWindowMenuPlan::on_radioButton_PLAN_hasta_clicked()
{
    if(ui->radioButton_PLAN_hasta->isChecked())
        ui->radioButton_PLAN_desde->setChecked(false);
    else
        ui->radioButton_PLAN_hasta->setChecked(true);
}


/*-----------------------------------------------------------------*/
/*------------------ EVENTO CLICK DEL CALENDARIO ------------------*/
/*-----------------------------------------------------------------*/
void MainWindowMenuPlan::on_calendarWidget_clicked(const QDate &date)
{
    if(ui->radioButton_PLAN_desde->isChecked())
        ui->dateEdit_desde->setDate(date);
    else if(ui->radioButton_PLAN_hasta->isChecked())
        if(date > ui->dateEdit_desde->date())
            ui->dateEdit_hasta->setDate(date);
        else
            QMessageBox::information(this,"Información","La fecha de finalización del plan no puede ser anterior a la de inicio.");
}



/*-----------------------------------------------------------------*/
/*------------ MUESTRA LA INGESTA DIARIA RECOMENDADA --------------*/
/*-----------------------------------------------------------------*/
void MainWindowMenuPlan::getIngestaDiariaRecomendada()
{
    ui->lineEdit_PLAN_acidofol->setText(QString::number(idrN.acidoFol));
    ui->lineEdit_PLAN_calcio->setText(QString::number(idrN.calcio));
    ui->lineEdit_PLAN_energia->setText(QString::number(idrN.energia));
    ui->lineEdit_PLAN_fosforo->setText(QString::number(idrN.fosforo));
    ui->lineEdit_PLAN_grasa->setText(QString::number(idrN.grasa));
    ui->lineEdit_PLAN_hierro->setText(QString::number(idrN.hierro));
    ui->lineEdit_PLAN_magnesio->setText(QString::number(idrN.magnesio));
    ui->lineEdit_PLAN_potasio->setText(QString::number(idrN.potasio));
    ui->lineEdit_PLAN_proteinas->setText(QString::number(idrN.proteinas));
    ui->lineEdit_PLAN_selenio->setText(QString::number(idrN.selenio));
    ui->lineEdit_PLAN_sodio->setText(QString::number(idrN.sodio));
    ui->lineEdit_PLAN_vita->setText(QString::number(idrN.vitA));
    ui->lineEdit_PLAN_vitb1->setText(QString::number(idrN.vitB1));
    ui->lineEdit_PLAN_vitb2->setText(QString::number(idrN.vitB2));
    ui->lineEdit_PLAN_vitb6->setText(QString::number(idrN.vitB6));
    ui->lineEdit_PLAN_vitb12->setText(QString::number(idrN.vitB12));
    ui->lineEdit_PLAN_vitc->setText(QString::number(idrN.vitC));
    ui->lineEdit_PLAN_vitd->setText(QString::number(idrN.vitD));
    ui->lineEdit_PLAN_vite->setText(QString::number(idrN.vitE));
    ui->lineEdit_PLAN_yodo->setText(QString::number(idrN.yodo));
    ui->lineEdit_PLAN_zinc->setText(QString::number(idrN.zinc));
}


/*-----------------------------------------------------------------*/
/*------------ MODIFICA LA INGESTA DIARIA RECOMENDADA -------------*/
/*-----------------------------------------------------------------*/
void MainWindowMenuPlan::setIngestaDiariaRecomendada()
{
    ACTION A = controllDataTextBoxNum(*ui->groupBox_PLAN_idr, 0);

    if(A == ACCEPT)
    {
        idrN.acidoFol = ui->lineEdit_PLAN_acidofol->text().toFloat();
        idrN.calcio = ui->lineEdit_PLAN_calcio->text().toFloat();
        idrN.energia = ui->lineEdit_PLAN_energia->text().toFloat();
        idrN.fosforo = ui->lineEdit_PLAN_fosforo->text().toFloat();
        idrN.grasa = ui->lineEdit_PLAN_grasa->text().toFloat();
        idrN.hierro =  ui->lineEdit_PLAN_hierro->text().toFloat();
        idrN.magnesio = ui->lineEdit_PLAN_magnesio->text().toFloat();
        idrN.potasio = ui->lineEdit_PLAN_potasio->text().toFloat();
        idrN.proteinas = ui->lineEdit_PLAN_proteinas->text().toFloat();
        idrN.selenio = ui->lineEdit_PLAN_selenio->text().toFloat();
        idrN.sodio = ui->lineEdit_PLAN_sodio->text().toFloat();
        idrN.vitA = ui->lineEdit_PLAN_vita->text().toFloat();
        idrN.vitB1 = ui->lineEdit_PLAN_vitb1->text().toFloat();
        idrN.vitB2 = ui->lineEdit_PLAN_vitb2->text().toFloat();
        idrN.vitB6 = ui->lineEdit_PLAN_vitb6->text().toFloat();
        idrN.vitB12 = ui->lineEdit_PLAN_vitb12->text().toFloat();
        idrN.vitC = ui->lineEdit_PLAN_vitc->text().toFloat();
        idrN.vitD = ui->lineEdit_PLAN_vitd->text().toFloat();
        idrN.vitE = ui->lineEdit_PLAN_vite->text().toFloat();
        idrN.yodo = ui->lineEdit_PLAN_yodo->text().toFloat();
        idrN.zinc = ui->lineEdit_PLAN_zinc->text().toFloat();
    }
}


/*-----------------------------------------------------------------*/
/*------ HABILITAR LOS TEXTBOX DE INGESTA DIARIA RECOMENDADA ------*/
/*-----------------------------------------------------------------*/
void MainWindowMenuPlan::enableIDR()
{
    QList<QLineEdit *> alltextbox = ui->groupBox_PLAN_idr->findChildren<QLineEdit *>();

    for(int i = 0; i < alltextbox.size(); i++)
        alltextbox.at(i)->setEnabled(true);

    ui->pushButton_PLAN_Cancelar->setEnabled(true);
    ui->pushButton_PLAN_Guardar->setEnabled(true);
}


/*-----------------------------------------------------------------*/
/*---- DESHABILITAR LOS TEXTBOX DE INGESTA DIARIA RECOMENDADA -----*/
/*-----------------------------------------------------------------*/
void MainWindowMenuPlan::disableIDR()
{
    QList<QLineEdit *> alltextbox = ui->groupBox_PLAN_idr->findChildren<QLineEdit *>();

    for(int i = 0; i < alltextbox.size(); i++)
        alltextbox.at(i)->setEnabled(false);

    ui->pushButton_PLAN_Cancelar->setEnabled(false);
    ui->pushButton_PLAN_Guardar->setEnabled(false);
}


/*-----------------------------------------------------------------*/
/*--------------- EVENTO CLICK DEL BOTON MODIFICAR ----------------*/
/*-----------------------------------------------------------------*/
void MainWindowMenuPlan::on_pushButton_PLAN_Modificar_clicked()
{
    enableIDR();
    ui->pushButton_PLAN_Modificar->setEnabled(false);
}


/*-----------------------------------------------------------------*/
/*--------------- EVENTO CLICK DEL BOTON GUARDAR ------------------*/
/*-----------------------------------------------------------------*/
void MainWindowMenuPlan::on_pushButton_PLAN_Guardar_clicked()
{
    setIngestaDiariaRecomendada();
    getIngestaDiariaRecomendada();
    disableIDR();
    ui->pushButton_PLAN_Modificar->setEnabled(true);
}


/*-----------------------------------------------------------------*/
/*--------------- EVENTO CLICK DEL BOTON CANCELAR -----------------*/
/*-----------------------------------------------------------------*/
void MainWindowMenuPlan::on_pushButton_PLAN_Cancelar_clicked()
{
    getIngestaDiariaRecomendada();
    disableIDR();
    ui->pushButton_PLAN_Modificar->setEnabled(true);
}





/*---------------------------------------------------------------------*/
/*--------------- EVENTO CLICK DEL BOTON GENERAR PLAN -----------------*/
/*---------------------------------------------------------------------*/
void MainWindowMenuPlan::on_pushButton_PLAN_GenerarPlan_clicked()
{
    FicheroDeTabla();                                                               //Actualizar el fichero de tabla de platos
}
