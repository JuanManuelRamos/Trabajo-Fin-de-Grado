#include "mainwindowmenuplan.h"
#include "ui_mainwindowmenuplan.h"



/*-------------------------------------------------------------------------*/
/*---------- HABILITACION, DESHABILITACION, BORRADO DE ELEMENTOS ----------*/
/*-------------------------------------------------------------------------*/


void MainWindowMenuPlan::enableGCPlatosButtons()            //habilitar los botones Guardar y Cancelar del apartado Platos
{
    ui->pushButton_Guardar_PLA->setEnabled(true);
    ui->pushButton_Cancelar_PLA->setEnabled(true);
}

void MainWindowMenuPlan::disableGCPlatosButtons()           //deshabilitar los botones Guardar y Cancelar del apartado Platos
{
    ui->pushButton_Guardar_PLA->setEnabled(false);
    ui->pushButton_Cancelar_PLA->setEnabled(false);
}

/*---------------------------------------------------------------------------------------------------------------------*/

void MainWindowMenuPlan::enableAMEPlatosButtons()           //habilitar los botones Añadir, Modificar y Eliminar del apartado Platos
{
    ui->pushButton_Aniadir_PLA->setEnabled(true);
    ui->pushButton_Modificar_PLA->setEnabled(true);
    ui->pushButton_Eliminar_PLA->setEnabled(true);
}

void MainWindowMenuPlan::disableAMEPlatosButtons()          //deshabilitar los botones Añadir, Modificar y Eliminar del apartado Platos
{
    ui->pushButton_Aniadir_PLA->setEnabled(false);
    ui->pushButton_Modificar_PLA->setEnabled(false);
    ui->pushButton_Eliminar_PLA->setEnabled(false);
}

/*---------------------------------------------------------------------------------------------------------------------*/

void MainWindowMenuPlan::enableAMEINGPLAButtons()           //habilitar los botones Añadir, Modificar y Eliminar de los ingredientes pertenecientes a un plato
{
    ui->pushButton_PLAING_aniadir->setEnabled(true);
    ui->pushButton_PLAING_modificar->setEnabled(true);
    ui->pushButton_PLAING_eliminar->setEnabled(true);
}

void MainWindowMenuPlan::disableAMEINGPLAButtons()          //deshabilitar los botones Añadir, Modificar y Eliminar de los ingredientes pertenecientes a un plato
{
    ui->pushButton_PLAING_aniadir->setEnabled(false);
    ui->pushButton_PLAING_modificar->setEnabled(false);
    ui->pushButton_PLAING_eliminar->setEnabled(false);
}

/*---------------------------------------------------------------------------------------------------------------------*/

void MainWindowMenuPlan::enablePlatosTextBox()              //habilitar los textbox (linedit) del apartado Platos
{
    ui->lineEdit_PLAnombre->setEnabled(true);
    ui->textEdit_PLAdescripcion->setEnabled(true);
    ui->lineEdit_PLAING_cantidad->setEnabled(true);
    ui->radioButton_primerP->setEnabled(true);
    ui->radioButton_segundoP->setEnabled(true);
    ui->radioButton_postre->setEnabled(true);
}

void MainWindowMenuPlan::disablePlatosTextBox()             //deshabilitar los textbox (linedit) del apartado Platos
{
    ui->lineEdit_PLAnombre->setEnabled(false);
    ui->textEdit_PLAdescripcion->setEnabled(false);
    ui->lineEdit_PLAING_cantidad->setEnabled(false);
    ui->listView_Ingredientes_PLA->setEnabled(false);
    ui->radioButton_primerP->setEnabled(false);
    ui->radioButton_segundoP->setEnabled(false);
    ui->radioButton_postre->setEnabled(false);
    ui->label_PLAING->setText("<html><head/><body><p align=\"center\"><span style=\" font-weight:600;\">Ingrediente a añadir</span></p></body></html>");
}

/*---------------------------------------------------------------------------------------------------------------------*/

void MainWindowMenuPlan::clearPlatosTextBox()               //Deja en blanco todos los textbox del apartado Platos
{
    QList<QLineEdit *> alltextbox = ui->groupBox_Plato->findChildren<QLineEdit *>();

    for(int i = 0; i < alltextbox.size(); i++)
    {
        alltextbox.at(i)->setText("");
    }
    ui->label_PLAid->setText("");
    ui->textEdit_PLAdescripcion->setText("");

    cleanListViewING_de_PLA();
}

void MainWindowMenuPlan::cleanListViewING_en_Platos()       //Se borra el listview con los ingredientes mostrados en el apartado Platos
{
    QStringListModel *model = new QStringListModel();
    model->removeRows(0, model->rowCount());
    ui->listView_Ingredientes_PLA->setModel(model);
    delete model;
}

