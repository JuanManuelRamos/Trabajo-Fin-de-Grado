#ifndef INDIVIDUO_H
#define INDIVIDUO_H

#include "mainwindowmenuplan.h"
#include "database.h"
#include "enums.h"


struct menuDiario                                               //Struct correspondiente a un menu
{
    std::pair<int,int> idPrimerPlato;                           //ID del plato (.first), posicion en el vector PrimerosPlatos (.second)
    std::pair<int,int> idSegundoPlato;                          //ID del plato (.first), posicion en el vector SegundosPlatos (.second)
    std::pair<int,int> idPostre;                                //ID del plato (.first), posicion en el vector Postres (.second)
};


class MainWindowMenuPlan;

class individuo
{
    private:

        menuDiario menu;

        std::vector<menuDiario> planDietetico;                          //Vector que almacena cada uno de los menus diarios
        unsigned int numMenus = 0;                                      //Numero de menus = numero de dias de los que esta compuesto el plan
        double objPrecio;                                               //Precio total de todos los platos incluidos en el plan (menor = mejor)
        double objGradoRepeticion;                                      //Valor de repeticion de platos en el plan (menor = mejor)
        std::vector<float> infNutricional;                              //Vector que almacena la suma de valores nutricionales de todos los platos incluidos en el plan
        std::vector<QString> alergenos;                                 //Vector que almacena los alergenos contenidos en el plan
        std::vector<QString> incompatibilidades;                        //Vector que almacena las incompatibilidades alimenticias contenidas en el plan

        double iDistance;
        std::vector<int> indvDominados;                                 //Vector de soluciones a las que el individuo actual domina. En la teoria denominada Sp
        int numDominantes;                                              //Numero de indivuos que dominan al individuo actual. En la teoria denominado np
        int rango;

        bool planAdecuado;                                              //Indica si un plan alimenticio cumple los requisitos nutricionales recomendados (true), o no (false)


        int imax = std::numeric_limits<int>::max();                     //Entero maximo (utilizado para calculos)

    public:
        individuo(int numDiasPlan, int numInfNutr, int numAlerg, int numIncomp);
        ~individuo();

        //Genera un menu aleatorio para un dia
        void setMenuDiario(std::vector<struct infoPlatos> pp, std::vector<struct infoPlatos> sp, std::vector<struct infoPlatos> p, std::vector<std::vector<int>> vectorFdeTabla, std::vector<std::pair<int,int>> vectorGruposAl, MENUINDIVIDUO MI);

        //Calcula el valor de objGradoRepeticion
        void setObjGradoRepeticion(std::vector<struct infoPlatos> pp, std::vector<struct infoPlatos> sp, std::vector<struct infoPlatos> p, std::vector<std::vector<int>> vectorFdeTabla, std::vector<std::pair<int,int>> vectorGruposAl);

        //menuDiario getMenuDiario(const unsigned int posPlan);                                                                                                                         //Obtiene el menu del dia de la posicion especificada del plan dietetico


        /* --- FUNCIONES PARA EL CALCULO DEL GRADO DE REPETICION DEL MENU --- */
            int getValorVectorFdeTabla(std::vector<std::vector<int>> vectorFdeTabla, int idPP, int idSP);           //Obtener el valor de la tabla de platos de compatibilidad entre primeros y segundos platos
            int setValorPP(std::vector<struct infoPlatos> &pp, int id);                                             //Calcula el valor de los Primeros Platos para la formula
            int setValorSP(std::vector<struct infoPlatos> &sp, int id);                                             //Calcula el valor de los Segunos Platos para la formula
            int setValorP(std::vector<struct infoPlatos> &p, int id);                                               //Calcula el valor de los Postres para la formula
            void setValorGA(std::vector<std::pair<int,int>> &vectorGruposAl, int ga);                               //Complementa las funciones getValorGA para el calculo de GAFirst y GASecond
            int getValorGAFirst(std::vector<std::pair<int,int>> &vectorGruposAl, std::vector<int> gaEleg);          //Obtener el valor total del numero de dias desde que se repitieron grupos alimenticios
            int getValorGASecond(std::vector<std::pair<int,int>> vectorGruposAl, std::vector<int> gaEleg);          //Obtener el valor total del numero de repeticiones de grupos alimenticios el mismo dia

            void sumValorPP(std::vector<struct infoPlatos> &pp);                                                    //Suma los valores de platos y grupos alimenticios elegidos para el siguiente dia
            void sumValorSP(std::vector<struct infoPlatos> &sp);                                                    //---
            void sumValorP(std::vector<struct infoPlatos> &p);                                                      //---
            void sumValorGA(std::vector<std::pair<int,int>> &vectorGruposAl);                                       //---

            bool gaElegidosPorIteracion(std::vector<int> vec, int valor);                                           //Comprueba los grupos alimenticios que se han elegido el mismo dia para ser añadidos a un vector
        /* ------------------------------------------------------------------ */



       std::vector<struct menuDiario> getPlanDietetico() { return planDietetico; }
       void setPlanDietetico(std::vector<struct menuDiario> nuevoPlan) { planDietetico.clear(); planDietetico = nuevoPlan; }

       double get_iDistance() { return iDistance; }
       void set_iDistance(double d) { iDistance = d; }

       double get_objPrecio() { return objPrecio; }
       double get_objGradoRepeticion() { return objGradoRepeticion; }

       //Funciones para la prueba del crowding distance y rango
       //void set_objPrecio(double x) { objPrecio = x; }
       //void set_objGradoRepeticion(double x) { objGradoRepeticion = x; }

       void set_numDominantes(int num) { numDominantes = num; }
       int get_numDominantes() { return numDominantes; }

       void set_indvDominados(int I) { indvDominados.push_back(I); }
       std::vector<int> get_indvDominados() { return indvDominados; }
       size_t get_NumIndDominados() { return indvDominados.size(); }
       int get_Ind_indDominados(int num) { return indvDominados[num]; }

       void set_rango(int num) { rango = num; }
       int get_rango() { return rango; }

       void set_planAdecuado(bool b) { planAdecuado = b; }
       bool get_planAdecuado() { return planAdecuado; }

       std::vector<float> get_infNutricional() { return infNutricional; }
       float get_valor_infNutricional(int pos) { return infNutricional[pos]; }
};













#endif // INDIVIDUO_H
