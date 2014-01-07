#include <QDebug>

#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->dial->setRange(5, 50);

    connect(&accSensor, SIGNAL(readingChanged()), this, SLOT(checkReading()));
    accSensor.start();

    checkPosTimer.setInterval(30 * 1000);
    connect(&checkPosTimer, SIGNAL(timeout()), this, SLOT(checkPos()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_dial_valueChanged(int value)
{
    QFont newFont(ui->label->font());
    newFont.setPixelSize(value);
    ui->label->setFont(newFont);

    printText(QString("value changed to: %1").arg(value));
}

void MainWindow::printText(const QString &text)
{
    qDebug() << "printing text" << text;
    ui->textBrowser->append(text + "\n");
}

void MainWindow::checkReading()
{
    qDebug() << __FUNCTION__;
    if (!checkPosTimer.isActive()) {
        checkPosTimer.start();
    }
}

void MainWindow::checkPos()
{
    qreal x = accSensor.reading()->x();
    qreal y = accSensor.reading()->y();
    qreal z = accSensor.reading()->z();

    printText(QTime::currentTime().toString("hh:mm:ss") + QString(" pos:\t") + QString::number(x) + "\t" + QString::number(y) + "\t" + QString::number(z));
}