void MainWindowMenuPlan::cleanListViewPlatos()              //Se borra el listview con los platos mostrados
{
    QStringListModel *model = new QStringListModel();
    model->removeRows(0, model->rowCount());
    ui->listView_Platos->setModel(model);
    delete model;
}

void MainWindowMenuPlan::cleanListViewING_de_PLA()          //Se borra el listview con los ingredientes correspondientes a un plato
{
    QStringListModel *model = new QStringListModel();
    model->removeRows(0, model->rowCount());
    ui->listView_INGPLA->setModel(model);
    delete model;
}

void MainWindowMenuPlan::disableImagenes_Incomp_Alerg()     //deshabilita las imagenes de alergenos e incompatibilidades
{
    ui->label_Aler_cereales->setVisible(false);
    ui->label_Aler_frutos_secos->setVisible(false);
    ui->label_Aler_legumbres->setVisible(false);
    ui->label_Aler_marisco->setVisible(false);
    ui->label_Aler_pescado->setVisible(false);
    ui->label_Aler_huevo->setVisible(false);
    ui->label_Aler_leche->setVisible(false);
    ui->label_Inc_celiaco->setVisible(false);
    ui->label_Inc_diabetico->setVisible(false);
    ui->label_Inc_semivegetariano->setVisible(false);
    ui->label_Inc_vegetariano->setVisible(false);
    ui->label_Inc_vegano->setVisible(false);
}




/*-------------------------------------------------------------------------*/
/*----------------------- EVENTOS CLICK DE BOTONES ------------------------*/
/*-------------------------------------------------------------------------*/


/*---------------------------------------------- AME (AÑADIR, MODIFICAR, ELIMINAR) PLATOS ------------------------------------------------------------*/

void MainWindowMenuPlan::on_pushButton_Aniadir_PLA_clicked()
{
    disableAMEPlatosButtons();                                                  //deshabilitar los botones AME
    enableGCPlatosButtons();                                                    //habilitar los botones GC
    clearPlatosTextBox();                                                       //limpiar los textbox
    enablePlatosTextBox();                                                      //habilitar los textbox
    ui->radioButton_primerP->setChecked(true);                                  //Activa por defecto el tipo Primer plato

    ui->listView_Platos->setEnabled(false);                                     //deshabilitar el listview de platos
    ui->listView_Platos->clearSelection();                                      //eliminar la seleccion en el listview de platos
    disableImagenes_Incomp_Alerg();                                             //deshabilita las imagenes de alergenos e incompatibilidades

    disableAMEINGPLAButtons();                                                  //deshabilitar los botones AME de ingredientes
    ui->lineEdit_PLAING_cantidad->setEnabled(false);                            //deshabilitar el textbox de cantidad de ingrediente

    Q = ANIADIRPLA;
    ui->label_InfoQuerys_2->setText("<html><head/><body><p><span style=\" font-weight:600; color:#0055ff;\">ADVERTENCIA: El campo </span><span style=\" font-weight:600; font-style:italic; color:#0055ff;\">&quot;Nombre&quot;</span><span style=\" font-weight:600; color:#0055ff;\"> es obligatorio. Si se deja cualquier otro campo vacío se rellenará con 0 por defecto.</span></p><p><span style=\" font-weight:600; color:#0055ff;\">Todos los campos, excepto </span><span style=\" font-weight:600; font-style:italic; color:#0055ff;\">&quot;Nombre&quot;</span><span style=\" font-weight:600; color:#0055ff;\"> y </span><span style=\" font-weight:600; font-style:italic; color:#0055ff;\">&quot;Descripción&quot;</span><span style=\" font-weight:600; color:#0055ff;\">, son numéricos. El símbolo de la coma para los decimales es </span><span style=\" font-weight:600; font-style:italic; color:#0055ff;\">&quot;.&quot;</span><span style=\" font-weight:600; color:#0055ff;\">.</span></p></body></html>");
}

void MainWindowMenuPlan::on_pushButton_Modificar_PLA_clicked()
{
    ACTION A = controllSelectionElement(*ui->listView_Platos);                  //Comprueba si hay un plato seleccionado

    if(A == ACCEPT)
    {
        disableAMEPlatosButtons();                                              //deshabilita los botones AME
        enableGCPlatosButtons();                                                //habilita los botones GC
        enablePlatosTextBox();                                                  //habilita los textbox
        enableAMEINGPLAButtons();                                               //habilita los botones AME de ingredientes
        ui->listView_Ingredientes_PLA->setEnabled(true);                        //habilita el listview de ingredientes totales
        ui->listView_Platos->setEnabled(false);                                 //deshabilita el listview de platos
        ui->listView_Platos->clearSelection();                                  //eliminar la seleccion del listview de platos
        disableImagenes_Incomp_Alerg();                                         //deshabilita las imagenes de alergenos e incompatibilidades

        Q = MODIFICARPLA;
        ui->label_InfoQuerys_2->setText("<html><head/><body><p><span style=\" font-weight:600; color:#0055ff;\">ADVERTENCIA: El campo </span><span style=\" font-weight:600; font-style:italic; color:#0055ff;\">&quot;Nombre&quot;</span><span style=\" font-weight:600; color:#0055ff;\"> es obligatorio. Si se deja cualquier otro campo numérico vacío se rellenará con 0 por defecto.</span></p><p><span style=\" font-weight:600; color:#0055ff;\">Todos los campos, excepto </span><span style=\" font-weight:600; font-style:italic; color:#0055ff;\">&quot;Nombre&quot;</span><span style=\" font-weight:600; color:#0055ff;\"> y </span><span style=\" font-weight:600; font-style:italic; color:#0055ff;\">&quot;Descripción&quot;</span><span style=\" font-weight:600; color:#0055ff;\">, son numéricos. El símbolo de la coma para los decimales es </span><span style=\" font-weight:600; font-style:italic; color:#0055ff;\">&quot;.&quot;</span><span style=\" font-weight:600; color:#0055ff;\">.</span></p></body></html>");
    }
}

