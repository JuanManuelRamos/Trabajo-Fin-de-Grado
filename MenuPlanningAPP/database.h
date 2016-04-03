#ifndef DATABASE_H
#define DATABASE_H

#include "mainwindowmenuplan.h"
#include "enums.h"


class database
{
    private:
        QSqlDatabase db;
        QString error;
        QSqlQuery *qry = 0;
        QSqlQueryModel *model = 0;

    public:

        database();                                                                             //Constructor
        ~database();                                                                            //Destructor

        bool connectBD();                                                                       //Conectar a la base de datos
        void disconnectBD();                                                                    //Desconectar de la base de datos
        QString errorMsg();                                                                     //Retornar mensajes de error
        void finishQuery();                                                                     //Funcion para liberar la memoria correspondiente a las variables *qry y *model

        QSqlQueryModel * makeQuerys(QUERYS Q, QString strID=NULL);                              //Funcion para hacer consultas (mostrar y eliminar)
        ACTION controllQuerys(QUERYS Q, APARTADOS AP, QString &strID1, QString strID2=NULL);    //Metodo para controlar la repeticion de ingredientes, platos o ingredientes de un plato

        /*--------------------*/
        /*--- INGREDIENTES ---*/
        /*--------------------*/
        void queryMostrarIngredientes(QString &str);                                            //Consulta para mostrar los ingredientes disponibles en la base de datos
        void queryMostrarInfoIngredientes(QString &str, QString &strID);                        //Consulta para mostrar la informacion de un ingrediente

        void addINGQuerys(QStringList &strl);                                                   //Consulta para crear un nuevo ingrediente
        void modINGQuerys(QStringList &strl);                                                   //Consulta para modificar los datos de un ingrediente
        void queryEliminarIngrediente(QString &strID);                                          //Consulta para eliminar un ingrediente

        float queryMostrarPrecioING(QString &nombre, float cantidad);                           //Consulta para mostrar el precio de un ingrediente en base a su cantidad
        QString queryIncompatibilidadesING(QString nombre);
        QString queryAlergenosING(QString nombre);
        QString queryTemporadaING(QString nombre);


        /*--------------*/
        /*--- PLATOS ---*/
        /*--------------*/
        void queryMostrarPlatos(QString &str);                                                  //Consulta para mostrar los platos disponibles en la base de datos
        void queryMostrarInfoPlatos(QString &str, QString &strID);                              //Consulta para mostrar la informacion de un plato
        void queryMostrarTiposPlatos(QString &str, QString &strID);                             //Consulta para mostrar los platos segun su tipo (primer plato, segundo plato o postre)

        void addPLAQuerys(QStringList &strl);                                                   //Consulta para crear un nuevo plato
        void modPLAQuerys(QStringList &strl);                                                   //Consulta para modificar los datos de un plato
        void queryEliminarPlato(QString &strID);                                                //Consulta para eliminar un plato

        void queryModificarCantidadPlato(QString &strID, QString &cantidad);                    //Consulta para modificar la cantidad en gramos de un plato
        void queryModificarPrecioPlato(QString &strID, QString &precio);                        //Consulta para modificar el precio de un plato
        void queryModificarIncompAlergPlato(QString &strID, QString &incomp, QString &alerg);   //Consulta para modificar las incompatibilidades y alergenos de un plato


        void queryUpdateInfoNING(QStringList &strl, QString &id);                               //Calculo de la informacion nutricional de un plato
        void queryMostrarInfoNING(QString &str, QString &nombre);                               //---
        QString queryMostrarCantidadING(QString &nombre);                                       //---


        /*--------------------------------*/
        /*--- INGREDIENTES DE UN PLATO ---*/
        /*--------------------------------*/
        void queryMostrarIngredientesPlatos(QString &str, QString &strID);                      //Consulta para mostrar los ingredientes de un plato
        QString queryMostrarCantidadInGPlatos(QString &strID, QString &nombre);                 //Consulta para mostrar la cantidad de un ingrediente en el plato seleccionado

        void addINGtoPLAQuery(QString &strIDPLA, QString &nombre, QString &cantidad);           //Consulta para añadir un ingrediente a un plato
        void modINGtoPLAQuery(QString &strIDPLA, QString &nombre, QString &cantidad);           //Consulta para modificar un ingrediente a un plato
        void removeINGtoPLAQuery(QString &strIDPLA, QString &nombre);                           //Consulta para eliminar un ingrediente a un plato



};


#endif // DATABASE_H
