#ifndef MAINWINDOWMENUPLAN_H
#define MAINWINDOWMENUPLAN_H

#include <QMainWindow>
#include <QApplication>
#include <QtSql>
#include <QMessageBox>
#include <QCloseEvent>
#include <iostream>
#include <fstream>
#include <vector>
#include <stdlib.h>
#include <time.h>
#include <limits>
#include <sstream>
#include <ctime>

#include "database.h"
#include "enums.h"
#include "individuo.h"
#include <QGroupBox>
#include <QtWidgets>

struct infoPlatos                       //Struct que almacena informacion de los platos utilizada en el proceso de creacion del plan
{
    int id;                             //Id del plato
    int nDias;                          //Numero de dias desde que se eligio el plato en el plan por ultima vez
    float precio;                       //Precio del plato
    std::vector<int> gruposAl;          //Grupos alimenticios correspondientes a los ingredientes principales del plato
    std::vector<float> infoN;           //Informacion nutricional del plato
    std::vector<QString> alerg;         //Alergenos del plato
    std::vector<QString> incomp;        //Incompatibilidades del plato
};


namespace Ui {class MainWindowMenuPlan;}

class database;
class individuo;




class MainWindowMenuPlan : public QMainWindow
{
    Q_OBJECT

private:
        Ui::MainWindowMenuPlan *ui;                 //Objeto de interfaz
        database *db1;                              //Objeto de base de datos
        QUERYS Q;                                   //Objeto de enum

        /*-- Variables de control de datos --*/
        const static int maxNumSize = 6;                        //Numero maximo de digitos en un campo numerico
        const static int NumInfN = 21;                          //Numero de datos nutricionales
        const static int NumMesesTemp = 12;                     //Numero de meses de temporada
        const static int NumAlergenos = 7;                      //Numero de alergenos
        const static int NumIncomp = 5;                         //Numero de incompatibilidades alimenticias
        const static int NumGruposAlimenticios = 10;            //Numero de grupos alimenticios
        const static int NumObjetivos = 2;                      //Numero de objetivos del problema = 2 (objetivo de precio y grado de repeticion de alimentos)
        int numDiasPlan;                                        //Numero de dias para los que se hace el plan
        const static int NumIndividuos = 30;                   //Numero de individuos a generarse en la primera poblacion
        const static int NumGeneraciones = 500;




        /*-- Arrays de datos--*/
        char mesesTemporada[NumMesesTemp];          //Array de meses de temporada
        char ary_alergenos[NumAlergenos];           //Array de alergenos
        char ary_incomp[NumIncomp];                 //Array de incompatibilidades alimenticias

        /*-- Checkbox correspondientes a los meses de temporada y layout que los contiene --*/
        QVBoxLayout *lay = new QVBoxLayout(this);
        QCheckBox *check = new QCheckBox("Todos / ninguno");
        QCheckBox *check1 = new QCheckBox("Enero");
        QCheckBox *check2 = new QCheckBox("Febrero");
        QCheckBox *check3 = new QCheckBox("Marzo");
        QCheckBox *check4 = new QCheckBox("Abril");
        QCheckBox *check5 = new QCheckBox("Mayo");
        QCheckBox *check6 = new QCheckBox("Junio");
        QCheckBox *check7 = new QCheckBox("Julio");
        QCheckBox *check8 = new QCheckBox("Agosto");
        QCheckBox *check9 = new QCheckBox("Septiembre");
        QCheckBox *check10 = new QCheckBox("Octubre");
        QCheckBox *check11 = new QCheckBox("Noviembre");
        QCheckBox *check12 = new QCheckBox("Diciembre");

        /*-- Vector correspondiente a la ingesta diaria recomendada --*/
        std::vector<float> idrN;
        std::vector< std::pair <float,float> > irnMinMax;       //Valores recomendados de nutrientes minimos y maximos permitidos en un plan alimenticio


        /*-- Constante y vectores para la generacion del menu --*/
        const int imax = std::numeric_limits<int>::max();                                   //Constante que almacena el numero maximo posible para un int
        std::vector<infoPlatos> PrimerosPlatos;                                             //Vector de struct (id de plato, numero de dias desde que se eligio este plato en un menu, vector de grupos alimenticios de ingredientes principales de plato, coste, informacion nutricional, alergenos, incompatibilidades)
        std::vector<infoPlatos> SegundosPlatos;                                             //...
        std::vector<infoPlatos> Postres;                                                    //...
        std::vector<std::pair<int,int>> vectorGruposAlimenticios;                           //Vector de pares que guarda el numero de dias desde que se eligio por ultima vez (.first) y el numero de veces en los que se repite el mismo dia (.second)
        std::vector<std::vector<int>> vectorFicheroDeTabla;                                 //Vector que almacena la tabla de grado de variabilidad de los platos escrita en el fichero tablaplatos.txt


