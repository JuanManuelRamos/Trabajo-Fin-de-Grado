#include "mainwindowmenuplan.h"
#include "ui_mainwindowmenuplan.h"


/*------------------------------------------------------------------*/
/*--------------- QUICKSORT PARA CROWDING DISTANCE -----------------*/
/*------------------------------------------------------------------*/
void MainWindowMenuPlan::quickSortCD(std::vector<individuo> &poblacionNonDom, int first, int last, int numObj)
{
    int pivotElement;

    if(first < last)
    {
        pivotElement = pivotCD(poblacionNonDom, first, last, numObj);
        quickSortCD(poblacionNonDom, first, pivotElement-1, numObj);
        quickSortCD(poblacionNonDom, pivotElement+1, last, numObj);
    }
}

int MainWindowMenuPlan::pivotCD(std::vector<individuo> &poblacionNonDom, int first, int last,  int numObj)
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



/*-------------------------------------------------------------*/
/*--------------- QUICKSORT PARA MATING POOL ------------------*/
/*-------------------------------------------------------------*/
void MainWindowMenuPlan::quickSortMP(std::vector<individuo> &pob, int first, int last)
{
    int pivotElement;

    if(first < last)
    {
        pivotElement = pivotMP(pob, first, last);
        quickSortMP(pob, first, pivotElement-1);
        quickSortMP(pob, pivotElement+1, last);
    }
}

int MainWindowMenuPlan::pivotMP(std::vector<individuo> &pob, int first, int last)
{
    int  p = first;
    for(int i = first+1; i <= last; i++)
    {
        /* If you want to sort the list in the other order, change "<=" to ">" */

        if(sortBestInd(pob[i], pob[first]))
        {
            p++;
            std::swap(pob[i], pob[p]);
        }
    }
    std::swap(pob[p], pob[first]);
    return p;
}

bool MainWindowMenuPlan::sortBestInd(individuo A, individuo B)
{
    return ((A.get_rango() < B.get_rango()) || ((A.get_rango() == B.get_rango()) && (A.get_iDistance() > B.get_iDistance())));
}



/*---------------------------------------------------------------------*/
/*--------------- QUICKSORT PARA PLANES RECOMENDADOS ------------------*/
/*---------------------------------------------------------------------*/

void MainWindowMenuPlan::quickSortGradoRep(std::vector<individuo> &pob, int first, int last)
{
    int pivotElement;

    if(first < last)
    {
        pivotElement = pivotGradoRep(pob, first, last);
        quickSortGradoRep(pob, first, pivotElement-1);
        quickSortGradoRep(pob, pivotElement+1, last);
    }
}

int MainWindowMenuPlan::pivotGradoRep(std::vector<individuo> &pob, int first, int last)
{
    int  p = first;
    double pivotElement = pob[first].get_objGradoRepeticion();

    for(int i = first+1; i <= last; i++)
    {
        /* If you want to sort the list in the other order, change "<=" to ">" */

        if(pob[i].get_objGradoRepeticion() <= pivotElement)
        {
            p++;
            std::swap(pob[i], pob[p]);
        }
    }
    std::swap(pob[p], pob[first]);
    return p;
}
