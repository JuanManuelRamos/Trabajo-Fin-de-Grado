#include "mainwindowmenuplan.h"
#include "ui_mainwindowmenuplan.h"
#include "database.h"


void MainWindowMenuPlan::ficheroDeTablaNuevo()
{
    std::vector<double> sz(Postres.size(), 0.0);                                     //Vector de postres
    std::vector<std::vector<double>> sz2(SegundosPlatos.size(), sz);                 //Plano de postres y segundos platos
    nuevoFicheroDeTabla.assign(PrimerosPlatos.size(), sz2);                          //Prisma rectangular de primeros, segundos platos y postres

    //Rellenar vector tridimensional
    setTablaPlatosNuevo(nuevoFicheroDeTabla);
}

void MainWindowMenuPlan::setTablaPlatosNuevo(std::vector<std::vector<std::vector<double>>> &vec)
{
    /* Nuevo valor de compatibilidad de platos = suma de grupos alimenticios repetidos
        1 carne 	+1
        6 marisco 	+0.9
        8 pescado 	+0.6
        7 pasta 	+0.5
        5 legumbre 	+0.3
        9 verdura	+0.1
        3 fruta		+0.1
        2 cereal	+0.3
        4 lacteo	+0.3
        0 otro		+0.1
    */

    std::vector<bool> gaElegidos;

    for(int y = 0; y < PrimerosPlatos.size(); y++)
        for(int x = 0; x < SegundosPlatos.size(); x++)
            for(int z = 0; z < Postres.size(); z++)
            {
                gaElegidos.clear();
                gaElegidos.assign(10,false);
                setGAElegidos(PrimerosPlatos[y].gruposAl, gaElegidos);
                vec[y][x][z] = setPenalizacion(SegundosPlatos[x].gruposAl, gaElegidos);
                setGAElegidos(SegundosPlatos[x].gruposAl, gaElegidos);
                vec[y][x][z] += setPenalizacion(Postres[z].gruposAl, gaElegidos);
            }
}

void MainWindowMenuPlan::setGAElegidos(std::vector<int> gal, std::vector<bool> &galE)
{
    for(int i = 0; i < gal.size(); i++)
        galE[gal[i]] = true;
}

double MainWindowMenuPlan::setPenalizacion(std::vector<int> gal, std::vector<bool> galE)
{
    double resultado = 0.0;
    for(int i = 0; i < gal.size(); i++)
    {
        if(galE[gal[i]])
            switch(gal[i])
            {
                case 0: case 3: case 9:
                    resultado += 2.0;
                break;

                case 1:
                    resultado += 3.0;
                break;

                case 2: case 4: case 5:
                    resultado += 2.5;
                break;

                case 6:
                    resultado += 2.8;
                break;

                case 7:
                    resultado += 2.5;
                break;

                case 8:
                    resultado += 2.5;
                break;
            }
    }
    return resultado;
}