void MainWindowMenuPlan::on_pushButton_Eliminar_PLA_clicked()
{
    ACTION A = controllSelectionElement(*ui->listView_Platos);                  //comprueba si hay un plato seleccionado

    if(A == ACCEPT)
    {
        QMessageBox msgBox;                                                     //mensaje de confirmacion
        msgBox.setIcon(QMessageBox::Warning);
        msgBox.setText("Un plato va a ser eliminado.");
        msgBox.setInformativeText("¿Está seguro de que quiere eliminar este plato de forma permanente?");
        QAbstractButton *myYesButton = msgBox.addButton(trUtf8("Sí"), QMessageBox::YesRole);
        msgBox.setStandardButtons(QMessageBox::No);
        msgBox.setDefaultButton(QMessageBox::No);
        msgBox.exec();

        if(msgBox.clickedButton() == myYesButton)
        {
            db1->queryEliminarPlato(ui->label_PLAid->text());                   //consulta para eliminar un plato
            ui->listView_Platos->setModel(db1->makeQuerys(MOSTRARPLA));         //consulta para mostrar los platos
            clearPlatosTextBox();                                               //limpiar los textbox
            cleanListViewING_de_PLA();                                          //limpiar el listview ingredientes de plato
            disableImagenes_Incomp_Alerg();                                     //deshabilita las imagenes de alergenos e incompatibilidades
        }
    }
}

/*-------------------------------------------------- GC (GUARDAR, CANCELAR) PLATOS ------------------------------------------------------------*/

