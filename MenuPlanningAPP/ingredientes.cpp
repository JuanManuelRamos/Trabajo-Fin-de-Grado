#include "mainwindowmenuplan.h"
#include "ui_mainwindowmenuplan.h"


/*-------------------------------------------------------------------------*/
/*---------- HABILITACION, DESHABILITACION, BORRADO DE ELEMENTOS ----------*/
/*-------------------------------------------------------------------------*/

void MainWindowMenuPlan::enableGCIngredientesButtons()      //habilitar los botones Guardar y Cancelar del apartado Ingredientes
{
    ui->pushButton_Guardar->setEnabled(true);
    ui->pushButton_Cancelar->setEnabled(true);
}

void MainWindowMenuPlan::disableGCIngredientesButtons()     //deshabilitar los botones Guardar y Cancelar del apartado Ingredientes
{
    ui->pushButton_Guardar->setEnabled(false);
    ui->pushButton_Cancelar->setEnabled(false);
}

/*---------------------------------------------------------------------------------------------------------------------*/

void MainWindowMenuPlan::enableAMEIngredientesButtons()     //habilitar los botones Añadir, Modificar y Eliminar del apartado Ingredientes
{
    ui->pushButton_Aniadir->setEnabled(true);
    ui->pushButton_Modificar->setEnabled(true);
    ui->pushButton_Eliminar->setEnabled(true);
}

void MainWindowMenuPlan::disableAMEIngredientesButtons()    //deshabilitar los botones Añadir, Modificar y Eliminar del apartado Ingredientes
{
    ui->pushButton_Aniadir->setEnabled(false);
    ui->pushButton_Modificar->setEnabled(false);
    ui->pushButton_Eliminar->setEnabled(false);
}

/*---------------------------------------------------------------------------------------------------------------------*/

void MainWindowMenuPlan::enableIngredientesTextBox()        //habilitar los textbox (linedit) y ceckbox del apartado Ingredientes
{
    QList<QLineEdit *> alltextbox = ui->groupBox_INGalimento->findChildren<QLineEdit *>();

    for(int i = 0; i < alltextbox.size(); i++)
    {
        alltextbox.at(i)->setEnabled(true);
    }

    QList<QCheckBox *> allcheckbox = ui->groupBox_INGalimento->findChildren<QCheckBox *>();     //habilita todos los checkbox
    for(int i = 0; i < allcheckbox.size(); i++)
        allcheckbox.at(i)->setEnabled(true);

    ui->comboBox_ING_GrupoAl->setEnabled(true);
}

void MainWindowMenuPlan::disableIngredientesTextBox()       //deshabilitar los textbox (linedit) y checkbox del apartado Ingredientes
{
    QList<QLineEdit *> alltextbox = ui->groupBox_INGalimento->findChildren<QLineEdit *>();

    for(int i = 0; i < alltextbox.size(); i++)
    {
        alltextbox.at(i)->setEnabled(false);
    }

    QList<QCheckBox *> allcheckbox = ui->groupBox_INGalimento->findChildren<QCheckBox *>();     //deshabilita todos los checkbox
    for(int i = 0; i < allcheckbox.size(); i++)
        allcheckbox.at(i)->setEnabled(false);

    ui->comboBox_ING_GrupoAl->setEnabled(false);
}

/*---------------------------------------------------------------------------------------------------------------------*/

void MainWindowMenuPlan::clearIngredientesTextBox()         //Deja en blanco todos los textbox del apartado Ingredientes
{
    QList<QLineEdit *> alltextbox = ui->groupBox_INGalimento->findChildren<QLineEdit *>();

    for(int i = 0; i < alltextbox.size(); i++)
        alltextbox.at(i)->setText("");

    ui->label_INGid->setText("");

    QList<QCheckBox *> allcheckbox = ui->groupBox_INGalimento->findChildren<QCheckBox *>();     //limpia todos los checkbox
    for(int i = 0; i < allcheckbox.size(); i++)
        allcheckbox.at(i)->setChecked(false);
}

