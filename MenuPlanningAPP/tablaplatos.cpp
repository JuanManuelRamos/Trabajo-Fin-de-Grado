#include "mainwindowmenuplan.h"
#include "ui_mainwindowmenuplan.h"
#include "database.h"



void MainWindowMenuPlan::ficheroDeTabla()
{
    std::fstream fs;
    fs.open("tablaplatos.txt", std::fstream::out | std::fstream::in);                                           //Si el archivo existe se abre

    if(!fs.is_open())                                                                                           //Si el archivo no existe se crea
        fs.open("tablaplatos.txt", std::fstream::out | std::fstream::in | std::fstream::trunc);

    std::vector<int> vec(db1->queryNumPlatos().toInt(), -1);                                                    //Crear vector de tamanio igual a numero de platos
    vectorFicheroDeTabla.assign(vec.size(), vec);                                                               //Crear vector bidimensional

    setTablaPlatos(vectorFicheroDeTabla);                                                                       //Rellenar el vector bidimensional o tabla

    /*for(int i = 0; i < vectorFicheroDeTabla.size(); i++)
    {
        for(int j = 0; j < vectorFicheroDeTabla.size(); j++)
            qDebug() << vectorFicheroDeTabla[i][j] << "  ";

        qDebug() << "----";
    }*/

    for(int i = 0; i < vectorFicheroDeTabla.size(); i++)                                                        //Escribir la tabla en el archivo
    {
        for(int j = 0; j < vectorFicheroDeTabla.size(); j++)
            fs << vectorFicheroDeTabla[i][j] << "\t";

        fs << "\n";
    }

    fs.close();
}



void MainWindowMenuPlan::setTablaPlatos(std::vector< std::vector<int> > &vec)
{
    int sz = 1;
    bool variedad = true;
    QSqlQueryModel *model;

    std::vector<int> grupoAl_1;
    std::vector<int> grupoAl_2;


    for(int i = 0; i < vec.size(); i++)
    {
        //Consulta para mostrar los ingredientes principales de un plato
        model = db1->queryMostrarGruposAldeIngPrincipales(QString::number(1+i));

        for(int k = 0; k < model->rowCount(); k++)
            grupoAl_1.push_back(model->index(k,0).data(Qt::DisplayRole).toInt());                                                                                   //Guardar su grupo alimenticio
        delete model;

        for(int j = 0; j < sz; j++)                                                                                                                                 //__Para cada plato i, comprarlo con el resto de platos j
        {
            if(i == j)                                                                                                                                              //Si la celda corresponde al mismo plato, VARIEDAD = 0
               vec[i][j] = 0;
            else
            {
                if(db1->queryMostrarTipoPlatoID(QString::number(1+i)) == db1->queryMostrarTipoPlatoID(QString::number(1+j)))                                        //Si la celda corresponde a dos platos del mismo tipo (2 primer plato o 2 segundos platos), VARIEDAD = 0
                    vec[i][j] = 0;
                else if(db1->queryMostrarTipoPlatoID(QString::number(1+i)) == 3 || db1->queryMostrarTipoPlatoID(QString::number(1+j)) == 3)                         //Si alguno de los platos es un postre, VARIEDAD = 0
                    vec[i][j] = 0;
                else                                                                                                                                                //Si la celda corresponde a un primer plato y un segundo plato...
                {
                    model = db1->queryMostrarGruposAldeIngPrincipales(QString::number(1+j));

                    for(int l = 0; l < model->rowCount(); l++)
                        grupoAl_2.push_back(model->index(l,0).data(Qt::DisplayRole).toInt());                                                                       //Guardar su grupo alimenticio
                    delete model;

                    if(grupoAl_1.size() > 0 && grupoAl_2.size() > 0)                                                                                                //Si el plato i y j tienen ingredientes principales
                    {
                        for(int x = 0; x < grupoAl_1.size(); x++)                                                                                                   //Comprobar si tienen en comun grupos alimenticios
                            for(int y = 0; y < grupoAl_2.size(); y++)                         
                                if(grupoAl_1[x] == grupoAl_2[y])
                                    variedad = false;

                        if(variedad)                                                                                                                                //Si NO tienen en comun grupos alimenticios, VARIEDAD = 10
                           vec[i][j] = 10;
                        else
                            vec[i][j] = 5;                                                                                                                          //Si tienen en comun grupos alimenticios, VARIEDAD = 5
                    }
                    else                                                                                                                                            //Si alguno de los platos no tiene ingrediente principal, VARIEDAD = 10
                        vec[i][j] = 10;

                }
            }

            variedad = true;        
            grupoAl_2.clear();
        }
        grupoAl_1.clear();
        sz++;
    }
}
