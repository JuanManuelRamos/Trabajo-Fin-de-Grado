#include "mainwindowmenuplan.h"
#include "ui_mainwindowmenuplan.h"


void MainWindowMenuPlan::crearPoblacion()
{
    individuo *ind = new individuo();

    ind->setMenuDiario(PrimerosPlatos, SegundosPlatos, Postres);

}
