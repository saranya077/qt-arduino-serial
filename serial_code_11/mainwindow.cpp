#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QSerialPort>
#include <QDebug>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // Create Serial Port object
    COMPORT = new QSerialPort(this);

    // Set COM Port
    COMPORT->setPortName("COM7");

    // Set Baud Rate
    COMPORT->setBaudRate(QSerialPort::Baud9600);

    // Set Data Bits
    COMPORT->setDataBits(QSerialPort::Data8);

    // Set Stop Bits
    COMPORT->setStopBits(QSerialPort::OneStop);

    // Set Parity
    COMPORT->setParity(QSerialPort::NoParity);

    // Set Flow Control
    COMPORT->setFlowControl(QSerialPort::NoFlowControl);

    // Open Serial Port
    if (COMPORT->open(QIODevice::ReadWrite))
    {
        qDebug() << "Serial Port Is Connected.";
    }
    else
    {
        qDebug() << "Serial Port Is Not Connected.";
        qDebug() << COMPORT->errorString();
    }
}

MainWindow::~MainWindow()
{
    if (COMPORT->isOpen())
    {
        COMPORT->close();
    }

    delete ui;
}
bool IS_Open=false;
void MainWindow::on_pushButton_clicked()
{

        if (COMPORT->isOpen())
        {
            COMPORT->write(ui->lineEdit->text().toLatin1() + char(10));
        }


}