void MainWindowMenuPlan::on_pushButton_Guardar_PLA_clicked()
{
    switch(Q)
    {
        case ANIADIRPLA:
        {
            ACTION A = controllDataTextBoxName(*ui->lineEdit_PLAnombre);                                            //comprobar si el nombre es correcto
            ACTION B = controllDataTextBoxNum(*ui->groupBox_Plato, 1);                                              //comprobar si el textbox numerico es correcto
            ACTION C = db1->controllQuerys(Q, PLATOS, ui->lineEdit_PLAnombre->text(), ui->label_PLAid->text());     //comprobar que no se inserte un plato ya existente

            if(A == ACCEPT && B == ACCEPT && C == ACCEPT)                                                       //__Si todo es correcto
            {
                db1->addPLAQuerys(captureTextBoxText(PLATOS));                                                  //consulta para añadir un plato
                ui->listView_Platos->setModel(db1->makeQuerys(MOSTRARPLA));                                     //consulta para mostrar los platos
                ui->comboBox_platos->setCurrentIndex(0);                                                        //Poner el combobox en el apartado Todos
                QSqlQueryModel *model = db1->makeQuerys(MOSTRARINFOPLA, ui->lineEdit_PLAnombre->text());        //consulta para mostrar la informacion recien añadida del plato
                fillIngPlaTextBox(model, PLATOS);                                                               //rellenar los textbox con la informacion

                QMessageBox msgBox;                                                                             //mensaje informativo para añadir ingredientes al plato
                msgBox.setIcon(QMessageBox::Information);
                msgBox.setText("Un plato ha sido añadido a la base de datos.");
                msgBox.setInformativeText("¿Quiere añadir ingredientes al plato creado?");
                QAbstractButton *myYesButton = msgBox.addButton(trUtf8("Sí"), QMessageBox::YesRole);
                msgBox.setStandardButtons(QMessageBox::No);
                msgBox.setDefaultButton(QMessageBox::No);
                msgBox.exec();

                if(msgBox.clickedButton() == myYesButton)                       //__Si se quiere añadir un ingrediente al plato
                {
                    Q = ANIADIRINGPLA;
                    ui->lineEdit_PLAING_cantidad->setEnabled(true);             //habilitar el textbox de cantidad de ingrediente
                    ui->pushButton_PLAING_aniadir->setEnabled(true);            //habilitar el boton añadir ingrediente
                    ui->listView_Ingredientes_PLA->setEnabled(true);            //habilitar el listview de ingredientes totales
                    ui->pushButton_Cancelar_PLA->setEnabled(false);             //deshabilitar el boton de cancelar
                }
                else                                                            //__Si no se quiere añadir un ingrediente al plato
                {
                    disableGCPlatosButtons();                                   //deshabilitar botones GC
                    enableAMEPlatosButtons();                                   //habilitar botones AME
                    clearPlatosTextBox();                                       //limpiar los textbox
                    disablePlatosTextBox();                                     //deshabilitar los textbox
                    disableImagenes_Incomp_Alerg();                             //deshabilita las imagenes de alergenos e incompatibilidades

                    ui->listView_Platos->setEnabled(true);                      //habilitar el listview de platos
                }
            }
            else                                                                //__Si hay algun fallo en los datos introducidos
            {
                disableGCPlatosButtons();                                       //deshabilitar los botones GC
                enableAMEPlatosButtons();                                       //habilitar los botones AME
                clearPlatosTextBox();                                           //limpiar los textbox
                disablePlatosTextBox();                                         //deshabilitar los textbox
                disableImagenes_Incomp_Alerg();                                 //deshabilita las imagenes de alergenos e incompatibilidades

                ui->listView_Platos->setEnabled(true);                          //habilitar el listview de platos
            }
        }
        break;

        case ANIADIRINGPLA:
            disableGCPlatosButtons();                                           //deshabilitar los botones AME
            enableAMEPlatosButtons();                                           //habilitar los botones AME
            disableAMEINGPLAButtons();                                          //deshabilitar los botones AME de ingredientes

            clearPlatosTextBox();                                               //limpiar los textbox
            disablePlatosTextBox();                                             //deshabilitar los textbox
            cleanListViewING_de_PLA();                                          //limpiar el listview de ingredientes de un plato
            disableImagenes_Incomp_Alerg();                                     //deshabilita las imagenes de alergenos e incompatibilidades

            ui->listView_Ingredientes_PLA->clearSelection();                    //Desselecciona el posible ingrediente seleccionado en el listview
            ui->listView_Platos->setEnabled("true");                            //habilitar el listview platos
        break;

        case MODIFICARPLA:
            ACTION A = controllDataTextBoxName(*ui->lineEdit_PLAnombre);                                            //comprobar si el nombre es correcto
            ACTION B = controllDataTextBoxNum(*ui->groupBox_Plato, 1);                                              //comprobar si los textbox numericos son correctos
            ACTION C = db1->controllQuerys(Q, PLATOS, ui->lineEdit_PLAnombre->text(), ui->label_PLAid->text());     //comprobar que no se añade un plato ya existente

            if(A == ACCEPT && B == ACCEPT && C == ACCEPT)                       //__Si los datos introducidos son correctos
            {
                db1->modPLAQuerys(captureTextBoxText(PLATOS));                                                      //consulta para modificar un plato
                ui->listView_Platos->setModel(db1->makeQuerys(MOSTRARPLA));                                         //consulta para mostrar los platos
                QSqlQueryModel *model = db1->makeQuerys(MOSTRARINFOPLA, ui->lineEdit_PLAnombre->text());            //consulta para mostrar la informacion recien modificada del plato
                fillIngPlaTextBox(model, PLATOS);                                                                   //rellenar los textbox con la informacion
                ui->comboBox_platos->setCurrentIndex(0);                                                            //Poner el combobox en el apartado Todos
            }

            disableGCPlatosButtons();                                       //deshabilitar los botones GC
            disableAMEINGPLAButtons();                                      //deshabilitar los botones AME de ingredientes
            enableAMEPlatosButtons();                                       //habilitar los botones AME
            clearPlatosTextBox();                                           //limpiar los textbox
            disablePlatosTextBox();                                         //deshabilitar los textbox
            disableImagenes_Incomp_Alerg();                                 //deshabilita las imagenes de alergenos e incompatibilidades

            ui->listView_Platos->setEnabled(true);                          //habilitar el listview de platos

        break;
    }

    ui->label_InfoQuerys_2->setText("");                        //Limpiar el label informativo
    ui->lineEdit_PLAING_cantidad->setText("");                  //Limpiar el textbox cantidad
    ui->listView_Platos->clearSelection();                      //Desselecciona el posible ingrediente seleccionado en el listview
    ui->listView_Ingredientes_PLA->clearSelection();            //Desselecciona el posible ingrediente seleccionado en el listview
}

