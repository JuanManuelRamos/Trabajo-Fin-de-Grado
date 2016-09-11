#include "mainwindowmenuplan.h"
#include "ui_mainwindowmenuplan.h"
#include "ingredientes.cpp"
#include "platos.cpp"
#include "planificador.cpp"
#include "tablaplatos.cpp"
#include "individuo.cpp"

/*-------------------------------------------------------------------------*/
/*----------------------- CONSTRUCTOR Y DESTRUCTOR ------------------------*/
/*-------------------------------------------------------------------------*/

MainWindowMenuPlan::MainWindowMenuPlan(QWidget *parent) : QMainWindow(parent),ui(new Ui::MainWindowMenuPlan)
{
    ui->setupUi(this);
    db1 = new database;

    //Establecer la pestaña inicio como la pagina principal al abrir la aplicacion
    ui->tabWidget->setCurrentIndex(0);
    ui->tabWidget_PLAN_alerg_incomp->setCurrentIndex(0);

    //Cargar las imagenes en la pantalla de inicio y platos
    ui->label_image->setPixmap(QPixmap(":/images/foto_inicio.png"));
    ui->label_Aler_cereales->setPixmap(QPixmap(":/images/alerg_cereales.png"));
    ui->label_Aler_frutos_secos->setPixmap(QPixmap(":/images/alerg_frutosSecos.png"));
    ui->label_Aler_legumbres->setPixmap(QPixmap(":/images/alerg_legumbres"));
    ui->label_Aler_marisco->setPixmap(QPixmap(":/images/alerg_marisco"));
    ui->label_Aler_pescado->setPixmap(QPixmap(":/images/alerg_pescado"));
    ui->label_Aler_huevo->setPixmap(QPixmap(":/images/alerg_huevo"));
    ui->label_Aler_leche->setPixmap(QPixmap(":/images/alerg_leche"));
    ui->label_Inc_celiaco->setPixmap(QPixmap(":/images/incomp_celiaco"));
    ui->label_Inc_diabetico->setPixmap(QPixmap(":/images/incomp_diabetico"));
    ui->label_Inc_semivegetariano->setPixmap(QPixmap(":/images/incomp_semivegetariano"));
    ui->label_Inc_vegetariano->setPixmap(QPixmap(":/images/incomp_vegetariano"));
    ui->label_Inc_vegano->setPixmap(QPixmap(":/images/incomp_vegano"));
    ui->label_Aler_cereales_2->setPixmap(QPixmap(":/images/alerg_cereales.png"));
    ui->label_Aler_frutos_secos_2->setPixmap(QPixmap(":/images/alerg_frutosSecos.png"));
    ui->label_Aler_legumbres_2->setPixmap(QPixmap(":/images/alerg_legumbres"));
    ui->label_Aler_marisco_2->setPixmap(QPixmap(":/images/alerg_marisco"));
    ui->label_Aler_pescado_2->setPixmap(QPixmap(":/images/alerg_pescado"));
    ui->label_Aler_huevo_2->setPixmap(QPixmap(":/images/alerg_huevo"));
    ui->label_Aler_leche_2->setPixmap(QPixmap(":/images/alerg_leche"));
    ui->label_Inc_celiaco_2->setPixmap(QPixmap(":/images/incomp_celiaco"));
    ui->label_Inc_diabetico_2->setPixmap(QPixmap(":/images/incomp_diabetico"));
    ui->label_Inc_semivegetariano_2->setPixmap(QPixmap(":/images/incomp_semivegetariano"));
    ui->label_Inc_vegetariano_2->setPixmap(QPixmap(":/images/incomp_vegetariano"));
    ui->label_Inc_vegano_2->setPixmap(QPixmap(":/images/incomp_vegano"));
    ui->label_Aler_cereales_3->setPixmap(QPixmap(":/images/alerg_cereales.png"));
    ui->label_Aler_frutos_secos_3->setPixmap(QPixmap(":/images/alerg_frutosSecos.png"));
    ui->label_Aler_legumbres_3->setPixmap(QPixmap(":/images/alerg_legumbres"));
    ui->label_Aler_marisco_3->setPixmap(QPixmap(":/images/alerg_marisco"));
    ui->label_Aler_pescado_3->setPixmap(QPixmap(":/images/alerg_pescado"));
    ui->label_Aler_huevo_3->setPixmap(QPixmap(":/images/alerg_huevo"));
    ui->label_Aler_leche_3->setPixmap(QPixmap(":/images/alerg_leche"));
    ui->label_Inc_celiaco_3->setPixmap(QPixmap(":/images/incomp_celiaco"));
    ui->label_Inc_diabetico_3->setPixmap(QPixmap(":/images/incomp_diabetico"));
    ui->label_Inc_semivegetariano_3->setPixmap(QPixmap(":/images/incomp_semivegetariano"));
    ui->label_Inc_vegetariano_3->setPixmap(QPixmap(":/images/incomp_vegetariano"));
    ui->label_Inc_vegano_3->setPixmap(QPixmap(":/images/incomp_vegano"));


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

    disableIngredientesTextBox();                               //Deshabilitar los textbox (lineedit) de Ingredientes al arranque de la aplicacion
    disablePlatosTextBox();                                     //Deshabilitar los textbox (lineedit) de Platos al arranque de la aplicacion
    disableImagenes_Incomp_Alerg();                             //Deshabilita las imagenes de alergenos e incompatibilidades
    disablePLANElements();                                      //Se deshabilitan los elementos en la seccion de planificador


    //Establecer las fechas por defecto en la seccion del Planificador
    ui->dateEdit_desde->setDate(QDate::currentDate());
    ui->dateEdit_hasta->setDate(QDate::currentDate().addMonths(1));

    //Establecer las ingestias diarias recomendadas
    idrN.assign(NumInfN,0.0f);
    std::pair <float,float> p;
    p.first = 0.0f;
    p.second = 0.0f;
    irnMinMax.assign(NumInfN,p);
    resetIngestaDiariaRecomendada();
    disableIDR();

    //Establecer el formato del boton Generar Plan
    QFont font("Times", 12);
    ui->pushButton_PLAN_GenerarPlan->setFont(font);
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


/*--------------------------------------------------------------------------*/
/*----------------------- SETTERS DE TIPOS DE PLATO ------------------------*/
/*--------------------------------------------------------------------------*/
void MainWindowMenuPlan::setPlatos()
{
    setPrimerosPlatos();
    setSegundosPlatos();
    setPostres();
}

void MainWindowMenuPlan::setPrimerosPlatos()
{
    PrimerosPlatos.clear();                                                                                             //Se limpia el vector
    infoPlatos iP;

    QAbstractItemModel *model = ui->listWidget_PLAN_PlatosSelec->model();                                               //Se obtiene la lista de platos seleccionados
    QSqlQueryModel *model2;
    QSqlQueryModel *model3;

    for(int i = 0; i < model->rowCount(); i++)
    {
        if(db1->queryMostrarTipoPlatoNombre(model->index(i, 0).data(Qt::DisplayRole).toString()) == "1")                //Se comprueba que el plato seleccionado sea Primer Plato
        {
            model3 = db1->queryMostrarInfoPlatos(model->index(i,0).data(Qt::DisplayRole).toString());

            //ID DEL PLATO
            iP.id = model3->index(0,0).data(Qt::DisplayRole).toInt();                                                   //Consulta para obtener el id del plato

            //NUMERO DE DIAS DESDE QUE SE ELIGIO EL PLATO POR ULTIMA VEZ
            iP.nDias = imax;                                                                                            //Se asigna numero de dias desde que se eligio el plato al segundo elemento del par

            //GRUPOS ALIMENTICIOS DE LOS INGREDIENTES PRINCIPALES DEL PLATO
            model2 = db1->queryMostrarGruposAldeIngPrincipales(QString::number(iP.id));                                 //Se hace una consulta para averiguar los grupos alimenticios de los ingredientes principales del plato

            for(int j = 0; j < model2->rowCount(); j++)
                iP.gruposAl.push_back(model2->index(j,0).data(Qt::DisplayRole).toInt());                                //Se guardan los grupos alimenticios en el vector correspondiente

            //PRECIO DEL PLATO
            iP.precio = model3->index(0,3).data(Qt::DisplayRole).toFloat();

            //INFORMACION NUTRICIONAL DEL PLATO
            for(int k = 0; k < NumInfN; k++)
                iP.infoN.push_back(model3->index(0,9+k).data(Qt::DisplayRole).toFloat());

            //ALERGENOS DEL PLATO
            QString aler = db1->queryMostrarAlergPlato(model3->index(0,0).data(Qt::DisplayRole).toString());
            for(int l = 0; l < NumAlergenos; l++)
                iP.alerg.push_back(aler.at(l));

            //INCOMPATIBILIDADES ALIMENTICIAS DEL PLATO
            QString inc = db1->queryMostrarIncompPlato(model3->index(0,0).data(Qt::DisplayRole).toString());
            for(int m = 0; m < NumIncomp; m++)
                iP.incomp.push_back(inc.at(m));


            PrimerosPlatos.push_back(iP);                                                                              //Se inserta toda la informacion en el vector de platos

            /*qDebug() << "id: " <<  iP.id << " nDias: " <<  iP.nDias << "precio: " <<  iP.precio;
            for(int z = 0; z < iP.gruposAl.size(); z++)
            {
                qDebug() << iP.gruposAl[z];
            }
            qDebug() << "---";
            for(int z = 0; z < iP.infoN.size(); z++)
            {
                qDebug() << iP.infoN[z];
            }
            qDebug() << "---";
            for(int z = 0; z < iP.alerg.size(); z++)
            {
                qDebug() << iP.alerg[z];
            }
            qDebug() << "---";
            for(int z = 0; z < iP.incomp.size(); z++)
            {
                qDebug() << iP.incomp[z];
            }*/

            iP.gruposAl.clear();
            iP.infoN.clear();
            iP.alerg.clear();
            iP.incomp.clear();
            delete model2;
            delete model3;
        }
        //qDebug() << "==========";
    }
}

void MainWindowMenuPlan::setSegundosPlatos()
{
    SegundosPlatos.clear();                                                                                             //Se limpia el vector
    infoPlatos iP;

    QAbstractItemModel *model = ui->listWidget_PLAN_PlatosSelec->model();                                               //Se obtiene la lista de platos seleccionados
    QSqlQueryModel *model2;
    QSqlQueryModel *model3;

    for(int i = 0; i < model->rowCount(); i++)
    {
        if(db1->queryMostrarTipoPlatoNombre(model->index(i, 0).data(Qt::DisplayRole).toString()) == "2")                //Se comprueba que el plato seleccionado sea Primer Plato
        {
            model3 = db1->queryMostrarInfoPlatos(model->index(i,0).data(Qt::DisplayRole).toString());

            //ID DEL PLATO
            iP.id = model3->index(0,0).data(Qt::DisplayRole).toInt();                                                   //Consulta para obtener el id del plato

            //NUMERO DE DIAS DESDE QUE SE ELIGIO EL PLATO POR ULTIMA VEZ
            iP.nDias = imax;                                                                                            //Se asigna numero de dias desde que se eligio el plato al segundo elemento del par

            //GRUPOS ALIMENTICIOS DE LOS INGREDIENTES PRINCIPALES DEL PLATO
            model2 = db1->queryMostrarGruposAldeIngPrincipales(QString::number(iP.id));                                 //Se hace una consulta para averiguar los grupos alimenticios de los ingredientes principales del plato

            for(int j = 0; j < model2->rowCount(); j++)
                iP.gruposAl.push_back(model2->index(j,0).data(Qt::DisplayRole).toInt());                                //Se guardan los grupos alimenticios en el vector correspondiente

            //PRECIO DEL PLATO
            iP.precio = model3->index(0,3).data(Qt::DisplayRole).toFloat();

            //INFORMACION NUTRICIONAL DEL PLATO
            for(int k = 0; k < NumInfN; k++)
                iP.infoN.push_back(model3->index(0,9+k).data(Qt::DisplayRole).toFloat());

            //ALERGENOS DEL PLATO
            QString aler = db1->queryMostrarAlergPlato(model3->index(0,0).data(Qt::DisplayRole).toString());
            for(int l = 0; l < NumAlergenos; l++)
                iP.alerg.push_back(aler.at(l));

            //INCOMPATIBILIDADES ALIMENTICIAS DEL PLATO
            QString inc = db1->queryMostrarIncompPlato(model3->index(0,0).data(Qt::DisplayRole).toString());
            for(int m = 0; m < NumIncomp; m++)
                iP.incomp.push_back(inc.at(m));


            SegundosPlatos.push_back(iP);                                                                              //Se inserta toda la informacion en el vector de platos

            iP.gruposAl.clear();
            iP.infoN.clear();
            iP.alerg.clear();
            iP.incomp.clear();
            delete model2;
            delete model3;
        }
    }
}

void MainWindowMenuPlan::setPostres()
{
    Postres.clear();                                                                                             //Se limpia el vector
    infoPlatos iP;

    QAbstractItemModel *model = ui->listWidget_PLAN_PlatosSelec->model();                                               //Se obtiene la lista de platos seleccionados
    QSqlQueryModel *model2;
    QSqlQueryModel *model3;

    for(int i = 0; i < model->rowCount(); i++)
    {
        if(db1->queryMostrarTipoPlatoNombre(model->index(i, 0).data(Qt::DisplayRole).toString()) == "3")                //Se comprueba que el plato seleccionado sea Primer Plato
        {
            model3 = db1->queryMostrarInfoPlatos(model->index(i,0).data(Qt::DisplayRole).toString());

            //ID DEL PLATO
            iP.id = model3->index(0,0).data(Qt::DisplayRole).toInt();                                                   //Consulta para obtener el id del plato

            //NUMERO DE DIAS DESDE QUE SE ELIGIO EL PLATO POR ULTIMA VEZ
            iP.nDias = imax;                                                                                            //Se asigna numero de dias desde que se eligio el plato al segundo elemento del par

            //GRUPOS ALIMENTICIOS DE LOS INGREDIENTES PRINCIPALES DEL PLATO
            model2 = db1->queryMostrarGruposAldeIngPrincipales(QString::number(iP.id));                                 //Se hace una consulta para averiguar los grupos alimenticios de los ingredientes principales del plato

            for(int j = 0; j < model2->rowCount(); j++)
                iP.gruposAl.push_back(model2->index(j,0).data(Qt::DisplayRole).toInt());                                //Se guardan los grupos alimenticios en el vector correspondiente

            //PRECIO DEL PLATO
            iP.precio = model3->index(0,3).data(Qt::DisplayRole).toFloat();

            //INFORMACION NUTRICIONAL DEL PLATO
            for(int k = 0; k < NumInfN; k++)
                iP.infoN.push_back(model3->index(0,9+k).data(Qt::DisplayRole).toFloat());

            //ALERGENOS DEL PLATO
            QString aler = db1->queryMostrarAlergPlato(model3->index(0,0).data(Qt::DisplayRole).toString());
            for(int l = 0; l < NumAlergenos; l++)
                iP.alerg.push_back(aler.at(l));

            //INCOMPATIBILIDADES ALIMENTICIAS DEL PLATO
            QString inc = db1->queryMostrarIncompPlato(model3->index(0,0).data(Qt::DisplayRole).toString());
            for(int m = 0; m < NumIncomp; m++)
                iP.incomp.push_back(inc.at(m));


            Postres.push_back(iP);                                                                              //Se inserta toda la informacion en el vector de platos

            /*qDebug() << "id: " <<  iP.id << " nDias: " <<  iP.nDias << "precio: " <<  iP.precio;
            for(int z = 0; z < iP.gruposAl.size(); z++)
            {
                qDebug() << iP.gruposAl[z];
            }
            qDebug() << "---";
            for(int z = 0; z < iP.infoN.size(); z++)
            {
                qDebug() << iP.infoN[z];
            }
            qDebug() << "---";
            for(int z = 0; z < iP.alerg.size(); z++)
            {
                qDebug() << iP.alerg[z];
            }
            qDebug() << "---";
            for(int z = 0; z < iP.incomp.size(); z++)
            {
                qDebug() << iP.incomp[z];
            }*/

            iP.gruposAl.clear();
            iP.infoN.clear();
            iP.alerg.clear();
            iP.incomp.clear();
            delete model2;
            delete model3;
        }
    }
}


/*---------------------------------------------------------------------*/
/*----------------------- CLEAR TIPOS DE PLATO ------------------------*/
/*---------------------------------------------------------------------*/
/*void MainWindowMenuPlan::clearPrimerosPlatos()
{
    for(int i = 0; i < PrimerosPlatos.size(); i++)
        PrimerosPlatos[i].nDias = imax;
}


void MainWindowMenuPlan::clearSegundosPlatos()
{
    std::tuple<int,int,std::vector<int>> tpl;

    for(int i = 0; i < SegundosPlatos.size(); i++)
        SegundosPlatos[i].nDias = imax;
}


void MainWindowMenuPlan::clearPostres()
{
    std::tuple<int,int,std::vector<int>> tpl;

    for(int i = 0; i < Postres.size(); i++)
        Postres[i].nDias = imax;
}*/

/*--------------------------------------------------------------------------*/
/*----------------------- GETTERS DE TIPOS DE PLATO ------------------------*/
/*--------------------------------------------------------------------------*/
//std::vector<vectorPlatos> MainWindowMenuPlan::getPrimerosPlatos(){ return PrimerosPlatos; }
//std::vector<vectorPlatos> MainWindowMenuPlan::getSegundosPlatos(){ return SegundosPlatos; }
//std::vector<vectorPlatos> MainWindowMenuPlan::getPostres(){ return Postres; }



/*------------------------------------------------------------------------------------*/
/*------------- SETTER DE VECTOR DE REPETICION DE GRUPOS ALIMENTICIOS ----------------*/
/*------------------------------------------------------------------------------------*/
void MainWindowMenuPlan::setVectorGruposAlimenticios()
{
    vectorGruposAlimenticios.clear();
    std::pair<int,int> ga;
    ga.first = imax;
    ga.second = imax;

    vectorGruposAlimenticios.assign(NumGruposAlimenticios, ga);
}





/*-------------------------------------------------------------------------*/
/*------------------------ CIERRE DE LA APLICACION ------------------------*/
/*-------------------------------------------------------------------------*/

void MainWindowMenuPlan::closeEvent(QCloseEvent * event)    //Desconectarse de la base de datos al salir de la aplicacion
{
    db1->disconnectBD();
    event->accept();
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

            ui->listView_Ingredientes->setModel(db1->queryMostrarIngredientes());           //______Se hace una consulta de los ingredientes para mostrarse en el apartado ingredientes
            ui->listView_Ingredientes_PLA->setModel(ui->listView_Ingredientes->model());    //______Se muestran los ingredientes en el apartado platos
            ui->listView_Platos->setModel(db1->queryMostrarPlatos());                       //______Se hace una consulta de los platos para mostrarse
            ui->listView_PLAN_Platos->setModel(ui->listView_Platos->model());               //______Se muestran los platos en el apartado platos de la seccion Planificador
            enableAMEIngredientesButtons();                                                 //______Se habilitan los botones de edicion en el panel de ingredientes
            enableAMEPlatosButtons();                                                       //______Se habilitan los botones de edicion en el panel de platos
            enablePLANElements();                                                           //______Se habilitan los elementos en la seccion de planificador
            infoPLANPlatos();                                                               //______Mostrar la informacion de numero de platos
            getIngestaDiariaRecomendada();                                                  //______Mostrar la informacion de ingestas diarias recomendadas
            inicializarTablas();                                                            //______Inicializar las tablas donde se muestran los planes alimenticios





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
        disablePLANElements();                                                          //_____Se deshabilitan los elementos en la seccion de planificador
        limpiarTablas();                                                                //_____Se limpian las tablas en donde se muestran los planes alimenticios
    }
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
            ui->lineEdit_INGacidofol->setText(model->index(0,10).data(Qt::DisplayRole).toString());
            ui->lineEdit_INGcalcio->setText(model->index(0,11).data(Qt::DisplayRole).toString());
            ui->lineEdit_INGenergia->setText(model->index(0,12).data(Qt::DisplayRole).toString());
            ui->lineEdit_INGfosforo->setText(model->index(0,13).data(Qt::DisplayRole).toString());
            ui->lineEdit_INGgrasa->setText(model->index(0,14).data(Qt::DisplayRole).toString());
            ui->lineEdit_INGhierro->setText(model->index(0,15).data(Qt::DisplayRole).toString());
            ui->lineEdit_INGmagnesio->setText(model->index(0,16).data(Qt::DisplayRole).toString());
            ui->lineEdit_INGpotasio->setText(model->index(0,17).data(Qt::DisplayRole).toString());
            ui->lineEdit_INGproteinas->setText(model->index(0,18).data(Qt::DisplayRole).toString());
            ui->lineEdit_INGselenio->setText(model->index(0,19).data(Qt::DisplayRole).toString());
            ui->lineEdit_INGsodio->setText(model->index(0,20).data(Qt::DisplayRole).toString());
            ui->lineEdit_INGvita->setText(model->index(0,21).data(Qt::DisplayRole).toString());
            ui->lineEdit_INGvitb1->setText(model->index(0,22).data(Qt::DisplayRole).toString());
            ui->lineEdit_INGvitb2->setText(model->index(0,23).data(Qt::DisplayRole).toString());
            ui->lineEdit_INGvitb6->setText(model->index(0,24).data(Qt::DisplayRole).toString());
            ui->lineEdit_INGvitb12->setText(model->index(0,25).data(Qt::DisplayRole).toString());
            ui->lineEdit_INGvitc->setText(model->index(0,26).data(Qt::DisplayRole).toString());
            ui->lineEdit_INGvitd->setText(model->index(0,27).data(Qt::DisplayRole).toString());
            ui->lineEdit_INGvite->setText(model->index(0,28).data(Qt::DisplayRole).toString());
            ui->lineEdit_INGyodo->setText(model->index(0,29).data(Qt::DisplayRole).toString());
            ui->lineEdit_INGzinc->setText(model->index(0,30).data(Qt::DisplayRole).toString());

            alltextbox = ui->groupBox_INGalimento->findChildren<QLineEdit *>();
            mostrar_mesesTemporada(model->index(0,5).data(Qt::DisplayRole).toString());                         //Rellenar los checbox de temporada
            mostrar_alergenosIncom(INCOMPATIBILIDADES, model->index(0,6).data(Qt::DisplayRole).toString());     //Rellenar los checkbox de incompatibilidades alimenticias
            mostrar_alergenosIncom(ALERGENOS, model->index(0,7).data(Qt::DisplayRole).toString());              //Rellenar los checkbox de alergenos
            mostrar_IngredientePrincipal(model->index(0,8).data(Qt::DisplayRole).toString());                   //Mostrar si es ingrediente principal o no
            mostrar_GrupoAlimenticio(model->index(0,9).data(Qt::DisplayRole).toString());                       //Mostrar el grupo alimenticio
        break;

        case PLATOS:
            ui->label_PLAid->setText(model->index(0,0).data(Qt::DisplayRole).toString());
            ui->lineEdit_PLAnombre->setText(model->index(0,1).data(Qt::DisplayRole).toString());
            ui->textEdit_PLAdescripcion->setText(model->index(0,2).data(Qt::DisplayRole).toString());
            ui->lineEdit_PLAprecio->setText(model->index(0,3).data(Qt::DisplayRole).toString());
            ui->lineEdit_PLAcantidad->setText(model->index(0,5).data(Qt::DisplayRole).toString());
            ui->lineEdit_PLAacidofol->setText(model->index(0,9).data(Qt::DisplayRole).toString());
            ui->lineEdit_PLAcalcio->setText(model->index(0,10).data(Qt::DisplayRole).toString());
            ui->lineEdit_PLAenergia->setText(model->index(0,11).data(Qt::DisplayRole).toString());
            ui->lineEdit_PLAfosforo->setText(model->index(0,12).data(Qt::DisplayRole).toString());
            ui->lineEdit_PLAgrasa->setText(model->index(0,13).data(Qt::DisplayRole).toString());
            ui->lineEdit_PLAhierro->setText(model->index(0,14).data(Qt::DisplayRole).toString());
            ui->lineEdit_PLAmagnesio->setText(model->index(0,15).data(Qt::DisplayRole).toString());
            ui->lineEdit_PLApotasio->setText(model->index(0,16).data(Qt::DisplayRole).toString());
            ui->lineEdit_PLAproteinas->setText(model->index(0,17).data(Qt::DisplayRole).toString());
            ui->lineEdit_PLAselenio->setText(model->index(0,18).data(Qt::DisplayRole).toString());
            ui->lineEdit_PLAsodio->setText(model->index(0,19).data(Qt::DisplayRole).toString());
            ui->lineEdit_PLAvita->setText(model->index(0,20).data(Qt::DisplayRole).toString());
            ui->lineEdit_PLAvitb1->setText(model->index(0,21).data(Qt::DisplayRole).toString());
            ui->lineEdit_PLAvitb2->setText(model->index(0,22).data(Qt::DisplayRole).toString());
            ui->lineEdit_PLAvitb6->setText(model->index(0,23).data(Qt::DisplayRole).toString());
            ui->lineEdit_PLAvitb12->setText(model->index(0,24).data(Qt::DisplayRole).toString());
            ui->lineEdit_PLAvitc->setText(model->index(0,25).data(Qt::DisplayRole).toString());
            ui->lineEdit_PLAvitd->setText(model->index(0,26).data(Qt::DisplayRole).toString());
            ui->lineEdit_PLAvite->setText(model->index(0,27).data(Qt::DisplayRole).toString());
            ui->lineEdit_PLAyodo->setText(model->index(0,28).data(Qt::DisplayRole).toString());
            ui->lineEdit_PLAzinc->setText(model->index(0,29).data(Qt::DisplayRole).toString());
            mostrarTipoPlato(model->index(0,4).data(Qt::DisplayRole).toString());

            alltextbox = ui->groupBox_Plato->findChildren<QLineEdit *>();
            disableImagenes_Incomp_Alerg();
            mostrar_Incomp_Alerg_Plato();
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


/*----------------------------------------------------------------------------*/
/*--------- CAPTURAR LOS DATOS DE TEXTBOX DE INGREDIENTES O PLATOS -----------*/
/*----------------------------------------------------------------------------*/

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
            << set_IngredientePrincipal()
            << set_GrupoAlimenticio()
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



/*---------------------------------------------------------------------------------------------*/
/*-------------------- RESETEO DE VALORES DE INGESTIA DIARIA RECOMENDADA ----------------------*/
/*---------------------------------------------------------------------------------------------*/
void MainWindowMenuPlan::resetIngestaDiariaRecomendada()
{ 
    /*
    idrN[0] = 135;              //acido folico
    idrN[1] = 585;              //calcio
    idrN[2] = 1012;             //energia
    idrN[3] = 562.5f;           //fosforo
    idrN[4] = 31.72f;           //grasa
    idrN[5] = 8.55f;            //hierro
    idrN[6] = 112.5f;           //magnesio
    idrN[7] = 2025;             //potasio
    idrN[8] = 27.08f;           //proteinas
    idrN[9] = 25.75;            //selenio
    idrN[10] = 870;             //sodio
    idrN[11] = 450;             //vitA
    idrN[12] = 0.41f;           //vitB1
    idrN[13] = 0.63f;           //vitB2
    idrN[14] = 0.54f;           //vitB6
    idrN[15] = 2.28f;           //vitB12
    idrN[16] = 27;              //vitC
    idrN[17] = 4.65f;           //vitD
    idrN[18] = 6.3f;            //vitE
    idrN[19] = 67.5f;           //yodo
    idrN[20] = 6.75f;           //zinc
    */

    std::fstream fs;
    fs.open("ingestarecomendada.txt", std::fstream::in);                                                        //Si el archivo existe se abre

    if(!fs.is_open())                                                                                           //Si el archivo no existe se crea
    {
        fs.open("ingestarecomendada.txt", std::fstream::out | std::fstream::trunc);
        fs << "135\n" << "585\n" << "1012\n" << "562.5\n" << "31.72\n" << "8.55\n" << "112.5\n" << "2025\n" << "27.08\n" << "25.75\n" << "870\n" << "450\n" << "0.41\n" << "0.63\n" << "0.54\n" << "2.28\n" << "27\n" << "4.65\n" << "6.3\n" << "67.5\n" << "6.75\n";
        fs.close();
        fs.open("ingestarecomendada.txt", std::fstream::in);
    }
    std::string data;
    std::string::size_type sz;

    for(int i = 0; i < NumInfN; i++)
    {
        fs >> data;
        idrN[i] = std::stof(data,&sz);
    }
    fs.close();


    /*for(int i = 0; i < idrN.size(); i++)
        qDebug() << QString::number(idrN[i]);*/
}



