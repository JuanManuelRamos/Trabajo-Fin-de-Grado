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


void individuo::setMenuDiario(std::vector<struct infoPlatos> pp, std::vector<struct infoPlatos> sp, std::vector<struct infoPlatos> p, std::vector<std::vector<int>> vectorFdeTabla, std::vector<int> vectorGruposAl)
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
    /*
    qDebug() << "--Menus del Plan--";
    for(unsigned int i = 0; i < numMenus; i++)   
        qDebug() << "PP: " << planDietetico[i].idPrimerPlato << "  SP: " << planDietetico[i].idSegundoPlato << "  P: " << planDietetico[i].idPostre;

    qDebug() << "--Precio total del plan--";
    qDebug() << objPrecio;

    qDebug() << "--Informacion nutricional--";
    for(unsigned int i = 0; i < infNutricional.size(); i++)
        qDebug() << infNutricional[i];

    qDebug() << "--Alergenos--";
    for(unsigned int i = 0; i < alergenos.size(); i++)
        qDebug() << alergenos[i];

    qDebug() << "--Incompatibilidades--";
    for(unsigned int i = 0; i < incompatibilidades.size(); i++)
        qDebug() << incompatibilidades[i];*/

    setObjGradoRepeticion(pp, sp, p, vectorFdeTabla, vectorGruposAl);

}



void individuo::setObjGradoRepeticion(std::vector<struct infoPlatos> pp, std::vector<struct infoPlatos> sp, std::vector<struct infoPlatos> p, std::vector<std::vector<int>> vectorFdeTabla, std::vector<int> vectorGruposAl)
{
    int valPP, valGAPP;
    int valSP, valGASP;

    for(unsigned int i = 0; i < numMenus; i++)
    {
        //PRIMER PLATO
        valPP = setValorPP(pp, planDietetico[i].idPrimerPlato.second);
        for(int j = 0; j < pp[planDietetico[i].idPrimerPlato.second].gruposAl.size(); j++)
            setValorGA(vectorGruposAl, pp[planDietetico[i].idPrimerPlato.second].gruposAl[j]);

        //SEGUNDO PLATO

    }
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

void individuo::setValorGA(std::vector<int> &vectorGruposAl, int ga)
{
    if(vectorGruposAl[ga] == imax)          //Si el grupo alimenticio es igual a imax, es que no se ha repetido nunca, por lo que se pone a 0
        vectorGruposAl[ga] = 0;
}

/*
El tema con los grupos alimenticios es que, a diferencia de los platos, un grupo alimenticio puede repetirse el mismo dia. Los tres platos del dia nunca se van a repetir
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

void individuo::sumValorGA(std::vector<int> &vectorGruposAl)
{
    for(int i = 0; i < vectorGruposAl.size(); i++)
        if(vectorGruposAl[i] != imax)
            vectorGruposAl[i]++;
}
