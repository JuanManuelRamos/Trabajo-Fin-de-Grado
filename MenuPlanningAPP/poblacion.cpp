#include "mainwindowmenuplan.h"
#include "ui_mainwindowmenuplan.h"


void MainWindowMenuPlan::crearPoblacion()
{
    indPoblacion.clear();

    for(int i = 0; i < NumIndividuos; i++)
    {
        individuo ind = individuo(numDiasPlan, NumInfN, NumAlergenos, NumIncomp);                                               //Crear un individuo
        ind.setMenuDiario(PrimerosPlatos, SegundosPlatos, Postres, vectorFicheroDeTabla, vectorGruposAlimenticios, GENERAR);    //Asignarle su plan alimenticio correspondiente

        indPoblacion.push_back(ind);                                                                                            //Añadir el individuo al vector de poblacion
    }


    /*
    qDebug() << "-----PADRES BIEEENNNNN------";
    individuo hijo1 = individuo(numDiasPlan, NumInfN, NumAlergenos, NumIncomp);                                               //Crear un individuo
    individuo hijo2 = individuo(numDiasPlan, NumInfN, NumAlergenos, NumIncomp);                                               //Crear un individuo

    reproduccion(indPoblacion[0].getPlanDietetico(), indPoblacion[1].getPlanDietetico(), hijo1, hijo2);
    qDebug() << "-----REPRODUCCION BIEEENNNNN------";

    hijo1.setMenuDiario(PrimerosPlatos, SegundosPlatos, Postres, vectorFicheroDeTabla, vectorGruposAlimenticios, ACTUALIZAR);    //Asignarle su plan alimenticio correspondiente
    hijo2.setMenuDiario(PrimerosPlatos, SegundosPlatos, Postres, vectorFicheroDeTabla, vectorGruposAlimenticios, ACTUALIZAR);    //Asignarle su plan alimenticio correspondiente
    qDebug() << "-----HIJOS REPRODUCCION BIEEENNNNN------";

    mutacion(hijo1);
    qDebug() << "-----HIJO 1 MUTACION BIEEENNNNN------";
    mutacion(hijo2);
    qDebug() << "-----HIJO 2 MUTACION BIEEENNNNN------";

    hijo1.setMenuDiario(PrimerosPlatos, SegundosPlatos, Postres, vectorFicheroDeTabla, vectorGruposAlimenticios, ACTUALIZAR);    //Asignarle su plan alimenticio correspondiente
    hijo2.setMenuDiario(PrimerosPlatos, SegundosPlatos, Postres, vectorFicheroDeTabla, vectorGruposAlimenticios, ACTUALIZAR);    //Asignarle su plan alimenticio correspondiente

    qDebug() << "-----TODO BIEEENNNNN------";  
    */

    crowdingDistance(indPoblacion);


}




/*-------------------------------------------------------------------------------------------------------------------*/
/*--------------- REPRODUCCION DE DOS INDIVIDUOS - GENERA PLAN DIETETICO PARA DOS NUEVOS INDIVIDUOS -----------------*/
/*-------------------------------------------------------------------------------------------------------------------*/

void MainWindowMenuPlan::reproduccion(std::vector<menuDiario> P1, std::vector<menuDiario> P2, individuo &H1, individuo &H2)
{
    int limitInf = (numDiasPlan/2)-((numDiasPlan/2)/2)-1;
    int limitSup = (numDiasPlan/2)+((numDiasPlan/2)/2)-1;

    int corte = 0;

    do
        corte = rand() % numDiasPlan;
    while(corte < limitInf || corte > limitSup);

    qDebug() << "limitINF: " << limitInf << " limitSUP: " << limitSup << " Corte: " << corte;

    std::vector<menuDiario> aux12, aux21;
    menuDiario menu;

    for(int i = 0; i < corte; i++)
    {
        menu.idPrimerPlato = P1[i].idPrimerPlato;
        menu.idSegundoPlato = P1[i].idSegundoPlato;
        menu.idPostre = P1[i].idPostre;
        aux12.push_back(menu);

        menu.idPrimerPlato = P2[i].idPrimerPlato;
        menu.idSegundoPlato = P2[i].idSegundoPlato;
        menu.idPostre = P2[i].idPostre;
        aux21.push_back(menu);
    }

    for(int j = corte; j < numDiasPlan; j++)
    {
        menu.idPrimerPlato = P1[j].idPrimerPlato;
        menu.idSegundoPlato = P1[j].idSegundoPlato;
        menu.idPostre = P1[j].idPostre;
        aux21.push_back(menu);

        menu.idPrimerPlato = P2[j].idPrimerPlato;
        menu.idSegundoPlato = P2[j].idSegundoPlato;
        menu.idPostre = P2[j].idPostre;
        aux12.push_back(menu);
    }

    H1.setPlanDietetico(aux12);
    H2.setPlanDietetico(aux21);
}



