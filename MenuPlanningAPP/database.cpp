#include "database.h"

/*-------------------------------------------------------------------------*/
/*----------------------- CONSTRUCTOR Y DESTRUCTOR ------------------------*/
/*-------------------------------------------------------------------------*/

database::database()
{
    db = QSqlDatabase::addDatabase("QMYSQL");
    db.setHostName("localhost");
    db.setDatabaseName("alimentos");
    db.setUserName("root");
    db.setPassword("password");
}


database::~database()
{
    QSqlDatabase::removeDatabase("QMYSQL");
}


/*-------------------------------------------------------------------------*/
/*-------------------- CONECTAR A LA BASE DE DATOS ------------------------*/
/*-------------------------------------------------------------------------*/

bool database::connectBD()
{
    if(!db.open())
    {     
        error = db.lastError().text();
        return false;
    }
    else
    {
        return true;
    }
}

/*-------------------------------------------------------------------------*/
/*------------------- DESCONECTAR DE LA BASE DE DATOS ---------------------*/
/*-------------------------------------------------------------------------*/

void database::disconnectBD()
{
    db.close();
}

/*-------------------------------------------------------------------------*/
/*--------------------------- MENSAJE DE ERROR ----------------------------*/
/*-------------------------------------------------------------------------*/
QString database::errorMsg()
{
    return error;
}

/*-------------------------------------------------------------------------*/
/*---------------------------- LIBERAR MEMORIA ----------------------------*/
/*-------------------------------------------------------------------------*/
void database::finishQuery()
{
    delete qry;
    delete model;
}

/*-------------------------------------------------------------------------------------*/
/*-------------------------- FUNCION GENERAL PARA CONSULTAS ---------------------------*/
/*-------------------------------------------------------------------------------------*/

QSqlQueryModel * database::makeQuerys(QUERYS Q, QString strID)
{
    QString str;

    switch(Q)
    {
        case MOSTRARING:
            queryMostrarIngredientes(str);
        break;

        case MOSTRARINFOING:
            queryMostrarInfoIngredientes(str, strID);
        break;

        case MOSTRARPLA:
            queryMostrarPlatos(str);
        break;

        case MOSTRARINFOPLA:
            queryMostrarInfoPlatos(str, strID);
        break;

        case MOSTRARINGPLA:
            queryMostrarIngredientesPlatos(str, strID);
        break;

        case MOSTRARINFONUTR:
            queryMostrarInfoNING(str, strID);
        break;
    }

    //qDebug() << str;
    qry = new QSqlQuery();
    model = new QSqlQueryModel();

    qry->prepare(str);
    qry->exec();
    model->setQuery(*qry);

    return model;
}

/*-------------------------------------------------------------------------------------*/
/*------------------------------- MOSTRAR INGREDIENTES --------------------------------*/
/*-------------------------------------------------------------------------------------*/
void database::queryMostrarIngredientes(QString &str)
{
    str = "SELECT nombre FROM AlimentosTAB ORDER BY nombre ASC";
}


/*-------------------------------------------------------------------------------------*/
/*--------------------------------- MOSTRAR PLATOS ------------------------------------*/
/*-------------------------------------------------------------------------------------*/
void database::queryMostrarPlatos(QString &str)
{
    str = "SELECT nombre FROM PlatosTAB ORDER BY nombre ASC";
}


/*-------------------------------------------------------------------------------------*/
/*----------------------- MOSTRAR INFORMACION DE INGREDIENTES -------------------------*/
/*-------------------------------------------------------------------------------------*/
void database::queryMostrarInfoIngredientes(QString &str, QString &strID)
{
    str = "SELECT * FROM AlimentosTAB WHERE nombre = \"";
    str.append(strID);
    str.append("\"");
}


/*-------------------------------------------------------------------------------------*/
/*-------------------------- MOSTRAR INFORMACION DE PLATOS ----------------------------*/
/*-------------------------------------------------------------------------------------*/
void database::queryMostrarInfoPlatos(QString &str, QString &strID)
{
    str = "SELECT * FROM PlatosTAB WHERE nombre = '";
    str.append(strID);
    str.append("'");
}


