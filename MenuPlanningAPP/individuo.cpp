#include "mainwindowmenuplan.h"
#include "ui_mainwindowmenuplan.h"
#include "database.h"
#include "individuo.h"

individuo::individuo(int numDiasPlan, int numInfNutr, int numAlerg, int numIncomp)
{
    numMenus = numDiasPlan;
    objPrecio = 0;
    objGradoRepeticion = 0;
    infNutricional.assign(numInfNutr, 0);
    alergenos.assign(numAlerg, 0);
    incompatibilidades.assign(numIncomp, 0);

    iDistance = 0;
    rango = 0;
    planAdecuado = false;
    evaluado = false;
}


individuo::~individuo()
{

}


void individuo::setMenuDiario(std::vector<struct infoPlatos> pp, std::vector<struct infoPlatos> sp, std::vector<struct infoPlatos> p, std::vector<std::vector<std::vector<double>>> vectorFdeTabla, std::vector<std::pair<int,int>> vectorGruposAl, MENUINDIVIDUO MI, std::vector<std::vector<int>> &ultimos5GA)
{
    int ipp, isp, ip;
    for(unsigned int i = 0; i < numMenus; i++)
    {
        //La funcion setMenuDiario sirve tanto para crear un individuo de forma aleatoria en la primera generacion como para actualizar los datos de un nuevo individuo
        //Por ello se debe controlar si el individuo se quiere generar de forma aleatoria o por el contrario ya existe y solo se desea actualizar sus datos

        if(MI == GENERAR)
        {
            //ID'S - Elegir aleatoriamente los platos
            ipp = rand() % pp.size();
            isp = rand() % sp.size();
            ip = rand() % p.size();

            menu.idPrimerPlato.first = pp[ipp].id;
            menu.idSegundoPlato.first = sp[isp].id;
            menu.idPostre.first = p[ip].id;
            menu.idPrimerPlato.second = ipp;
            menu.idSegundoPlato.second = isp;
            menu.idPostre.second = ip;
            planDietetico.push_back(menu);
        }
        else
        {
            ipp = planDietetico[i].idPrimerPlato.second;
            isp = planDietetico[i].idSegundoPlato.second;
            ip = planDietetico[i].idPostre.second;
        }


        //PRECIO
        objPrecio = objPrecio + (double)pp[ipp].precio + (double)sp[isp].precio + (double)p[ip].precio;

        //INFORMACION NUTRICIONAL
        for(int j = 0; j < infNutricional.size(); j++)
            infNutricional[j] = infNutricional[j] + pp[ipp].infoN[j] + sp[isp].infoN[j] + p[ip].infoN[j];

        //ALERGENOS
        for(int k = 0; k < alergenos.size(); k++)
            if(alergenos[k] == 0 && (pp[ipp].alerg[k] == "1" || sp[isp].alerg[k] == "1" || p[ip].alerg[k] == "1"))
                alergenos[k] = 1;

        //INCOMPATIBILIDADES ALIMENTICIAS
        for(int l = 0; l < incompatibilidades.size(); l++)
            if(incompatibilidades[l] == 0 && (pp[ipp].incomp[l] == "1" || sp[isp].incomp[l] == "1" || p[ip].incomp[l] == "1"))
                incompatibilidades[l] = 1;
    }

    //VALOR DE REPETICION O VARIABILIDAD DE PLATOS
    setObjGradoRepeticion(pp, sp, p, vectorFdeTabla, vectorGruposAl, ultimos5GA);
}



