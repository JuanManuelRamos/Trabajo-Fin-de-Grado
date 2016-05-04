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
            std::pair<int,int> idPrimerPlato;                           //ID del plato (.first), posicion en el vector PrimerosPlatos (.second)
            std::pair<int,int> idSegundoPlato;
            std::pair<int,int> idPostre;
        }menu;

        std::vector<menuDiario> planDietetico;                          //Vector que almacena cada uno de los menus diarios
        unsigned int numMenus = 0;                                      //Numero de menus = numero de dias de los que esta compuesto el plan
        float objPrecio;                                                //Precio total de todos los platos incluidos en el plan (menor = mejor)
        double objGradoRepeticion;                                      //Valor de repeticion de platos en el plan (menor = mejor)
        std::vector<float> infNutricional;                              //Vector que almacena la suma de valores nutricionales de todos los platos incluidos en el plan
        std::vector<QString> alergenos;                                 //Vector que almacena los alergenos contenidos en el plan
        std::vector<QString> incompatibilidades;                        //Vector que almacena las incompatibilidades alimenticias contenidas en el plan

        const int imax = std::numeric_limits<int>::max();

    public:
        individuo(int numDiasPlan, int numInfNutr, int numAlerg, int numIncomp);
        ~individuo();

        void setMenuDiario(std::vector<struct infoPlatos> pp, std::vector<struct infoPlatos> sp, std::vector<struct infoPlatos> p, std::vector<std::vector<int>> vectorFdeTabla, std::vector<std::pair<int,int>> vectorGruposAl);       //Genera un menu aleatorio para un dia
        void setObjGradoRepeticion(std::vector<struct infoPlatos> pp, std::vector<struct infoPlatos> sp, std::vector<struct infoPlatos> p, std::vector<std::vector<int>> vectorFdeTabla, std::vector<std::pair<int,int>> vectorGruposAl);
        //menuDiario getMenuDiario(const unsigned int posPlan);                                                                                                                         //Obtiene el menu del dia de la posicion especificada del plan dietetico

        int getValorVectorFdeTabla(std::vector<std::vector<int>> vectorFdeTabla, int idPP, int idSP);
        int setValorPP(std::vector<struct infoPlatos> &pp, int id);
        int setValorSP(std::vector<struct infoPlatos> &sp, int id);
        int setValorP(std::vector<struct infoPlatos> &p, int id);
        void setValorGA(std::vector<std::pair<int,int>> &vectorGruposAl, int ga);
        int getValorGAFirst(std::vector<std::pair<int,int>> &vectorGruposAl, std::vector<int> gaEleg);
        int getValorGASecond(std::vector<std::pair<int,int>> vectorGruposAl, std::vector<int> gaEleg);

        void sumValorPP(std::vector<struct infoPlatos> &pp);
        void sumValorSP(std::vector<struct infoPlatos> &sp);
        void sumValorP(std::vector<struct infoPlatos> &p);
        void sumValorGA(std::vector<std::pair<int,int>> &vectorGruposAl);

        bool gaElegidosPorIteracion(std::vector<int> vec, int valor);
};













#endif // INDIVIDUO_H