void MainWindowMenuPlan::on_pushButton_Cancelar_PLA_clicked()
{
    enableAMEPlatosButtons();
    disableGCPlatosButtons();
    disableAMEINGPLAButtons();

    disablePlatosTextBox();
    clearPlatosTextBox();
    cleanListViewING_de_PLA();
    disableImagenes_Incomp_Alerg();                             //deshabilita las imagenes de alergenos e incompatibilidades

    ui->listView_Ingredientes_PLA->clearSelection();            //Desselecciona el posible ingrediente seleccionado en el listview
    ui->listView_Platos->clearSelection();                      //Desselecciona el posible ingrediente seleccionado en el listview

    ui->listView_Platos->setEnabled("true");
    ui->label_InfoQuerys_2->setText("");                          //Label informativo
    ui->lineEdit_PLAING_cantidad->setText("");
}


/*---------------------------------------- AME (AÑADIR, MODIFICAR, ELIMINAR) INGREDIENTES DE PLATOS ------------------------------------------------------------*/

void MainWindowMenuPlan::on_pushButton_PLAING_aniadir_clicked()
{
    ACTION A = controllSelectionElement(*ui->listView_Ingredientes_PLA);                                    //Controlar que haya un elemento seleccionado
    ACTION B = controllDataTextBoxNum(*ui->groupBox_PLAING, 0);                                             //Controlar que el nombre es correcto
    ACTION C = DENY;

    if(A == ACCEPT && B == ACCEPT)
    {
        const QModelIndexList indexL = ui->listView_Ingredientes_PLA->selectionModel()->selectedIndexes();      //Captura la seleccion del listview de ingredientes
        const QModelIndex index = indexL.at(0);
        C = db1->controllQuerys(ANIADIRINGPLA, INGDEPLATO, index.data(Qt::DisplayRole).toString(), ui->label_PLAid->text());         //Controla que no se añadan al plato ingredientes ya añadidos

        if(A == ACCEPT && B == ACCEPT && C == ACCEPT)
        {
            db1->addINGtoPLAQuery(ui->label_PLAid->text(), index.data(Qt::DisplayRole).toString(), ui->lineEdit_PLAING_cantidad->text());   //Consulta para añadir ingrediente
            ui->listView_INGPLA->setModel(db1->makeQuerys(MOSTRARINGPLA, ui->label_PLAid->text()));                                         //Consulta para mostrar los ingredientes del plato
            ui->lineEdit_PLAING_cantidad->setText("");                                                                                      //Limpiar el textbox cantidad
            nutricionalInfo();                                                                                                              //Calcular la informacion nutricional del plato
            setCantidadPlato();                                                                                                             //Calcular la cantidad del plato
            setPrecioPlato();                                                                                                               //Calcular el precio del plato
            set_Incomp_Alerg_Plato();                                                                                                       //Calcula las incompatibilidades y alergenos del plato
            mostrar_Incomp_Alerg_Plato();
        }
    }
}

void MainWindowMenuPlan::on_pushButton_PLAING_modificar_clicked()
{
    ACTION A = controllSelectionElement(*ui->listView_INGPLA);                                          //Controlar que haya un elemento seleccionado
    ACTION B = controllDataTextBoxNum(*ui->groupBox_PLAING, 0);                                         //Controlar que los textbox numericos sean correctos

    if(A == ACCEPT && B == ACCEPT)
    {
        const QModelIndexList indexL = ui->listView_INGPLA->selectionModel()->selectedIndexes();        //Captura la seleccion del listview de ingredientes
        const QModelIndex index = indexL.at(0);

        db1->modINGtoPLAQuery(ui->label_PLAid->text(), index.data(Qt::DisplayRole).toString(), ui->lineEdit_PLAING_cantidad->text());   //Consulta para modificar un ingrediente de un plato
        ui->listView_INGPLA->setModel(db1->makeQuerys(MOSTRARINGPLA, ui->label_PLAid->text()));                                         //Consulta para mostrar los ingredientes del plato
        nutricionalInfo();                                                                                                              //Calcular la informacion nutricional del plato
        setCantidadPlato();                                                                                                             //Calcular la cantidad del plato
        setPrecioPlato();                                                                                                               //Calcular el precio del plato
        set_Incomp_Alerg_Plato();                                                                                                       //Calcula las incompatibilidades y alergenos del plato
        mostrar_Incomp_Alerg_Plato();
    }


}

