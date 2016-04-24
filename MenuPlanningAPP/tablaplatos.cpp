#include "mainwindowmenuplan.h"
#include "ui_mainwindowmenuplan.h"
#include "database.h"



void MainWindowMenuPlan::FicheroDeTabla()
{
    std::fstream fs;
    fs.open("tablaplatos.txt", std::fstream::out | std::fstream::in);                                   //Si el archivo existe se abre

    if(!fs.is_open())                                                                                   //Si el archivo no existe se crea
        fs.open("tablaplatos.txt", std::fstream::out | std::fstream::in | std::fstream::trunc);

    std::vector<int> vec(db1->queryNumPlatos().toInt(), -1);                                            //Crear vector de tamanio igual a numero de platos
    std::vector< std::vector<int> > tablaPlatos(vec.size(), vec);                                       //Crear vector bidimensional

    rellenarTablaPlatos(tablaPlatos);                                                                   //Rellenar el vector bidimensional o tabla

    for(int i = 0; i < tablaPlatos.size(); i++)                                                         //Escribir la tabla en el archivo
    {
        for(int j = 0; j < tablaPlatos.size(); j++)
            fs << tablaPlatos[i][j] << "\t";

        fs << "\n";
    }

    fs.close();
}



void MainWindowMenuPlan::rellenarTablaPlatos(std::vector< std::vector<int> > &vec)
{
    int sz = 1;
    bool variedad = true;
    QSqlQueryModel model;

    std::vector<int> grupoAl_1;
    std::vector<int> grupoAl_2;


    for(int i = 0; i < vec.size(); i++)
    {
        QString str = "SELECT id_AlimentosTAB FROM AlimentosTAB WHERE id_AlimentosTAB IN (SELECT AlimentosTAB_id FROM IngredientesTAB WHERE PlatosTAB_id =";        //Ingredientes del plato i
        str.append(QString::number(1+i));
        str.append(")");
        model.setQuery(str);

        for(int k = 0; k < model.rowCount(); k++)
            if(db1->queryEsIngredientePrincipal(model.index(k,0).data(Qt::DisplayRole).toString()))                                                                 //Comprobar si el ingrediente k del plato i es principal
                grupoAl_1.push_back(db1->queryMostrarGrupoAlimenticio(model.index(k,0).data(Qt::DisplayRole).toString()));                                          //Si lo es, guardar su grupo alimenticio


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
                    str = "SELECT id_AlimentosTAB FROM AlimentosTAB WHERE id_AlimentosTAB IN (SELECT AlimentosTAB_id FROM IngredientesTAB WHERE PlatosTAB_id =";    //Ingredientes del plato j
                    str.append(QString::number(1+j));
                    str.append(")");
                    model.setQuery(str);

                    for(int l = 0; l < model.rowCount(); l++)
                        if(db1->queryEsIngredientePrincipal(model.index(l,0).data(Qt::DisplayRole).toString()))                                                     //Comprobar si el ingrediente l del plato j es principal
                            grupoAl_2.push_back(db1->queryMostrarGrupoAlimenticio(model.index(l,0).data(Qt::DisplayRole).toString()));                              //Si lo es, guardar su grupo alimenticio

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
