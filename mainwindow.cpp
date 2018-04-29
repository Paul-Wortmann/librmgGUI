

#include <sstream>
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "../librmg/source/librmg.hpp"

rmg::sMap map;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    //MainWindow::ui->textEdit_mapView->setTextInteractionFlags(QFlags<NoTextInteraction>);

    map.generationAlgorithm = RMG_GEN_C1;
    map.connectivityAlgorithm = RMG_PATH_ND;
    map.roomShape = RMG_SQUARE;
    map.w = 100;
    map.h = 100;
    map.density = 60;
    map.pass = 4;
    map.directionBias = RMG_EAST;
    map.directionBiasStrength = 6;
    rmg::prefabFind(map);
}

MainWindow::~MainWindow()
{
    rmg::mapFree(map);
    delete ui;
}

void MainWindow::on_pushButton_released()
{
    std::stringstream tempStream;
    map.seed = 0;
    rmg::mapGen(map);
    MainWindow::ui->textEdit_mapView->clear();
     for (uint32_t i = 0; i < map.tileCount; i++)
     {
         switch (map.tile[i].b)
         {
             case RMG_BASE_WALL:
                tempStream << "<font color=#003300>";
             break;
             case RMG_BASE_LIQUID:
                 tempStream << "<font color=#000066>";
             break;
             case RMG_BASE_FLOOR:
                 switch (map.tile[i].o)
                 {
                     case RMG_OBJECT_NONE:
                        tempStream << "<font color=#D8F8D8>";
                     break;
                     default:
                        tempStream << "<font color=#FF0000>";
                     break;
                 }
             break;
             default:
                 tempStream << "<font color=#FF0000>";
             break;
         }
         tempStream << "&#9632;" << "   ";
         tempStream << "</font>";
         if (i < (map.tileCount - (map.w / 2)))
            if ((i % map.w) == (map.w-1)) tempStream << "<br>";
     }
     MainWindow::ui->textEdit_mapView->insertHtml(tempStream.str().c_str());

}

void MainWindow::on_comboBox_algorithm_currentIndexChanged(int index)
{
    map.generationAlgorithm = index;
}