void MainWindowMenuPlan::on_pushButton_PLAING_eliminar_clicked()
{
    ACTION A = controllSelectionElement(*ui->listView_INGPLA);                                                      //Controlar que haya un elemento seleccionado

    if(A == ACCEPT)
    {
        QMessageBox msgBox;                                                                                         //Mensaje de confirmacion de eliminacion
        msgBox.setIcon(QMessageBox::Warning);
        msgBox.setText("Un ingrediente del plato va a ser eliminado.");
        msgBox.setInformativeText("¿Está seguro de que quiere eliminar este ingrediente de forma permanente?");
        QAbstractButton *myYesButton = msgBox.addButton(trUtf8("Sí"), QMessageBox::YesRole);
        msgBox.setStandardButtons(QMessageBox::No);
        msgBox.setDefaultButton(QMessageBox::No);
        msgBox.exec();

        if(msgBox.clickedButton() == myYesButton)
        {
            const QModelIndexList indexL = ui->listView_INGPLA->selectionModel()->selectedIndexes();                //Captura la seleccion del listview de ingredientes
            const QModelIndex index = indexL.at(0);

            db1->removeINGtoPLAQuery(ui->label_PLAid->text(), index.data(Qt::DisplayRole).toString());              //Consulta para eliminar un ingrediente de un plato
            ui->listView_INGPLA->setModel(db1->makeQuerys(MOSTRARINGPLA, ui->label_PLAid->text()));                 //Consulta para mostrar los ingredientes de un plato
            ui->lineEdit_PLAING_cantidad->setText("");                                                              //Limpiar el textbox cantidad
            nutricionalInfo();                                                                                      //Calcular la informacion nutricional del plato
            setCantidadPlato();                                                                                     //Calcular la cantidad del plato
            setPrecioPlato();                                                                                       //Calcular el precio del plato
            set_Incomp_Alerg_Plato();                                                                               //Calcula las incompatibilidades y alergenos del plato
            mostrar_Incomp_Alerg_Plato();
        }
    }
}


/*-------------------------------------------------------------------------*/
/*---------- EVENTO CLICK DE LISTVIEW PLATOS DEL APARTADO PLATOS ----------*/
/*-------------------------------------------------------------------------*/

void MainWindowMenuPlan::on_listView_Platos_clicked(const QModelIndex &index)
{
    QString str = index.data(Qt::DisplayRole).toString();                                       //Elemento del listview al que se ha hecho click
    QSqlQueryModel *model = db1->makeQuerys(MOSTRARINFOPLA, str);                               //Consulta para mostrar los datos del plato seleccionado

    fillIngPlaTextBox(model, PLATOS);

    ui->listView_INGPLA->setModel(db1->makeQuerys(MOSTRARINGPLA, ui->label_PLAid->text()));     //Consulta para mostrar los ingredientes del plato
    ui->lineEdit_PLAING_cantidad->setText("");                                                  //Limpiar el textbox cantidad

    delete model;
}


/*-------------------------------------------------------------------------*/
/*-------- EVENTO CLICK DE LISTVIEW DE ING EN EL APARTADO PLATOS ----------*/
/*-------------------------------------------------------------------------*/

void MainWindowMenuPlan::on_listView_Ingredientes_PLA_clicked(const QModelIndex &index)
{
    QString str = "<html><head/><body><p align=\"center\"><span style=\" font-weight:600;\">";
    str.append(index.data(Qt::DisplayRole).toString());                                             //Elemento del listview al que se ha hecho click
    str.append("</span></p></body></html>");
    ui->label_PLAING->setText(str);                                                                 //Mostrar el ingrediente seleccionado en el label de ingredientes de plato
    ui->lineEdit_PLAING_cantidad->setText("");                                                      //Limpiar el textbox cantidad
}


/*-------------------------------------------------------------------------*/
/*--- EVENTO CLICK DE LISTVIEW DE ING DE UN PLATO EN EL APARTADO PLATOS ---*/
/*-------------------------------------------------------------------------*/

void MainWindowMenuPlan::on_listView_INGPLA_clicked(const QModelIndex &index)
{
    //Consulta para mostrar la cantidad del ingrediente seleccionado
    ui->lineEdit_PLAING_cantidad->setText(db1->queryMostrarCantidadInGPlatos(ui->label_PLAid->text(), index.data(Qt::DisplayRole).toString()));

    //Controlar que la cantidad mostrada no supere el numero maximo de digitos
    QString str = ui->lineEdit_PLAING_cantidad->text();
    if(str.size() > maxNumSize)
    {
        str.remove(maxNumSize, (str.size()-maxNumSize));    //Borrar el contenido que exceda maxNumSize
        ui->lineEdit_PLAING_cantidad->setText(str);
    }
}


/*-------------------------------------------------------------------------*/
/*------------- CALCULAR INFORMACION NUTRICIONAL DE PLATOS ----------------*/
/*-------------------------------------------------------------------------*/

