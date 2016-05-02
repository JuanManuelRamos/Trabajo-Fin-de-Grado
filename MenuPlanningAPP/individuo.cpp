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


void individuo::setMenuDiario(std::vector<struct infoPlatos> pp, std::vector<struct infoPlatos> sp, std::vector<struct infoPlatos> p)
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

        menu.idPrimerPlato = pp[ipp].id;
        menu.idSegundoPlato = sp[isp].id;
        menu.idPostre = p[ip].id;
        planDietetico.push_back(menu);

        objPrecio = objPrecio + pp[ipp].precio + sp[isp].precio + p[ip].precio;

        for(int j = 0; j < infNutricional.size(); j++)
            infNutricional[j] = infNutricional[j] + pp[ipp].infoN[j] + sp[isp].infoN[j] + p[ip].infoN[j];

        for(int k = 0; k < alergenos.size(); k++)
            if(alergenos[k] == "0" && (pp[ipp].alerg[k] == "1" || sp[isp].alerg[k] == "1" || p[ip].alerg[k] == "1"))
                alergenos[k] = "1";

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

}
