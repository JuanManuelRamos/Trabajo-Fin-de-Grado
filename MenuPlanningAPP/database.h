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
        ~database();                                                                            //Deestructor

        bool connectBD();                                                                       //Conectar a la base de datos
        void disconnectBD();                                                                    //Desconectar de la base de datos
        QString errorMsg();                                                                     //Retornar mensajes de error

        QSqlQueryModel * makeQuerys(QUERYS Q, QString strID=NULL);                              //Funcion para hacer consultas (mostrar y eliminar)

        void queryMostrarIngredientes(QString &str);                                            //Consulta para mostrar los ingredientes disponibles en la base de datos
        void queryMostrarInfoIngredientes(QString &str, QString &strID);                        //Consulta para mostrar la informacion de un ingrediente
        void queryEliminarIngrediente(QString &strID);                                          //Consulta para eliminar un ingrediente

        void queryMostrarPlatos(QString &str);                                                  //Consulta para mostrar los platos disponibles en la base de datos
        void queryMostrarInfoPlatos(QString &str, QString &strID);                              //Consulta para mostrar la informacion de un plato
        void queryMostrarTiposPlatos(QString &str, QString &strID);                             //Consulta para mostrar los platos segun su tipo (primer plato, segundo plato o postre)
        void queryMostrarIngredientesPlatos(QString &str, QString &strID);                      //Consulta para mostrar los ingredientes de un plato
        QString queryMostrarCantidadInGPlatos(QString &strID, QString &nombre);                 //Consulta para mostrar la cantidad de un ingrediente en el plato seleccionado
        void queryEliminarPlato(QString &strID);                                                //Consulta para eliminar un plato

        void modINGQuerys(QStringList &strl);                                                   //Consulta para modificar los datos de un ingrediente
        void addINGQuerys(QStringList &strl);                                                   //Consulta para crear un nuevo ingrediente
        void modPLAQuerys(QStringList &strl);                                                   //Consulta para modificar los datos de un plato
        void addPLAQuerys(QStringList &strl);                                                   //Consulta para crear un nuevo plato
        void addINGtoPLAQuery(QString &strIDPLA, QString &nombre, QString &cantidad);           //Consulta para añadir un ingrediente a un plato
        void modINGtoPLAQuery(QString &strIDPLA, QString &nombre, QString &cantidad);           //Consulta para modificar un ingrediente a un plato
        void removeINGtoPLAQuery(QString &strIDPLA, QString &nombre);                           //Consulta para eliminar un ingrediente a un plato

        ACTION controllQuerys(QUERYS Q, APARTADOS AP, QString &strID1, QString strID2=NULL);


        //Calculo de la informacion nutricional de un plato
        QString queryMostrarCantidadING(QString &nombre);
        void queryMostrarInfoNING(QString &str, QString &nombre);
        void queryUpdateInfoNING(QStringList &strl, QString &id);


        void finishQuery();                                                                     //Funcion para liberar la memoria correspondiente a las variables *qry y *model
};


#endif // DATABASE_H
