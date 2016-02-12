#include "mainwindowmenuplan.h"
#include "ui_mainwindowmenuplan.h"

/*-------------------------------------------------------------------------*/
/*----------------------- CONSTRUCTOR Y DESTRUCTOR ------------------------*/
/*-------------------------------------------------------------------------*/

MainWindowMenuPlan::MainWindowMenuPlan(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindowMenuPlan)
{
    ui->setupUi(this);
    db1 = new database;

    //Deshabilitar los botones de la parte de Ingredientes al arranque de la aplicacion
    disableGCIngredientesButtons();
    disableAMEIngredientesButtons();
    //Deshabilitar los botones de la parte de Platos al arranque de la aplicacion
    disableGCPlatosButtons();
    disableAMEPlatosButtons();
    disableAMEINGPLAButtons();


    //Deshabilitar los textbox (lineedit) de Ingredientes al arranque de la aplicacion
    disableIngredientesTextBox();

    //Deshabilitar los textbox (lineedit) de Platos al arranque de la aplicacion
    disablePlatosTextBox();
}

MainWindowMenuPlan::~MainWindowMenuPlan()
{
    delete db1;
    delete ui;
}


/*-------------------------------------------------------------------------*/
/*------------------------ CIERRE DE LA APLICACION ------------------------*/
/*-------------------------------------------------------------------------*/

void MainWindowMenuPlan::closeEvent(QCloseEvent * event)    //Desconectarse de la base de datos al salir de la aplicacion
{
    db1->disconnectBD();
    event->accept();
}



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
/*
void MainWindowMenuPlan::enableAMEINGPLAButtons()           //habilitar los botones Añadir, Modificar y Eliminar de los ingredientes pertenecientes a un plato
{
    ui->pushButton_PLAING_aniadir->setEnabled(true);
    ui->pushButton_PLAING_modificar->setEnabled(true);
    ui->pushButton_PLAING_eliminar->setEnabled(true);
}*/

void MainWindowMenuPlan::disableAMEINGPLAButtons()          //deshabilitar los botones Añadir, Modificar y Eliminar de los ingredientes pertenecientes a un plato
{
    ui->pushButton_PLAING_aniadir->setEnabled(false);
    ui->pushButton_PLAING_modificar->setEnabled(false);
    ui->pushButton_PLAING_eliminar->setEnabled(false);
}

/*---------------------------------------------------------------------------------------------------------------------*/

void MainWindowMenuPlan::enableIngredientesTextBox()        //habilitar los textbox (linedit) del apartado Ingredientes
{
    QList<QLineEdit *> alltextbox = ui->groupBox_INGalimento->findChildren<QLineEdit *>();

    for(int i = 0; i < alltextbox.size(); i++)
    {
        alltextbox.at(i)->setEnabled(true);
    }
}

void MainWindowMenuPlan::disableIngredientesTextBox()       //deshabilitar los textbox (linedit) del apartado Ingredientes
{
    QList<QLineEdit *> alltextbox = ui->groupBox_INGalimento->findChildren<QLineEdit *>();

    for(int i = 0; i < alltextbox.size(); i++)
    {
        alltextbox.at(i)->setEnabled(false);
    }
}

/*---------------------------------------------------------------------------------------------------------------------*/

void MainWindowMenuPlan::enablePlatosTextBox()              //habilitar los textbox (linedit) del apartado Platos
{
    ui->lineEdit_PLAnombre->setEnabled(true);
    ui->lineEdit_PLAprecio->setEnabled(true);
    ui->lineEdit_PLAcantidad->setEnabled(true);
    ui->textEdit_PLAdescripcion->setEnabled(true);
    ui->lineEdit_PLAING_cantidad->setEnabled(true);
}

void MainWindowMenuPlan::disablePlatosTextBox()             //deshabilitar los textbox (linedit) del apartado Platos
{
    ui->lineEdit_PLAnombre->setEnabled(false);
    ui->lineEdit_PLAprecio->setEnabled(false);
    ui->lineEdit_PLAcantidad->setEnabled(false);
    ui->textEdit_PLAdescripcion->setEnabled(false);
    ui->lineEdit_PLAING_cantidad->setEnabled(false);
    ui->listView_Ingredientes_PLA->setEnabled(false);
    ui->label_PLAING->setText("<html><head/><body><p align=\"center\"><span style=\" font-weight:600;\">Ingrediente a añadir</span></p></body></html>");
}

