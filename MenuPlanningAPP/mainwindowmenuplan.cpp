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

    //Establecer la pestaña inicio como la pagina principal al abrir la aplicacion
    ui->tabWidget->setCurrentIndex(0);

    //Cargar la imagen en la pantalla de inicio
    QImage image("foto_inicio.png");
    QPixmap pixm = QPixmap(":/images/foto_inicio.png");
    ui->label_image->setPixmap(pixm);

    //Establecer el tamaño de los elementos en la parte de ingredientes del plato (ya que en ocasiones se redimensionaba)
    ui->pushButton_PLAING_aniadir->setMinimumSize(66,23);
    ui->pushButton_PLAING_modificar->setMinimumSize(65,23);
    ui->pushButton_PLAING_eliminar->setMinimumSize(66,23);
    ui->label_123->setMinimumSize(66,20);
    ui->lineEdit_PLAING_cantidad->setMinimumSize(65,20);
    ui->label_124->setMinimumSize(66,20);
    ui->pushButton_PLAING_aniadir->setMaximumSize(66,23);
    ui->pushButton_PLAING_modificar->setMaximumSize(65,23);
    ui->pushButton_PLAING_eliminar->setMaximumSize(66,23);
    ui->label_123->setMaximumSize(66,20);
    ui->lineEdit_PLAING_cantidad->setMaximumSize(65,20);
    ui->label_124->setMaximumSize(66,20);

    //Establecimiento de los checkbox en en layout con sus respectivos nombres
    lay->addWidget(check);
    lay->addWidget(check1);
    lay->addWidget(check2);
    lay->addWidget(check3);
    lay->addWidget(check4);
    lay->addWidget(check5);
    lay->addWidget(check6);
    lay->addWidget(check7);
    lay->addWidget(check8);
    lay->addWidget(check9);
    lay->addWidget(check10);
    lay->addWidget(check11);
    lay->addWidget(check12);
    ui->scrollAreaWidgetContents->setLayout(lay);
    connect(check, SIGNAL(stateChanged(int)), this, SLOT(checkboxClicked()));       //Creacion del evento click en el checkbox de Marcar/Desmarcar todos

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
    delete lay;
    delete check;
    delete check1;
    delete check2;
    delete check3;
    delete check4;
    delete check5;
    delete check6;
    delete check7;
    delete check8;
    delete check9;
    delete check10;
    delete check11;
    delete check12;
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

void MainWindowMenuPlan::enableIngredientesTextBox()        //habilitar los textbox (linedit) y ceckbox del apartado Ingredientes
{
    QList<QLineEdit *> alltextbox = ui->groupBox_INGalimento->findChildren<QLineEdit *>();

    for(int i = 0; i < alltextbox.size(); i++)
    {
        alltextbox.at(i)->setEnabled(true);
    }

    ui->groupBox_incompatibilidades->setEnabled(true);                                          //habilita los checbox de icompatibilidades
    ui->groupBox_alergenos->setEnabled(true);                                                   //habilita los checbox de alergenos

    QList<QCheckBox *> allcheckbox = ui->scrollArea_temporada->findChildren<QCheckBox *>();     //habilita los checkbox de temporada
    for(int i = 0; i < allcheckbox.size(); i++)
        allcheckbox.at(i)->setEnabled(true);

}

void MainWindowMenuPlan::disableIngredientesTextBox()       //deshabilitar los textbox (linedit) y checkbox del apartado Ingredientes
{
    QList<QLineEdit *> alltextbox = ui->groupBox_INGalimento->findChildren<QLineEdit *>();

    for(int i = 0; i < alltextbox.size(); i++)
    {
        alltextbox.at(i)->setEnabled(false);
    }

    ui->groupBox_incompatibilidades->setEnabled(false);                                         //deshabilita los checbox de icompatibilidades
    ui->groupBox_alergenos->setEnabled(false);                                                  //deshabilita los checbox de alergenos

    QList<QCheckBox *> allcheckbox = ui->scrollArea_temporada->findChildren<QCheckBox *>();     //deshabilita los checkbox de temporada
    for(int i = 0; i < allcheckbox.size(); i++)
        allcheckbox.at(i)->setEnabled(false);
}

