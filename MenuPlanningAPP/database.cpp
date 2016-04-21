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

        case MOSTRARTIPOPLA:
            queryMostrarTiposPlatos(str, strID);
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


/*-----------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------*/
/*----------------------------------------------       INGREDIENTES        ----------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------*/


/*-------------------------------------------------------------------------------------*/
/*------------------------------- MOSTRAR INGREDIENTES --------------------------------*/
/*-------------------------------------------------------------------------------------*/
void database::queryMostrarIngredientes(QString &str)
{
    str = "SELECT nombre FROM AlimentosTAB ORDER BY nombre ASC";
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
    str.append(",temporada='");
    str.append(strl.at(5));
    str.append("',incompatibilidades='");
    str.append(strl.at(6));
    str.append("',alergenos='");
    str.append(strl.at(7));
    str.append("',ingrediente_principal='");
    str.append(strl.at(8));
    str.append("',grupo_alimenticio='");
    str.append(strl.at(9));
    str.append("',acido_folico_ug=");
    str.append(strl.at(10));
    str.append(",calcio_mg=");
    str.append(strl.at(11));
    str.append(",energia_kcal=");
    str.append(strl.at(12));
    str.append(",fosforo_mg=");
    str.append(strl.at(13));
    str.append(",grasa_total_g=");
    str.append(strl.at(14));
    str.append(",hierro_mg=");
    str.append(strl.at(15));
    str.append(",magnesio_mg=");
    str.append(strl.at(16));
    str.append(",potasio_mg=");
    str.append(strl.at(17));
    str.append(",proteinas_g=");
    str.append(strl.at(18));
    str.append(",selenio_ug=");
    str.append(strl.at(19));
    str.append(",sodio_mg=");
    str.append(strl.at(20));
    str.append(",vit_a_ug=");
    str.append(strl.at(21));
    str.append(",vit_b1_tiamina_mg=");
    str.append(strl.at(22));
    str.append(",vit_b2_riboflavina_mg=");
    str.append(strl.at(23));
    str.append(",vit_b6_piridoxina_mg=");
    str.append(strl.at(24));
    str.append(",vit_b12_cianocobalamina_ug=");
    str.append(strl.at(25));
    str.append(",vit_c_mg=");
    str.append(strl.at(26));
    str.append(",vit_d_ug=");
    str.append(strl.at(27));
    str.append(",vit_e_mg=");
    str.append(strl.at(28));
    str.append(",yodo_ug=");
    str.append(strl.at(29));
    str.append(",zinc_mg=");
    str.append(strl.at(30));
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
    QString str = "ALTER TABLE AlimentosTAB AUTO_INCREMENT = 1; INSERT INTO AlimentosTAB (nombre, cantidad_gramos, cantidad_g_precio, precio, temporada, incompatibilidades, alergenos, ingrediente_principal, grupo_alimenticio, acido_folico_ug, calcio_mg, energia_kcal, fosforo_mg, grasa_total_g, hierro_mg, magnesio_mg, potasio_mg, proteinas_g, selenio_ug, sodio_mg, vit_a_ug, vit_b1_tiamina_mg, vit_b2_riboflavina_mg, vit_b6_piridoxina_mg, vit_b12_cianocobalamina_ug, vit_c_mg, vit_d_ug, vit_e_mg, yodo_ug, zinc_mg) VALUES ('";
    str.append(strl.at(1));
    str.append("',");
    str.append(strl.at(2));
    str.append(",");
    str.append(strl.at(3));
    str.append(",");
    str.append(strl.at(4));
    str.append(",'");
    str.append(strl.at(5));
    str.append("','");
    str.append(strl.at(6));
    str.append("','");
    str.append(strl.at(7));
    str.append("','");
    str.append(strl.at(8));
    str.append("','");
    str.append(strl.at(9));
    str.append("',");
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
    str.append(",");
    str.append(strl.at(27));
    str.append(",");
    str.append(strl.at(28));
    str.append(",");
    str.append(strl.at(29));
    str.append(",");
    str.append(strl.at(30));
    str.append(");");

    qry = new QSqlQuery();
    qry->prepare(str);
    qry->exec();
}