void MainWindowMenuPlan::cleanListViewING()                 //Se borra el listview con los ingredientes mostrados en el apartado Ingredientes
{
    QStringListModel *model = new QStringListModel();
    model->removeRows(0, model->rowCount());
    ui->listView_Ingredientes->setModel(model);
    delete model;
}



/*-------------------------------------------------------------------------*/
/*----------------------- EVENTOS CLICK DE BOTONES ------------------------*/
/*-------------------------------------------------------------------------*/

/*--------------------------------------------------- AME (AÑADIR, MODIFICAR, ELIMINAR) INGREDIENTES ------------------------------------------------------------*/

void MainWindowMenuPlan::on_pushButton_Aniadir_clicked()
{
    disableAMEIngredientesButtons();                                            //deshabilitar botones AME
    enableGCIngredientesButtons();                                              //habilitar botones GC
    clearIngredientesTextBox();                                                 //Limpiar textbox
    enableIngredientesTextBox();                                                //habilitar textbox
    ui->listView_Ingredientes->setEnabled(false);

    Q = ANIADIRING;
    ui->label_InfoQuerys->setText("<html><head/><body><p><span style=\" font-weight:600; color:#0055ff;\">ADVERTENCIA: El campo </span><span style=\" font-weight:600; font-style:italic; color:#0055ff;\">&quot;Nombre&quot;</span><span style=\" font-weight:600; color:#0055ff;\"> es obligatorio. Si se deja cualquier otro campo vacío se rellenará con 0 por defecto.</span></p><p><span style=\" font-weight:600; color:#0055ff;\">Todos los campos, excepto </span><span style=\" font-weight:600; font-style:italic; color:#0055ff;\">&quot;Nombre&quot;</span><span style=\" font-weight:600; color:#0055ff;\">, son numéricos. El símbolo de la coma para los decimales es </span><span style=\" font-weight:600; font-style:italic; color:#0055ff;\">&quot;.&quot;</span><span style=\" font-weight:600; color:#0055ff;\">.</span></p></body></html>");
}

void MainWindowMenuPlan::on_pushButton_Modificar_clicked()
{
    ACTION A = controllSelectionElement(*ui->listView_Ingredientes);            //Comprueba si hay un ingrediente seleccionado

    if(A == ACCEPT)
    {
        disableAMEIngredientesButtons();                                        //deshabilitar botones AME
        enableGCIngredientesButtons();                                          //habilitar botones GC
        enableIngredientesTextBox();                                            //habilitar textbox
        ui->listView_Ingredientes->setEnabled(false);

        Q = MODIFICARING;
        ui->label_InfoQuerys->setText("<html><head/><body><p><span style=\" font-weight:600; color:#0055ff;\">ADVERTENCIA: El campo </span><span style=\" font-weight:600; font-style:italic; color:#0055ff;\">&quot;Nombre&quot;</span><span style=\" font-weight:600; color:#0055ff;\"> es obligatorio. Si se deja cualquier otro campo vacío se rellenará con 0 por defecto.</span></p><p><span style=\" font-weight:600; color:#0055ff;\">Todos los campos, excepto </span><span style=\" font-weight:600; font-style:italic; color:#0055ff;\">&quot;Nombre&quot;</span><span style=\" font-weight:600; color:#0055ff;\">, son numéricos. El símbolo de la coma para los decimales es </span><span style=\" font-weight:600; font-style:italic; color:#0055ff;\">&quot;.&quot;</span><span style=\" font-weight:600; color:#0055ff;\">.</span></p></body></html>");
    }
}

