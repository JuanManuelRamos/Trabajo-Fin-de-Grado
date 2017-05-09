#include "mainwindowmenuplan.h"
#include "ui_mainwindowmenuplan.h"


void MainWindowMenuPlan::crearPoblacion()
{
    std::clock_t start;
    double duration;

    start = std::clock();


    indPoblacion.clear();
    planesRecomendados.clear();
    numEvaluaciones = 0;

    //--- CREAR PRIMERA POBLACION ---

    for(int i = 0; i < NumIndividuos; i++)
    {
        individuo ind = individuo(numDiasPlan, NumInfN, NumAlergenos, NumIncomp);                                               //Crear un individuo
        ind.set_idIndividuo(i);                                                                                                 //Asignarle el id = posicion en el vector indPoblacion
		ind.setMenuDiario(PrimerosPlatos, SegundosPlatos, Postres, nuevoFicheroDeTabla, vectorGruposAlimenticios, GENERAR, ultimos5GA);

        indPoblacion.push_back(ind);                                                                                            //Añadir el individuo al vector de poblacion
    }


    //--- COMPROBAR RESTRICCIONES DEL PROBLEMA ---

    comprobarInfNutricional();

    //--- FAST NON DOMINATED SORT --- Calculo del rango y crowding distance

    fastNonDominatedSort();

    std::vector<individuo> aux;
    int Prand = 0;
    int tamIndPob = 0;   
    int x = 0;
    int N = 0;

    for(int n = 1; n <= 1+indPoblacion.size(); n++)
    {
        for(int i = 0; i < indPoblacion.size(); i++)
        {
            if(indPoblacion[i].get_rango() == n)
                aux.push_back(indPoblacion[i]);
        }
        if(aux.size() > 0)
        {
            crowdingDistance(aux);
            aux.clear();
        }
    }

    //-----------------------------
    //--- COMIENZO GENERACIONES ---
    //-----------------------------


    for(int gen = 0; gen < NumGeneraciones; gen++)
    {

        //--- SELECCION PADRES ---

        set_matingPool(NumIndividuos/2);
        indPoblacion.clear();


        // --- CRUCE/MUTACION ---

        for(int j = 0; j < matingPool.size(); j++)
        {
            do
            {
                Prand = rand() % matingPool.size();
            }
            while(Prand == j);

            individuo hijo1 = individuo(numDiasPlan, NumInfN, NumAlergenos, NumIncomp);
            individuo hijo2 = individuo(numDiasPlan, NumInfN, NumAlergenos, NumIncomp);


            x = rand() % 100;
            if(x < probCruce)
            {
                reproduccion(matingPool[j].getPlanDietetico(), matingPool[Prand].getPlanDietetico(), hijo1, hijo2);
            }
            else
            {
                hijo1 = matingPool[j];
                hijo2 = matingPool[Prand];
            }

            mutacion(hijo1);
            mutacion(hijo2);

			hijo1.setMenuDiario(PrimerosPlatos, SegundosPlatos, Postres, nuevoFicheroDeTabla, vectorGruposAlimenticios, GENERAR, ultimos5GA);
            hijo2.setMenuDiario(PrimerosPlatos, SegundosPlatos, Postres, nuevoFicheroDeTabla, vectorGruposAlimenticios, GENERAR, ultimos5GA);

            indPoblacion.push_back(hijo1);
            tamIndPob = static_cast<int>(indPoblacion.size()-1);
            indPoblacion[tamIndPob].set_idIndividuo(tamIndPob);
            indPoblacion.push_back(hijo2);
            tamIndPob = static_cast<int>(indPoblacion.size()-1);
            indPoblacion[tamIndPob].set_idIndividuo(tamIndPob);
        }


        //--- COMPROBAR RESTRICCIONES DEL PROBLEMA ---

        comprobarInfNutricional();

        //Resetear valores de fast non dominated sort
        for(int k = 0; k < matingPool.size(); k++)
        {
            matingPool[k].set_rango(0);
            matingPool[k].set_iDistance(0);
            matingPool[k].clear_indvDominados();
            indPoblacion.push_back(matingPool[k]);
            tamIndPob = static_cast<int>(indPoblacion.size()-1);
            indPoblacion[tamIndPob].set_idIndividuo(tamIndPob);
        }


        //--- FAST NON DOMINATED SORT --- Calculo del rango y crowding distance

        fastNonDominatedSort();
        aux.clear();
        for(int n = 1; n <= 1+indPoblacion.size(); n++)
        {
            for(int i = 0; i < indPoblacion.size(); i++)
            {
                if(indPoblacion[i].get_rango() == n)
                    aux.push_back(indPoblacion[i]);
            }
            if(aux.size() > 0)
            {
                crowdingDistance(aux);
                aux.clear();
            }
        }

        //--- SELECCION NUEVA POBLACION ---

        set_matingPool(NumIndividuos);
        indPoblacion.clear();
        indPoblacion = matingPool;
        numEvaluaciones += NumIndividuos;

        //---PLANES RECOMENDADOS---

        for(int i = 0; i < indPoblacion.size(); i++)
            if(indPoblacion[i].get_rango() == 1 && indPoblacion[i].get_planAdecuado() && !esRepetido(indPoblacion[i], planesRecomendados))
                planesRecomendados.push_back(indPoblacion[i]);


        indPoblacion = planesRecomendados;
        //Resetear valores de fast non dominated sort
        for(int k = 0; k < indPoblacion.size(); k++)
        {
            indPoblacion[k].set_rango(0);
            indPoblacion[k].set_iDistance(0);
            indPoblacion[k].clear_indvDominados();
            indPoblacion[k].set_idIndividuo(k);
        }
        fastNonDominatedSort();
        planesRecomendados.clear();
        planesRecomendados = indPoblacion;
        indPoblacion.clear();
        indPoblacion = matingPool;



        for(int j = 0; j < planesRecomendados.size(); j++)
            if(planesRecomendados[j].get_rango() != 1)
            {
                planesRecomendados.erase(planesRecomendados.begin()+j);
                j--;
            }




        //LLAMADA A TEST OUTPUT

        int a = 0;
        bool b = false;
        while(a <= eval)
        {
            if(a == numEvaluaciones)
                b = true;
            a += 10000;
        }

        if(b)
        { 
            N = static_cast<int>(planesRecomendados.size()-1);
            quickSortGradoRep(planesRecomendados, 0, N);
            outputFile(nombreAr, true, numEvaluaciones, 0);
        }
    }

    duration = ( std::clock() - start ) / (double) CLOCKS_PER_SEC;

    qDebug() << ""; qDebug() << "";
    qDebug() << "Tiempo de ejecucion: " << duration << " segundos";

    visualizarPlanes();
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
    int x = 0;
    bool mutado = false;
    int ipp, isp, ip;
    std::vector<menuDiario> aux = I.getPlanDietetico();

    for(int i = 0; i < numDiasPlan; i++)
    {
        x = rand() % 100;
        if(x < probMutacion)
        {
            mutado = true;
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



    for(int i = 0; i < NumObjetivos; i++)
    {
        quickSortCD(poblacionNonDom, 0, N, 1+i);
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

    for(int x = 0; x < poblacionNonDom.size(); x++)
        indPoblacion[poblacionNonDom[x].get_idIndividuo()].set_iDistance(poblacionNonDom[x].get_iDistance());
}



double MainWindowMenuPlan::maxObj(std::vector<individuo> poblacionNonDom, int numObj)
{

    double max = 0;
    for(int i = 0; i < poblacionNonDom.size(); i++)
    {
        if(numObj == 1)
        {
            if(poblacionNonDom[i].get_objPrecio() > max)
                max = poblacionNonDom[i].get_objPrecio();
        }
        else if(numObj == 2)
        {
            if(poblacionNonDom[i].get_objGradoRepeticion() > max)
                max = poblacionNonDom[i].get_objGradoRepeticion();
        }
    }
    return max;
}

double MainWindowMenuPlan::minObj(std::vector<individuo> poblacionNonDom, int numObj)
{
    double min = std::numeric_limits<double>::max();
    for(int i = 0; i < poblacionNonDom.size(); i++)
    {
        if(numObj == 1)
        {
            if(poblacionNonDom[i].get_objPrecio() < min)
                min = poblacionNonDom[i].get_objPrecio();
        }
        else if(numObj == 2)
        {
            if(poblacionNonDom[i].get_objGradoRepeticion() < min)
                min = poblacionNonDom[i].get_objGradoRepeticion();
        }
    }
    return min;
}




/*--------------------------------------------------------------------------------------------------------------*/
/*--------------- FAST NON DOMINATED SORT - FUNCION PARA EL CALCULO DEL RANGO DE CADA SOLUCION -----------------*/
/*--------------------------------------------------------------------------------------------------------------*/

void MainWindowMenuPlan::fastNonDominatedSort()
{
    DOMINANCE D;
    std::vector<int> aux;
    bool auxPB = false;
    std::vector< std::vector<int> > indPorFrente;                                       //Vector bidimensional de individuos que almacena las posiciones de los individuos dividios por el frente al que pertenecen

    //Primera parte - rango del primer nivel de no dominancia

    for(int i = 0; i < indPoblacion.size(); i++)
    {
        indPoblacion[i].set_numDominantes(0);

        for(int j = 0; j < indPoblacion.size(); j++)
        {
            if(i != j)
            {
                D = p_dominate_q(indPoblacion[i], indPoblacion[j]);

                if(D == TRUE_D)
                    indPoblacion[i].set_indvDominados(j);
                else if(D == FALSE_D)
                    indPoblacion[i].set_numDominantes(indPoblacion[i].get_numDominantes() + 1);
            }
        }

        if(indPoblacion[i].get_numDominantes() == 0)
        {
            indPoblacion[i].set_rango(1);
            aux.push_back(i);
        }
    }
    indPorFrente.push_back(aux);
    aux.clear();

    //Segunda parte - rango del resto de niveles de no dominancia

    int nivel = 1;
    int pos = 0;

    while((nivel-1) < indPorFrente.size())
    {
        for(int k = 0; k < indPorFrente[nivel-1].size(); k++)
        {
            for(int l = 0; l < indPoblacion[indPorFrente[nivel-1][k]].get_NumIndDominados(); l++)
            {
                pos = indPoblacion[indPorFrente[nivel-1][k]].get_Ind_indDominados(l);
                indPoblacion[pos].set_numDominantes(indPoblacion[pos].get_numDominantes()-1);

                if(indPoblacion[pos].get_numDominantes() == 0)
                {
                    indPoblacion[pos].set_rango(1+nivel);
                    aux.push_back(pos);
                    auxPB = true;
                }
            }
        }
        nivel++;

        if(auxPB)
        {
            indPorFrente.push_back(aux);
            auxPB = false;
            aux.clear();
        }
    }

    aux.clear();
    indPorFrente.clear();
}



DOMINANCE MainWindowMenuPlan::p_dominate_q(individuo P, individuo Q)
{
    if(P.get_objPrecio() < Q.get_objPrecio() && P.get_objGradoRepeticion() < Q.get_objGradoRepeticion())
        return TRUE_D;
    else if(P.get_objPrecio() > Q.get_objPrecio() && P.get_objGradoRepeticion() > Q.get_objGradoRepeticion())
        return FALSE_D;
    else
        return ND;
}




/*----------------------------------------------------------------------------------------------------------------------------*/
/*--------------- COMPRUEBA SI LOS PLANES ALIMENTICIOS CUMPLEN CON LOS REQUISITOS NUTRICIONALES RECOMENDADOS -----------------*/
/*----------------------------------------------------------------------------------------------------------------------------*/
void MainWindowMenuPlan::comprobarInfNutricional()
{
    bool resultado = true;
    float valor = 0.0f;
    //int num = 0;

    for(int i = 0; i < indPoblacion.size(); i++)
    {
        for(int j = 0; j < indPoblacion[i].get_infNutricional().size(); j++)
        {
            valor = indPoblacion[i].get_valor_infNutricional(j);        
            if(valor < irnMinMax[j].first || valor > irnMinMax[j].second)
            {
                resultado = false;
                break;
            }
        }
        indPoblacion[i].set_planAdecuado(resultado);
        resultado = true;
    }
}



/*----------------------------------------------*/
/*--------------- MATING POOL -----------------*/
/*----------------------------------------------*/
void MainWindowMenuPlan::set_matingPool(const int numIndSelec)
{
    std::vector<individuo> pobRecom, pobNoRecom;            //pobRecom = vector de individuos que cumple los requisitos nutricionales, pobNoRecom = individuos que no los cumplen
    double crowD = minCrowDist;


    for(int i = 0; i < indPoblacion.size(); i++)            //Rellenar los vectores pobRecom y pobNoRecom
    {
        if(indPoblacion[i].get_planAdecuado())
            pobRecom.push_back(indPoblacion[i]);
        else
            pobNoRecom.push_back(indPoblacion[i]);
    }


    int N = static_cast<int>(pobRecom.size()-1);
    quickSortMP(pobRecom, 0, N);

    N = static_cast<int>(pobNoRecom.size()-1);
    quickSortMP(pobNoRecom, 0, N);


    int cont = 0;
    int tam = 0;
    matingPool.clear();

    //Rellenar el mating pool con los individuos adecuados

    while(matingPool.size() != numIndSelec)
    {
        //Poblacion de individuos que cumplen las restricciones del problema
        for(int j = 0; j < pobRecom.size(); j++)
        {
            if(cont < numIndSelec)
            {
                if((pobRecom[j].get_iDistance() > crowD && !esRepetido(pobRecom[j], matingPool) && crowD >= 0) || crowD < 0)
                {
                    matingPool.push_back(pobRecom[j]);
                    tam = static_cast<int>(matingPool.size()-1);
                    matingPool[tam].set_idIndividuo(tam);
                    cont++;
                }
            }
            else
            {
                break;
            }
        }

        //Poblacion de individuos que NO cumplen las restricciones del problema
        for(int k = 0; k < pobNoRecom.size(); k++)
        {
            if(cont < numIndSelec)
            {
                if((pobNoRecom[k].get_iDistance() > crowD && !esRepetido(pobNoRecom[k], matingPool) && crowD >= 0) || crowD < 0)
                {
                    matingPool.push_back(pobNoRecom[k]);
                    tam = static_cast<int>(matingPool.size()-1);
                    matingPool[tam].set_idIndividuo(tam);
                    cont++;
                }
            }
            else
            {
                break;
            }
        }
        crowD -= 0.1;
    }
}



bool MainWindowMenuPlan::esRepetido(individuo ind, std::vector<individuo> &vec)
{
    for(int i = 0; i < vec.size(); i++)
    {
        if(vec[i].get_objPrecio() == ind.get_objPrecio() && vec[i].get_objGradoRepeticion() == ind.get_objGradoRepeticion())
            return true;
    }
    return false;
}