/*--------------------------------------------------------------------------------------------------------*/
/*------- MOSTRAR LA CANTIDAD EN GRAMOS DE UN INGREDIENTE EN LA BASE DE DATOS (NO EN UN PLATO) -----------*/
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
    str = "SELECT acido_folico_ug, calcio_mg, energia_kcal, fosforo_mg, grasa_total_g, hierro_mg, magnesio_mg, potasio_mg, proteinas_g, selenio_ug, sodio_mg, vit_a_ug, vit_b1_tiamina_mg, vit_b2_riboflavina_mg, vit_b6_piridoxina_mg, vit_b12_cianocobalamina_ug, vit_c_mg, vit_d_ug, vit_e_mg, yodo_ug, zinc_mg FROM AlimentosTAB WHERE nombre='";
    str.append(nombre);
    str.append("'");
}


/*-------------------------------------------------------------------------------------*/
/*------- MOSTRAR EL PRECIO DE UN INGREDIENTE PARA UNA CANTIDAD DETERMINADA -----------*/
/*-------------------------------------------------------------------------------------*/
float database::queryMostrarPrecioING(QString &nombre, float cantidad)
{
    QString str = "SELECT precio, cantidad_g_precio FROM AlimentosTAB WHERE nombre='";
    str.append(nombre);
    str.append("'");

    qry = new QSqlQuery();
    model = new QSqlQueryModel();

    qry->prepare(str);
    qry->exec();
    model->setQuery(*qry);

    float precio = (cantidad * model->record(0).value(0).toFloat()) / model->record(0).value(1).toFloat();

    delete model;
    delete qry;

    return precio;
}


/*-------------------------------------------------------------------------------------*/
/*------------ MOSTRAR LAS INCOMPATIBILIDADES DE UN INGREDIENTE CONCRETO --------------*/
/*-------------------------------------------------------------------------------------*/
QString database::queryIncompatibilidadesING(QString nombre)
{
    QString str = "SELECT incompatibilidades FROM AlimentosTAB WHERE nombre = \"";
    str.append(nombre);
    str.append("\"");

    qry = new QSqlQuery();
    model = new QSqlQueryModel();

    qry->prepare(str);
    qry->exec();
    model->setQuery(*qry);

    str = model->index(0,0).data(Qt::DisplayRole).toString();

    delete model;
    delete qry;

    return str;
}


/*-------------------------------------------------------------------------------------*/
/*---------------- MOSTRAR LOS ALERGENOS DE UN INGREDIENTE CONCRETO -------------------*/
/*-------------------------------------------------------------------------------------*/
QString database::queryAlergenosING(QString nombre)
{
    QString str = "SELECT alergenos FROM AlimentosTAB WHERE nombre = \"";
    str.append(nombre);
    str.append("\"");

    qry = new QSqlQuery();
    model = new QSqlQueryModel();

    qry->prepare(str);
    qry->exec();
    model->setQuery(*qry);

    str = model->index(0,0).data(Qt::DisplayRole).toString();

    delete model;
    delete qry;

    return str;
}


/*-------------------------------------------------------------------------------------*/
/*------------ MOSTRAR LOS MESES DE TEMPORADA DE UN INGREDIENTE CONCRETO --------------*/
/*-------------------------------------------------------------------------------------*/
QString database::queryTemporadaING(QString nombre)
{
    QString str = "SELECT temporada FROM AlimentosTAB WHERE nombre = \"";
    str.append(nombre);
    str.append("\"");

    qry = new QSqlQuery();
    model = new QSqlQueryModel();

    qry->prepare(str);
    qry->exec();
    model->setQuery(*qry);

    str = model->index(0,0).data(Qt::DisplayRole).toString();

    delete model;
    delete qry;

    return str;
}




/*-----------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------*/
/*-------------------------------------------------       PLATOS        -------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------*/