/*---------------------------------------------------------------------------------------------------------------------*/

void MainWindowMenuPlan::enablePlatosTextBox()              //habilitar los textbox (linedit) del apartado Platos
{
    ui->lineEdit_PLAnombre->setEnabled(true);
    ui->lineEdit_PLAprecio->setEnabled(true);
    ui->lineEdit_PLAcantidad->setEnabled(true);
    ui->textEdit_PLAdescripcion->setEnabled(true);
    ui->lineEdit_PLAING_cantidad->setEnabled(true);
    ui->radioButton_primerP->setEnabled(true);
    ui->radioButton_segundoP->setEnabled(true);
    ui->radioButton_postre->setEnabled(true);
}

void MainWindowMenuPlan::disablePlatosTextBox()             //deshabilitar los textbox (linedit) del apartado Platos
{
    ui->lineEdit_PLAnombre->setEnabled(false);
    ui->lineEdit_PLAprecio->setEnabled(false);
    ui->lineEdit_PLAcantidad->setEnabled(false);
    ui->textEdit_PLAdescripcion->setEnabled(false);
    ui->lineEdit_PLAING_cantidad->setEnabled(false);
    ui->listView_Ingredientes_PLA->setEnabled(false);
    ui->radioButton_primerP->setEnabled(false);
    ui->radioButton_segundoP->setEnabled(false);
    ui->radioButton_postre->setEnabled(false);
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

void MainWindowMenuPlan::cleanListViewING_de_PLA()          //Se borra el listview con los ingredientes correspondientes a un plato
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
    disableAMEIngredientesButtons();                                            //deshabilitar botones AME
    enableGCIngredientesButtons();                                              //habilitar botones GC
    clearIngredientesTextBox();                                                 //Limpiar textbox
    enableIngredientesTextBox();                                                //habilitar textbox

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

/*--------------------------------------------------------- AME PLATOS ------------------------------------------------------------*/

void MainWindowMenuPlan::on_pushButton_Aniadir_PLA_clicked()
{
    disableAMEPlatosButtons();                                                  //deshabilitar los botones AME
    enableGCPlatosButtons();                                                    //habilitar los botones GC
    clearPlatosTextBox();                                                       //limpiar los textbox
    enablePlatosTextBox();                                                      //habilitar los textbox
    ui->radioButton_primerP->setChecked(true);                                  //Activa por defecto el tipo Primer plato

    ui->listView_Platos->setEnabled(false);                                     //deshabilitar el listview de platos
    ui->listView_Platos->clearSelection();                                      //eliminar la seleccion en el listview de platos

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
        }
    }
}

/*--------------------------------------------------------- GC INGREDIENTES ------------------------------------------------------------*/

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
}

void MainWindowMenuPlan::on_pushButton_Cancelar_clicked()
{
    enableAMEIngredientesButtons();                             //habilita los botones AME
    disableGCIngredientesButtons();                             //deshabilita los botones GC
    disableIngredientesTextBox();                               //deshabilita los textbox
    clearIngredientesTextBox();                                 //limpia los textbox

    ui->label_InfoQuerys->setText("");                          //borra el label informativo
    ui->listView_Ingredientes->clearSelection();                //Desselecciona el posible ingrediente seleccionado en el listview
}

/*--------------------------------------------------------- GC PLATOS ------------------------------------------------------------*/

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
                    disablePlatosTextBox();                                             //deshabilitar los textbox

                    ui->listView_Platos->setEnabled(true);                      //habilitar el listview de platos
                }
            }
            else                                                                //__Si hay algun fallo en los datos introducidos
            {
                disableGCPlatosButtons();                                       //deshabilitar los botones GC
                enableAMEPlatosButtons();                                       //habilitar los botones AME
                clearPlatosTextBox();                                           //limpiar los textbox
                disablePlatosTextBox();                                             //deshabilitar los textbox

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
            }

            disableGCPlatosButtons();                                       //deshabilitar los botones GC
            disableAMEINGPLAButtons();                                      //deshabilitar los botones AME de ingredientes
            enableAMEPlatosButtons();                                       //habilitar los botones AME
            clearPlatosTextBox();                                           //limpiar los textbox
            disablePlatosTextBox();                                         //deshabilitar los textbox

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

    ui->listView_Ingredientes_PLA->clearSelection();            //Desselecciona el posible ingrediente seleccionado en el listview
    ui->listView_Platos->clearSelection();                      //Desselecciona el posible ingrediente seleccionado en el listview

    ui->listView_Platos->setEnabled("true");
    ui->label_InfoQuerys_2->setText("");                          //Label informativo
    ui->lineEdit_PLAING_cantidad->setText("");
}


