#include "mainwindowmenuplan.h"
#include "ui_mainwindowmenuplan.h"
#include "database.h"
#include "individuo.h"

individuo::individuo()
{
    //PENDIENTE DE ACTUALIZAR
    numMenus = 20;
    qDebug() << "constructor";
}


individuo::~individuo()
{

}


void individuo::setMenuDiario(std::vector<std::tuple<int,int,std::vector<int>>> pp, std::vector<std::tuple<int,int,std::vector<int>>> sp, std::vector<std::tuple<int,int,std::vector<int>>> p)
{
    qDebug() << "set menu";
    std::tuple<int,int,std::vector<int>> tpl;

    for(unsigned int i = 0; i < numMenus; i++)
    {
        tpl = pp[rand() % pp.size()];
        menu.idPrimerPlato = std::get<0>(tpl);
        tpl = sp[rand() % sp.size()];
        menu.idSegundoPlato = std::get<0>(tpl);
        tpl = p[rand() % p.size()];
        menu.idPostre = std::get<0>(tpl);

        planDietetico.push_back(menu);
    }

    for(unsigned int i = 0; i < numMenus; i++)
    {
        qDebug() << "PP: " << planDietetico[i].idPrimerPlato << "  SP: " << planDietetico[i].idSegundoPlato << "  P: " << planDietetico[i].idPostre;
    }
}
