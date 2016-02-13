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
//#pragma once

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

        //void enableAMEINGPLAButtons();                          //habilitar los botones Añadir, Modificar y Eliminar de los ingredientes pertenecientes a un plato
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
        ACTION controllDataTextBoxNum(QGroupBox &gb);                           //Controla que los datos numericos introducidos o modificados por el usuario sean validos
        ACTION controllSelectionElement(QListView &lv);                         //Controla si se ha seleccionado un elemento de un listview para su posterior manipulacion



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

private:
        Ui::MainWindowMenuPlan *ui;
        database *db1;
        QUERYS Q;
        ACTION AC;                          //Se usa unicamente para las variables CREARPLATO y CREARINGDEPLATO
        const int maxNumSize = 6;
};

#endif // MAINWINDOWMENUPLAN_H
