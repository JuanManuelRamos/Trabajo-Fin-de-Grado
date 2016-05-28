#include "mainwindowmenuplan.h"
#include "ui_mainwindowmenuplan.h"



void MainWindowMenuPlan::comprobarAlerIncomp(std::vector<int> &aler, std::vector<int> &incomp)
{
    aler.assign(NumAlergenos, 0);

    if(ui->checkBox_cereales_2->isChecked())
        aler[0] = 1;
    if(ui->checkBox_frutos_secos_2->isChecked())
        aler[1] = 1;
    if(ui->checkBox_legumbres_2->isChecked())
        aler[2] = 1;
    if(ui->checkBox_marisco_2->isChecked())
        aler[3] = 1;
    if(ui->checkBox_pescado_2->isChecked())
        aler[4] = 1;
    if(ui->checkBox_huevo_2->isChecked())
        aler[5] = 1;
    if(ui->checkBox_leche_2->isChecked())
        aler[6] = 1;

    incomp.assign(NumIncomp, 0);

    if(ui->checkBox_celiaco_2->isChecked())
        incomp[0] = 1;
    if(ui->checkBox_diabetico_2->isChecked())
        incomp[1] = 1;
    if(ui->checkBox_semivegetariano_2->isChecked())
        incomp[2] = 1;
    if(ui->checkBox_vegetariano_2->isChecked())
        incomp[3] = 1;
    if(ui->checkBox_vegano_2->isChecked())
        incomp[4] = 1;
}

bool MainWindowMenuPlan::comprobarPlanActual(std::vector<int> aler, std::vector<int> incomp, individuo ind)
{
    for(int i = 0; i < NumAlergenos; i++)
        if(aler[i] == 1 && ind.get_alergeno(i) == 1)
            return false;
    for(int j = 0; j < NumIncomp; j++)
        if(incomp[j] == 1 && ind.get_incompatibilidad(j) == 1)
            return false;

    return true;
}


void MainWindowMenuPlan::set_PlatosEspeciales(std::vector<int> &ppE, std::vector<int> &spE, std::vector<int> &pE)
{
    for(int i = 0; i < PrimerosPlatos.size(); i++)
    {

    }

}


void MainWindowMenuPlan::set_PlanEspecial()
{
    std::vector<int> alerEvitar, incompEvitar, ppE, spE, pE;
    comprobarAlerIncomp(alerEvitar, incompEvitar);
    set_PlatosEspeciales(ppE, spE, pE);

    for(int i = 0; i < planesRecomendados.size(); i++)
    {
        if(comprobarPlanActual(alerEvitar, incompEvitar, planesRecomendados[i]))
            planesEspeciales.push_back(planesRecomendados[i]);
        else



    }
}