/*--------------------------------------------------------- AME ING PLATOS ------------------------------------------------------------*/

void MainWindowMenuPlan::on_pushButton_PLAING_aniadir_clicked()
{
    ACTION A = controllSelectionElement(*ui->listView_Ingredientes_PLA);                                    //Controlar que haya un elemento seleccionado
    ACTION B = controllDataTextBoxNum(*ui->groupBox_PLAING, 0);                                             //Controlar que el nombre es correcto

    const QModelIndexList indexL = ui->listView_Ingredientes_PLA->selectionModel()->selectedIndexes();      //Captura la seleccion del listview de ingredientes
    const QModelIndex index = indexL.at(0);

    ACTION C = db1->controllQuerys(ANIADIRINGPLA, INGDEPLATO, index.data(Qt::DisplayRole).toString(), ui->label_PLAid->text());         //Controla que no se añadan al plato ingredientes ya añadidos

    if(A == ACCEPT && B == ACCEPT && C == ACCEPT)
    {
        db1->addINGtoPLAQuery(ui->label_PLAid->text(), index.data(Qt::DisplayRole).toString(), ui->lineEdit_PLAING_cantidad->text());   //Consulta para añadir ingrediente
        ui->listView_INGPLA->setModel(db1->makeQuerys(MOSTRARINGPLA, ui->label_PLAid->text()));                                         //Consulta para mostrar los ingredientes del plato
        ui->lineEdit_PLAING_cantidad->setText("");                                                                                      //Limpiar el textbox cantidad
        nutricionalInfo();                                                                                                              //Calcular la informacion nutricional del plato
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
        }
    }
}