        /*-- Datos correspondientes a los individuos y poblaciones del problema --*/
        std::vector<individuo> indPoblacion;                                                //Vector de individuos que almacena todos los individuos de la poblacion
        std::vector<individuo> meetingPool;                                                 //Vector donde se almacenan los mejores padres en cada generacion
        std::vector<individuo> planesRecomendados;
        std::vector<individuo> planesEspeciales;



    public:
        explicit MainWindowMenuPlan(QWidget *parent = 0);
        ~MainWindowMenuPlan();



        //Funciones de control de datos
        void fillIngPlaTextBox(QSqlQueryModel *model, APARTADOS A);             //Rellena los textbox con los datos de cada ingrediente o plato
        QStringList captureTextBoxText(APARTADOS AP);                           //Captura los datos escritos en los textbox
        ACTION controllDataTextBoxName(QLineEdit &le);                          //Controla si el campo "nombre" de un ingrediente o plato esta vacio o no
        ACTION controllDataTextBoxNum(QGroupBox &gb, int indexFor);             //Controla que los datos numericos introducidos o modificados por el usuario sean validos
        ACTION controllSelectionElement(QListView &lv);                         //Controla si se ha seleccionado un elemento de un listview para su posterior manipulacion


        /*--------------------*/
        /*--- INGREDIENTES ---*/
        /*--------------------*/
        void enableGCIngredientesButtons();                     //habilitar los botones Guardar y Cancelar del apartado Ingredientes
        void disableGCIngredientesButtons();                    //deshabilitar los botones Guardar y Cancelar del apartado Ingredientes
        void enableAMEIngredientesButtons();                    //habilitar los botones Añadir, Modificar y Eliminar del apartado Ingredientes
        void disableAMEIngredientesButtons();                   //deshabilitar los botones Añadir, Modificar y Eliminar del apartado Ingredientes

        void cleanListViewING();                                //Limpia de contenido el list view de Ingredientes

        void enableIngredientesTextBox();                       //habilitar los textbox (linedit) del apartado Ingredientes
        void disableIngredientesTextBox();                      //deshabilitar los textbox (linedit) del apartado Ingredientes
        void clearIngredientesTextBox();                        //Deja en blanco todos los textbox del apartado Ingredientes

        QString set_mesesTemporada();                                           //Rellena el array mesesTemporada segun los meses en los que un ingrediente esta de temporada
        QString set_Incompatibilidades();                                       //Rellena el array de incompatibilidades
        QString set_Alergenos();                                                //Rellena el array de alergenos
        void mostrar_mesesTemporada(QString meses);                             //Muestra en la aplicacion los meses en los que un ingrediente esta de temporada
        void mostrar_alergenosIncom(CHECKBOX CB, QString array);                //Muestra en la aplicacion los alergenos y/o las incompatibilidades alimenticias de un ingrediente

        QString set_IngredientePrincipal();                                     //Establece si un ingrediente es principal o no
        QString set_GrupoAlimenticio();                                         //Establece el grupo alimenticio de un ingrediente
        void mostrar_IngredientePrincipal(QString str);                         //Muestra si un ingrediente es principal o no
        void mostrar_GrupoAlimenticio(QString grp);                             //Muestra el grupo alimenticio al que pertenece un ingrediente


        /*--------------*/
        /*--- PLATOS ---*/
        /*--------------*/
        void enableGCPlatosButtons();                           //habilitar los botones Guardar y Cancelar del apartado Platos
        void disableGCPlatosButtons();                          //deshabilitar los botones Guardar y Cancelar del apartado Platos
        void enableAMEPlatosButtons();                          //habilitar los botones Añadir, Modificar y Eliminar del apartado Platos
        void disableAMEPlatosButtons();                         //deshabilitar los botones Añadir, Modificar y Eliminar del apartado Platos
        void disableImagenes_Incomp_Alerg();                    //deshabilita las imagenes de alergenos e incompatibilidades

        void cleanListViewING_en_Platos();                      //Limpia de contenido el list view de Ingredientes en el apartado Platos
        void cleanListViewPlatos();                             //Limpia de contenido el list view de Platos

        void enablePlatosTextBox();                             //habilitar los textbox (linedit) del apartado Platos
        void disablePlatosTextBox();                            //deshabilitar los textbox (linedit) del apartado Platos
        void clearPlatosTextBox();                              //Deja en blanco todos los textbox del apartado Platos

