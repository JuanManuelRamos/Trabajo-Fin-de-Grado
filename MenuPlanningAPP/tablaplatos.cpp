#include "mainwindowmenuplan.h"
#include "ui_mainwindowmenuplan.h"
#include "database.h"



void MainWindowMenuPlan::FicheroDeTabla()
{
    fstream fs;
    fs.open("tablaplatos.txt", fstream::out | fstream::in);                             //Si el archivo existe se abre

    if(!fs.is_open())                                                                   //Si el archivo no existe se crea
        fs.open("tablaplatos.txt", fstream::out | fstream::in | fstream::trunc);


    vector<int> prueba(5,-1);

    for(int i = 1; i < prueba.size(); i++)
        qDebug() << prueba.at(i);


    fs.close();
}