void MainWindowMenuPlan::nutricionalInfo()
{
    QAbstractItemModel *model = ui->listView_INGPLA->model();                                               //Captura el modelo del listview de ingredientes de un plato (captura todos los ingredientes del plato)
    QSqlQueryModel * model2;
    QString ing;
    float cantidadIngPlato = 0, cantidadIngBD = 0;
    QStringList infoN, temp;

    initializeInfoN(infoN);                                                                                 //Inisializa la lista donde sera almacenada toda la informacion

    for(int i = 0; i < model->rowCount(); i++)
    {
        ing = ui->listView_INGPLA->model()->index(i,0).data(Qt::DisplayRole).toString();                    //Captura el nombre del ingrediente
        cantidadIngPlato = db1->queryMostrarCantidadInGPlatos(ui->label_PLAid->text(), ing).toFloat();      //Captura la cantidad de dicho ingrediente en el plato
        cantidadIngBD = db1->queryMostrarCantidadING(ing).toFloat();                                        //Captura la cantidad de dicho ingrediente en la base de datos donde se almacena la informacion de ese ingrediente

        model2 = new QSqlQueryModel;
        model2 = db1->makeQuerys(MOSTRARINFONUTR, ing);                                                     //Consulta para guardar en un modelo la informacion nutricional del ingrediente

        for(int i = 0; i < NumInfN; i++)
        {
            temp << model2->index(0,i).data(Qt::DisplayRole).toString();                                    //Guardar la inf nutricional en una lista temporal
        }

        for(int i = 0; i < temp.size(); i++)                                                                //Hacer el calculo de la inf nutricional para el plato
        {
            temp[i] = QString::number((cantidadIngPlato * temp[i].toFloat()) / cantidadIngBD);
            infoN[i] = QString::number(temp[i].toFloat() + infoN[i].toFloat());
        }

        temp.clear();
        delete model2;
    }

    showInfoN(infoN);                                                                                       //Mostrar la informacion nutricional calculada
}


/*-------------------------------------------------------------------------*/
/*-------- INICIALIZAR LA LISTA DONDE SE GUARDA LA INF NUTRICIONAL --------*/
/*-------------------------------------------------------------------------*/
void MainWindowMenuPlan::initializeInfoN(QStringList &infoN)
{
    for(int i = 0; i < NumInfN; i++)
    {
        infoN.push_back("0");
    }
}


/*-------------------------------------------------------------------------*/
/*------------ MOSTRAR LA INFORMACION NUTRICIONAL DEL PLATO ---------------*/
/*-------------------------------------------------------------------------*/
void MainWindowMenuPlan::showInfoN(QStringList &infoN)
{
    db1->queryUpdateInfoNING(infoN, ui->label_PLAid->text());                                       //Consulta para actualizar los datos
    QSqlQueryModel *model3 = db1->makeQuerys(MOSTRARINFOPLA, ui->lineEdit_PLAnombre->text());       //Consulta para mostrar los datos del plato

    fillIngPlaTextBox(model3, PLATOS);                                                              //Rellenar los textbox con los datos consultados
    delete model3;
}


/*-------------------------------------------------------------------------------------------------*/
/*------------ COMPROBAR QUE TIPO DE PLATO ES (PRIMER PLATO, SEGUNO PLATO O POSTRE) ---------------*/
/*-------------------------------------------------------------------------------------------------*/
QString MainWindowMenuPlan::setTipoPlato()
{
    QString tipo;

    if(ui->radioButton_primerP->isChecked())
        tipo = '1';
    else if(ui->radioButton_segundoP->isChecked())
        tipo = '2';
    else
        tipo = '3';
    return tipo;
}

/*-------------------------------------------------------------------------------------------------*/
/*------ MOSTRAR EL TIPO DE PLATO EN EL RADIOBUTTON (PRIMER PLATO, SEGUNO PLATO O POSTRE) ---------*/
/*-------------------------------------------------------------------------------------------------*/
void MainWindowMenuPlan::mostrarTipoPlato(QString tipo)
{
    if(tipo == "1")
        ui->radioButton_primerP->setChecked(true);
    else if (tipo == "2")
        ui->radioButton_segundoP->setChecked(true);
    else
        ui->radioButton_postre->setChecked(true);
}


/*-------------------------------------------------------------------------------------------------*/
/*----------- MUESTRA LOS PLATOS SEGUN EL TIPO DE PLATO QUE SE ELIJA EN EL COMBOBOX ---------------*/
/*-------------------------------------------------------------------------------------------------*/

void MainWindowMenuPlan::on_comboBox_platos_activated(const QString &arg1)
{
    if(arg1 == "Todos")
        ui->listView_Platos->setModel(db1->makeQuerys(MOSTRARPLA));                     //Consulta de todos los platos

    else if(arg1 == "Primer plato")
        ui->listView_Platos->setModel(db1->makeQuerys(MOSTRARTIPOPLA, QString('1')));   //Consulta de solo los primeros platos

    else if(arg1 == "Segundo plato")
        ui->listView_Platos->setModel(db1->makeQuerys(MOSTRARTIPOPLA, QString('2')));   //Consulta de solo los segundos platos

    else if(arg1 == "Postre")
        ui->listView_Platos->setModel(db1->makeQuerys(MOSTRARTIPOPLA, QString('3')));   //Consulta de solo los postres
}


