#include "mainwindowmenuplan.h"
#include "ui_mainwindowmenuplan.h"


void MainWindowMenuPlan::crearPoblacion()
{

    std::clock_t start;
    double duration;

    start = std::clock();


    indPoblacion.clear();

    for(int i = 0; i < NumIndividuos; i++)
    {
        individuo ind = individuo(numDiasPlan, NumInfN, NumAlergenos, NumIncomp);                                               //Crear un individuo
        ind.set_idIndividuo(i);                                                                                                 //Asignarle el id = posicion en el vector indPoblacion
        ind.setMenuDiario(PrimerosPlatos, SegundosPlatos, Postres, vectorFicheroDeTabla, vectorGruposAlimenticios, GENERAR);    //Asignarle su plan alimenticio correspondiente

        indPoblacion.push_back(ind);                                                                                            //Añadir el individuo al vector de poblacion
    }


    /*==============================================================*/
    /* EJEMPLO PARA PRUEBA DE LAS FUNCIONES DE REPRODUCCION Y MUTACION */
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
    /*==============================================================*/



    /*==============================================================*/
    /* EJEMPLO DE CONJUNTO DE SOLUCIONES NO DOMINADAS PARA PROBAR LA FUNCION DE CROWDING DISTANCE Y FIRST NON DOMINATED SORT*/

    /*indPoblacion.clear();

    individuo ind = individuo(numDiasPlan, NumInfN, NumAlergenos, NumIncomp);
    ind.set_objPrecio(30.67);
    ind.set_objGradoRepeticion(7.43);
    indPoblacion.push_back(ind);

    ind = individuo(numDiasPlan, NumInfN, NumAlergenos, NumIncomp);
    ind.set_objPrecio(29.69);
    ind.set_objGradoRepeticion(11.12);
    indPoblacion.push_back(ind);

    ind = individuo(numDiasPlan, NumInfN, NumAlergenos, NumIncomp);
    ind.set_objPrecio(33.04);
    ind.set_objGradoRepeticion(11.07);
    indPoblacion.push_back(ind);

    ind = individuo(numDiasPlan, NumInfN, NumAlergenos, NumIncomp);
    ind.set_objPrecio(30.74);
    ind.set_objGradoRepeticion(14.76);
    indPoblacion.push_back(ind);

    ind = individuo(numDiasPlan, NumInfN, NumAlergenos, NumIncomp);
    ind.set_objPrecio(32.78);
    ind.set_objGradoRepeticion(10.87);
    indPoblacion.push_back(ind);

    ind = individuo(numDiasPlan, NumInfN, NumAlergenos, NumIncomp);
    ind.set_objPrecio(27.06);
    ind.set_objGradoRepeticion(13.05);
    indPoblacion.push_back(ind);

    ind = individuo(numDiasPlan, NumInfN, NumAlergenos, NumIncomp);
    ind.set_objPrecio(31.44);
    ind.set_objGradoRepeticion(9.23);
    indPoblacion.push_back(ind);

    ind = individuo(numDiasPlan, NumInfN, NumAlergenos, NumIncomp);
    ind.set_objPrecio(30.88);
    ind.set_objGradoRepeticion(9.59);
    indPoblacion.push_back(ind);

    ind = individuo(numDiasPlan, NumInfN, NumAlergenos, NumIncomp);
    ind.set_objPrecio(28.43);
    ind.set_objGradoRepeticion(6.77);
    indPoblacion.push_back(ind);

    ind = individuo(numDiasPlan, NumInfN, NumAlergenos, NumIncomp);
    ind.set_objPrecio(32.67);
    ind.set_objGradoRepeticion(8.87);
    indPoblacion.push_back(ind);

    ind = individuo(numDiasPlan, NumInfN, NumAlergenos, NumIncomp);
    ind.set_objPrecio(4.8);
    ind.set_objGradoRepeticion(16.5);
    indPoblacion.push_back(ind);

    ind = individuo(numDiasPlan, NumInfN, NumAlergenos, NumIncomp);
    ind.set_objPrecio(2.5);
    ind.set_objGradoRepeticion(22);
    indPoblacion.push_back(ind);

    crowdingDistance(indPoblacion);

    for(int j = 0; j < indPoblacion.size(); j++)
            qDebug() << "Precio: " << indPoblacion[j].get_objPrecio() << " Repeticion: " << indPoblacion[j].get_objGradoRepeticion() << " iDistance: " << indPoblacion[j].get_iDistance();

    qDebug() << "-----------";*/
    /*==============================================================*/



    comprobarInfNutricional();
    //qDebug() << "comprobarInfNutricional BIEN";
    fastNonDominatedSort();
    //qDebug() << "fastNonDominatedSort BIEN";

    std::vector<individuo> aux;
    int Prand = 0;
    int tamIndPob = 0;

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

    //qDebug() << "crowdingDistance BIEN";


    for(int gen = 0; gen < NumGeneraciones; gen++)
    {
        set_meetingPool(NumIndividuos/2);
        //qDebug() << "meetingPool BIEN";


        indPoblacion.clear();


        for(int j = 0; j < meetingPool.size(); j++)
        {
            do
            {
                Prand = rand() % meetingPool.size();
            }
            while(Prand == j);

            //qDebug() << "Padre 1: " << j << " Padre 2: " << Prand;
            individuo hijo1 = individuo(numDiasPlan, NumInfN, NumAlergenos, NumIncomp);
            individuo hijo2 = individuo(numDiasPlan, NumInfN, NumAlergenos, NumIncomp);

            reproduccion(meetingPool[j].getPlanDietetico(), meetingPool[Prand].getPlanDietetico(), hijo1, hijo2);
            //qDebug() << "reproduccion BIEN";
            mutacion(hijo1);
            mutacion(hijo2);
            //qDebug() << "mutacion BIEN";

            hijo1.setMenuDiario(PrimerosPlatos, SegundosPlatos, Postres, vectorFicheroDeTabla, vectorGruposAlimenticios, ACTUALIZAR);
            hijo2.setMenuDiario(PrimerosPlatos, SegundosPlatos, Postres, vectorFicheroDeTabla, vectorGruposAlimenticios, ACTUALIZAR);
            //qDebug() << "actualizacion BIEN";

            indPoblacion.push_back(hijo1);
            tamIndPob = static_cast<int>(indPoblacion.size()-1);
            indPoblacion[tamIndPob].set_idIndividuo(tamIndPob);
            indPoblacion.push_back(hijo2);
            tamIndPob = static_cast<int>(indPoblacion.size()-1);
            indPoblacion[tamIndPob].set_idIndividuo(tamIndPob);
        }

        comprobarInfNutricional();

        for(int k = 0; k < meetingPool.size(); k++)
        {
            meetingPool[k].set_rango(0);
            meetingPool[k].set_iDistance(0);
            meetingPool[k].clear_indvDominados();
            indPoblacion.push_back(meetingPool[k]);
            tamIndPob = static_cast<int>(indPoblacion.size()-1);
            indPoblacion[tamIndPob].set_idIndividuo(tamIndPob);
        }

        //qDebug() << "Num total de padres: " << meetingPool.size();
        //qDebug() << "Num total de hijos: " << indPoblacion.size();


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
        //qDebug() << "crowding-distance BIEN";

        /*qDebug() << "--- PADRES ---";
        for(int x = 0; x < meetingPool.size(); x++)
            qDebug() << x << "[" << meetingPool[x].get_planAdecuado() << "] Rango: " << meetingPool[x].get_rango() << " Crow_dist: " << meetingPool[x].get_iDistance();


        qDebug() << "--- HIJOS ---";
        for(int x = 0; x < indPoblacion.size(); x++)
            qDebug() << x << "[" << indPoblacion[x].get_planAdecuado() << "] Rango: " << indPoblacion[x].get_rango() << " Crow_dist: " << indPoblacion[x].get_iDistance();*/


        set_meetingPool(NumIndividuos);
        indPoblacion.clear();
        indPoblacion = meetingPool;

        /*if(gen == 0 || gen == 250 || gen == 500 || gen == 750)
        {
            qDebug() << "--- POBLACION FINAL " << gen << " ---";
            for(int x = 0; x < indPoblacion.size(); x++)
                qDebug() << x << "[" << indPoblacion[x].get_planAdecuado() << "] Rango: " << indPoblacion[x].get_rango() << " Crow_dist: " << indPoblacion[x].get_iDistance() << " Precio: " << indPoblacion[x].get_objPrecio() << " Repeticion: " << indPoblacion[x].get_objGradoRepeticion();

            qDebug() << "";
            qDebug() << "";
            qDebug() << "";
        }*/
    }

    qDebug() << "--- POBLACION FINAL ---";
    for(int x = 0; x < indPoblacion.size(); x++)
        qDebug() << x << "[" << indPoblacion[x].get_planAdecuado() << "] Rango: " << indPoblacion[x].get_rango() << " Crow_dist: " << indPoblacion[x].get_iDistance() << " Precio: " << indPoblacion[x].get_objPrecio() << " Repeticion: " << indPoblacion[x].get_objGradoRepeticion();

    qDebug() << "";
    qDebug() << "";
    qDebug() << "";




    duration = ( std::clock() - start ) / (double) CLOCKS_PER_SEC;

    qDebug() << ""; qDebug() << "";
    qDebug() << "Tiempo de ejeucion: " << duration << " segundos";



    /*=================================*/

    planesRecomendados.clear();

    int p = 0;
    while(indPoblacion[p].get_rango() == 1 && indPoblacion[p].get_iDistance() > 0)
    {
        planesRecomendados.push_back(indPoblacion[p]);
        p++;
    }
    if(planesRecomendados.size() == 0)
    {
        for(int i = 0; i < 5; i++)
            planesRecomendados.push_back(indPoblacion[i]);
    }





    /*qDebug() << "--Menus del Plan--";
    for(int i = 0; i < numDiasPlan; i++)
        qDebug() << "PP: " << planesRecomendados[0].get_idPlatoPP(i) << "  SP: " << planesRecomendados[0].get_idPlatoSP(i) << "  P: " << planesRecomendados[0].get_idPlatoP(i);*/


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

    //qDebug() << "limitINF: " << limitInf << " limitSUP: " << limitSup << " Corte: " << corte;

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
        if(probabilidadMutacion < 5)
        {
            mutado = true;
            //qDebug() << "Mutado menu nº " << 1+i;

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
            //qDebug() << "Precio: " << indPoblacion[j].get_objPrecio() << " Repeticion: " << indPoblacion[j].get_objGradoRepeticion() << " iDistance: " << indPoblacion[j].get_iDistance();
            if(i == 0)
                aux = poblacionNonDom[j].get_iDistance() + ((poblacionNonDom[1+j].get_objPrecio() - poblacionNonDom[j-1].get_objPrecio()) / (max - min));
            else if(i == 1)
                aux = poblacionNonDom[j].get_iDistance() + ((poblacionNonDom[1+j].get_objGradoRepeticion() - poblacionNonDom[j-1].get_objGradoRepeticion()) / (max - min));

            /*if(i == 0)
                qDebug() << poblacionNonDom[j].get_iDistance() << " + " << "((" << poblacionNonDom[1+j].get_objPrecio() << " - " << poblacionNonDom[j-1].get_objPrecio() << ") / (" << max << " - " << min << ")) = " << aux;
            else if(i == 1)
                qDebug() << poblacionNonDom[j].get_iDistance() << " + " << "((" << poblacionNonDom[1+j].get_objGradoRepeticion() << " - " << poblacionNonDom[j-1].get_objGradoRepeticion() << ") / (" << max << " - " << min << ")) = " << aux;
            */

            poblacionNonDom[j].set_iDistance(aux);
            //qDebug() << "";
        }

        /*for(int j = 0; j < indPoblacion.size(); j++)
                qDebug() << "Precio: " << indPoblacion[j].get_objPrecio() << " Repeticion: " << indPoblacion[j].get_objGradoRepeticion() << " iDistance: " << indPoblacion[j].get_iDistance();

        qDebug() << "==============================";*/
    }

    for(int x = 0; x < poblacionNonDom.size(); x++)
        indPoblacion[poblacionNonDom[x].get_idIndividuo()].set_iDistance(poblacionNonDom[x].get_iDistance());

    /*for(int x = 0; x < indPoblacion.size(); x++)
        qDebug() << "Rango: " << indPoblacion[x].get_rango() << " iDistance: " << indPoblacion[x].get_iDistance();
    qDebug() << "================";*/

    /*for(int j = 0; j < poblacionNonDom.size(); j++)
        qDebug() << "Precio: " << poblacionNonDom[j].get_objPrecio() << " Repeticion: " << poblacionNonDom[j].get_objGradoRepeticion() << " iDistance: " << poblacionNonDom[j].get_iDistance();

    qDebug() << "-----------";*/
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


    /*for(int i = 0; i < indPorFrente.size(); i++)
    {
        qDebug() << "Frente " << 1+i;
        for(int j = 0; j < indPorFrente[i].size(); j++)
            qDebug() << 1+indPorFrente[i][j];
    }*/


    /*for(int j = 0; j < indPoblacion.size(); j++)
        qDebug() << "IND " << 1+j << " Precio: " << indPoblacion[j].get_objPrecio() << " Repeticion: " << indPoblacion[j].get_objGradoRepeticion() << " Rango: " << indPoblacion[j].get_rango() << "Domina a: " << indPoblacion[j].get_NumIndDominados() << " Es dominado por: " << indPoblacion[j].get_numDominantes();

    qDebug() << "===========";*/

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
                //qDebug() << "IN_" << j << " Minimo: " << irnMinMax[j].first << "Maximo: " << irnMinMax[j].second << " Recomendado: " << idrN[j];
                //qDebug() << valor;
                //num++;
                resultado = false;
                break;
            }
        }
        indPoblacion[i].set_planAdecuado(resultado);
        resultado = true;
        //qDebug() << "===========";
    }

    //qDebug() << "Planes dieteticos no recomendados: " << num << " de " << indPoblacion.size();
}



