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

    void on_scaleLatter1_valueChanged(double arg1);

    void on_xPositionLetter1_valueChanged(double arg1);

    void on_yPositionLetter1_valueChanged(double arg1);

    void on_widthLetter1_valueChanged(double arg1);

    void on_heightLetter1_valueChanged(double arg1);

    void on_scaleWorld_valueChanged(double arg1);

    void on_xPositionWorld_valueChanged(double arg1);

    void on_yPositionWorld_valueChanged(double arg1);

    void on_scaleLetter2_valueChanged(double arg1);

    void on_xPositionLetter2_valueChanged(double arg1);

    void on_yPositionLetter2_valueChanged(double arg1);

    void on_wigthLetter2_valueChanged(double arg1);

    void on_heightLetter2_valueChanged(double arg1);

    void on_scaleLetter3_valueChanged(double arg1);

    void on_xPositionLetter3_valueChanged(double arg1);

    void on_yPositionLetter3_valueChanged(double arg1);

    void on_wigthLetter3_valueChanged(double arg1);

    void on_heightLetter3_valueChanged(double arg1);

    void on_checkBox_clicked(bool checked);

    void on_checkBox_2_clicked(bool checked);

    void on_checkBox_3_clicked(bool checked);

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
