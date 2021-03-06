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
    ui->lineEdit_PLAN_acidofol->setText(QString::number(idrN[0]));
    ui->lineEdit_PLAN_calcio->setText(QString::number(idrN[1]));
    ui->lineEdit_PLAN_energia->setText(QString::number(idrN[2]));
    ui->lineEdit_PLAN_fosforo->setText(QString::number(idrN[3]));
    ui->lineEdit_PLAN_grasa->setText(QString::number(idrN[4]));
    ui->lineEdit_PLAN_hierro->setText(QString::number(idrN[5]));
    ui->lineEdit_PLAN_magnesio->setText(QString::number(idrN[6]));
    ui->lineEdit_PLAN_potasio->setText(QString::number(idrN[7]));
    ui->lineEdit_PLAN_proteinas->setText(QString::number(idrN[8]));
    ui->lineEdit_PLAN_selenio->setText(QString::number(idrN[9]));
    ui->lineEdit_PLAN_sodio->setText(QString::number(idrN[10]));
    ui->lineEdit_PLAN_vita->setText(QString::number(idrN[11]));
    ui->lineEdit_PLAN_vitb1->setText(QString::number(idrN[12]));
    ui->lineEdit_PLAN_vitb2->setText(QString::number(idrN[13]));
    ui->lineEdit_PLAN_vitb6->setText(QString::number(idrN[14]));
    ui->lineEdit_PLAN_vitb12->setText(QString::number(idrN[15]));
    ui->lineEdit_PLAN_vitc->setText(QString::number(idrN[16]));
    ui->lineEdit_PLAN_vitd->setText(QString::number(idrN[17]));
    ui->lineEdit_PLAN_vite->setText(QString::number(idrN[18]));
    ui->lineEdit_PLAN_yodo->setText(QString::number(idrN[19]));
    ui->lineEdit_PLAN_zinc->setText(QString::number(idrN[20]));
}