/*-------------------------------------------------------------------------------------*/
/*---------------------- MOSTRAR LOS INGREDIENTES DE UN PLATO -------------------------*/
/*-------------------------------------------------------------------------------------*/
void database::queryMostrarIngredientesPlatos(QString &str, QString &strID)
{
    str = "SELECT nombre FROM AlimentosTAB WHERE id_AlimentosTAB IN (SELECT AlimentosTAB_id FROM IngredientesTAB WHERE PlatosTAB_id =";
    str.append(strID);
    str.append(")");
}


/*-------------------------------------------------------------------------------------*/
/*----------- MOSTRAR LA CANTIDAD EN GRAMOS DEL INGREDIENTE DE UN PLATO ---------------*/
/*-------------------------------------------------------------------------------------*/
QString database::queryMostrarCantidadInGPlatos(QString &strID, QString &nombre)
{
    QString str = "SELECT cantidad_gramos FROM IngredientesTAB WHERE platostab_id=";
    str.append(strID);
    str.append(" AND alimentostab_id=(SELECT id_alimentostab FROM AlimentosTAB WHERE nombre='");
    str.append(nombre);
    str.append("')");

    qry = new QSqlQuery();
    model = new QSqlQueryModel();

    qry->prepare(str);
    qry->exec();
    model->setQuery(*qry);

    QString resultado = model->record(0).value(0).toString();

    delete model;
    delete qry;

    return resultado;
}


/*-------------------------------------------------------------------------------------*/
/*----------------------------- ELIMINAR UN INGREDIENTE -------------------------------*/
/*-------------------------------------------------------------------------------------*/
void database::queryEliminarIngrediente(QString &strID)
{
    QString str = "SET SQL_SAFE_UPDATES = 0; DELETE FROM IngredientesTAB WHERE AlimentosTAB_id=";
    str.append(strID);
    str.append("; DELETE FROM AlimentosTAB WHERE id_AlimentosTAB=");
    str.append(strID);
    str.append(";");

    qry = new QSqlQuery();
    qry->prepare(str);
    qry->exec();
}


/*-------------------------------------------------------------------------------------*/
/*---------------------------- MODIFICAR UN INGREDIENTE -------------------------------*/
/*-------------------------------------------------------------------------------------*/
void database::modINGQuerys(QStringList &strl)
{
    QString str = "UPDATE AlimentosTAB SET nombre='";
    str.append(strl.at(1));
    str.append("',cantidad_gramos=");
    str.append(strl.at(2));
    str.append(",cantidad_g_precio=");
    str.append(strl.at(3));
    str.append(",precio=");
    str.append(strl.at(4));
    str.append(",precio_temporada=");
    str.append(strl.at(5));
    str.append(",acido_folico_ug=");
    str.append(strl.at(6));
    str.append(",calcio_mg=");
    str.append(strl.at(7));
    str.append(",energia_kcal=");
    str.append(strl.at(8));
    str.append(",fosforo_mg=");
    str.append(strl.at(9));
    str.append(",grasa_total_g=");
    str.append(strl.at(10));
    str.append(",hierro_mg=");
    str.append(strl.at(11));
    str.append(",magnesio_mg=");
    str.append(strl.at(12));
    str.append(",potasio_mg=");
    str.append(strl.at(13));
    str.append(",proteinas_g=");
    str.append(strl.at(14));
    str.append(",selenio_ug=");
    str.append(strl.at(15));
    str.append(",sodio_mg=");
    str.append(strl.at(16));
    str.append(",vit_a_ug=");
    str.append(strl.at(17));
    str.append(",vit_b1_tiamina_mg=");
    str.append(strl.at(18));
    str.append(",vit_b2_riboflavina_mg=");
    str.append(strl.at(19));
    str.append(",vit_b6_piridoxina_mg=");
    str.append(strl.at(20));
    str.append(",vit_b12_cianocobalamina_ug=");
    str.append(strl.at(21));
    str.append(",vit_c_mg=");
    str.append(strl.at(22));
    str.append(",vit_d_ug=");
    str.append(strl.at(23));
    str.append(",vit_e_mg=");
    str.append(strl.at(24));
    str.append(",yodo_ug=");
    str.append(strl.at(25));
    str.append(",zinc_mg=");
    str.append(strl.at(26));  
    str.append(" WHERE id_AlimentosTAB=");
    str.append(strl.at(0));

    qry = new QSqlQuery();
    qry->prepare(str);
    qry->exec();
}


