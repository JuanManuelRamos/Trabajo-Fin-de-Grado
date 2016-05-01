#include "mainwindowmenuplan.h"
#include "ui_mainwindowmenuplan.h"
#include "database.h"
#include "individuo.h"

individuo::individuo(int numDiasPlan)
{
    numMenus = numDiasPlan;
}


individuo::~individuo()
{

}


void individuo::setMenuDiario(std::vector<struct infoPlatos> pp, std::vector<struct infoPlatos> sp, std::vector<struct infoPlatos> p)
{
    for(unsigned int i = 0; i < numMenus; i++)
    {      
        menu.idPrimerPlato = pp[rand() % pp.size()].id;
        menu.idSegundoPlato = sp[rand() % sp.size()].id;
        menu.idPostre = p[rand() % p.size()].id;

        planDietetico.push_back(menu);
    }

    for(unsigned int i = 0; i < numMenus; i++)
    {
        qDebug() << "PP: " << planDietetico[i].idPrimerPlato << "  SP: " << planDietetico[i].idSegundoPlato << "  P: " << planDietetico[i].idPostre;
    }
}
