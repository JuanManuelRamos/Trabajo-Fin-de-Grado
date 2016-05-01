#include "mainwindowmenuplan.h"
#include "ui_mainwindowmenuplan.h"


void MainWindowMenuPlan::crearPoblacion(int numDiasPlan)
{
    individuo *ind = new individuo(numDiasPlan);

    ind->setMenuDiario(PrimerosPlatos, SegundosPlatos, Postres);
}