/*-------------------------------------------------------------------------------------*/
/*------------------------------ AÑADIR UN INGREDIENTE --------------------------------*/
/*-------------------------------------------------------------------------------------*/
void database::addINGQuerys(QStringList &strl)
{
    QString str = "INSERT INTO AlimentosTAB (nombre, cantidad_gramos, cantidad_g_precio, precio, precio_temporada, acido_folico_ug, calcio_mg, energia_kcal, fosforo_mg, grasa_total_g, hierro_mg, magnesio_mg, proteinas_g, potasio_mg, selenio_ug, sodio_mg, vit_a_ug, vit_b1_tiamina_mg, vit_b2_riboflavina_mg, vit_b6_piridoxina_mg, vit_b12_cianocobalamina_ug, vit_c_mg, vit_d_ug, vit_e_mg, yodo_ug, zinc_mg) VALUES ('";
    str.append(strl.at(1));
    str.append("',");
    str.append(strl.at(2));
    str.append(",");
    str.append(strl.at(3));
    str.append(",");
    str.append(strl.at(4));
    str.append(",");
    str.append(strl.at(5));
    str.append(",");
    str.append(strl.at(6));
    str.append(",");
    str.append(strl.at(7));
    str.append(",");
    str.append(strl.at(8));
    str.append(",");
    str.append(strl.at(9));
    str.append(",");
    str.append(strl.at(10));
    str.append(",");
    str.append(strl.at(11));
    str.append(",");
    str.append(strl.at(12));
    str.append(",");
    str.append(strl.at(13));
    str.append(",");
    str.append(strl.at(14));
    str.append(",");
    str.append(strl.at(15));
    str.append(",");
    str.append(strl.at(16));
    str.append(",");
    str.append(strl.at(17));
    str.append(",");
    str.append(strl.at(18));
    str.append(",");
    str.append(strl.at(19));
    str.append(",");
    str.append(strl.at(20));
    str.append(",");
    str.append(strl.at(21));
    str.append(",");
    str.append(strl.at(22));
    str.append(",");
    str.append(strl.at(23));
    str.append(",");
    str.append(strl.at(24));
    str.append(",");
    str.append(strl.at(25));
    str.append(",");
    str.append(strl.at(26));
    str.append(");");

    qry = new QSqlQuery();
    qry->prepare(str);
    qry->exec();
}


/*-------------------------------------------------------------------------------------*/
/*--------------------------------- AÑADIR UN PLATO -----------------------------------*/
/*-------------------------------------------------------------------------------------*/
void database::addPLAQuerys(QStringList &strl)
{
    QString str = "INSERT INTO PlatosTAB (nombre, descripcion, precio, cantidad_gramos, acido_folico_ug, calcio_mg, energia_kcal, fosforo_mg, grasa_total_g, hierro_mg, magnesio_mg, proteinas_g, potasio_mg, selenio_ug, sodio_mg, vit_a_ug, vit_b1_mg, vit_b2_mg, vit_b6_mg, vit_b12_ug, vit_c_mg, vit_d_ug, vit_e_mg, yodo_ug, zinc_mg) VALUES ('";
    str.append(strl.at(1));
    str.append("','");
    str.append(strl.at(2));
    str.append("',");
    str.append(strl.at(3));
    str.append(",");
    str.append(strl.at(4));
    str.append(",");
    str.append(strl.at(5));
    str.append(",");
    str.append(strl.at(6));
    str.append(",");
    str.append(strl.at(7));
    str.append(",");
    str.append(strl.at(8));
    str.append(",");
    str.append(strl.at(9));
    str.append(",");
    str.append(strl.at(10));
    str.append(",");
    str.append(strl.at(11));
    str.append(",");
    str.append(strl.at(12));
    str.append(",");
    str.append(strl.at(13));
    str.append(",");
    str.append(strl.at(14));
    str.append(",");
    str.append(strl.at(15));
    str.append(",");
    str.append(strl.at(16));
    str.append(",");
    str.append(strl.at(17));
    str.append(",");
    str.append(strl.at(18));
    str.append(",");
    str.append(strl.at(19));
    str.append(",");
    str.append(strl.at(20));
    str.append(",");
    str.append(strl.at(21));
    str.append(",");
    str.append(strl.at(22));
    str.append(",");
    str.append(strl.at(23));
    str.append(",");
    str.append(strl.at(24));
    str.append(",");
    str.append(strl.at(25));
    str.append(");");

    qry = new QSqlQuery();
    qry->prepare(str);
    qry->exec();
}


