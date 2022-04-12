#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:

    void on_buttonAddColor_clicked();

    void on_RotationX_valueChanged(double arg1);

    void on_RotationY_valueChanged(double arg1);

    void on_RotationZ_valueChanged(double arg1);

    void on_SpeedRotation_valueChanged(double arg1);

    void on_typeView_currentIndexChanged(int index);

    void on_ColorR_Poly_valueChanged(double arg1);

    void on_ColorG_Poly_valueChanged(double arg1);

    void on_ColorB_Poly_valueChanged(double arg1);

    void on_radiusSphere_valueChanged(double arg1);

    void on_sectorSphere_valueChanged(int arg1);

    void on_stackSphere_valueChanged(int arg1);

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