/*-----------------------------------------------------------------*/
/*------------ MODIFICA LA INGESTA DIARIA RECOMENDADA -------------*/
/*-----------------------------------------------------------------*/
void MainWindowMenuPlan::setIngestaDiariaRecomendada()
{
    ACTION A = controllDataTextBoxNum(*ui->groupBox_PLAN_idr, 0);

    if(A == ACCEPT)
    {
        std::fstream fs;
        fs.open("ingestarecomendada.txt", std::fstream::out | std::fstream::trunc);
        fs << ui->lineEdit_PLAN_acidofol->text().toStdString() << "\n";
        fs << ui->lineEdit_PLAN_calcio->text().toStdString() << "\n";
        fs << ui->lineEdit_PLAN_energia->text().toStdString() << "\n";
        fs << ui->lineEdit_PLAN_fosforo->text().toStdString() << "\n";
        fs << ui->lineEdit_PLAN_grasa->text().toStdString() << "\n";
        fs << ui->lineEdit_PLAN_hierro->text().toStdString() << "\n";
        fs << ui->lineEdit_PLAN_magnesio->text().toStdString() << "\n";
        fs << ui->lineEdit_PLAN_potasio->text().toStdString() << "\n";
        fs << ui->lineEdit_PLAN_proteinas->text().toStdString() << "\n";
        fs << ui->lineEdit_PLAN_selenio->text().toStdString() << "\n";
        fs << ui->lineEdit_PLAN_sodio->text().toStdString() << "\n";
        fs << ui->lineEdit_PLAN_vita->text().toStdString() << "\n";
        fs << ui->lineEdit_PLAN_vitb1->text().toStdString() << "\n";
        fs << ui->lineEdit_PLAN_vitb2->text().toStdString() << "\n";
        fs << ui->lineEdit_PLAN_vitb6->text().toStdString() << "\n";
        fs << ui->lineEdit_PLAN_vitb12->text().toStdString() << "\n";
        fs << ui->lineEdit_PLAN_vitc->text().toStdString() << "\n";
        fs << ui->lineEdit_PLAN_vitd->text().toStdString() << "\n";
        fs << ui->lineEdit_PLAN_vite->text().toStdString() << "\n";
        fs << ui->lineEdit_PLAN_yodo->text().toStdString() << "\n";
        fs << ui->lineEdit_PLAN_zinc->text().toStdString() << "\n";
        fs.close();
        resetIngestaDiariaRecomendada();
        getIngestaDiariaRecomendada();
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



/*------------------------------------------------------------------------------------------------------------*/
/*--------------- DEVUELVE EL NUMERO DE DIAS DEL PLAN SEGUN LO ESPECIFICADO EN EL CALENDARIO -----------------*/
/*------------------------------------------------------------------------------------------------------------*/
void MainWindowMenuPlan::setNumDiasPlan()
{
    int nDias = ui->dateEdit_desde->date().daysTo(ui->dateEdit_hasta->date())+1;
    numDiasPlan = nDias;
    QDate d = ui->dateEdit_desde->date();

    for(int i = 0; i < nDias; i++)
    {
        if(d.dayOfWeek() == 6 || d.dayOfWeek() == 7)
            numDiasPlan--;

        d = d.addDays(1);
    }
}


/*------------------------------------------------------------------------------------------------------------------------*/
/*--------------- EDITA LOS DATOS DE INGESTIA DIARIA RECOMENDADA ADAPTANDOLOS AL NUMERO DE DIAS DEL PLAN -----------------*/
/*------------------------------------------------------------------------------------------------------------------------*/
void MainWindowMenuPlan::setIngestaDiariaRecomendadaPorDias()
{
    for(int i = 0; i < idrN.size(); i++)
        idrN[i] *= (float)numDiasPlan;
    set_irnMinMax();
}


/*---------------------------------------------------------------------------------------------------*/
/*--------------- ESTABLECER LOS VALORES DE NUTRIENTES MINIMOS Y MAXIMOS EN EL PLAN -----------------*/
/*---------------------------------------------------------------------------------------------------*/
void MainWindowMenuPlan::set_irnMinMax()
{
    for(int i = 0; i < idrN.size(); i++)
    {
        irnMinMax[i].first = idrN[i]-(idrN[i]/(float)1.5);
        irnMinMax[i].second = idrN[i]*2;
    }
}


/*---------------------------------------------------------------------*/
/*--------------- EVENTO CLICK DEL BOTON GENERAR PLAN -----------------*/
/*---------------------------------------------------------------------*/
void MainWindowMenuPlan::on_pushButton_PLAN_GenerarPlan_clicked()
{
    ui->pushButton_PLAN_GenerarPlan->setEnabled(false);
    ui->label_generarPlan->setText("Generando plan alimenticio. Espere...");
    ui->listWidget_PLAND_Recomendados->clear();
    ui->tableWidget_PLAND_Recomendados->clear();
    ui->tableWidget_PLAND_Especiales->clear();
    qApp->processEvents();

    setNumDiasPlan();                                               //Calculo del numero de dias del plan alimenticio

    if(ui->label_PLAN_PP_2->text() == "0")
        QMessageBox::information(this,"Información","Debe seleccionar al menos un primer plato.");
    else if (ui->label_PLAN_SP_2->text() == "0")
        QMessageBox::information(this,"Información","Debe seleccionar al menos un segundo plato.");
    else if(ui->label_PLAN_P_2->text() == "0")
        QMessageBox::information(this,"Información","Debe seleccionar al menos un postre.");
    else if(numDiasPlan <= 0)
        QMessageBox::information(this,"Información","El numero de días debe ser superior a 0 (sábados y domingos excluidos).");
    else
    {
        setPlatos();                                                //Actualiza las tres listas correspondientes a los tres tipos de platos
        setVectorGruposAlimenticios();                              //Genera el vector de grupos alimenticios
		ficheroDeTablaNuevo();

        numDiasPlan = 15;
        ejecuciones = 1;

        resetIngestaDiariaRecomendada();                            //Se resetea para que se vuelva a los valores anteriores a la modificacion por numero de dias del plan (por si el numero de dias cambia)
        setIngestaDiariaRecomendadaPorDias();                       //Se calculan los valores nutricionales recomendados segun el numero de dias elegido para el plan

        int pm[3] = {5,10,15};
        int pc[3] = {80,90,100};
        int posm = 0, posc = 0;

        for(int j = 0; j < 1; j++)                      //9 archivos
        {
            for(int i = 0; i < ejecuciones; i++)        //50 ejecuciones cada archivo
            {
                probCruce = pc[posc];
                probMutacion = pm[posm];

                nombreAr = "MenuPlanning_";
                nombreAr.append(QString::number(numDiasPlan));
                nombreAr.append("_");
                nombreAr.append(QString::number(NumIndividuos));
                nombreAr.append("_");
                nombreAr.append(QString::number(probMutacion));
                nombreAr.append("_");
                nombreAr.append(QString::number(probCruce));
                nombreAr.append("_");
                nombreAr.append(QString::number(i+1));
                nombreAr.append(".dat");

                outputFile(nombreAr, false, 0, i+1);
                crearPoblacion();                                           //Comienza la creacion de individuos
                set_PlanEspecial();                                         //Creacion de plan especial
            }

            posc++;
            if(posc == 3) {posm++;posc = 0;}
            if(posm >= 3) {posm = 0;}
        }
    }

    ui->pushButton_PLAN_GenerarPlan->setEnabled(true);
    ui->label_generarPlan->setText("");
    QApplication::quit();
}