void MainWindowMenuPlan::on_pushButton_Eliminar_clicked()
{
    ACTION A = controllSelectionElement(*ui->listView_Ingredientes);            //Comprueba si hay un ingrediente seleccionado

    if(A == ACCEPT)
    {
        QMessageBox msgBox;                                                     //Mensaje de confirmacion
        msgBox.setIcon(QMessageBox::Warning);
        msgBox.setText("Un ingrediente va a ser eliminado.");
        msgBox.setInformativeText("¿Está seguro de que quiere eliminar este ingrediente de forma permanente?");
        QAbstractButton *myYesButton = msgBox.addButton(trUtf8("Sí"), QMessageBox::YesRole);
        msgBox.setStandardButtons(QMessageBox::No);
        msgBox.setDefaultButton(QMessageBox::No);
        msgBox.exec();

        if(msgBox.clickedButton() == myYesButton)
        {
            db1->queryEliminarIngrediente(ui->label_INGid->text());                         //Consulta de eliminacion de ingrediente
            ui->listView_Ingredientes->setModel(db1->makeQuerys(MOSTRARING));               //Consulta para mostrar los ingredientes
            ui->listView_Ingredientes_PLA->setModel(ui->listView_Ingredientes->model());    //Mostrar los ingredientes actualizados en el listview de ingredientes en el apartado platos
            clearIngredientesTextBox();                                                     //Limpiar los textbox
        }
    }
}

/*-------------------------------------------------- GC (GUARDAR, CANCELAR) INGREDIENTES ------------------------------------------------------------*/

void MainWindowMenuPlan::on_pushButton_Guardar_clicked()
{
    enableAMEIngredientesButtons();                                                                             //habilitar los botones AME
    disableGCIngredientesButtons();                                                                             //deshabilitar los botones GC
    disableIngredientesTextBox();                                                                               //deshabilitar los textbox
    ACTION A = controllDataTextBoxName(*ui->lineEdit_INGnombre);                                                //Comprobar si el nombre es correcto
    ACTION B = controllDataTextBoxNum(*ui->groupBox_INGalimento, 1);                                            //Comprobar si los textbox numericos son correctos
    ACTION C = db1->controllQuerys(Q, INGREDIENTES, ui->lineEdit_INGnombre->text(), ui->label_INGid->text());   //Controlar que no se inserte un nuevo ingrediente ya existente

    if(A == ACCEPT && B == ACCEPT && C == ACCEPT)
    {
        if(Q == MODIFICARING)
            db1->modINGQuerys(captureTextBoxText(INGREDIENTES));                                //Consulta para modificar ingredientes

        else if(Q == ANIADIRING)
            db1->addINGQuerys(captureTextBoxText(INGREDIENTES));                                //Consulta para añadir ingrediente

        ui->listView_Ingredientes->setModel(db1->makeQuerys(MOSTRARING));                       //Consulta para mostrar ingredientes
        ui->listView_Ingredientes_PLA->setModel(ui->listView_Ingredientes->model());            //Mostrar los ingredientes actualizados en el listview de ingredientes en el apartado platos
    }

    clearIngredientesTextBox();                                 //Limpiar textbox
    ui->label_InfoQuerys->setText("");                          //Label informativo
    ui->listView_Ingredientes->clearSelection();                //Desselecciona el posible ingrediente seleccionado en el listview
    ui->listView_Ingredientes->setEnabled(true);
}

void MainWindowMenuPlan::on_pushButton_Cancelar_clicked()
{
    enableAMEIngredientesButtons();                             //habilita los botones AME
    disableGCIngredientesButtons();                             //deshabilita los botones GC
    disableIngredientesTextBox();                               //deshabilita los textbox
    clearIngredientesTextBox();                                 //limpia los textbox

    ui->label_InfoQuerys->setText("");                          //borra el label informativo
    ui->listView_Ingredientes->clearSelection();                //Desselecciona el posible ingrediente seleccionado en el listview
    ui->listView_Ingredientes->setEnabled(true);
}



/*---------------------------------------------- CHECKBOX MARCAR O DESMARCAR TODOS MESES DE TEMPORADA ------------------------------------------------------------*/

