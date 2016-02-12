#include "database.h"


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


bool database::connectBD()
{
    if(!db.open())
    {
        //qDebug() << "Error connection... " << db.lastError().text();
        error = db.lastError().text();
        return false;
    }
    else
    {
        //ui->label->setText("Conectado");
        return true;
    }
}

void database::disconnectBD()
{
    db.close();
}


QString database::errorMsg()
{
    return error;
}

void database::finishQuery()
{
    delete qry;
    delete model;
}

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

        case ELIMINARING:
            queryEliminarIngrediente(str, strID);
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
    }

    //qDebug() << str;
    qry = new QSqlQuery();
    model = new QSqlQueryModel();

    qry->prepare(str);
    qry->exec();
    model->setQuery(*qry);

    return model;
}


void database::queryMostrarIngredientes(QString &str)
{
    str = "SELECT nombre FROM AlimentosTAB ORDER BY nombre ASC";
}

void database::queryMostrarPlatos(QString &str)
{
    str = "SELECT nombre FROM PlatosTAB ORDER BY nombre ASC";
}

void database::queryMostrarInfoIngredientes(QString &str, QString &strID)
{
    str = "SELECT * FROM AlimentosTAB WHERE nombre = \"";
    str.append(strID);
    str.append("\"");
}

void database::queryMostrarInfoPlatos(QString &str, QString &strID)
{
    str = "SELECT * FROM PlatosTAB WHERE nombre = '";
    str.append(strID);
    str.append("'");
}

void database::queryMostrarIngredientesPlatos(QString &str, QString &strID)
{
    str = "SELECT nombre FROM AlimentosTAB WHERE id_AlimentosTAB IN (SELECT AlimentosTAB_id FROM IngredientesTAB WHERE PlatosTAB_id =";
    str.append(strID);
    str.append(")");
}

QSqlQueryModel * database::queryMostrarCantidadInGPlatos(QString &strID, QString &nombre)
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

    return model;
}







void database::queryEliminarIngrediente(QString &str, QString &strID)
{
    str = "SET SQL_SAFE_UPDATES = 0; DELETE FROM IngredientesTAB WHERE AlimentosTAB_id=";
    str.append(strID);
    str.append("; DELETE FROM AlimentosTAB WHERE id_AlimentosTAB=");
    str.append(";");
}

QSqlQueryModel * database::modINGQuerys(QStringList &strl)
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
    model = new QSqlQueryModel();

    qry->prepare(str);
    qry->exec();
    model->setQuery(*qry);

    return model;
}


QSqlQueryModel * database::addINGQuerys(QStringList &strl)
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
    model = new QSqlQueryModel();

    qry->prepare(str);
    qry->exec();
    model->setQuery(*qry);

    return model;
}