void individuo::setObjGradoRepeticion(std::vector<struct infoPlatos> pp, std::vector<struct infoPlatos> sp, std::vector<struct infoPlatos> p, std::vector<std::vector<std::vector<double>>> vectorFdeTabla, std::vector<std::pair<int,int>> vectorGruposAl, std::vector<std::vector<int>> &ultimos5GA)
{
    double valPP, valSP, valP, valTabla, valGAFirst, valGASecond;
    double numPP = 8;
    double numSP = 10;
    double numP = 2;
    double  valTotal = 0;
    std::vector<int> gaElegidos;                                                                                //Vector que guarda los grupos alimenticios pertenecientes a los platos elegidos
    std::vector<int> gaElegidosAnterior;                                                                        //Vector que guarda los ga pertenecientes al menu de la iteracion anterior


    for(unsigned int i = 0; i < numMenus; i++)
    {
        //PRIMER PLATO
        valPP = setValorPP(pp, planDietetico[i].idPrimerPlato.second);                                          //Numero de dias desde que se repitio el plato seleccionado
        for(int j = 0; j < pp[planDietetico[i].idPrimerPlato.second].gruposAl.size(); j++)                      //Numero de dias desde que se repitio el grupo alimenticio
        {
            //en este for se va desde 0 hasta el numero total de grupos alimenticios que tiene este primer plato i
            //comprueba si ya habia aparecido en el menu el grupo alimenticio j, si no lo añade al vector gaElegidos
            if(gaElegidosPorIteracion(gaElegidos, pp[planDietetico[i].idPrimerPlato.second].gruposAl[j]))
                gaElegidos.push_back(pp[planDietetico[i].idPrimerPlato.second].gruposAl[j]);
        }

        //SEGUNDO PLATO
        valSP = setValorSP(sp, planDietetico[i].idSegundoPlato.second);
        for(int k = 0; k < sp[planDietetico[i].idSegundoPlato.second].gruposAl.size(); k++)
        {
            if(gaElegidosPorIteracion(gaElegidos, sp[planDietetico[i].idSegundoPlato.second].gruposAl[k]))
                gaElegidos.push_back(sp[planDietetico[i].idSegundoPlato.second].gruposAl[k]);
        }

        //POSTRE
        valP = setValorP(p, planDietetico[i].idPostre.second);
        for(int l = 0; l < p[planDietetico[i].idPostre.second].gruposAl.size(); l++)
        {
            if(gaElegidosPorIteracion(gaElegidos, p[planDietetico[i].idPostre.second].gruposAl[l]))
                gaElegidos.push_back(p[planDietetico[i].idPostre.second].gruposAl[l]);
        }



		valTabla = vectorFdeTabla[planDietetico[i].idPrimerPlato.second][planDietetico[i].idSegundoPlato.second][planDietetico[i].idPostre.second];
		valGAFirst = set_ValorGAFirstAlternativa(ultimos5GA, gaElegidos);
		valTotal += valTabla + numPP/valPP + numSP/valSP + numP/valP + valGAFirst;

        sumValorPP(pp);                                                                                                                             //Suma los valores de platos y grupos alimenticios elegidos para el siguiente dia
        sumValorSP(sp);
        sumValorP(p);
        sumValorGA(vectorGruposAl);

		set_ultimos5GA(ultimos5GA, gaElegidos);
        gaElegidosAnterior = gaElegidos;
        gaElegidos.clear();
    }

    ultimos5GA.clear();
    gaElegidosAnterior.clear();
    objGradoRepeticion = valTotal;
}



bool individuo::gaElegidosPorIteracion(std::vector<int> vec, int valor)
{
    bool resultado = true;
    for(int i = 0; i < vec.size(); i++)
        if(vec[i] == valor)
            resultado = false;
    return resultado;
}


int individuo::getValorVectorFdeTabla(std::vector<std::vector<int>> vectorFdeTabla, int idPP, int idSP)
{
    if(idPP > idSP)
        return vectorFdeTabla[idPP][idSP];
    else
        return vectorFdeTabla[idSP][idPP];
}


int individuo::setValorPP(std::vector<struct infoPlatos> &pp, int id)
{
    int valor = imax;                          //Tengo que retornar el numero de dias desde que se eligio el plato por ultima vez
    if(pp[id].nDias != imax)                //Si el numero de dias es imax, significa que nunca se ha elegido, por lo que retorno 0
        valor = pp[id].nDias;               //Si el numero de dias es distinto a imax, retorno el valor y reseteo el numero de dias a 0
    pp[id].nDias = 0;

    return valor;
}

int individuo::setValorSP(std::vector<struct infoPlatos> &sp, int id)
{
    int valor = imax;
    if(sp[id].nDias != imax)
        valor = sp[id].nDias;
    sp[id].nDias = 0;

    return valor;
}

int individuo::setValorP(std::vector<struct infoPlatos> &p, int id)
{
    int valor = imax;
    if(p[id].nDias != imax)
        valor = p[id].nDias;
    p[id].nDias = 0;

    return valor;
}

void individuo::setValorGA(std::vector<std::pair<int,int>> &vectorGruposAl, int ga)
{
    //first es el numero de dias desde que se repitio por ultima vez y second el numero de veces que se repite un mismo dia
    //por ahora este metodo solo inicializa el grupo alimenticio que no se haya repetido nunca, en first, y en second si que suma el numero de veces que se repite al dia

    if(vectorGruposAl[ga].first == imax)          //Si el grupo alimenticio es igual a imax, es que no se ha repetido nunca, por lo que se pone a 0
        vectorGruposAl[ga].first = 0;
    if(vectorGruposAl[ga].second == imax)
        vectorGruposAl[ga].second = 0;
    else
        vectorGruposAl[ga].second++;
}


