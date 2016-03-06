#ifndef MAINWINDOWMENUPLAN_H
#define MAINWINDOWMENUPLAN_H

#include <QMainWindow>
#include <QApplication>
#include <QtSql>
#include <QMessageBox>
#include <QCloseEvent>
#include <iostream>

#include "database.h"
#include "enums.h"
#include <QGroupBox>
#include <QtWidgets>


using namespace std;

namespace Ui {class MainWindowMenuPlan;}

class database;


class MainWindowMenuPlan : public QMainWindow
{
    Q_OBJECT

    public:
        explicit MainWindowMenuPlan(QWidget *parent = 0);
        ~MainWindowMenuPlan();

        //Funciones de habilitacion, deshabilitacion, limpieza, etc de elementos

        void enableGCIngredientesButtons();                     //habilitar los botones Guardar y Cancelar del apartado Ingredientes
        void disableGCIngredientesButtons();                    //deshabilitar los botones Guardar y Cancelar del apartado Ingredientes
        void enableGCPlatosButtons();                           //habilitar los botones Guardar y Cancelar del apartado Platos
        void disableGCPlatosButtons();                          //deshabilitar los botones Guardar y Cancelar del apartado Platos

        void enableAMEIngredientesButtons();                    //habilitar los botones Añadir, Modificar y Eliminar del apartado Ingredientes
        void disableAMEIngredientesButtons();                   //deshabilitar los botones Añadir, Modificar y Eliminar del apartado Ingredientes
        void enableAMEPlatosButtons();                          //habilitar los botones Añadir, Modificar y Eliminar del apartado Platos
        void disableAMEPlatosButtons();                         //deshabilitar los botones Añadir, Modificar y Eliminar del apartado Platos

        void enableAMEINGPLAButtons();                          //habilitar los botones Añadir, Modificar y Eliminar de los ingredientes pertenecientes a un plato
        void disableAMEINGPLAButtons();                         //deshabilitar los botones Añadir, Modificar y Eliminar de los ingredientes pertenecientes a un plato

        void cleanListViewING();                                //Limpia de contenido el list view de Ingredientes
        void cleanListViewING_en_Platos();                      //Limpia de contenido el list view de Ingredientes en el apartado Platos
        void cleanListViewPlatos();                             //Limpia de contenido el list view de Platos
        void cleanListViewING_de_PLA();                         //Limpia de contenido el list view de ingredientes pertenecientes a un plato, en el apartado Platos

        void enableIngredientesTextBox();                       //habilitar los textbox (linedit) del apartado Ingredientes
        void disableIngredientesTextBox();                      //deshabilitar los textbox (linedit) del apartado Ingredientes
        void enablePlatosTextBox();                             //habilitar los textbox (linedit) del apartado Platos
        void disablePlatosTextBox();                            //deshabilitar los textbox (linedit) del apartado Platos

        void clearIngredientesTextBox();                        //Deja en blanco todos los textbox del apartado Ingredientes
        void clearPlatosTextBox();                              //Deja en blanco todos los textbox del apartado Platos

        //Funciones de control de datos
        void fillIngPlaTextBox(QSqlQueryModel *model, APARTADOS A);             //Rellena los textbox con los datos de cada ingrediente o plato
        QStringList captureTextBoxText(APARTADOS AP);                           //Captura los datos escritos en los textbox
        ACTION controllDataTextBoxName(QLineEdit &le);                          //Controla si el campo "nombre" de un ingrediente o plato esta vacio o no
        ACTION controllDataTextBoxNum(QGroupBox &gb, int indexFor);             //Controla que los datos numericos introducidos o modificados por el usuario sean validos
        ACTION controllSelectionElement(QListView &lv);                         //Controla si se ha seleccionado un elemento de un listview para su posterior manipulacion


        void nutricionalInfo();                                                 //Calcula la informacion nutricional de un plato segun sus ingredientes
        void initializeInfoN(QStringList &infoN);                               //Inicializa la lista en donde se guarda la informacion nutricional
        void showInfoN(QStringList &infoN);                                     //Muestra la informacion nutricional

        QString set_mesesTemporada();                                           //Rellena el array mesesTemporada segun los meses en los que un ingrediente esta de temporada
        QString set_Incompatibilidades();
        QString set_Alergenos();
        void mostrar_mesesTemporada(QString meses);                             //Muestra en la aplicacion los meses en los que un ingrediente esta de temporada
        void mostrar_alergenosIncom(CHECKBOX CB, QString array);

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

private:
        Ui::MainWindowMenuPlan *ui;
        database *db1;
        QUERYS Q;
        const int maxNumSize = 6;                   //Numero maximo de digitos en un campo numerico
        const int NumInfN = 21;                     //Numero de datos nutricionales
        const static int NumMesesTemp = 12;         //Numero de meses de temporada
        const static int NumAlergenos = 7;          //Numero de alergenos
        const static int NumIncomp = 5;             //Numero de incompatibilidades alimenticias

        char mesesTemporada[NumMesesTemp];          //Array de meses de temporada
        char ary_alergenos[NumAlergenos];           //Array de alergenos
        char ary_incomp[NumIncomp];                 //Array de incompatibilidades alimenticias

        //Checkbox correspondientes a los meses de temporada y layout que los contiene
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


};

#endif // MAINWINDOWMENUPLAN_H