/*----------------------------------------------------------*/
/*--------------- MUTACION DE UN INDIVIDUO -----------------*/
/*----------------------------------------------------------*/

void MainWindowMenuPlan::mutacion(individuo &I)
{
    int probabilidadMutacion = 0;
    bool mutado = false;
    int ipp, isp, ip;
    std::vector<menuDiario> aux = I.getPlanDietetico();

    for(int i = 0; i < numDiasPlan; i++)
    {
        probabilidadMutacion = rand() % 100;
        if(probabilidadMutacion < 10)
        {
            mutado = true;
            qDebug() << "Mutado menu nº " << 1+i;

            ipp = rand() % PrimerosPlatos.size();
            isp = rand() % SegundosPlatos.size();
            ip = rand() % Postres.size();

            aux[i].idPrimerPlato.first = PrimerosPlatos[ipp].id;
            aux[i].idSegundoPlato.first = SegundosPlatos[isp].id;
            aux[i].idPostre.first = Postres[ip].id;
            aux[i].idPrimerPlato.second = ipp;
            aux[i].idSegundoPlato.second = isp;
            aux[i].idPostre.second = ip;
        }
    }

    if(mutado)
        I.setPlanDietetico(aux);
}



/*-----------------------------------------------------------------------------------------*/
/*--------------- CALCULO DE CROWDING DISTANCE DE INDIVIDUOS NO DOMINADOS -----------------*/
/*-----------------------------------------------------------------------------------------*/

void MainWindowMenuPlan::crowdingDistance(std::vector<individuo> &poblacionNonDom)
{
    int N = static_cast<int>(poblacionNonDom.size()-1);
    double dmax = std::numeric_limits<double>::max();
    double aux = 0, max, min;

    /*for(int j = 0; j < poblacionNonDom.size(); j++)
        qDebug() << "Precio: " << poblacionNonDom[j].get_objPrecio() << " Repeticion: " << poblacionNonDom[j].get_objGradoRepeticion();

    qDebug() << "-----------";*/

    for(int i = 0; i < NumObjetivos; i++)
    {
        quickSort(poblacionNonDom, 0, N, 1+i);
        poblacionNonDom[0].set_iDistance(dmax);
        poblacionNonDom[N].set_iDistance(dmax);
        max = maxObj(poblacionNonDom, 1+i);
        min = minObj(poblacionNonDom, 1+i);

        for(int j = 1; j < N; j++)
        {
            if(i == 0)
                aux = poblacionNonDom[j].get_iDistance() + ((poblacionNonDom[1+j].get_objPrecio() - poblacionNonDom[j-1].get_objPrecio()) / (max - min));
            else if(i == 1)
                aux = poblacionNonDom[j].get_iDistance() + ((poblacionNonDom[1+j].get_objGradoRepeticion() - poblacionNonDom[j-1].get_objGradoRepeticion()) / (max - min));

            poblacionNonDom[j].set_iDistance(aux);
        }
    }
}



double MainWindowMenuPlan::maxObj(std::vector<individuo> poblacionNonDom, int numObj)
{
    double max = 0;
    for(int i = 0; i < poblacionNonDom.size(); i++)
    {
        if(numObj == 1)
            if(poblacionNonDom[i].get_objPrecio() > max)
                max = poblacionNonDom[i].get_objPrecio();
        else if(numObj == 2)
            if(poblacionNonDom[i].get_objGradoRepeticion() > max)
                max = poblacionNonDom[i].get_objGradoRepeticion();
    }
    return max;
}

double MainWindowMenuPlan::minObj(std::vector<individuo> poblacionNonDom, int numObj)
{
    double min = std::numeric_limits<double>::max();
    for(int i = 0; i < poblacionNonDom.size(); i++)
    {
        if(numObj == 1)
            if(poblacionNonDom[i].get_objPrecio() < min)
                min = poblacionNonDom[i].get_objPrecio();
        else if(numObj == 2)
            if(poblacionNonDom[i].get_objGradoRepeticion() < min)
                min = poblacionNonDom[i].get_objGradoRepeticion();
    }
    return min;
}