/*-------------------------------------------------------------------------------------*/
/*------------------------------- MODIFICAR UN PLATO ----------------------------------*/
/*-------------------------------------------------------------------------------------*/
void database::modPLAQuerys(QStringList &strl)
{
    QString str = "UPDATE PlatosTAB SET nombre='";
    str.append(strl.at(1));
    str.append("',descripcion='");
    str.append(strl.at(2));
    str.append("',precio=");
    str.append(strl.at(3));
    str.append(",cantidad_gramos=");
    str.append(strl.at(4));
    str.append(",acido_folico_ug=");
    str.append(strl.at(5));
    str.append(",calcio_mg=");
    str.append(strl.at(6));
    str.append(",energia_kcal=");
    str.append(strl.at(7));
    str.append(",fosforo_mg=");
    str.append(strl.at(8));
    str.append(",grasa_total_g=");
    str.append(strl.at(9));
    str.append(",hierro_mg=");
    str.append(strl.at(10));
    str.append(",magnesio_mg=");
    str.append(strl.at(11));
    str.append(",potasio_mg=");
    str.append(strl.at(12));
    str.append(",proteinas_g=");
    str.append(strl.at(13));
    str.append(",selenio_ug=");
    str.append(strl.at(14));
    str.append(",sodio_mg=");
    str.append(strl.at(15));
    str.append(",vit_a_ug=");
    str.append(strl.at(16));
    str.append(",vit_b1_mg=");
    str.append(strl.at(17));
    str.append(",vit_b2_mg=");
    str.append(strl.at(18));
    str.append(",vit_b6_mg=");
    str.append(strl.at(19));
    str.append(",vit_b12_ug=");
    str.append(strl.at(20));
    str.append(",vit_c_mg=");
    str.append(strl.at(21));
    str.append(",vit_d_ug=");
    str.append(strl.at(22));
    str.append(",vit_e_mg=");
    str.append(strl.at(23));
    str.append(",yodo_ug=");
    str.append(strl.at(24));
    str.append(",zinc_mg=");
    str.append(strl.at(25));
    str.append(" WHERE id_PlatosTAB=");
    str.append(strl.at(0));

    qry = new QSqlQuery();
    qry->prepare(str);
    qry->exec();
}


/*-------------------------------------------------------------------------------------*/
/*----------------------------- ELIMINAR UN PLATO -------------------------------------*/
/*-------------------------------------------------------------------------------------*/
void database::queryEliminarPlato(QString &strID)
{
    QString str = "SET SQL_SAFE_UPDATES = 0; DELETE FROM IngredientesTAB WHERE PlatosTAB_id=";
    str.append(strID);
    str.append("; DELETE FROM PlatosTAB WHERE id_PlatosTAB=");
    str.append(strID);
    str.append(";");

    qry = new QSqlQuery();
    qry->prepare(str);
    qry->exec();
}


/*-------------------------------------------------------------------------------------*/
/*------------------------ AÑADIR UN INGREDIENTE A UN PLATO ---------------------------*/
/*-------------------------------------------------------------------------------------*/
void database::addINGtoPLAQuery(QString &strIDPLA, QString &nombre, QString &cantidad)
{
    QString str = "INSERT INTO IngredientesTAB (cantidad_gramos, alimentostab_id, platostab_id) VALUES (";
    str.append(cantidad);
    str.append(",(SELECT id_alimentostab FROM AlimentosTAB WHERE nombre='");
    str.append(nombre);
    str.append("'),");
    str.append(strIDPLA);
    str.append(")");

    qry = new QSqlQuery();
    qry->prepare(str);
    qry->exec();
}

