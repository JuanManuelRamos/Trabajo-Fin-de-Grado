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
    alergenos.assign(numAlerg, "0");
    incompatibilidades.assign(numIncomp, "0");
}


individuo::~individuo()
{

}


void individuo::setMenuDiario(std::vector<struct infoPlatos> pp, std::vector<struct infoPlatos> sp, std::vector<struct infoPlatos> p, std::vector<std::vector<int>> vectorFdeTabla, std::vector<std::pair<int,int>> vectorGruposAl)
{
    int ipp, isp, ip;
    for(unsigned int i = 0; i < numMenus; i++)
    {
        //*** IDEA FELIZ *** SI PONGO AQUI UN CONTROL PARA QUE EL RANDOM NO ACEPTE PLATOS CON DETERMINADOS ALERGENOS O INCOMPATIBILIDADES,
        //¿SOLUCIONARA ESO EL PROBLEMA DE LOS MENUS PARA PERSONAS CON DETERMINADAS ALERGIAS O INCOMPATIBILIDADES?
        //ESTE METODO CREA LOS INDIVIDUOS DE LA PRIMERA GENERACION, YA QUE SE CREAN DE FORMA ALEATORIA, SI DESDE EL COMIENZO NO SE ELIGEN PLATOS CON DETERMINADAS
        //CARACTERISTICAS, NO DEBERIAN APARECER EN POSTERIORES GENERACIONES

        ipp = rand() % pp.size();
        isp = rand() % sp.size();
        ip = rand() % p.size();

        //ID'S
        menu.idPrimerPlato.first = pp[ipp].id;
        menu.idSegundoPlato.first = sp[isp].id;
        menu.idPostre.first = p[ip].id;
        menu.idPrimerPlato.second = ipp;
        menu.idSegundoPlato.second = isp;
        menu.idPostre.second = ip;
        planDietetico.push_back(menu);

        //PRECIO
        objPrecio = objPrecio + pp[ipp].precio + sp[isp].precio + p[ip].precio;

        //INFORMACION NUTRICIONAL
        for(int j = 0; j < infNutricional.size(); j++)
            infNutricional[j] = infNutricional[j] + pp[ipp].infoN[j] + sp[isp].infoN[j] + p[ip].infoN[j];

        //ALERGENOS
        for(int k = 0; k < alergenos.size(); k++)
            if(alergenos[k] == "0" && (pp[ipp].alerg[k] == "1" || sp[isp].alerg[k] == "1" || p[ip].alerg[k] == "1"))
                alergenos[k] = "1";

        //INCOMPATIBILIDADES ALIMENTICIAS
        for(int l = 0; l < incompatibilidades.size(); l++)
            if(incompatibilidades[l] == "0" && (pp[ipp].incomp[l] == "1" || sp[isp].incomp[l] == "1" || p[ip].incomp[l] == "1"))
                incompatibilidades[l] = "1";
    }

    //qDebug() << "hola_1";
    setObjGradoRepeticion(pp, sp, p, vectorFdeTabla, vectorGruposAl);
    //qDebug() << "hola_2";


    qDebug() << "--Menus del Plan--";
    for(unsigned int i = 0; i < numMenus; i++)
        qDebug() << "PP: " << planDietetico[i].idPrimerPlato.first << "  SP: " << planDietetico[i].idSegundoPlato.first << "  P: " << planDietetico[i].idPostre.first;

    qDebug() << "--Precio total del plan--";
    qDebug() << objPrecio;

    qDebug() << "--Grado de Repeticion del plan--";
    qDebug() << objGradoRepeticion;

    qDebug() << "--Informacion nutricional--";
    for(unsigned int i = 0; i < infNutricional.size(); i++)
        qDebug() << infNutricional[i];

    qDebug() << "--Alergenos--";
    for(unsigned int i = 0; i < alergenos.size(); i++)
        qDebug() << alergenos[i];

    qDebug() << "--Incompatibilidades--";
    for(unsigned int i = 0; i < incompatibilidades.size(); i++)
        qDebug() << incompatibilidades[i];

}



