#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_buttonAddColor_clicked()
{
    ui->openGLWidget->setColorLine(ui->ColorR->value(), ui->ColorG->value(), ui->ColorB->value());
}


void MainWindow::on_RotationX_valueChanged(double arg1)
{
    ui->openGLWidget->setX((float)arg1);
}


void MainWindow::on_RotationY_valueChanged(double arg1)
{
    ui->openGLWidget->setY((float)arg1);
}


void MainWindow::on_RotationZ_valueChanged(double arg1)
{
    ui->openGLWidget->setZ((float)arg1);
}


void MainWindow::on_SpeedRotation_valueChanged(double arg1)
{
    ui->openGLWidget->setSpeedRotation((float)arg1);
}


void MainWindow::on_typeView_currentIndexChanged(int index)
{
    ui->openGLWidget->setView(index);
}


void MainWindow::on_ColorR_Poly_valueChanged(double arg1)
{
    ui->openGLWidget->setColorPolygons(arg1, ui->ColorG_Poly->value(), ui->ColorB_Poly->value());
}


void MainWindow::on_ColorG_Poly_valueChanged(double arg1)
{
    ui->openGLWidget->setColorPolygons(ui->ColorR_Poly->value(), arg1, ui->ColorB_Poly->value());
}


void MainWindow::on_ColorB_Poly_valueChanged(double arg1)
{
    ui->openGLWidget->setColorPolygons(ui->ColorR_Poly->value(), ui->ColorG_Poly->value(), arg1);
}


void MainWindow::on_radiusSphere_valueChanged(double arg1)
{
    ui->openGLWidget->sphere2.set(arg1, ui->sectorSphere->value(), ui->stackSphere->value(), 0);
}


void MainWindow::on_sectorSphere_valueChanged(int arg1)
{
    ui->openGLWidget->sphere2.set(ui->radiusSphere->value(), arg1, ui->stackSphere->value(), 0);
}


void MainWindow::on_stackSphere_valueChanged(int arg1)
{
    ui->openGLWidget->sphere2.set(ui->radiusSphere->value(), ui->sectorSphere->value(), arg1, 0);
}