/*--------------------------------------------------------- CHECKBOX MARCAR O DESMARCAR TODOS ------------------------------------------------------------*/

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
        clearIngredientesTextBox();                                                     //_____Se borran los textbox de ingredientes
        clearPlatosTextBox();                                                           //_____Se borran los textbox de platos
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
    QSqlQueryModel *model = db1->makeQuerys(MOSTRARINFOING, str);   //Consulta para mostrar los datos del ingrediente seleccionado

    fillIngPlaTextBox(model, INGREDIENTES);                         //Rellenar los textbox con la informacion del ingrediente

    delete model;
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
            ui->lineEdit_INGacidofol->setText(model->index(0,8).data(Qt::DisplayRole).toString());
            ui->lineEdit_INGcalcio->setText(model->index(0,9).data(Qt::DisplayRole).toString());
            ui->lineEdit_INGenergia->setText(model->index(0,10).data(Qt::DisplayRole).toString());
            ui->lineEdit_INGfosforo->setText(model->index(0,11).data(Qt::DisplayRole).toString());
            ui->lineEdit_INGgrasa->setText(model->index(0,12).data(Qt::DisplayRole).toString());
            ui->lineEdit_INGhierro->setText(model->index(0,13).data(Qt::DisplayRole).toString());
            ui->lineEdit_INGmagnesio->setText(model->index(0,14).data(Qt::DisplayRole).toString());
            ui->lineEdit_INGpotasio->setText(model->index(0,15).data(Qt::DisplayRole).toString());
            ui->lineEdit_INGproteinas->setText(model->index(0,16).data(Qt::DisplayRole).toString());
            ui->lineEdit_INGselenio->setText(model->index(0,17).data(Qt::DisplayRole).toString());
            ui->lineEdit_INGsodio->setText(model->index(0,18).data(Qt::DisplayRole).toString());
            ui->lineEdit_INGvita->setText(model->index(0,19).data(Qt::DisplayRole).toString());
            ui->lineEdit_INGvitb1->setText(model->index(0,20).data(Qt::DisplayRole).toString());
            ui->lineEdit_INGvitb2->setText(model->index(0,21).data(Qt::DisplayRole).toString());
            ui->lineEdit_INGvitb6->setText(model->index(0,22).data(Qt::DisplayRole).toString());
            ui->lineEdit_INGvitb12->setText(model->index(0,23).data(Qt::DisplayRole).toString());
            ui->lineEdit_INGvitc->setText(model->index(0,24).data(Qt::DisplayRole).toString());
            ui->lineEdit_INGvitd->setText(model->index(0,25).data(Qt::DisplayRole).toString());
            ui->lineEdit_INGvite->setText(model->index(0,26).data(Qt::DisplayRole).toString());
            ui->lineEdit_INGyodo->setText(model->index(0,27).data(Qt::DisplayRole).toString());
            ui->lineEdit_INGzinc->setText(model->index(0,28).data(Qt::DisplayRole).toString());

            alltextbox = ui->groupBox_INGalimento->findChildren<QLineEdit *>();
            mostrar_mesesTemporada(model->index(0,5).data(Qt::DisplayRole).toString());                         //Rellenar los checbox de temporada
            mostrar_alergenosIncom(INCOMPATIBILIDADES, model->index(0,6).data(Qt::DisplayRole).toString());     //Rellenar los checkbox de incompatibilidades alimenticias
            mostrar_alergenosIncom(ALERGENOS, model->index(0,7).data(Qt::DisplayRole).toString());              //Rellenar los checkbox de alergenos
        break;

        case PLATOS:
            ui->label_PLAid->setText(model->index(0,0).data(Qt::DisplayRole).toString());
            ui->lineEdit_PLAnombre->setText(model->index(0,1).data(Qt::DisplayRole).toString());
            ui->textEdit_PLAdescripcion->setText(model->index(0,2).data(Qt::DisplayRole).toString());
            ui->lineEdit_PLAprecio->setText(model->index(0,3).data(Qt::DisplayRole).toString());
            ui->lineEdit_PLAcantidad->setText(model->index(0,5).data(Qt::DisplayRole).toString());
            ui->lineEdit_PLAacidofol->setText(model->index(0,6).data(Qt::DisplayRole).toString());
            ui->lineEdit_PLAcalcio->setText(model->index(0,7).data(Qt::DisplayRole).toString());
            ui->lineEdit_PLAenergia->setText(model->index(0,8).data(Qt::DisplayRole).toString());
            ui->lineEdit_PLAfosforo->setText(model->index(0,9).data(Qt::DisplayRole).toString());
            ui->lineEdit_PLAgrasa->setText(model->index(0,10).data(Qt::DisplayRole).toString());
            ui->lineEdit_PLAhierro->setText(model->index(0,11).data(Qt::DisplayRole).toString());
            ui->lineEdit_PLAmagnesio->setText(model->index(0,12).data(Qt::DisplayRole).toString());
            ui->lineEdit_PLApotasio->setText(model->index(0,13).data(Qt::DisplayRole).toString());
            ui->lineEdit_PLAproteinas->setText(model->index(0,14).data(Qt::DisplayRole).toString());
            ui->lineEdit_PLAselenio->setText(model->index(0,15).data(Qt::DisplayRole).toString());
            ui->lineEdit_PLAsodio->setText(model->index(0,16).data(Qt::DisplayRole).toString());
            ui->lineEdit_PLAvita->setText(model->index(0,17).data(Qt::DisplayRole).toString());
            ui->lineEdit_PLAvitb1->setText(model->index(0,18).data(Qt::DisplayRole).toString());
            ui->lineEdit_PLAvitb2->setText(model->index(0,19).data(Qt::DisplayRole).toString());
            ui->lineEdit_PLAvitb6->setText(model->index(0,20).data(Qt::DisplayRole).toString());
            ui->lineEdit_PLAvitb12->setText(model->index(0,21).data(Qt::DisplayRole).toString());
            ui->lineEdit_PLAvitc->setText(model->index(0,22).data(Qt::DisplayRole).toString());
            ui->lineEdit_PLAvitd->setText(model->index(0,23).data(Qt::DisplayRole).toString());
            ui->lineEdit_PLAvite->setText(model->index(0,24).data(Qt::DisplayRole).toString());
            ui->lineEdit_PLAyodo->setText(model->index(0,25).data(Qt::DisplayRole).toString());
            ui->lineEdit_PLAzinc->setText(model->index(0,26).data(Qt::DisplayRole).toString());
            mostrarTipoPlato(model->index(0,4).data(Qt::DisplayRole).toString());

            alltextbox = ui->groupBox_Plato->findChildren<QLineEdit *>();
        break;
    }




    //___Controlar que los campos numericos en los textbox no superen los maxNumSize digitos
    /*___Este control se hace en esta funcion aparte de en controllDataTextBoxNum ya que en ocasiones la recogida de datos
     * desde la base de datos devuelve valores numericos mayores a maxNumSize. La funcion controllDataTextBoxNum se utiliza
     * cuando se generan datos por parte del usuario, esta funcion actua cuando se recogen datos de la base de datos.
     */

    QString str;
    ACTION AC = ACCEPT;

    for(int i = 0; i < alltextbox.size(); i++)
    {
        str = alltextbox.at(i)->text();
        AC = ACCEPT;

        if(str.size() > maxNumSize)
        {
            for(int j = 0; j < str.size(); j++)                     //__Controlar que el textbox no corresponda a un textbox no numerico
            {
                if((str.at(j) < 48 || str.at(j) > 57) && str.at(j) != '.')
                {
                    AC = DENY;
                    break;
                }
            }

            if(AC == ACCEPT)                                        //__En caso de que el textbox sea numerico y superior a maxNumSize
            {
                str.remove(maxNumSize, (str.size()-maxNumSize));    //Borrar el contenido que exceda maxNumSize
                alltextbox.at(i)->setText(str);
            }
        }
    }
}


