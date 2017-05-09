#include "mainwindowmenuplan.h"
#include "ui_mainwindowmenuplan.h"


void MainWindowMenuPlan::matLabScript()
{
    QString name = "i";
    name.append(QString::number(NumIndividuos));
    name.append("_m");
    name.append(QString::number(probMutacion));
    name.append("_c");
    name.append(QString::number(probCruce));
    name.append(".m");

    std::ofstream file;
    file.open(name.toStdString(), std::ios_base::app);

    QString line, line2;
    for(int i = 0; i < v1.size(); i++)
    {
        line = "x";
        line.append(QString::number(i));
        line.append("=[");
        line2 = "y";
        line2.append(QString::number(i));
        line2.append("=[");

        for(int j = 0; j < v1[i].size(); j++)
        {
            line.append(QString::number(v1[i][j].x));
            line2.append(QString::number(v1[i][j].y));
            if(j < v1[i].size()-1)
            {
                line.append(",");
                line2.append(",");
            }
        }
        line.append("];");
        line2.append("];");

        file << line.toStdString() << "\n";
        file << line2.toStdString() << "\n";
    }
    for(int i = 0; i < v1.size(); i++)
    {
        line = "plot(x";
        line.append(QString::number(i));
        line.append(",y");
        line.append(QString::number(i));
        line.append(",'-+')");
        file << line.toStdString() << "\n";
        line = "hold on";
        file << line.toStdString() << "\n";
    }

    file.close();
}