void MainWindowMenuPlan::checkboxClicked()
{
    QList<QCheckBox *> allcheckbox = ui->scrollArea_temporada->findChildren<QCheckBox *>();     //Se guarda en un QList todos los checkbox existentes

    //Al hacer click en el checkbox se cambia el estado antes de llegar a esta parte del codigo. Por lo que si el estado es checkeado, se chekean todos.
    //Si el estado es no checkeado, se descheckean todos.

    if(check->isChecked())
    {
        for(int i = 0; i < allcheckbox.size(); i++)
        {
            allcheckbox.at(i)->setChecked(true);
        }
    }
    else
    {
        for(int i = 0; i < allcheckbox.size(); i++)
        {
            allcheckbox.at(i)->setChecked(false);
        }
    }
}


/*-------------------------------------------------------------------------*/
/*---------- EVENTO CLICK DE LISTVIEW  DEL APARTADO INGREDIENTES ----------*/
/*-------------------------------------------------------------------------*/

void MainWindowMenuPlan::on_listView_Ingredientes_clicked(const QModelIndex &index)
{
    QString str = index.data(Qt::DisplayRole).toString();           //Elemento del listview al que se ha hecho click
    QSqlQueryModel *model = db1->makeQuerys(MOSTRARINFOING, str);   //Consulta para mostrar los datos del ingrediente seleccionado

    fillIngPlaTextBox(model, INGREDIENTES);                         //Rellenar los textbox con la informacion del ingrediente

    delete model;
}



/*-------------------------------------------------------------------------------------------------*/
/*------------ RELLENA EL ARRAY mesesTemporada SEGUN LA TEMPORADA DE UN INGREDIENTE ---------------*/
/*-------------------------------------------------------------------------------------------------*/
QString MainWindowMenuPlan::set_mesesTemporada()
{
    QList<QCheckBox *> allcheckbox = ui->scrollArea_temporada->findChildren<QCheckBox *>();     //Se guarda en un QList todos los checkbox existentes

    for(int i = 0; i < NumMesesTemp; i++)           //Se rellena el array con 0 y 1 dependiendo de si el checkbox esta marcado o no
    {
        if(allcheckbox.at(1+i)->isChecked())
        {
            mesesTemporada[i] = '1';
        }
        else
        {
           mesesTemporada[i] = '0';
        }
    }
    QString str;
    for(int i = 0; i < NumMesesTemp; i++)           //Se convierte el array en un string
        str.append(mesesTemporada[i]);

    return str;
}

/*-------------------------------------------------------------------------------------------------*/
/*---- RELLENA EL ARRAY ary_incomp SEGUN LAS INCOMPATIBILIDADES ALIMENTICIAS DE UN INGREDIENTE ----*/
/*-------------------------------------------------------------------------------------------------*/
QString MainWindowMenuPlan::set_Incompatibilidades()
{
    QList<QCheckBox *> allcheckbox = ui->groupBox_incompatibilidades->findChildren<QCheckBox *>();     //Se guarda en un QList todos los checkbox existentes

    for(int i = 0; i < NumIncomp; i++)              //Se rellena el array con 0 y 1 dependiendo de si el checkbox esta marcado o no
    {
        if(allcheckbox.at(i)->isChecked())
        {
            ary_incomp[i] = '1';
        }
        else
        {
           ary_incomp[i] = '0';
        }
    }
    QString str;                                    //Se convierte el array en un string
    for(int i = 0; i < NumIncomp; i++)
        str.append(ary_incomp[i]);

    return str;
}

