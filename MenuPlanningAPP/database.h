#ifndef DATABASE_H
#define DATABASE_H

#include "mainwindowmenuplan.h"
#include "enums.h"

//#pragma once



class database
{
    private:
        QSqlDatabase db;
        QString error;
        QSqlQuery *qry = 0;
        QSqlQueryModel *model = 0;

    public:

        database();
        ~database();

        bool connectBD();                                                               //Conectar a la base de datos
        void disconnectBD();                                                            //Desconectar de la base de datos
        QString errorMsg();                                                             //Retornar mensajes de error

        QSqlQueryModel * makeQuerys(QUERYS Q, QString strID=NULL);                      //Funcion para hacer consultas (mostrar y eliminar)

        void queryMostrarIngredientes(QString &str);                                    //Consulta para mostrar los ingredientes disponibles en la base de datos
        void queryMostrarInfoIngredientes(QString &str, QString &strID);                //Consulta para mostrar la informacion de un ingrediente
        void queryEliminarIngrediente(QString &str, QString &strID);                    //Consulta para eliminar un ingrediente

        void queryMostrarPlatos(QString &str);                                          //Consulta para mostrar los platos disponibles en la base de datos
        void queryMostrarInfoPlatos(QString &str, QString &strID);                      //Consulta para mostrar la informacion de un plato
        void queryMostrarIngredientesPlatos(QString &str, QString &strID);              //Consulta para mostrar los ingredientes de un plato
        QSqlQueryModel * queryMostrarCantidadInGPlatos(QString &strID, QString &nombre);//Consulta para mostrar la cantidad de un ingrediente en el plato seleccionado
        void queryEliminarPlato(QString &str, QString &strID);                          //Consulta para eliminar un plato

        QSqlQueryModel * modINGQuerys(QStringList &strl);                               //Consulta para modificar los datos de un ingrediente
        QSqlQueryModel * addINGQuerys(QStringList &strl);                               //Consulta para crear un nuevo ingrediente
        QSqlQueryModel * modPLAQuerys(QStringList &strl);                               //Consulta para modificar los datos de un plato
        QSqlQueryModel * addPLAQuerys(QStringList &strl);                               //Consulta para crear un nuevo plato
        QSqlQueryModel * addINGtoPLAQuery(QString &strIDPLA, QString &nombre, QString &cantidad);        //Consulta para añadir un ingrediente a un plato
        QSqlQueryModel * modINGtoPLAQuery(QString &strIDPLA, QString &nombre, QString &cantidad);        //Consulta para modificar un ingrediente a un plato
        QSqlQueryModel * removeINGtoPLAQuery(QString &strIDPLA, QString &nombre);                        //Consulta para eliminar un ingrediente a un plato

        void finishQuery();                                                             //Funcion para liberar la memoria correspondiente a las variables *qry y *model
};











#endif // DATABASE_H
