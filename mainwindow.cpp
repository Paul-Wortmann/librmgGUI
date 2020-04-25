#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    map.data.generator         = eGenerator::generatorC1;
    map.data.connect_algorithm = eConnectAlgorithm::connectND;
    map.data.room_shape = eRoomShape::roomShapeSquare;
    map.data.tile_x = 130;
    map.data.tile_y = 60;
    map.data.density = 60;
    map.data.maxItterations = 4;
    map.data.direction_bias = eDirection::directionEast;
    map.data.direction_biasStrength = 6;
    map.init();
}

MainWindow::~MainWindow()
{
    map.free();
    delete ui;
}

void MainWindow::on_comboBox_generation_algorithm_currentIndexChanged(int index)
{
    map.data.generator = static_cast<eGenerator>(index);
    std::cout << "index: " << index << std::endl;
}

void MainWindow::on_pushButton_generate_released()
{
    std::stringstream tempStream;
    map.data.seed = 0;
    map.generate();
    MainWindow::ui->textEdit_mapView->clear();
     for (uint32_t i = 0; i < map.data.tile_count; i++)
     {
         switch (map.data.tile[i].base)
         {
             case eBase::baseWall:
                tempStream << "<font color=#003300>";
             break;
             case eBase::baseLiquid:
                 tempStream << "<font color=#000066>";
             break;
             case eBase::baseFloor:
                 tempStream << "<font color=#D8F8D8>";
             /*
                 switch (map.data.tile[i].objectID)
                 {
                     case RMG_OBJECT_NONE:
                        tempStream << "<font color=#D8F8D8>";
                     break;
                     default:
                        tempStream << "<font color=#FF0000>";
                     break;
                 }
             */
             break;
             default:
                 tempStream << "<font color=#FF0000>";
             break;
         }
         tempStream << "&#9608;" << "";
         tempStream << "</font>";
         if (i < (map.data.tile_count - (map.data.tile_x / 2)))
            if ((i % map.data.tile_x) == (map.data.tile_x-1)) tempStream << "<br>";
     }
     MainWindow::ui->textEdit_mapView->insertHtml(tempStream.str().c_str());
}
