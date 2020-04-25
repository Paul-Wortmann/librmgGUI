#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <sstream>

#include "source/libRMG.hpp"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_comboBox_generation_algorithm_currentIndexChanged(int index);

    void on_pushButton_generate_released();

private:
    Ui::MainWindow *ui;

    cLibRMGMap map;
};

#endif // MAINWINDOW_H
