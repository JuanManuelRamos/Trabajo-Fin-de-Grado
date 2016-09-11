#include "mainwindowmenuplan.h"
#include "ui_mainwindowmenuplan.h"



bool MainWindowMenuPlan::comprobarAlerIncomp()
{
    bool x = false;

    alerEvitar.clear();
    alerEvitar.assign(NumAlergenos, 0);

    if(ui->checkBox_cereales_2->isChecked())
        alerEvitar[0] = 1;
    if(ui->checkBox_frutos_secos_2->isChecked())
        alerEvitar[1] = 1;
    if(ui->checkBox_legumbres_2->isChecked())
        alerEvitar[2] = 1;
    if(ui->checkBox_marisco_2->isChecked())
        alerEvitar[3] = 1;
    if(ui->checkBox_pescado_2->isChecked())
        alerEvitar[4] = 1;
    if(ui->checkBox_huevo_2->isChecked())
        alerEvitar[5] = 1;
    if(ui->checkBox_leche_2->isChecked())
        alerEvitar[6] = 1;

    incompEvitar.clear();
    incompEvitar.assign(NumIncomp, 0);

    if(ui->checkBox_celiaco_2->isChecked())
        incompEvitar[0] = 1;
    if(ui->checkBox_diabetico_2->isChecked())
        incompEvitar[1] = 1;
    if(ui->checkBox_semivegetariano_2->isChecked())
        incompEvitar[2] = 1;
    if(ui->checkBox_vegetariano_2->isChecked())
        incompEvitar[3] = 1;
    if(ui->checkBox_vegano_2->isChecked())
        incompEvitar[4] = 1;

    for(int i = 0; i < alerEvitar.size(); i++)
        if(alerEvitar[i] == 1)
            x = true;
    for(int j = 0; j < incompEvitar.size(); j++)
        if(incompEvitar[j] == 1)
            x = true;
    return x;
}

bool MainWindowMenuPlan::comprobarPlanActual(individuo ind)
{
    for(int i = 0; i < NumAlergenos; i++)
        if(alerEvitar[i] == 1 && ind.get_alergeno(i) == 1)
            return false;
    for(int j = 0; j < NumIncomp; j++)
        if(incompEvitar[j] == 1 && ind.get_incompatibilidad(j) == 1)
            return false;

    return true;
}


bool MainWindowMenuPlan::comprobarPlatossEsp(infoPlatos iF)
{
    for(int i = 0; i < NumAlergenos; i++)
        if(alerEvitar[i] == 1 && iF.alerg[i] == "1")
            return false;
    for(int j = 0; j < NumIncomp; j++)
        if(incompEvitar[j] == 1 && iF.incomp[j] == "1")
            return false;

    return true;
}


void MainWindowMenuPlan::set_PlatosEspeciales(std::vector<int> &ppE, std::vector<int> &spE, std::vector<int> &pE)
{
    for(int i = 0; i < PrimerosPlatos.size(); i++)
        if(comprobarPlatossEsp(PrimerosPlatos[i]))
            ppE.push_back(PrimerosPlatos[i].id);

    for(int j = 0; j < SegundosPlatos.size(); j++)
        if(comprobarPlatossEsp(SegundosPlatos[j]))
            spE.push_back(SegundosPlatos[j].id);

    for(int k = 0; k < Postres.size(); k++)
        if(comprobarPlatossEsp(Postres[k]))
            pE.push_back(Postres[k].id);
}


void MainWindowMenuPlan::set_PlanEspecial()
{   
    if(comprobarAlerIncomp())
    {
        std::vector<int> ppE, spE, pE;
        set_PlatosEspeciales(ppE, spE, pE);
        int platoRand = 0;

        planesEspeciales.clear();
        planesEspeciales = planesRecomendados;

        for(int i = 0; i < planesEspeciales.size(); i++)
        {
            if(!comprobarPlanActual(planesEspeciales[i]))
            {
                for(int j = 0; j < numDiasPlan; j++)
                {

                    if(!comprobarPlatoActual(planesEspeciales[i].get_menuDiarioPP(j),1,ppE,spE,pE) && ppE.size() > 0)
                    {
                        platoRand = rand() % ppE.size();
                        planesEspeciales[i].set_menuDiarioPP(j,ppE[platoRand]);
                    }                
                    if(!comprobarPlatoActual(planesEspeciales[i].get_menuDiarioSP(j),2,ppE,spE,pE) && spE.size() > 0)
                    {
                        platoRand = rand() % spE.size();
                        planesEspeciales[i].set_menuDiarioSP(j,spE[platoRand]);
                    }               
                    if(!comprobarPlatoActual(planesEspeciales[i].get_menuDiarioP(j),3,ppE,spE,pE) && pE.size() > 0)
                    {
                        platoRand = rand() % pE.size();
                        planesEspeciales[i].set_menuDiarioP(j,pE[platoRand]);
                    }            
                }

            }
        }
        infoPlanEsp(ppE, spE, pE);
    }
}


bool MainWindowMenuPlan::comprobarPlatoActual(int p, int tipoP, std::vector<int> ppE, std::vector<int> spE, std::vector<int> pE)
{
    bool x = false;
    switch(tipoP)
    {
        case 1:
        for(int i = 0; i < ppE.size(); i++)
            if(ppE[i] == p)
                x = true;
        break;

        case 2:
            for(int j = 0; j < spE.size(); j++)
                if(spE[j] == p)
                    x = true;
        break;

        case 3:
            for(int k = 0; k < pE.size(); k++)
                if(pE[k] == p)
                    x = true;
        break;
    }
    return x;
}


void MainWindowMenuPlan::infoPlanEsp(std::vector<int> ppE, std::vector<int> spE, std::vector<int> pE)
{
    QString str = "No se han encontrado platos que cumplan las restricciones alimenticias en: ";
    bool x = false;
    if(ppE.size() == 0)
    {
        str.append("\n- primer plato");
        x = true;
    }
    if(spE.size() == 0)
    {
        str.append("\n- segundo plato");
        x = true;
    }
    if(pE.size() == 0)
    {
        str.append("\n- postre");
        x = true;
    }
    if(x)
        QMessageBox::information(this,"Información",str);
}
