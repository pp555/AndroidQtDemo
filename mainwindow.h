#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include <QtSensors>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_dial_valueChanged(int value);

    void printText(const QString &text);

    void checkReading();

    void checkPos();

private:
    Ui::MainWindow *ui;

    QAccelerometer accSensor;

    QTimer checkPosTimer;
};

#endif // MAINWINDOW_H