/*---------------------------------------------------------------------------------------------------------------------*/

void MainWindowMenuPlan::clearIngredientesTextBox()         //Deja en blanco todos los textbox del apartado Ingredientes
{
    QList<QLineEdit *> alltextbox = ui->groupBox_INGalimento->findChildren<QLineEdit *>();

    for(int i = 0; i < alltextbox.size(); i++)
    {
        alltextbox.at(i)->setText("");
    }
    ui->label_INGid->setText("");
}

void MainWindowMenuPlan::cleanListViewING()                 //Se borra el listview con los ingredientes mostrados en el apartado Ingredientes
{
    QStringListModel *model = new QStringListModel();
    model->removeRows(0, model->rowCount());
    ui->listView_Ingredientes->setModel(model);
    delete model;
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

void MainWindowMenuPlan::cleanListViewING_de_PLA()
{
    QStringListModel *model = new QStringListModel();
    model->removeRows(0, model->rowCount());
    ui->listView_INGPLA->setModel(model);
    delete model;
}

/*-------------------------------------------------------------------------*/
/*----------------------- EVENTOS CLICK DE BOTONES ------------------------*/
/*-------------------------------------------------------------------------*/

/*--------------------------------------------------------- AME INGREDIENTES ------------------------------------------------------------*/

void MainWindowMenuPlan::on_pushButton_Aniadir_clicked()
{
    enableGCIngredientesButtons();
    disableAMEIngredientesButtons();
    enableIngredientesTextBox();
    clearIngredientesTextBox();
    Q = ANIADIRING;
    ui->label_InfoQuerys->setText("<html><head/><body><p><span style=\" font-weight:600; color:#0055ff;\">ADVERTENCIA: El campo </span><span style=\" font-weight:600; font-style:italic; color:#0055ff;\">&quot;Nombre&quot;</span><span style=\" font-weight:600; color:#0055ff;\"> es obligatorio. Si se deja cualquier otro campo vacío se rellenará con 0 por defecto.</span></p><p><span style=\" font-weight:600; color:#0055ff;\">Todos los campos, excepto </span><span style=\" font-weight:600; font-style:italic; color:#0055ff;\">&quot;Nombre&quot;</span><span style=\" font-weight:600; color:#0055ff;\">, son numéricos. El símbolo de la coma para los decimales es </span><span style=\" font-weight:600; font-style:italic; color:#0055ff;\">&quot;.&quot;</span><span style=\" font-weight:600; color:#0055ff;\">.</span></p></body></html>");
}

void MainWindowMenuPlan::on_pushButton_Modificar_clicked()
{
    ACTION A = controllSelectedING();

    if(A == ACCEPT)
    {
        enableGCIngredientesButtons();
        disableAMEIngredientesButtons();
        enableIngredientesTextBox();
        Q = MODIFICARING;
        ui->label_InfoQuerys->setText("<html><head/><body><p><span style=\" font-weight:600; color:#0055ff;\">ADVERTENCIA: El campo </span><span style=\" font-weight:600; font-style:italic; color:#0055ff;\">&quot;Nombre&quot;</span><span style=\" font-weight:600; color:#0055ff;\"> es obligatorio. Si se deja cualquier otro campo vacío se rellenará con 0 por defecto.</span></p><p><span style=\" font-weight:600; color:#0055ff;\">Todos los campos, excepto </span><span style=\" font-weight:600; font-style:italic; color:#0055ff;\">&quot;Nombre&quot;</span><span style=\" font-weight:600; color:#0055ff;\">, son numéricos. El símbolo de la coma para los decimales es </span><span style=\" font-weight:600; font-style:italic; color:#0055ff;\">&quot;.&quot;</span><span style=\" font-weight:600; color:#0055ff;\">.</span></p></body></html>");
    }
}

void MainWindowMenuPlan::on_pushButton_Eliminar_clicked()
{
    ACTION A = controllSelectedING();

    if(A == ACCEPT)
    {
        QMessageBox msgBox;
        msgBox.setText("Un ingrediente va a ser eliminado.");
        msgBox.setInformativeText("¿Está seguro de que quiere eliminar este ingrediente de forma permanente?");
        QAbstractButton *myYesButton = msgBox.addButton(trUtf8("Sí"), QMessageBox::YesRole);
        msgBox.setStandardButtons(QMessageBox::No);
        msgBox.setDefaultButton(QMessageBox::No);
        msgBox.exec();

        if(msgBox.clickedButton() == myYesButton)
        {
            ui->listView_Ingredientes->setModel(db1->makeQuerys(ELIMINARING, ui->label_INGid->text()));
            ui->listView_Ingredientes->setModel(db1->makeQuerys(MOSTRARING));
            clearIngredientesTextBox();
        }
    }
}

/*--------------------------------------------------------- AME PLATOS ------------------------------------------------------------*/

void MainWindowMenuPlan::on_pushButton_Aniadir_PLA_clicked()
{
    enableGCPlatosButtons();
    disableAMEPlatosButtons();
    enablePlatosTextBox();
    clearPlatosTextBox();

    ui->listView_Platos->setEnabled(false);
    ui->listView_Platos->clearSelection();

    disableAMEINGPLAButtons();
    ui->lineEdit_PLAING_cantidad->setEnabled(false);
}

void MainWindowMenuPlan::on_pushButton_Modificar_PLA_clicked()
{

}

void MainWindowMenuPlan::on_pushButton_Eliminar_PLA_clicked()
{

}

/*--------------------------------------------------------- GC INGREDIENTES ------------------------------------------------------------*/

void MainWindowMenuPlan::on_pushButton_Guardar_clicked()
{
    enableAMEIngredientesButtons();
    disableGCIngredientesButtons();
    disableIngredientesTextBox();
    ACTION A = controllDataTextBox();

    if(A == ACCEPT)
    {
        if(Q == MODIFICARING)
        {
            ui->listView_Ingredientes->setModel(db1->modINGQuerys(captureTextBoxText()));
            ui->listView_Ingredientes->setModel(db1->makeQuerys(MOSTRARING));
        }
        else if(Q == ANIADIRING)
        {
            ui->listView_Ingredientes->setModel(db1->addINGQuerys(captureTextBoxText()));
            ui->listView_Ingredientes->setModel(db1->makeQuerys(MOSTRARING));
        }
    }
    clearIngredientesTextBox();

    ui->label_InfoQuerys->setText("");      //Label informativo
}

void MainWindowMenuPlan::on_pushButton_Cancelar_clicked()
{
    enableAMEIngredientesButtons();
    disableGCIngredientesButtons();
    disableIngredientesTextBox();
    clearIngredientesTextBox();
    ui->label_InfoQuerys->setText("");
}

/*--------------------------------------------------------- GC PLATOS ------------------------------------------------------------*/

void MainWindowMenuPlan::on_pushButton_Guardar_PLA_clicked()
{
    ui->listView_Platos->setEnabled("true");
}

void MainWindowMenuPlan::on_pushButton_Cancelar_PLA_clicked()
{
    enableAMEPlatosButtons();
    disableGCPlatosButtons();
    disableAMEINGPLAButtons();


    disablePlatosTextBox();
    clearPlatosTextBox();
    cleanListViewING_de_PLA();

    ui->listView_Ingredientes_PLA->clearSelection();            //Desselecciona el posible ingrediente seleccionado en el listview
    ui->listView_Platos->setEnabled("true");
}


/*--------------------------------------------------------- AME ING PLATOS ------------------------------------------------------------*/

void MainWindowMenuPlan::on_pushButton_PLAING_aniadir_clicked()
{
    const QModelIndexList index = ui->listView_Ingredientes_PLA->selectionModel()->selectedIndexes();

    if(index.size() == 1)
    {
        if(ui->lineEdit_PLAING_cantidad->text() == "")      //___Comprobar si se ha seleccionado un ingrediente
        {
            QMessageBox::information(this,"Información","Debe añadir una cantidad en gramos al ingrediente seleccionado.");
        }
        else
        {
            QString str = ui->lineEdit_PLAING_cantidad->text();
            bool accept = true;

            for(int i = 0; i < str.size(); i++)             //___Si se ha seleccionado, comprobar que la cantidad esta escrita correctamente
            {
                if(str.at(i) < 48 || str.at(i) > 57)
                {
                    QMessageBox::information(this,"Información","La cantidad del ingrediente debe ser numérica.");
                    accept = false;
                    break;
                }
            }
            if(accept)                                      //___Ingrediente seleccionado y cantidad escrita correctamente
            {


            }
        }
    }
    else
    {
        QMessageBox::information(this,"Información","Debe seleccionar un ingrediente para añadirlo.");
    }
}

void MainWindowMenuPlan::on_pushButton_PLAING_modificar_clicked()
{

}

void MainWindowMenuPlan::on_pushButton_PLAING_eliminar_clicked()
{

}


/*----------------------------------------------------------------------------------------------------*/
/*---------------------- BOTON DE CONEXION Y DESCONEXION A LA BASE DE DATOS --------------------------*/
/*----------------------------------------------------------------------------------------------------*/

void MainWindowMenuPlan::on_pushButton_ConectarBD_clicked()
{
    QString labelText;

    //______Si NO se esta conectado a la base de datos se intenta conectar...
    if(ui->label_EstadoConexion->text() == "<html><head/><body><p><span style=\" font-size:10pt; font-weight:600; color:#ff0000;\">Desconectado</span></p></body></html>")
    {
        if(db1->connectBD())                                                            //______Si se conecta a la base de datos con exito...
        {
            labelText = "<html><head/><body><p><span style=\" font-size:10pt; font-weight:600; color:#00aa00;\">Conectado</span></p></body></html>";
            ui->label_EstadoConexion->setText(labelText);
            ui->pushButton_ConectarBD->setText("Desconectar");

            ui->listView_Ingredientes->setModel(db1->makeQuerys(MOSTRARING));           //______Se hace una consulta de los ingredientes para mostrarse en el apartado ingredientes
            ui->listView_Ingredientes_PLA->setModel(db1->makeQuerys(MOSTRARING));       //______Se hace una consulta de los ingredientes para mostrarse en el apartado platos
            ui->listView_Platos->setModel(db1->makeQuerys(MOSTRARPLA));                 //______Se hace una consulta de los platos para mostrarse
            enableAMEIngredientesButtons();                                             //______Se habilitan los botones de edicion en el panel de ingredientes
            enableAMEPlatosButtons();                                                   //______Se habilitan los botones de edicion en el panel de platos
        }
        else                                                                            //______Si se produce un error de conexion a la base de datos...
        {
            QMessageBox::critical(this, "Error de conexión", db1->errorMsg());
        }
    }
    else                                                                                //______Si se esta conectado a la base de datos se intenta desconectar...
    {
        db1->disconnectBD();
        labelText = "<html><head/><body><p><span style=\" font-size:10pt; font-weight:600; color:#ff0000;\">Desconectado</span></p></body></html>";
        ui->label_EstadoConexion->setText(labelText);
        ui->pushButton_ConectarBD->setText("Conectar");

        cleanListViewING();                                                             //_____Se borra el listview con los ingredientes mostrados en el apartado ingredientes
        cleanListViewING_en_Platos();                                                   //_____Se borra el listview con los ingredientes mostrados en el apartado platos
        cleanListViewING_de_PLA();                                                      //_____Se borra el listview con los ingredientes pertenecientes a un plato en el apartado platos
        cleanListViewPlatos();                                                          //_____Se borra el listview con los platos mostrados
        disableAMEIngredientesButtons();                                                //_____Se deshabilitan los botones de edicion del panel de ingredientes
        disableAMEPlatosButtons();                                                      //_____Se deshabilitan los botones de edicion del panel de platos
    }
}


/*-------------------------------------------------------------------------*/
/*---------- EVENTO CLICK DE LISTVIEW  DEL APARTADO INGREDIENTES ----------*/
/*-------------------------------------------------------------------------*/

void MainWindowMenuPlan::on_listView_Ingredientes_clicked(const QModelIndex &index)
{
    QString str = index.data(Qt::DisplayRole).toString();           //Elemento del listview al que se ha hecho click
    //qDebug() << str;
    QSqlQueryModel *model = db1->makeQuerys(MOSTRARINFOING, str);

    fillIngPlaTextBox(model, INGREDIENTES);

    delete model;
}

/*-------------------------------------------------------------------------*/
/*---------- EVENTO CLICK DE LISTVIEW PLATOS DEL APARTADO PLATOS ----------*/
/*-------------------------------------------------------------------------*/

void MainWindowMenuPlan::on_listView_Platos_clicked(const QModelIndex &index)
{
    QString str = index.data(Qt::DisplayRole).toString();           //Elemento del listview al que se ha hecho click
    QSqlQueryModel *model = db1->makeQuerys(MOSTRARINFOPLA, str);

    fillIngPlaTextBox(model, PLATOS);

    ui->listView_INGPLA->setModel(db1->makeQuerys(MOSTRARINGPLA, ui->label_PLAid->text()));     //Mostrar los ingredientes del plato

    delete model;
}

/*-------------------------------------------------------------------------*/
/*-------- EVENTO CLICK DE LISTVIEW DE ING EN EL APARTADO PLATOS ----------*/
/*-------------------------------------------------------------------------*/

void MainWindowMenuPlan::on_listView_Ingredientes_PLA_clicked(const QModelIndex &index)
{
    QString str = "<html><head/><body><p align=\"center\"><span style=\" font-weight:600;\">";
    str.append(index.data(Qt::DisplayRole).toString());                                         //____Elemento del listview al que se ha hecho click
    str.append("</span></p></body></html>");
    ui->label_PLAING->setText(str);
}

/*-------------------------------------------------------------------------*/
/*--- EVENTO CLICK DE LISTVIEW DE ING DE UN PLATO EN EL APARTADO PLATOS ---*/
/*-------------------------------------------------------------------------*/

void MainWindowMenuPlan::on_listView_INGPLA_clicked(const QModelIndex &index)
{
    QSqlQueryModel *model = db1->queryMostrarCantidadInGPlatos(ui->label_PLAid->text(), index.data(Qt::DisplayRole).toString());

    ui->lineEdit_PLAING_cantidad->setText(model->index(0,0).data(Qt::DisplayRole).toString());
    delete model;
}


/*-------------------------------------------------------------------------*/
/*------------ RELLENAR LOS TEXTBOX DE INGREDIENTES O PLATOS --------------*/
/*-------------------------------------------------------------------------*/

void MainWindowMenuPlan::fillIngPlaTextBox(QSqlQueryModel *model, APARTADOS A)
{   
    //___Escribir cada uno de los datos en su textbox correspondiente

    QList<QLineEdit *> alltextbox;

    switch(A)
    {
        case INGREDIENTES:
            ui->label_INGid->setText(model->index(0,0).data(Qt::DisplayRole).toString());
            ui->lineEdit_INGnombre->setText(model->index(0,1).data(Qt::DisplayRole).toString());
            ui->lineEdit_INGcantidad->setText(model->index(0,2).data(Qt::DisplayRole).toString());
            ui->lineEdit_INGcantporprecio->setText(model->index(0,3).data(Qt::DisplayRole).toString());
            ui->lineEdit_INGprecio->setText(model->index(0,4).data(Qt::DisplayRole).toString());
            ui->lineEdit_INGpreciotemp->setText(model->index(0,5).data(Qt::DisplayRole).toString());
            ui->lineEdit_INGacidofol->setText(model->index(0,6).data(Qt::DisplayRole).toString());
            ui->lineEdit_INGcalcio->setText(model->index(0,7).data(Qt::DisplayRole).toString());
            ui->lineEdit_INGenergia->setText(model->index(0,8).data(Qt::DisplayRole).toString());
            ui->lineEdit_INGfosforo->setText(model->index(0,9).data(Qt::DisplayRole).toString());
            ui->lineEdit_INGgrasa->setText(model->index(0,10).data(Qt::DisplayRole).toString());
            ui->lineEdit_INGhierro->setText(model->index(0,11).data(Qt::DisplayRole).toString());
            ui->lineEdit_INGmagnesio->setText(model->index(0,12).data(Qt::DisplayRole).toString());
            ui->lineEdit_INGpotasio->setText(model->index(0,13).data(Qt::DisplayRole).toString());
            ui->lineEdit_INGproteinas->setText(model->index(0,14).data(Qt::DisplayRole).toString());
            ui->lineEdit_INGselenio->setText(model->index(0,15).data(Qt::DisplayRole).toString());
            ui->lineEdit_INGsodio->setText(model->index(0,16).data(Qt::DisplayRole).toString());
            ui->lineEdit_INGvita->setText(model->index(0,17).data(Qt::DisplayRole).toString());
            ui->lineEdit_INGvitb1->setText(model->index(0,18).data(Qt::DisplayRole).toString());
            ui->lineEdit_INGvitb2->setText(model->index(0,19).data(Qt::DisplayRole).toString());
            ui->lineEdit_INGvitb6->setText(model->index(0,20).data(Qt::DisplayRole).toString());
            ui->lineEdit_INGvitb12->setText(model->index(0,21).data(Qt::DisplayRole).toString());
            ui->lineEdit_INGvitc->setText(model->index(0,22).data(Qt::DisplayRole).toString());
            ui->lineEdit_INGvitd->setText(model->index(0,23).data(Qt::DisplayRole).toString());
            ui->lineEdit_INGvite->setText(model->index(0,24).data(Qt::DisplayRole).toString());
            ui->lineEdit_INGyodo->setText(model->index(0,25).data(Qt::DisplayRole).toString());
            ui->lineEdit_INGzinc->setText(model->index(0,26).data(Qt::DisplayRole).toString());

            disableIngredientesTextBox();
            alltextbox = ui->groupBox_INGalimento->findChildren<QLineEdit *>();

        break;

        case PLATOS:
            ui->label_PLAid->setText(model->index(0,0).data(Qt::DisplayRole).toString());
            ui->lineEdit_PLAnombre->setText(model->index(0,1).data(Qt::DisplayRole).toString());
            ui->textEdit_PLAdescripcion->setText(model->index(0,2).data(Qt::DisplayRole).toString());
            ui->lineEdit_PLAprecio->setText(model->index(0,3).data(Qt::DisplayRole).toString());
            ui->lineEdit_PLAcantidad->setText(model->index(0,4).data(Qt::DisplayRole).toString());
            ui->lineEdit_PLAacidofol->setText(model->index(0,5).data(Qt::DisplayRole).toString());
            ui->lineEdit_PLAcalcio->setText(model->index(0,6).data(Qt::DisplayRole).toString());
            ui->lineEdit_PLAenergia->setText(model->index(0,7).data(Qt::DisplayRole).toString());
            ui->lineEdit_PLAfosforo->setText(model->index(0,8).data(Qt::DisplayRole).toString());
            ui->lineEdit_PLAgrasa->setText(model->index(0,9).data(Qt::DisplayRole).toString());
            ui->lineEdit_PLAhierro->setText(model->index(0,10).data(Qt::DisplayRole).toString());
            ui->lineEdit_PLAmagnesio->setText(model->index(0,11).data(Qt::DisplayRole).toString());
            ui->lineEdit_PLApotasio->setText(model->index(0,12).data(Qt::DisplayRole).toString());
            ui->lineEdit_PLAproteinas->setText(model->index(0,13).data(Qt::DisplayRole).toString());
            ui->lineEdit_PLAselenio->setText(model->index(0,14).data(Qt::DisplayRole).toString());
            ui->lineEdit_PLAsodio->setText(model->index(0,15).data(Qt::DisplayRole).toString());
            ui->lineEdit_PLAvita->setText(model->index(0,16).data(Qt::DisplayRole).toString());
            ui->lineEdit_PLAvitb1->setText(model->index(0,17).data(Qt::DisplayRole).toString());
            ui->lineEdit_PLAvitb2->setText(model->index(0,18).data(Qt::DisplayRole).toString());
            ui->lineEdit_PLAvitb6->setText(model->index(0,19).data(Qt::DisplayRole).toString());
            ui->lineEdit_PLAvitb12->setText(model->index(0,20).data(Qt::DisplayRole).toString());
            ui->lineEdit_PLAvitc->setText(model->index(0,21).data(Qt::DisplayRole).toString());
            ui->lineEdit_PLAvitd->setText(model->index(0,23).data(Qt::DisplayRole).toString());
            ui->lineEdit_PLAvite->setText(model->index(0,22).data(Qt::DisplayRole).toString());
            ui->lineEdit_PLAyodo->setText(model->index(0,24).data(Qt::DisplayRole).toString());
            ui->lineEdit_PLAzinc->setText(model->index(0,25).data(Qt::DisplayRole).toString());

            disablePlatosTextBox();
            alltextbox = ui->groupBox_Plato->findChildren<QLineEdit *>();

        break;
    }




    //___Controlar que los campos numericos en los textbox no superen los seis digitos

    QString str;

    for(int i = 0; i < alltextbox.size(); i++)
    {
        str = alltextbox.at(i)->text();

        if(str.size() > 6)
        {
            if(str.at(0) >= 48 && str.at(0) <= 57)
            {
                str.remove(6, (str.size()-6));
                alltextbox.at(i)->setText(str);
            }
        }
    }
}


/*-------------------------------------------------------------------------*/
/*------------ CAPTURAR LOS DATOS DE TEXTBOX DE INGREDIENTES --------------*/
/*-------------------------------------------------------------------------*/

QStringList MainWindowMenuPlan::captureTextBoxText()
{
    QStringList dataTextBox;

    dataTextBox << ui->label_INGid->text()
    << ui->lineEdit_INGnombre->text()
    << ui->lineEdit_INGcantidad->text()
    << ui->lineEdit_INGcantporprecio->text()
    << ui->lineEdit_INGprecio->text()
    << ui->lineEdit_INGpreciotemp->text()
    << ui->lineEdit_INGacidofol->text()
    << ui->lineEdit_INGcalcio->text()
    << ui->lineEdit_INGenergia->text()
    << ui->lineEdit_INGfosforo->text()
    << ui->lineEdit_INGgrasa->text()
    << ui->lineEdit_INGhierro->text()
    << ui->lineEdit_INGmagnesio->text()
    << ui->lineEdit_INGpotasio->text()
    << ui->lineEdit_INGproteinas->text()
    << ui->lineEdit_INGselenio->text()
    << ui->lineEdit_INGsodio->text()
    << ui->lineEdit_INGvita->text()
    << ui->lineEdit_INGvitb1->text()
    << ui->lineEdit_INGvitb2->text()
    << ui->lineEdit_INGvitb6->text()
    << ui->lineEdit_INGvitb12->text()
    << ui->lineEdit_INGvitc->text()
    << ui->lineEdit_INGvitd->text()
    << ui->lineEdit_INGvite->text()
    << ui->lineEdit_INGyodo->text()
    << ui->lineEdit_INGzinc->text();

    /*for (int i = 0; i < dataTextBox.size(); ++i)
    {
        qDebug() << dataTextBox.at(i);
    }*/
    return dataTextBox;
}


/*-------------------------------------------------------------------------*/
/*-------------- CONTROL DE DATOS MODIFICADOS POR EL USUARIO --------------*/
/*-------------------------------------------------------------------------*/

ACTION MainWindowMenuPlan::controllDataTextBox()
{
    ACTION A;

    if(ui->lineEdit_INGnombre->text() == "")            //Controla si el nombre esta vacio
    {
        QMessageBox::critical(this, "Error", "El campo \"Nombre\" es obligatorio.");
        A = DENY;
        return A;
    }

    QList<QLineEdit *> alltextbox = ui->groupBox_INGalimento->findChildren<QLineEdit *>();
    QString str;

    for(int i = 1; i < alltextbox.size(); i++)          //____Empieza en 1 para no contar el textbox referente al nombre
    {
        str = alltextbox.at(i)->text();
        if(str.size() == 1 && str == ".")               //____Controlar que el textbox no se rellene solo con una coma
        {
            QMessageBox::critical(this, "Error", "Un campo no puede ser rellenado sólo con una coma.");
            A = DENY;
            return A;
        }
        else if(str.size() > 6)
        {
            QMessageBox::information(this,"Información","Los campos numéricos no aceptan más de seis dígitos.");
        }

        for(int j = 0; j < str.size(); j++)             //____Se controla que el textbox numerico no contenga otro caracter que no sea digito o punto
        {
            if((str.at(j) < 48 || str.at(j) > 57) && str.at(j) != '.')
            {
                QMessageBox::critical(this, "Error", "Los campos numéricos sólo aceptan dígitos y comas decimales.");
                A = DENY;
                return A;
            }
        }

        if(alltextbox.at(i)->text() == "")              //____Si el campo numerico esta vacio se rellena con 0
        {
            alltextbox.at(i)->setText("0");
        }
        //qDebug() << alltextbox.at(i)->text();
    }

    A = ACCEPT;
    return A;
}


/*-------------------------------------------------------------------------*/
/*--------- CONTROL DE SELECCION DE DATOS AL MODIFICAR Y ELIMINAR ---------*/
/*-------------------------------------------------------------------------*/

ACTION MainWindowMenuPlan::controllSelectedING()
{
    ACTION A = ACCEPT;
    if(ui->label_INGid->text() == "")               //Controla si al querer modificar o eliminar hay un ingrediente seleccionado
    {
        QMessageBox::information(this,"Información","Debe seleccionar un ingrediente para poder modificar o eliminar.");
        A = DENY;
    }
    return A;
}