/*-------------------------------------------------------------------------------------*/
/*--------------------------------- MOSTRAR PLATOS ------------------------------------*/
/*-------------------------------------------------------------------------------------*/
void database::queryMostrarPlatos(QString &str)
{
    str = "SELECT nombre FROM PlatosTAB ORDER BY nombre ASC";
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
/*------------------------ MOSTRAR LOS PLATOS SEGUN SU TIPO ---------------------------*/
/*-------------------------------------------------------------------------------------*/
void database::queryMostrarTiposPlatos(QString &str, QString &strID)
{
    str = "SELECT nombre FROM PlatosTAB WHERE tipo ='";
    str.append(strID);
    str.append("' ORDER BY nombre ASC");
}


/*-------------------------------------------------------------------------------------*/
/*------------------- MOSTRAR EL TIPO DE UN PLATO DETERMINADO -------------------------*/
/*-------------------------------------------------------------------------------------*/
QString database::queryMostrarTipoPlato(QString nombre)
{
    QString str = "SELECT tipo FROM platosTAB WHERE nombre='";
    str.append(nombre);
    str.append("'");

    qry = new QSqlQuery();
    model = new QSqlQueryModel();

    qry->prepare(str);
    qry->exec();
    model->setQuery(*qry);

    str = model->record(0).value(0).toString();

    delete model;
    delete qry;

    return str;
}


/*-------------------------------------------------------------------------------------*/
/*--------------------------------- AÑADIR UN PLATO -----------------------------------*/
/*-------------------------------------------------------------------------------------*/
void database::addPLAQuerys(QStringList &strl)
{
    QString str = "ALTER TABLE PlatosTAB AUTO_INCREMENT = 1; INSERT INTO PlatosTAB (nombre, descripcion, precio, tipo, cantidad_gramos, incompatibilidades, alergenos, temporada, acido_folico_ug, calcio_mg, energia_kcal, fosforo_mg, grasa_total_g, hierro_mg, magnesio_mg, potasio_mg, proteinas_g, selenio_ug, sodio_mg, vit_a_ug, vit_b1_mg, vit_b2_mg, vit_b6_mg, vit_b12_ug, vit_c_mg, vit_d_ug, vit_e_mg, yodo_ug, zinc_mg) VALUES ('";
    str.append(strl.at(1));
    str.append("','");
    str.append(strl.at(2));
    str.append("',");
    str.append(strl.at(3));
    str.append(",'");
    str.append(strl.at(4));
    str.append("',");
    str.append(strl.at(5));
    str.append(",'00000','0000000',0,");
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
    str.append(",tipo='");
    str.append(strl.at(4));
    str.append("',cantidad_gramos=");
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
    str.append(",vit_b1_mg=");
    str.append(strl.at(18));
    str.append(",vit_b2_mg=");
    str.append(strl.at(19));
    str.append(",vit_b6_mg=");
    str.append(strl.at(20));
    str.append(",vit_b12_ug=");
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


/*-------------------------------------------------------------------------------*/
/*----------------- ACTUALIZAR INF NUTRICIONAL DE UN PLATO ----------------------*/
/*-------------------------------------------------------------------------------*/

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


/*-------------------------------------------------------------------------------------*/
/*-------------- MODIFICAR LA CANTIDAD EN GRAMOS DE UN PLATO --------------------------*/
/*-------------------------------------------------------------------------------------*/
void database::queryModificarCantidadPlato(QString &strID, QString &cantidad)
{
    QString str = "UPDATE PlatosTAB SET cantidad_gramos=";
    str.append(cantidad);
    str.append(" WHERE id_PlatosTAB=");
    str.append(strID);

    qry = new QSqlQuery();
    model = new QSqlQueryModel();

    qry->prepare(str);
    qry->exec();
    model->setQuery(*qry);

    delete model;
    delete qry;
}


/*-------------------------------------------------------------------------------------*/
/*------------------------ MODIFICAR EL PRECIO DE UN PLATO ----------------------------*/
/*-------------------------------------------------------------------------------------*/
void database::queryModificarPrecioPlato(QString &strID, QString &precio)
{
    QString str = "UPDATE PlatosTAB SET precio=";
    str.append(precio);
    str.append(" WHERE id_PlatosTAB=");
    str.append(strID);

    qry = new QSqlQuery();
    model = new QSqlQueryModel();

    qry->prepare(str);
    qry->exec();
    model->setQuery(*qry);

    delete model;
    delete qry;
}


/*-------------------------------------------------------------------------------------*/
/*------------ MODIFICAR LAS INCOMPATIBILIDADES Y ALERGENOS DE UN PLATO ---------------*/
/*-------------------------------------------------------------------------------------*/
void database::queryModificarIncompAlergPlato(QString &strID, QString &incomp, QString &alerg)
{
    QString str = "UPDATE PlatosTAB SET incompatibilidades='";
    str.append(incomp);
    str.append("',alergenos='");
    str.append(alerg);
    str.append("' WHERE id_PlatosTAB=");
    str.append(strID);

    qry = new QSqlQuery();
    model = new QSqlQueryModel();

    qry->prepare(str);
    qry->exec();
    model->setQuery(*qry);

    delete model;
    delete qry;
}


/*-------------------------------------------------------------------------------------*/
/*------------ MOSTRAR LAS INCOMPATIBILIDADES DE UN PLATO ---------------*/
/*-------------------------------------------------------------------------------------*/
QString database::queryMostrarIncompPlato(QString id)
{
    QString str = "SELECT incompatibilidades FROM PlatosTAB WHERE id_PlatosTAB=";
    str.append(id);

    qry = new QSqlQuery();
    model = new QSqlQueryModel();

    qry->prepare(str);
    qry->exec();
    model->setQuery(*qry);

    str = model->index(0,0).data(Qt::DisplayRole).toString();

    delete model;
    delete qry;

    return str;
}

/*-------------------------------------------------------------------------------------*/
/*-------------- MOSTRAR LOS ALERGENOS DE UN PLATO ---------------*/
/*-------------------------------------------------------------------------------------*/
QString database::queryMostrarAlergPlato(QString id)
{
    QString str = "SELECT alergenos FROM PlatosTAB WHERE id_PlatosTAB=";
    str.append(id);

    qry = new QSqlQuery();
    model = new QSqlQueryModel();

    qry->prepare(str);
    qry->exec();
    model->setQuery(*qry);

    str = model->index(0,0).data(Qt::DisplayRole).toString();

    delete model;
    delete qry;

    return str;
}



/*-----------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------*/
/*----------------------------------------       INGREDIENTES DE UN PLATO        ----------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------*/

/*-------------------------------------------------------------------------------------*/
/*---------------------- MOSTRAR LOS INGREDIENTES DE UN PLATO -------------------------*/
/*-------------------------------------------------------------------------------------*/
void database::queryMostrarIngredientesPlatos(QString &str, QString &strID)
{
    str = "SELECT nombre FROM AlimentosTAB WHERE id_AlimentosTAB IN (SELECT AlimentosTAB_id FROM IngredientesTAB WHERE PlatosTAB_id =";
    str.append(strID);
    str.append(") ORDER BY nombre ASC");
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



/*-----------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------*/
/*----------------------------------------       INGREDIENTES DE UN PLATO        ----------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------*/
QString database::queryNumPlatos()
{
    QString str = "SELECT COUNT(*) FROM platosTAB";
    qry = new QSqlQuery();
    model = new QSqlQueryModel();

    qry->prepare(str);
    qry->exec();
    model->setQuery(*qry);

    str = model->record(0).value(0).toString();

    delete model;
    delete qry;

    return str;
}

QString database::queryNumPriPlato()
{
    QString str = "SELECT COUNT(*) FROM platosTAB WHERE tipo=1";
    qry = new QSqlQuery();
    model = new QSqlQueryModel();

    qry->prepare(str);
    qry->exec();
    model->setQuery(*qry);

    str = model->record(0).value(0).toString();

    delete model;
    delete qry;

    return str;
}

QString database::queryNumSegPlato()
{
    QString str = "SELECT COUNT(*) FROM platosTAB WHERE tipo=2";
    qry = new QSqlQuery();
    model = new QSqlQueryModel();

    qry->prepare(str);
    qry->exec();
    model->setQuery(*qry);

    str = model->record(0).value(0).toString();

    delete model;
    delete qry;

    return str;
}

QString database::queryNumPostre()
{
    QString str = "SELECT COUNT(*) FROM platosTAB WHERE tipo=3";
    qry = new QSqlQuery();
    model = new QSqlQueryModel();

    qry->prepare(str);
    qry->exec();
    model->setQuery(*qry);

    str = model->record(0).value(0).toString();

    delete model;
    delete qry;

    return str;
}





/*-----------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------*/
/*------------------------------------       ACTUALIZAR ID'S DE PLATOS        -------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------*/

void database::ActualizarIDPlatos()
{
    int actualID = 0;
    int numPlatos = queryNumPlatos().toInt();

    QString str = "SELECT id_PlatosTAB FROM platosTAB ORDER BY id_PlatosTAB ASC";
    qry = new QSqlQuery();
    model = new QSqlQueryModel();

    qry->prepare(str);
    qry->exec();
    model->setQuery(*qry);

    for(int i = 0; i < numPlatos; i++)
    {
        actualID = model->index(i,0).data(Qt::DisplayRole).toInt();
        if(actualID != 1+i)
        {
            str = "SET FOREIGN_KEY_CHECKS=0; UPDATE platosTAB SET id_platosTAB=";
            str.append(QString::number(1+i));
            str.append(" WHERE id_platosTAB=");
            str.append(QString::number(actualID));
            str.append("; SET FOREIGN_KEY_CHECKS=1; UPDATE ingredientesTAB SET PlatosTAB_id=");
            str.append(QString::number(1+i));
            str.append(" WHERE PlatosTAB_id=");
            str.append(QString::number(actualID));

            qry->prepare(str);
            qry->exec();
        }
    }

    delete model;
    delete qry;
}







