#include "mainwindowmenuplan.h"
#include "ui_mainwindowmenuplan.h"


void MainWindowMenuPlan::outputFile(QString name, bool b, int eval, int ejec)
{
    std::ofstream file;
    file.open(name.toStdString(), std::ios_base::app);

    if(b)
    {
        file << "Num_Eval: " << eval << "\n";
        int pp,sp,p;

        for(int x = 0; x < planesRecomendados.size(); x++)
        {
            file << "[";
            for(int y = 0; y < numDiasPlan; y++)
            {
                pp = planesRecomendados[x].get_idPlatoPPSec(y);
                sp = planesRecomendados[x].get_idPlatoSPSec(y);
                p = planesRecomendados[x].get_idPlatoPSec(y);


                file << "(";
                file << db1->queryMostrarNombrePlatoPorID(QString::number(planesRecomendados[x].get_idPlatoPP(y))).toStdString();
                for(int a = 0; a < PrimerosPlatos[pp].gruposAl.size(); a++)
                    file << PrimerosPlatos[pp].gruposAl[a];

                file << ",";
                file << db1->queryMostrarNombrePlatoPorID(QString::number(planesRecomendados[x].get_idPlatoSP(y))).toStdString();
                for(int b = 0; b < SegundosPlatos[sp].gruposAl.size(); b++)
                    file << SegundosPlatos[sp].gruposAl[b];

                file << ",";
                file << db1->queryMostrarNombrePlatoPorID(QString::number(planesRecomendados[x].get_idPlatoP(y))).toStdString();
                for(int c = 0; c < Postres[p].gruposAl.size(); c++)
                    file << Postres[p].gruposAl[c];

                if(y == numDiasPlan-1)
                    file << ")";
                else
                    file << "),";
            }
            file << "]" << "\n";
            file << planesRecomendados[x].get_objPrecio() << " " << planesRecomendados[x].get_objGradoRepeticion() << "\n";
        }
        file << "\n";
    }

    file.close();
}