        void nutricionalInfo();                                 //Calcula la informacion nutricional de un plato segun sus ingredientes
        void initializeInfoN(QStringList &infoN);               //Inicializa la lista en donde se guarda la informacion nutricional
        void showInfoN(QStringList &infoN);                     //Muestra la informacion nutricional

        QString setTipoPlato();                                 //Determina que tipo de plato es el que se crea
        void mostrarTipoPlato(QString tipo);                    //Muestra en el combo box el tipo de plato seleccionado

        void setCantidadPlato();                                //Calcula la cantidad en gramos de un plato en base a la cantidad de sus ingredientes
        void setPrecioPlato();                                  //Calcula el precio de un plato en base al precio y la cantidad de sus ingredientes

        void set_Incomp_Alerg_Plato();                          //Calcula las incompatibilidades y alergenos del plato segun sus ingredientes
        void mostrar_Incomp_Alerg_Plato();                      //Muestra las incompatibilidades y alergenos del plato
        void set_temporada_Plato();                             //Calcula la calidad de un plato segun la temporada de sus ingredientes


        /*--------------------------------*/
        /*--- INGREDIENTES DE UN PLATO ---*/
        /*--------------------------------*/
        void enableAMEINGPLAButtons();                          //habilitar los botones Añadir, Modificar y Eliminar de los ingredientes pertenecientes a un plato
        void disableAMEINGPLAButtons();                         //deshabilitar los botones Añadir, Modificar y Eliminar de los ingredientes pertenecientes a un plato

        void cleanListViewING_de_PLA();                         //Limpia de contenido el list view de ingredientes pertenecientes a un plato, en el apartado Platos


        /*--------------------*/
        /*--- PLANIFICADOR ---*/
        /*--------------------*/
        void enablePLANElements();                              //Funciones de activacion o desactivacion de elementos de la seccion Planificador
        void disablePLANElements();                             //...
        void disablePLANLabelsSelec();                          //...

        void infoPLANPlatos();                                  //Muestra el numero de platos existentes
        void infoPLANPlatosSelec();                             //Muestra el numero de platos seleccionados para el plan

        void getIngestaDiariaRecomendada();                     //Muestra los datos de ingestas diarias recomendadas
        void setIngestaDiariaRecomendada();                     //Edita los datos de ingestas diarias recomendada
        void enableIDR();                                       //Activa los botones correspondientes a la edicion de datos de ingesta diraria recomendada
        void disableIDR();                                      //Desactiva los botones correspondientes a la edicion de datos de ingesta diraria recomendada
        void resetIngestaDiariaRecomendada();                   //Funcion que resetea los valores de ingestia diaria recomendada a los valores por defecto
        void setIngestaDiariaRecomendadaPorDias();              //Edita los datos de ingestia diaria recomendada segun los dias establecidos en el plan alimenticio
        void set_irnMinMax();

        void setNumDiasPlan();                                  //Devuelve el numero de dias o menus a realizar en el plan segun lo especificado en el calendario


        /*-----------------------*/
        /*--- TABLA DE PLATOS ---*/
        /*-----------------------*/

        void ficheroDeTabla();                                                  //Funcion que crea el archivo "tablaPlatos.txt" y copia la tabla en el
        void setTablaPlatos(std::vector< std::vector<int> > &vec);              //Funcion que crea la tabla comparando todos los platos entre si y dando un valor a su composicion en funcion de su compatibilidad


        /*-------------------------------------------------------------------*/
        /*--- FUNCIONES DE ELEMENTOS NECESARIOS PARA LA CREACION DEL PLAN ---*/
        /*-------------------------------------------------------------------*/
        void setPlatos();                                                       //Ejecuta las funciones set Primeros, Segundos platos y Postres
        void setPrimerosPlatos();                                               //Guarda en el vector PrimerosPlatos los primeros platos seleccionados para el plan
        void setSegundosPlatos();                                               //Guarda en el vector SegundsPlatos los segundos platos seleccionados para el plan
        void setPostres();                                                      //Guarda en el vector Postres los postres seleccionados para el plan
        void editPrimerosPlatos();                                              //***********************************************************
        void editSegundosPlatos();                                              //***********************************************************
        void editPostres();                                                     //***********************************************************
        void clearPrimerosPlatos();                                             //Dejar a imax el numero de dias desde que se eligio un plato determinado
        void clearSegundosPlatos();                                             //...
        void clearPostres();                                                    //...

        void setVectorGruposAlimenticios();                                     //Rellena el vector vectorGruposAlimenticios para controlar el grado de repeticion de los mismos en el plan
        void editVectorGruposAlimenticios();                                    //**************************************************************************


        /*-------------------*/
        /*---- POBLACION ----*/
        /*-------------------*/
        void crearPoblacion();                                                                                              //Funcion que crea la poblacion de individuos