/*-------------------------------------------------------------------------------------*/
/*--------------------- MODIFICAR UN INGREDIENTE DE UN PLATO --------------------------*/
/*-------------------------------------------------------------------------------------*/
void database::modINGtoPLAQuery(QString &strIDPLA, QString &nombre, QString &cantidad)
{
    QString str = "UPDATE IngredientesTAB SET cantidad_gramos=";
    str.append(cantidad);
    str.append(" WHERE AlimentosTAB_id=(SELECT id_alimentostab FROM AlimentosTAB WHERE nombre='");
    str.append(nombre);
    str.append("') AND PlatosTAB_id=");
    str.append(strIDPLA);

    qry = new QSqlQuery();
    qry->prepare(str);
    qry->exec();
}

/*-------------------------------------------------------------------------------------*/
/*--------------------- ELIMINAR UN INGREDIENTE DE UN PLATO ---------------------------*/
/*-------------------------------------------------------------------------------------*/
void database::removeINGtoPLAQuery(QString &strIDPLA, QString &nombre)
{
    QString str = "SET SQL_SAFE_UPDATES = 0; DELETE FROM IngredientesTAB WHERE PlatosTAB_id=";
    str.append(strIDPLA);
    str.append(" AND AlimentosTAB_id= (SELECT id_alimentostab FROM AlimentosTAB WHERE nombre='");
    str.append(nombre);
    str.append("')");

    qry = new QSqlQuery();
    qry->prepare(str);
    qry->exec();
}


/*-------------------------------------------------------------------------------------*/
/*--------------- CONTROLAR LA REPETICIÓN DE INGREDIENTES O PLATOS --------------------*/
/*-------------------------------------------------------------------------------------*/
ACTION database::controllQuerys(QUERYS Q, APARTADOS AP, QString &strID1, QString strID2)
{
    QString result = NULL;
    QString query;
    QString info = "Ya existe un ";
    ACTION AC = ACCEPT;

    switch(AP)                              //__Averiguar de que tipo de elemento se trata (ingrediente, plato o ingrediente de un plato)
    {
        case INGREDIENTES:
            query = "SELECT id_AlimentosTAB FROM AlimentosTAB WHERE nombre ='";
            query.append(strID1);
            query.append("'");
            info.append("ingrediente");
        break;

        case PLATOS:
            query = "SELECT id_PlatosTAB FROM PlatosTAB WHERE nombre ='";
            query.append(strID1);
            query.append("'");
            info.append("plato");
        break;

        case INGDEPLATO:
            query = "SELECT id_IngredientesTAB FROM IngredientesTAB WHERE AlimentosTAB_id = (SELECT id_alimentostab FROM AlimentosTAB WHERE nombre='";
            query.append(strID1);
            query.append("') AND PlatosTAB_id =");
            query.append(strID2);
            info.append("ingrediente para este plato");
        break;
    }

    info.append(" con este nombre en la base de datos.");
    qry = new QSqlQuery();
    model = new QSqlQueryModel();

    qry->prepare(query);
    qry->exec();
    model->setQuery(*qry);

    result = model->record(0).value(0).toString();      //__Recoge el resultado devuelto por la consulta anteriormente realizada

    delete model;
    delete qry;

    switch(Q)                                           //__Comprueba si el resultado dado por la consulta indica una repeticion de ingrediente, plato o ingrediente de plato
    {
        case ANIADIRING:
            if(result != "" || result != NULL)
                AC = DENY;
        break;

        case ANIADIRPLA:
            if(result != "" || result != NULL)
                AC = DENY;
        break;

        case MODIFICARING:
            if((result != "" || result != NULL) && result != strID2)
                AC = DENY;
        break;

        case MODIFICARPLA:
            if((result != "" || result != NULL) && result != strID2)
                AC = DENY;
        break;

        case ANIADIRINGPLA:
            if(result != "" || result != NULL)
                AC = DENY;
        break;
    }

    if(AC == DENY)                                  //__Si se ha detectado una repeticion de ingrediente o plato
    {
        QMessageBox msgBox;                         //__Se muestra un mensaje notificando
        msgBox.setIcon(QMessageBox::Information);
        msgBox.setText("Información");
        msgBox.setInformativeText(info);
        msgBox.setStandardButtons(QMessageBox::Ok);
        msgBox.setDefaultButton(QMessageBox::Ok);
        msgBox.exec();
        return DENY;                                //__Se retorna una denegacion para realizar la consulta que provoca la repeticion
    }
    else
    {
        return ACCEPT;
    }
}



