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
        float objPrecio;                                                //Precio total de todos los platos incluidos en el plan (menor = mejor)
        double objGradoRepeticion;                                      //Valor de repeticion de platos en el plan (menor = mejor)
        std::vector<float> infNutricional;                              //Vector que almacena la suma de valores nutricionales de todos los platos incluidos en el plan
        std::vector<int> alergenos;                                     //Vector que almacena los alergenos contenidos en el plan
        std::vector<int> incompatibilidades;                            //Vector que almacena las incompatibilidades alimenticias contenidas en el plan

    public:
        individuo(int numDiasPlan);
        ~individuo();

        void setMenuDiario(std::vector<struct infoPlatos> pp, std::vector<struct infoPlatos> sp, std::vector<struct infoPlatos> p);        //Genera un menu aleatorio para un dia
        menuDiario getMenuDiario(const unsigned int posPlan);                                                                                                                                       //Obtiene el menu del dia de la posicion especificada del plan dietetico


};













#endif // INDIVIDUO_H
