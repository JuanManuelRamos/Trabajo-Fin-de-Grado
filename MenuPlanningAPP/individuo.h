#ifndef INDIVIDUO_H
#define INDIVIDUO_H

#include "mainwindowmenuplan.h"
#include "database.h"

class MainWindowMenuPlan;


class individuo
{
    private:

        struct menuDiario                                               //Struct correspondiente a un menu
        {
            int idPrimerPlato;
            int idSegundoPlato;
            int idPostre;
        }menu;

        std::vector<menuDiario> planDietetico;                          //Vector que almacena cada uno de los menus diarios
        unsigned int numMenus = 0;                                      //Numero de menus = numero de dias de los que esta compuesto el plan



    public:
        individuo();
        ~individuo();

        void setMenuDiario(std::vector<std::tuple<int,int,std::vector<int>>> pp, std::vector<std::tuple<int,int,std::vector<int>>> sp, std::vector<std::tuple<int,int,std::vector<int>>> p);        //Genera un menu aleatorio para un dia
        menuDiario getMenuDiario(const unsigned int posPlan);                                                                                                                                       //Obtiene el menu del dia de la posicion especificada del plan dietetico

};













#endif // INDIVIDUO_H