/*------------------------------------------------------------------------------------------------------------*/
/*----------- CALCULA LA CANTIDAD EN GRAMOS DE UN PLATO, EN BASE A LA CANTIDAD DE INGREDIENTES ---------------*/
/*------------------------------------------------------------------------------------------------------------*/
void MainWindowMenuPlan::setCantidadPlato()
{
    float f = 0;

    for(int i = 0; i < ui->listView_INGPLA->model()->rowCount(); i++)  
        f += db1->queryMostrarCantidadInGPlatos(ui->label_PLAid->text(), ui->listView_INGPLA->model()->index(i,0).data(Qt::DisplayRole).toString()).toFloat();

    db1->queryModificarCantidadPlato(ui->label_PLAid->text(), QString::number(f));
    ui->lineEdit_PLAcantidad->setText(QString::number(f));
}


/*---------------------------------------------------------------------------------------------------------*/
/*----------- CALCULA EL PRECIO DE UN PLATO, EN BASE A LA CANTIDAD Y PRECIO DE INGREDIENTES ---------------*/
/*---------------------------------------------------------------------------------------------------------*/
void MainWindowMenuPlan::setPrecioPlato()
{
    float f = 0;

    for(int i = 0; i < ui->listView_INGPLA->model()->rowCount(); i++)
        f += db1->queryMostrarPrecioING(ui->listView_INGPLA->model()->index(i,0).data(Qt::DisplayRole).toString(), db1->queryMostrarCantidadInGPlatos(ui->label_PLAid->text(), ui->listView_INGPLA->model()->index(i,0).data(Qt::DisplayRole).toString()).toFloat());

    db1->queryModificarPrecioPlato(ui->label_PLAid->text(), QString::number(f));
    ui->lineEdit_PLAprecio->setText(QString::number(f));
}



/*---------------------------------------------------------------------------------------------------------*/
/*------------ CALCULA LAS INCOMPATIBILIDADES Y ALERGENOS DEL PLATO SEGUN SUS INGREDIENTES ---------------*/
/*---------------------------------------------------------------------------------------------------------*/
void MainWindowMenuPlan::set_Incomp_Alerg_Plato()
{
    QString incompING, alergING;
    QString incompPLA = "00000";
    QString alergPLA = "0000000";

    for(int i = 0; i < ui->listView_INGPLA->model()->rowCount(); i++)
    {
        incompING = db1->queryIncompatibilidadesING(ui->listView_INGPLA->model()->index(i,0).data(Qt::DisplayRole).toString());
        alergING = db1->queryAlergenosING(ui->listView_INGPLA->model()->index(i,0).data(Qt::DisplayRole).toString());

        for(int j = 0; j < incompING.size(); j++)
        {
            if(incompING.at(j) == '1' && incompPLA.at(j) == '0')
                incompPLA.replace(j, 1, '1');
        }

        for(int j = 0; j < alergING.size(); j++)
        {
            if(alergING.at(j) == '1' && alergPLA.at(j) == '0')
                alergPLA.replace(j, 1, '1');
        }
    }

    db1->queryModificarIncompAlergPlato(ui->label_PLAid->text(), incompPLA, alergPLA);
}


/*---------------------------------------------------------------------------------------------------------*/
/*------------------ CALCULA LOS MESES DE TEMPORADA DEL PLATO SEGUN SUS INGREDIENTES ----------------------*/
/*---------------------------------------------------------------------------------------------------------*/
void MainWindowMenuPlan::mostrar_Incomp_Alerg_Plato()
{
    QString inc = db1->queryMostrarIncompPlato(ui->label_PLAid->text());
    QString aler = db1->queryMostrarAlergPlato(ui->label_PLAid->text());

    if(inc.at(0) == '1')
        ui->label_Inc_celiaco->setVisible(true);
    if(inc.at(1) == '1')
        ui->label_Inc_diabetico->setVisible(true);
    if(inc.at(2) == '1')
        ui->label_Inc_semivegetariano->setVisible(true);
    if(inc.at(3) == '1')
        ui->label_Inc_vegetariano->setVisible(true);
    if(inc.at(4) == '1')
        ui->label_Inc_vegano->setVisible(true);

    if(aler.at(0) == '1')
        ui->label_Aler_cereales->setVisible(true);
    if(aler.at(1) == '1')
        ui->label_Aler_frutos_secos->setVisible(true);
    if(aler.at(2) == '1')
        ui->label_Aler_legumbres->setVisible(true);
    if(aler.at(3) == '1')
        ui->label_Aler_marisco->setVisible(true);
    if(aler.at(4) == '1')
        ui->label_Aler_pescado->setVisible(true);
    if(aler.at(5) == '1')
        ui->label_Aler_huevo->setVisible(true);
    if(aler.at(6) == '1')
        ui->label_Aler_leche->setVisible(true);
}



/*---------------------------------------------------------------------------------------------------------*/
/*----------------- CALCULA LA CALIDAD DEL PLATO SEGUN LOS INGREDIENTES DE TEMPORADA ----------------------*/
/*---------------------------------------------------------------------------------------------------------*/
void MainWindowMenuPlan::set_temporada_Plato()
{

}


