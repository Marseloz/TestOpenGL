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

void MainWindow::on_scaleLatter1_valueChanged(double arg1)
{
    ui->openGLWidget->latter_1.setScale(arg1);
}


void MainWindow::on_xPositionLetter1_valueChanged(double arg1)
{
    ui->openGLWidget->latter_1.setPositionX(arg1);
}


void MainWindow::on_yPositionLetter1_valueChanged(double arg1)
{
    ui->openGLWidget->latter_1.setPositionY(arg1);
}


void MainWindow::on_widthLetter1_valueChanged(double arg1)
{
    ui->openGLWidget->latter_1.setWidth(arg1);
}


void MainWindow::on_heightLetter1_valueChanged(double arg1)
{
    ui->openGLWidget->latter_1.setHeight(arg1);
}


void MainWindow::on_scaleWorld_valueChanged(double arg1)
{
    ui->openGLWidget->setWorldScale(arg1);
}


void MainWindow::on_xPositionWorld_valueChanged(double arg1)
{
    ui->openGLWidget->setWorldPositionX(arg1);
}


void MainWindow::on_yPositionWorld_valueChanged(double arg1)
{
    ui->openGLWidget->setWorldPositionY(arg1);
}


void MainWindow::on_scaleLetter2_valueChanged(double arg1)
{
    ui->openGLWidget->latter_2.setScale(arg1);
}


void MainWindow::on_xPositionLetter2_valueChanged(double arg1)
{
    ui->openGLWidget->latter_2.setPositionX(arg1);
}


void MainWindow::on_yPositionLetter2_valueChanged(double arg1)
{
    ui->openGLWidget->latter_2.setPositionY(arg1);
}


void MainWindow::on_wigthLetter2_valueChanged(double arg1)
{
    ui->openGLWidget->latter_2.setWidth(arg1);
}


void MainWindow::on_heightLetter2_valueChanged(double arg1)
{
    ui->openGLWidget->latter_2.setHeight(arg1);
}


void MainWindow::on_scaleLetter3_valueChanged(double arg1)
{
    ui->openGLWidget->latter_3.setScale(arg1);
}


void MainWindow::on_xPositionLetter3_valueChanged(double arg1)
{
    ui->openGLWidget->latter_3.setPositionX(arg1);
}


void MainWindow::on_yPositionLetter3_valueChanged(double arg1)
{
    ui->openGLWidget->latter_3.setPositionY(arg1);
}


void MainWindow::on_wigthLetter3_valueChanged(double arg1)
{
    ui->openGLWidget->latter_3.setWidth(arg1);
}


void MainWindow::on_heightLetter3_valueChanged(double arg1)
{
    ui->openGLWidget->latter_3.setHeight(arg1);
}


void MainWindow::on_checkBox_clicked(bool checked)
{
    ui->openGLWidget->latter_1.setTrigg(checked);
}


void MainWindow::on_checkBox_2_clicked(bool checked)
{
    ui->openGLWidget->latter_2.setTrigg(checked);
}


void MainWindow::on_checkBox_3_clicked(bool checked)
{
    ui->openGLWidget->latter_3.setTrigg(checked);
}