/*--------------------------------------------------------------------------------------------------------*/
/*------- MOATRAR LA CANTIDAD EN GRAMOS DE UN INGREDIENTE EN LA BASE DE DATOS (NO EN UN PLATO) -----------*/
/*--------------------------------------------------------------------------------------------------------*/

QString database::queryMostrarCantidadING(QString &nombre)
{
    QString query = "SELECT cantidad_gramos FROM AlimentosTAB WHERE nombre='";
    query.append(nombre);
    query.append("'");

    qry = new QSqlQuery();
    model = new QSqlQueryModel();

    qry->prepare(query);
    qry->exec();
    model->setQuery(*qry);

    QString resultado = model->record(0).value(0).toString();

    delete model;
    delete qry;

    return resultado;
}

/*-------------------------------------------------------------------------------------*/
/*------------------ MOSTRAR INF NUTRICIONAL DE UN INGREDIENTE ------------------------*/
/*-------------------------------------------------------------------------------------*/

void database::queryMostrarInfoNING(QString &str, QString &nombre)
{
    str = "SELECT acido_folico_ug, calcio_mg, energia_kcal, fosforo_mg, grasa_total_g, hierro_mg, magnesio_mg, proteinas_g, potasio_mg, selenio_ug, sodio_mg, vit_a_ug, vit_b1_tiamina_mg, vit_b2_riboflavina_mg, vit_b6_piridoxina_mg, vit_b12_cianocobalamina_ug, vit_c_mg, vit_d_ug, vit_e_mg, yodo_ug, zinc_mg FROM AlimentosTAB WHERE nombre='";
    str.append(nombre);
    str.append("'");
}


/*-------------------------------------------------------------------------------------*/
/*----------------- ACTUALIZAR INF NUTRICIONAL DE UN INGREDIENTE ----------------------*/
/*-------------------------------------------------------------------------------------*/

void database::queryUpdateInfoNING(QStringList &strl, QString &id)
{
    QString str = "UPDATE PlatosTAB SET acido_folico_ug=";
    str.append(strl.at(0));
    str.append(",calcio_mg=");
    str.append(strl.at(1));
    str.append(",energia_kcal=");
    str.append(strl.at(2));
    str.append(",fosforo_mg=");
    str.append(strl.at(3));
    str.append(",grasa_total_g=");
    str.append(strl.at(4));
    str.append(",hierro_mg=");
    str.append(strl.at(5));
    str.append(",magnesio_mg=");
    str.append(strl.at(6));
    str.append(",potasio_mg=");
    str.append(strl.at(7));
    str.append(",proteinas_g=");
    str.append(strl.at(8));
    str.append(",selenio_ug=");
    str.append(strl.at(9));
    str.append(",sodio_mg=");
    str.append(strl.at(10));
    str.append(",vit_a_ug=");
    str.append(strl.at(11));
    str.append(",vit_b1_mg=");
    str.append(strl.at(12));
    str.append(",vit_b2_mg=");
    str.append(strl.at(13));
    str.append(",vit_b6_mg=");
    str.append(strl.at(14));
    str.append(",vit_b12_ug=");
    str.append(strl.at(15));
    str.append(",vit_c_mg=");
    str.append(strl.at(16));
    str.append(",vit_d_ug=");
    str.append(strl.at(17));
    str.append(",vit_e_mg=");
    str.append(strl.at(18));
    str.append(",yodo_ug=");
    str.append(strl.at(19));
    str.append(",zinc_mg=");
    str.append(strl.at(20));
    str.append(" WHERE id_PlatosTAB=");
    str.append(id);

    qry = new QSqlQuery();

    qry->prepare(str);
    qry->exec();

    delete qry;
}