        void reproduccion(std::vector<menuDiario> P1, std::vector<menuDiario> P2, individuo &H1, individuo &H2);            //Funcion para reproducir dos Planes Dieteticos. P1 y P2 son los planes dieteticos de los padres, que se mezclaran y crearan los planes dieteticos de los hijos H1 y H2
        void mutacion(individuo &I);

        void crowdingDistance(std::vector<individuo> &poblacionNonDom);

        void fastNonDominatedSort();
        DOMINANCE p_dominate_q(individuo P, individuo Q);                                                                   //Funcion para comprobar si P domina a Q

        void comprobarInfNutricional();

        void set_meetingPool(const int numIndSelec);                                                                        //Funcion que selecciona a los 50 mejores padres
        bool esRepetido(individuo ind);


        /*-------------------*/
        /*---- QUICKSORT ----*/
        /*-------------------*/
        void quickSortCD(std::vector<individuo> &poblacionNonDom, int first, int last, int numObj);
        int pivotCD(std::vector<individuo> &poblacionNonDom, int first, int last, int numObj);
        double maxObj(std::vector<individuo> poblacionNonDom, int numObj);
        double minObj(std::vector<individuo> poblacionNonDom, int numObj);

        void quickSortMP(std::vector<individuo> &pob, int first, int last);
        int pivotMP(std::vector<individuo> &pob, int first, int last);
        bool sortBestInd(individuo A, individuo B);


        /*----------------------------------------------*/
        /*---- VISUALIZACION DE PLANES ALIMENTICIOS ----*/
        /*----------------------------------------------*/
        void inicializarTablas();
        void limpiarTablas();
        void visualizarPlanes();
        QString get_variedad(double var);



        /*---------------------------------------------------------------------------------------*/
        /*---- CREACION DE PLAN ESPECIAL (SIN DETERMINADOS ALERGENOS Y/O INCOMPATIBILIDADES) ----*/
        /*---------------------------------------------------------------------------------------*/
        void comprobarAlerIncomp(std::vector<int> &aler, std::vector<int> &incomp);                                     //Comprobar cuales son los alergenos e incompatibilidades que se desean evitar en el plan alimenticio
        bool comprobarPlanActual(std::vector<int> aler, std::vector<int> incomp, individuo ind);                        //Comprueba si un plan alimenticio cumple con las restricciones de alergenos e incompatibilidades
        void set_PlanEspecial();
        void set_PlatosEspeciales(std::vector<int> &ppE, std::vector<int> &spE, std::vector<int> &pE);                  //Seleccionar los platos compatibles con los alergenos e incompatibilidades a evitar





    private slots:

        void closeEvent(QCloseEvent * event);
        void on_pushButton_Aniadir_clicked();
        void on_pushButton_Modificar_clicked();
        void on_pushButton_Eliminar_clicked();
        void on_pushButton_Guardar_clicked();
        void on_pushButton_Cancelar_clicked();
        void on_pushButton_ConectarBD_clicked();
        void on_listView_Ingredientes_clicked(const QModelIndex &index);
        void on_listView_Platos_clicked(const QModelIndex &index);
        void on_listView_Ingredientes_PLA_clicked(const QModelIndex &index);
        void on_pushButton_Aniadir_PLA_clicked();
        void on_pushButton_Modificar_PLA_clicked();
        void on_pushButton_Eliminar_PLA_clicked();
        void on_pushButton_Guardar_PLA_clicked();
        void on_pushButton_Cancelar_PLA_clicked();
        void on_pushButton_PLAING_aniadir_clicked();
        void on_pushButton_PLAING_modificar_clicked();
        void on_pushButton_PLAING_eliminar_clicked();
        void on_listView_INGPLA_clicked(const QModelIndex &index);
        void checkboxClicked();
        void on_comboBox_platos_activated(const QString &arg1);
        void on_pushButton_PLAN_der_clicked();
        void on_pushButton_PLAN_izq_clicked();
        void on_pushButton_PLAN_der2_clicked();
        void on_pushButton_PLAN_izq2_clicked();
        void on_calendarWidget_clicked(const QDate &date);
        void on_radioButton_PLAN_desde_clicked();
        void on_radioButton_PLAN_hasta_clicked();
        void on_pushButton_PLAN_Modificar_clicked();
        void on_pushButton_PLAN_Guardar_clicked();
        void on_pushButton_PLAN_Cancelar_clicked();
        void on_pushButton_PLAN_GenerarPlan_clicked();

        void on_listWidget_PLAND_Recomendados_clicked(const QModelIndex &index);
};

#endif // MAINWINDOWMENUPLAN_H
