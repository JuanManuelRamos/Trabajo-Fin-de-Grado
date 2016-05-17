#include "mainwindowmenuplan.h"
#include "ui_mainwindowmenuplan.h"


void MainWindowMenuPlan::quickSort(std::vector<individuo> &poblacionNonDom, int first, int last, int numObj)
{
    int pivotElement;

    if(first < last)
    {
        pivotElement = pivot(poblacionNonDom, first, last, numObj);
        quickSort(poblacionNonDom, first, pivotElement-1, numObj);
        quickSort(poblacionNonDom, pivotElement+1, last, numObj);
    }
}

int MainWindowMenuPlan::pivot(std::vector<individuo> &poblacionNonDom, int first, int last,  int numObj)
{
    int  p = first;
    double pivotElement = 0;

    switch(numObj)
    {
        case 1:
            pivotElement = poblacionNonDom[first].get_objPrecio();
        break;

        case 2:
            pivotElement = poblacionNonDom[first].get_objGradoRepeticion();
        break;
    }




    for(int i = first+1; i <= last; i++)
    {
        /* If you want to sort the list in the other order, change "<=" to ">" */

        if(poblacionNonDom[i].get_objPrecio() <= pivotElement && numObj == 1)
        {
            p++;
            std::swap(poblacionNonDom[i], poblacionNonDom[p]);
        }
        else if(poblacionNonDom[i].get_objGradoRepeticion() <= pivotElement && numObj == 2)
        {
            p++;
            std::swap(poblacionNonDom[i], poblacionNonDom[p]);
        }
    }
    std::swap(poblacionNonDom[p], poblacionNonDom[first]);
    return p;
}