/*-------------------------------------------------------------------------*/
/*------------ CAPTURAR LOS DATOS DE TEXTBOX DE INGREDIENTES --------------*/
/*-------------------------------------------------------------------------*/

QStringList MainWindowMenuPlan::captureTextBoxText(APARTADOS AP)
{
    //Captura los datos escritos en los textbox de ingredientes o platos y los guarda en una lista

    QStringList dataTextBox;

    switch(AP)
    {
        case INGREDIENTES:     
            dataTextBox << ui->label_INGid->text()
            << ui->lineEdit_INGnombre->text()
            << ui->lineEdit_INGcantidad->text()
            << ui->lineEdit_INGcantporprecio->text()
            << ui->lineEdit_INGprecio->text()
            << set_mesesTemporada()                         //Rellenar el array mesesTemporada
            << set_Incompatibilidades()                     //Rellena el array ary_incomp
            << set_Alergenos()                              //Rellena el array ary_alergenos
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
        break;

        case PLATOS:
            dataTextBox << ui->label_PLAid->text()
            << ui->lineEdit_PLAnombre->text()
            << ui->textEdit_PLAdescripcion->toPlainText()
            << ui->lineEdit_PLAprecio->text()
            << setTipoPlato()
            << ui->lineEdit_PLAcantidad->text()
            << ui->lineEdit_PLAacidofol->text()
            << ui->lineEdit_PLAcalcio->text()
            << ui->lineEdit_PLAenergia->text()
            << ui->lineEdit_PLAfosforo->text()
            << ui->lineEdit_PLAgrasa->text()
            << ui->lineEdit_PLAhierro->text()
            << ui->lineEdit_PLAmagnesio->text()
            << ui->lineEdit_PLApotasio->text()
            << ui->lineEdit_PLAproteinas->text()
            << ui->lineEdit_PLAselenio->text()
            << ui->lineEdit_PLAsodio->text()
            << ui->lineEdit_PLAvita->text()
            << ui->lineEdit_PLAvitb1->text()
            << ui->lineEdit_PLAvitb2->text()
            << ui->lineEdit_PLAvitb6->text()
            << ui->lineEdit_PLAvitb12->text()
            << ui->lineEdit_PLAvitc->text()
            << ui->lineEdit_PLAvitd->text()
            << ui->lineEdit_PLAvite->text()
            << ui->lineEdit_PLAyodo->text()
            << ui->lineEdit_PLAzinc->text();
        break;
    }

    return dataTextBox;
}