/*-------------------------------------------------------------------------------------------------*/
/*------------ RELLENA EL ARRAY ary_alergenos SEGUN LOS ALERGENOS DE UN INGREDIENTE ---------------*/
/*-------------------------------------------------------------------------------------------------*/
QString MainWindowMenuPlan::set_Alergenos()
{
    QList<QCheckBox *> allcheckbox = ui->groupBox_alergenos->findChildren<QCheckBox *>();     //Se guarda en un QList todos los checkbox existentes

    for(int i = 0; i < NumAlergenos; i++)           //Se rellena el array con 0 y 1 dependiendo de si el checkbox esta marcado o no
    {
        if(allcheckbox.at(i)->isChecked())
        {
            ary_alergenos[i] = '1';
        }
        else
        {
           ary_alergenos[i] = '0';
        }
    }
    QString str;                                    //Se convierte el array en un string
    for(int i = 0; i < NumAlergenos; i++)
        str.append(ary_alergenos[i]);

    return str;
}



/*-------------------------------------------------------------------------------------------------*/
/*----------------- MUESTRA LOS CHECKBOX SEGUN LA TEMPORADA DE UN INGREDIENTE ---------------------*/
/*-------------------------------------------------------------------------------------------------*/
void MainWindowMenuPlan::mostrar_mesesTemporada(QString meses)
{
    QList<QCheckBox *> allcheckbox = ui->scrollArea_temporada->findChildren<QCheckBox *>();     //Se guarda en un QList todos los checkbox existentes
    allcheckbox.at(0)->setChecked(false);

    for(int i = 0; i < meses.size(); i++)         //Empieza en 1 para saltarse el checkbox de marcar/desmarcar todos
    {
        if(meses.at(i) == '1')
        {
            allcheckbox.at(1+i)->setChecked(true);
        }
        else
        {
            allcheckbox.at(1+i)->setChecked(false);
        }
    }
}


/*-------------------------------------------------------------------------------------------------*/
/*--------- MUESTRA LOS CHECKBOX SEGUN LAS INCOMPATIBILIDADES ALIMENTICIAS Y ALERGENOS ------------*/
/*-------------------------------------------------------------------------------------------------*/
void MainWindowMenuPlan::mostrar_alergenosIncom(CHECKBOX CB, QString array)
{
    QList<QCheckBox *> allcheckbox;

    switch(CB)                          //Se comprueban los checkcobx a mostrar
    {
        case INCOMPATIBILIDADES:
            allcheckbox = ui->groupBox_incompatibilidades->findChildren<QCheckBox *>();      
        break;

        case ALERGENOS:
            allcheckbox = ui->groupBox_alergenos->findChildren<QCheckBox *>();
        break;
    }

    for(int i = 0; i < array.size(); i++)
    {
        if(array.at(i) == '1')
        {
            allcheckbox.at(i)->setChecked(true);
        }
        else
        {
            allcheckbox.at(i)->setChecked(false);
        }
    }
}



/*---------------------------------------------------------------------*/
/*--------- COMPRUEBA SI EL PLATO ES INGREDIENTE PRINCIPAL ------------*/
/*---------------------------------------------------------------------*/
QString MainWindowMenuPlan::set_IngredientePrincipal()
{
    if(ui->checkBox_ING_ingredientePrinc->isChecked())
        return "1";
    else
        return "0";
}

void MainWindowMenuPlan::mostrar_IngredientePrincipal(QString str)
{
    if(str == "1")
        ui->checkBox_ING_ingredientePrinc->setChecked(true);
    else
        ui->checkBox_ING_ingredientePrinc->setChecked(false);
}


/*-------------------------------------------------------------------------------------*/
/*--------- COMPRUEBA EL GRUPO ALIMENTICIO AL QUE PERTENECE EL INGREDIENTE ------------*/
/*-------------------------------------------------------------------------------------*/
QString MainWindowMenuPlan::set_GrupoAlimenticio()
{
    /* 0 Otros, 1 Carne, 2 Cereal, 3 Fruta, 4 Legumbre, 5 Marisco, 6 Pasta, 7 Pescado, 8 Verdura */
    return QString::number(ui->comboBox_ING_GrupoAl->currentIndex());
}


void MainWindowMenuPlan::mostrar_GrupoAlimenticio(QString grp)
{
    ui->comboBox_ING_GrupoAl->setCurrentIndex(grp.toInt());
}