/*----------------------------------------------*/
/*--------------- MEETING POOL -----------------*/
/*----------------------------------------------*/
void MainWindowMenuPlan::set_meetingPool(const int numIndSelec)
{
    std::vector<individuo> pobRecom, pobNoRecom;            //pobRecom = vector de individuos que cumple los requisitos nutricionales, pobNoRecom = individuos que no los cumplen

    for(int i = 0; i < indPoblacion.size(); i++)            //Rellenar los vectores pobRecom y pobNoRecom
    {
        if(indPoblacion[i].get_planAdecuado())
            pobRecom.push_back(indPoblacion[i]);
        else
            pobNoRecom.push_back(indPoblacion[i]);
    }


    int N = static_cast<int>(pobRecom.size()-1);
    quickSortMP(pobRecom, 0, N);

    /*for(int x = 0; x < pobRecom.size(); x++)
        qDebug() << x << "[" << pobRecom[x].get_planAdecuado() << "] Rango: " << pobRecom[x].get_rango() << " Crow_dist: " << pobRecom[x].get_iDistance();

    qDebug() << "";
    qDebug() << "-- Poblacion NO recomendada --";*/

    N = static_cast<int>(pobNoRecom.size()-1);
    quickSortMP(pobNoRecom, 0, N);

    /*for(int x = 0; x < pobNoRecom.size(); x++)
        qDebug() << x << "[" << pobNoRecom[x].get_planAdecuado() << "] Rango: " << pobNoRecom[x].get_rango() << " Crow_dist: " << pobNoRecom[x].get_iDistance();*/


    int cont = 0;
    int tam = 0;
    meetingPool.clear();

    /*if(pobRecom.size() >= numIndSelec)
    {
        for(cont; cont < numIndSelec; cont++)
        {
            meetingPool.push_back(pobRecom[cont]);
            meetingPool[cont].set_idIndividuo(cont);
        }

    }
    else
    {
        for(int j = 0; j < pobRecom.size(); j++)
        {
            meetingPool.push_back(pobRecom[j]);
            meetingPool[j].set_idIndividuo(j);
            cont++;
        }
        for(int k = 0; k < pobNoRecom.size(); k++)
        {
            if(cont < numIndSelec)
            {
                meetingPool.push_back(pobNoRecom[k]);
                meetingPool[k].set_idIndividuo(k);
                cont++;
            }
            else
                break;
        }
    }*/

    for(int j = 0; j < pobRecom.size(); j++)
    {
        if(cont < numIndSelec)
        {
            if(pobRecom[j].get_iDistance() > (double)0.6)
            {
                meetingPool.push_back(pobRecom[j]);
                tam = static_cast<int>(meetingPool.size()-1);
                meetingPool[tam].set_idIndividuo(tam);
                cont++;
            }
        }
        else
        {
            break;
        }
    }
    for(int k = 0; k < pobNoRecom.size(); k++)
    {
        if(cont < numIndSelec)
        {
            if(pobNoRecom[k].get_iDistance() > (double)0.6)
            {
                meetingPool.push_back(pobNoRecom[k]);
                tam = static_cast<int>(meetingPool.size()-1);
                meetingPool[tam].set_idIndividuo(tam);
                cont++;
            }
        }
        else
        {
            break;
        }
    }


    /*qDebug() << "";
    qDebug() << "";
    qDebug() << "";
    qDebug() << "--- MEETING POOL ---";

    for(int x = 0; x < meetingPool.size(); x++)
        qDebug() << x << "[" << meetingPool[x].get_planAdecuado() << "] " << meetingPool[x].get_idIndividuo() << " Rango: " << meetingPool[x].get_rango() << " Crow_dist: " << meetingPool[x].get_iDistance();*/
}