int individuo::getValorGAFirst(std::vector<std::pair<int,int>> &vectorGruposAl, std::vector<int> gaEleg)
{
   int valor = 0;
   for(int i = 0; i < vectorGruposAl.size(); i++)
       if(vectorGruposAl[i].first != imax && !gaElegidosPorIteracion(gaEleg, i))
       {
           valor += vectorGruposAl[i].first;
           vectorGruposAl[i].first = 0;
       }
   if(valor == 0)
       valor = imax;                                        //Si el valor es = 0 devuelve imax porque si no dara error al dividir por 0

   return valor;
}

int individuo::getValorGASecond(std::vector<std::pair<int,int>> vectorGruposAl, std::vector<int> gaEleg)
{
    int valor = 0;
    for(int i = 0; i < vectorGruposAl.size(); i++)
        if(vectorGruposAl[i].second != imax && !gaElegidosPorIteracion(gaEleg, i))
            valor += vectorGruposAl[i].second;

    return valor;
}

void individuo::sumValorPP(std::vector<struct infoPlatos> &pp)
{
    for(int i = 0; i < pp.size(); i++)
        if(pp[i].nDias != imax)
            pp[i].nDias++;
}

void individuo::sumValorSP(std::vector<struct infoPlatos> &sp)
{
    for(int i = 0; i < sp.size(); i++)
        if(sp[i].nDias != imax)
            sp[i].nDias++;
}

void individuo::sumValorP(std::vector<struct infoPlatos> &p)
{
    for(int i = 0; i < p.size(); i++)
        if(p[i].nDias != imax)
            p[i].nDias++;
}

void individuo::sumValorGA(std::vector<std::pair<int,int>> &vectorGruposAl)
{
    for(int i = 0; i < vectorGruposAl.size(); i++)
    {
        if(vectorGruposAl[i].first != imax)
            vectorGruposAl[i].first++;
        vectorGruposAl[i].second = imax;
    }
}


int individuo::getValorGAFirstCorreccion(std::vector<std::pair<int, int> > &vectorGruposAl, std::vector<int> &gaElegidosAnterior)
{
    int min = imax;


    for(int i = 0; i < vectorGruposAl.size(); i++)
    {
        if(gaElegidosAnterior.size() > 0)
            for(int u = 0; u < gaElegidosAnterior.size(); u++)
                if(vectorGruposAl[gaElegidosAnterior[u]].first == 0)
                    min = 1;
        if(vectorGruposAl[i].first < min && vectorGruposAl[i].first != 0)
            min = vectorGruposAl[i].first;
    }

    return min;
}


void individuo::set_ultimos5GA(std::vector<std::vector<int>> &ultimos5GA, std::vector<int> vec)
{
    if(ultimos5GA.size() < 5)
        ultimos5GA.push_back(vec);
    else
    {
        ultimos5GA.erase(ultimos5GA.begin());
        ultimos5GA.push_back(vec);
    }
}


double individuo::set_ValorGAFirstAlternativa(std::vector<std::vector<int>> &ultimos5GA, std::vector<int> vec)
{
    /* 0 Otros, 1 Carne, 2 Cereal, 3 Fruta, 4 Lacteo, 5 Legumbre, 6 Marisco, 7 Pasta, 8 Pescado, 9 Verdura */
    double penalizacionPorGA[10] = {0.1,3,0.3,0.1,0.3,0.3,2,1.5,0.5,0.1};
    double penalizacionPorDi­as[5] = {3,2.5,1.8,1,0.2};
    bool pen[5] = {false, false, false, false, false};
    double resultado = 0;


    if(ultimos5GA.size() > 0)
    {
        for(int i = 0; i < vec.size(); i++)
        {
            for(int j = 0; j < ultimos5GA.size(); j++)
                for(int k = 0; k < ultimos5GA[j].size(); k++)
                {
                    if(vec[i] == ultimos5GA[j][k])
                    {
                        pen[j] = true;
                        resultado += penalizacionPorGA[vec[i]];
                    }
                }
        }
        for(int x = 0; x < 5; x++)
            if(pen[x])
            {
                resultado += penalizacionPorDi­as[x];
                pen[x] = false;
            }
    }

    return resultado;
}