void individuo::setObjGradoRepeticion(std::vector<struct infoPlatos> pp, std::vector<struct infoPlatos> sp, std::vector<struct infoPlatos> p, std::vector<std::vector<int>> vectorFdeTabla, std::vector<std::pair<int,int>> vectorGruposAl)
{
    double valPP, valSP, valP, valTabla, valGAFirst, valGASecond;
    double uno = 1;
    double  valTotal = 0;
    std::vector<int> gaElegidos;

    for(unsigned int i = 0; i < numMenus; i++)
    {
        //PRIMER PLATO
        valPP = setValorPP(pp, planDietetico[i].idPrimerPlato.second);
        for(int j = 0; j < pp[planDietetico[i].idPrimerPlato.second].gruposAl.size(); j++)
        {
            setValorGA(vectorGruposAl, pp[planDietetico[i].idPrimerPlato.second].gruposAl[j]);
            if(gaElegidosPorIteracion(gaElegidos, pp[planDietetico[i].idPrimerPlato.second].gruposAl[j]))
                gaElegidos.push_back(pp[planDietetico[i].idPrimerPlato.second].gruposAl[j]);
        }


        qDebug() << "pp: " << valPP;
        for(int x = 0; x < pp.size(); x++)
            qDebug() << pp[x].id << " - " << pp[x].nDias;
        qDebug() << "-----";

        //SEGUNDO PLATO
        valSP = setValorSP(sp, planDietetico[i].idSegundoPlato.second);
        for(int k = 0; k < sp[planDietetico[i].idSegundoPlato.second].gruposAl.size(); k++)
        {
            setValorGA(vectorGruposAl, sp[planDietetico[i].idSegundoPlato.second].gruposAl[k]);
            if(gaElegidosPorIteracion(gaElegidos, sp[planDietetico[i].idSegundoPlato.second].gruposAl[k]))
                gaElegidos.push_back(sp[planDietetico[i].idSegundoPlato.second].gruposAl[k]);
        }

        qDebug() << "sp: " << valSP;
        for(int x = 0; x < sp.size(); x++)
            qDebug() << sp[x].id << " - " << sp[x].nDias;
        qDebug() << "-----";

        //POSTRE
        valP = setValorP(p, planDietetico[i].idPostre.second);
        for(int l = 0; l < p[planDietetico[i].idPostre.second].gruposAl.size(); l++)
        {
            setValorGA(vectorGruposAl, p[planDietetico[i].idPostre.second].gruposAl[l]);
            if(gaElegidosPorIteracion(gaElegidos, p[planDietetico[i].idPostre.second].gruposAl[l]))
                gaElegidos.push_back(p[planDietetico[i].idPostre.second].gruposAl[l]);
        }

        qDebug() << "p: " << valP;
        for(int x = 0; x < p.size(); x++)
            qDebug() << p[x].id << " - " << p[x].nDias;
        qDebug() << "-----";

        for(int x = 0; x < vectorGruposAl.size(); x++)
            qDebug() << x << " - " << vectorGruposAl[x].first << " --> " << vectorGruposAl[x].second;
        qDebug() << "-----";




        qDebug() << "pp: " << valPP;
        qDebug() << "sp: " << valSP;
        qDebug() << "p: " << valP;
        valTabla = getValorVectorFdeTabla(vectorFdeTabla, planDietetico[i].idPrimerPlato.first-1, planDietetico[i].idSegundoPlato.first-1);
        qDebug() << "tabla: " << valTabla;
        valGAFirst = getValorGAFirst(vectorGruposAl, gaElegidos);
        qDebug() << "valorGAFirst: " << valGAFirst;
        valGASecond = getValorGASecond(vectorGruposAl, gaElegidos);
        qDebug() << "valorGASecond: " << valGASecond;

        valTotal += uno/(valTabla + valPP + valSP + valP) + uno/valGAFirst + valGASecond;
        qDebug() << "valorTotal: " << valTotal;

        qDebug() << "=========" << i;

        sumValorPP(pp);
        sumValorSP(sp);
        sumValorP(p);
        sumValorGA(vectorGruposAl);

        gaElegidos.clear();
    }

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
    int valor = 0;                          //Tengo que retornar el numero de dias desde que se eligio el plato por ultima vez
    if(pp[id].nDias != imax)                //Si el numero de dias es imax, significa que nunca se ha elegido, por lo que retorno 0
        valor = pp[id].nDias;               //Si el numero de dias es distinto a imax, retorno el valor y reseteo el numero de dias a 0
    pp[id].nDias = 0;

    return valor;
}

int individuo::setValorSP(std::vector<struct infoPlatos> &sp, int id)
{
    int valor = 0;
    if(sp[id].nDias != imax)
        valor = sp[id].nDias;
    sp[id].nDias = 0;

    return valor;
}

int individuo::setValorP(std::vector<struct infoPlatos> &p, int id)
{
    int valor = 0;
    if(p[id].nDias != imax)
        valor = p[id].nDias;
    p[id].nDias = 0;

    return valor;
}

void individuo::setValorGA(std::vector<std::pair<int,int>> &vectorGruposAl, int ga)
{
    if(vectorGruposAl[ga].first == imax)          //Si el grupo alimenticio es igual a imax, es que no se ha repetido nunca, por lo que se pone a 0
        vectorGruposAl[ga].first = 0;
    if(vectorGruposAl[ga].second == imax)
        vectorGruposAl[ga].second = 0;
    else
        vectorGruposAl[ga].second++;
}


int individuo::getValorGAFirst(std::vector<std::pair<int,int>> vectorGruposAl, std::vector<int> gaEleg)
{
    qDebug() << "-- GA Elegidos--";
   for(int i = 0; i < gaEleg.size(); i++)
       qDebug() << gaEleg[i];
   qDebug() << "------";

   int valor = 0;
   for(int i = 0; i < vectorGruposAl.size(); i++)
       if(vectorGruposAl[i].first != imax && !gaElegidosPorIteracion(gaEleg, i))
           valor += vectorGruposAl[i].first;
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


/*
El tema con los grupos alimenticios es que, a diferencia de los platos, un grupo alimenticio puede repetirse el mismo dia. Los tres platos del dia nunca se van a repetir el mismo dia
porque son de diferente tipo, pero los grupos alimenticios son comunes a los tres tipos de platos. Por lo que se debe hacer una separacion entre numero de dias desde que se repitio
un grupo alimenticio y si un grupo alimenticio determinado se repite el mismo dia

Si el grupo alimenticio X se repite 2 o mas veces el mismo dia, debe ser penalizable de forma aparte a si se repite dias despues. Por tanto, se podria volver a hacer el vector
grupoAL como vector de pares, en el que el primer elemento hace referencia al numero de dias desde que se repitio por ultima vez, y el segundo elemento el numero de veces que se
ha repetido ese dia. Al final de cada iteracion, este segundo elemento se resetea a 0 para todos los grupos alimenticios, y el primer elemento (el contador de dias), se utiliza de la misma
forma que para los tipos de platos. Como el numero de repeticiones de grupo alimenticio es algo muy evitable, y cuanto mayor peor, se puede incluir en la ecuacion como la suma de este
valor, en el numerador.

*/

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
