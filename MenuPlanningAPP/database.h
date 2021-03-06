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

        ACTION controllQuerys(QUERYS Q, APARTADOS AP, QString &strID1, QString strID2=NULL);    //Metodo para controlar la repeticion de ingredientes, platos o ingredientes de un plato

        /*--------------------*/
        /*--- INGREDIENTES ---*/
        /*--------------------*/
        QSqlQueryModel* queryMostrarIngredientes();                                             //Consulta para mostrar los ingredientes disponibles en la base de datos
        QSqlQueryModel* queryMostrarInfoIngredientes(QString strID);                            //Consulta para mostrar la informacion de un ingrediente

        void addINGQuerys(QStringList &strl);                                                   //Consulta para crear un nuevo ingrediente
        void modINGQuerys(QStringList &strl);                                                   //Consulta para modificar los datos de un ingrediente
        void queryEliminarIngrediente(QString &strID);                                          //Consulta para eliminar un ingrediente

        float queryMostrarPrecioING(QString &nombre, float cantidad);                           //Consulta para mostrar el precio de un ingrediente en base a su cantidad
        QString queryIncompatibilidadesING(QString nombre);
        QString queryAlergenosING(QString nombre);

        bool queryEsIngredientePrincipal(QString id);
        int queryMostrarGrupoAlimenticio(QString id);
        int queryMostrarGrupoAlimenticioPorNombre(QString nombre);


        /*--------------*/
        /*--- PLATOS ---*/
        /*--------------*/
        QSqlQueryModel* queryMostrarPlatos();                                                   //Consulta para mostrar los platos disponibles en la base de datos
        QSqlQueryModel* queryMostrarInfoPlatos(QString strID);                                  //Consulta para mostrar la informacion de un plato
        QSqlQueryModel* queryMostrarNombrePlatosPorTipo(QString strID);                         //Consulta para mostrar los nombres de los platos segun su tipo (primer plato, segundo plato o postre)
        QString queryMostrarTipoPlatoNombre(QString nombre);                                    //Consulta para mostrar de que tipo es un plato determinado por nombre (primer plato, segundo plato o postre)
        int queryMostrarTipoPlatoID(QString id);                                                //Consulta para mostrar de que tipo es un plato determinado por id(primer plato, segundo plato o postre)
        QString queryMostrarNombrePlatoPorID(QString id);                                       //Consulta para mostrar el nombre de un plato por su ID
        QString queryMostrarGramosPlatoPorID(QString id);

        void addPLAQuerys(QStringList &strl);                                                   //Consulta para crear un nuevo plato
        void modPLAQuerys(QStringList &strl);                                                   //Consulta para modificar los datos de un plato
        void queryEliminarPlato(QString &strID);                                                //Consulta para eliminar un plato

        void queryModificarCantidadPlato(QString &strID, QString &cantidad);                    //Consulta para modificar la cantidad en gramos de un plato
        void queryModificarPrecioPlato(QString &strID, QString &precio);                        //Consulta para modificar el precio de un plato
        void queryModificarIncompAlergPlato(QString &strID, QString &incomp, QString &alerg);   //Consulta para modificar las incompatibilidades y alergenos de un plato
        QString queryMostrarIncompPlato(QString id);
        QString queryMostrarAlergPlato(QString id);


        void queryUpdateInfoNING(QStringList &strl, QString &id);                               //Calculo de la informacion nutricional de un plato
        QSqlQueryModel* queryMostrarInfoNING(QString nombre);                                   //---
        QString queryMostrarCantidadING(QString &nombre);                                       //---


        /*--------------------------------*/
        /*--- INGREDIENTES DE UN PLATO ---*/
        /*--------------------------------*/
        QSqlQueryModel* queryMostrarIngredientesPlatos(QString strID);                          //Consulta para mostrar los ingredientes de un plato
        QString queryMostrarCantidadInGPlatos(QString &strID, QString &nombre);                 //Consulta para mostrar la cantidad de un ingrediente en el plato seleccionado

        void addINGtoPLAQuery(QString &strIDPLA, QString &nombre, QString &cantidad);           //Consulta para añadir un ingrediente a un plato
        void modINGtoPLAQuery(QString &strIDPLA, QString &nombre, QString &cantidad);           //Consulta para modificar un ingrediente a un plato
        void removeINGtoPLAQuery(QString &strIDPLA, QString &nombre);                           //Consulta para eliminar un ingrediente a un plato


        /*--------------------*/
        /*--- PLANIFICADOR ---*/
        /*--------------------*/
        QString queryNumPlatos();                                                               //Consulta para mostrar el numero total de platos
        QString queryNumPriPlato();                                                             //Consulta para mostrar el numero de primeros platos
        QString queryNumSegPlato();                                                             //Consulta para mostrar el numero de segundos platos
        QString queryNumPostre();                                                               //Consulta para mostrar el numero de postres



        /*---------------------------------*/
        /*--- ACTUALIZAR ID'S DE PLATOS ---*/
        /*---------------------------------*/
        void ActualizarIDPlatos();
        QSqlQueryModel* queryMostrarGruposAldeIngPrincipales(QString idPlato);
        QSqlQueryModel* queryMostrarGruposAl(QString idPlato);


        /*-----------------------------*/
        /*--- FUNCIONES OPTIMIZADAS ---*/
        /*-----------------------------*/
        void querysVOID(QString str);
        QString querysQSTRING(QString str);
        QSqlQueryModel* querysQSQLQUERYMODEL(QString str);

};


#endif // DATABASE_H
