#include "mainwindowmenuplan.h"
#include "ui_mainwindowmenuplan.h"


void MainWindowMenuPlan::crearPoblacion(int numDiasPlan)
{
    const int numIndividuos = 100;                                                                                          //Numero de individuos totales de la poblacion

    for(int i = 0; i < numIndividuos; i++)
    {
        individuo ind = individuo(numDiasPlan, NumInfN, NumAlergenos, NumIncomp);                                           //Crear un individuo
        ind.setMenuDiario(PrimerosPlatos, SegundosPlatos, Postres, vectorFicheroDeTabla, vectorGruposAlimenticios);         //Asignarle su plan alimenticio correspondiente

        indPoblacion.push_back(ind);                                                                                        //Añadir el individuo al vector de poblacion
    }


}