/*-------------------------------------------------------------------------*/
/*---------- CONTROL DEL CAMPO NOMBRE PARA INGREDIENTES O PLATOS ----------*/
/*-------------------------------------------------------------------------*/

ACTION MainWindowMenuPlan::controllDataTextBoxName(QLineEdit &le)
{
    //Controla si el nombre esta vacio (obligatorio), en cuyo caso retorna un acceso denegado
    ACTION A = ACCEPT;

    if(le.text() == "")
    {
        QMessageBox::critical(this, "Error", "El campo \"Nombre\" es obligatorio.");
        A = DENY;
    }

    return A;
}


/*-------------------------------------------------------------------------*/
/*-------- CONTROL DE DATOS NUMERICOS INTRODUCIDOS O MODIFICADOS ----------*/
/*-------------------------------------------------------------------------*/

ACTION MainWindowMenuPlan::controllDataTextBoxNum(QGroupBox &gb, int indexFor)
{
    //Controla si los textbox numericos cumplen con los requisitos para ser validos

    ACTION A;
    QList<QLineEdit *> alltextbox = gb.findChildren<QLineEdit *>();
    QString str;

    for(int i = indexFor; i < alltextbox.size(); i++)                   //____Empieza en 1 para no contar el textbox referente al nombre
    {
        str = alltextbox.at(i)->text();
        if(str.size() == 1 && str == ".")                               //____Controlar que el textbox no se rellene solo con una coma
        {
            QMessageBox::critical(this, "Error", "Un campo no puede ser rellenado sólo con una coma.");
            A = DENY;
            return A;
        }
        else if(str.size() > maxNumSize)                                //____Controlar que el campo numerico no sea superior a MaxNumSize digitos
        {
            QString str2 = "Los campos numericos no aceptan mas de ";
            str2.append(QString::number(maxNumSize));
            str2.append(" dígitos.");
            QMessageBox::information(this,"Información",str2);

            str.remove(maxNumSize, (str.size()-maxNumSize));
            alltextbox.at(i)->setText(str);
        }

        for(int j = 0; j < str.size(); j++)                             //____Se controla que el textbox numerico no contenga otro caracter que no sea digito o punto
        {
            if((str.at(j) < 48 || str.at(j) > 57) && str.at(j) != '.')
            {
                QMessageBox::critical(this, "Error", "Los campos numéricos sólo aceptan dígitos y comas decimales.");
                A = DENY;
                return A;
            }
        }

        if(alltextbox.at(i)->text() == "")                              //____Si el campo numerico esta vacio se rellena con 0
        {
            alltextbox.at(i)->setText("0");
        }
    }

    A = ACCEPT;
    return A;
}


/*-------------------------------------------------------------------------*/
/*-------------------- CONTROL DE SELECCION DE DATOS ----------------------*/
/*-------------------------------------------------------------------------*/

ACTION MainWindowMenuPlan::controllSelectionElement(QListView &lv)
{
    ACTION A = ACCEPT;
    const QModelIndexList index = lv.selectionModel()->selectedIndexes();       //Captura la seleccion del listview

    if(index.size() != 1)                                                       //Controla si se ha seleccionado en elemento del listview
    {
        A = DENY;
        QMessageBox::information(this,"Información","Debe seleccionar un elemento de la lista.");
    }
    return A;
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
/*--------- MUESTRA LOS CHECKBOX SEGUN LAs INCOMPATIBILIDADES ALIMENTICIAS Y ALERGENOS ------------*/
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


void MainWindowMenuPlan::mostrarTipoPlato(QString tipo)
{
    if(tipo == "1")
        ui->radioButton_primerP->setChecked(true);
    else if (tipo == "2")
        ui->radioButton_segundoP->setChecked(true);
    else
        ui->radioButton_postre->setChecked(true);
}
