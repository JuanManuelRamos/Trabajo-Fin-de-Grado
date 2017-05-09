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



/*-------------------------------------------------------------------------------------------*/
/*--------------- QUICKSORT PARA PLANES RECOMENDADOS - GRADO DE REPETICION ------------------*/
/*-------------------------------------------------------------------------------------------*/

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

    for(int i = first+1; i <= last; i++)
    {
        if(sortBestIndGR(pob[i], pob[first]))
        {
            p++;
            std::swap(pob[i], pob[p]);
        }
    }
    std::swap(pob[p], pob[first]);
    return p;
}

bool MainWindowMenuPlan::sortBestIndGR(individuo A, individuo B)
{
    return ((A.get_objGradoRepeticion() < B.get_objGradoRepeticion()) || ((A.get_objGradoRepeticion() == B.get_objGradoRepeticion()) && (A.get_planAdecuado() && !B.get_planAdecuado())));
}


/*------------------------------------------------------------------------------*/
/*--------------- QUICKSORT PARA PLANES RECOMENDADOS - PRECIO ------------------*/
/*------------------------------------------------------------------------------*/

void MainWindowMenuPlan::quickSortPrecio(std::vector<individuo> &pob, int first, int last)
{
    int pivotElement;

    if(first < last)
    {
        pivotElement = pivotPrecio(pob, first, last);
        quickSortPrecio(pob, first, pivotElement-1);
        quickSortPrecio(pob, pivotElement+1, last);
    }
}

int MainWindowMenuPlan::pivotPrecio(std::vector<individuo> &pob, int first, int last)
{
    int  p = first;

    for(int i = first+1; i <= last; i++)
    {
        if(sortBestIndP(pob[i], pob[first]))
        {
            p++;
            std::swap(pob[i], pob[p]);
        }
    }
    std::swap(pob[p], pob[first]);
    return p;
}

bool MainWindowMenuPlan::sortBestIndP(individuo A, individuo B)
{
    return ((A.get_objPrecio() < B.get_objPrecio()) || ((A.get_objPrecio() == B.get_objPrecio()) && (A.get_planAdecuado() && !B.get_planAdecuado())));
}
