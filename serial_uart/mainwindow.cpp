#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QSerialPort>
#include <QDebug>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // Create serial port
    COMPORT = new QSerialPort(this);

    // Set COM port
    COMPORT->setPortName("COM7");

    // Set baud rate
    COMPORT->setBaudRate(QSerialPort::Baud9600);

    // Set data bits
    COMPORT->setDataBits(QSerialPort::Data8);

    // Set parity
    COMPORT->setParity(QSerialPort::NoParity);

    // Set stop bits
    COMPORT->setStopBits(QSerialPort::OneStop);

    // Set flow control
    COMPORT->setFlowControl(QSerialPort::NoFlowControl);

    // IMPORTANT:
    // When Arduino sends data, Qt calls readSerialData()
    connect(COMPORT,
            &QSerialPort::readyRead,
            this,
            &MainWindow::readSerialData);

    // Open COM port
    if (COMPORT->open(QIODevice::ReadWrite))
    {
        qDebug() << "Serial Port Connected";

        ui->label->setText("Serial Port Connected");
    }
    else
    {
        qDebug() << "Serial Port Not Connected";
        qDebug() << COMPORT->errorString();

        ui->label->setText("Serial Port Not Connected");
    }
}


//------------------------------------
// RECEIVE DATA FROM ARDUINO
//------------------------------------

void MainWindow::readSerialData()
{
    QByteArray data;

    // Read data received from Arduino
    data = COMPORT->readAll();

    qDebug() << "Received Data:" << data;

    // Display data in QLabel
    ui->label->setText(QString::fromLatin1(data).trimmed());
}


//------------------------------------
// DESTRUCTOR
//------------------------------------

MainWindow::~MainWindow()
{
    if (COMPORT->isOpen())
    {
        COMPORT->close();
    }

    delete ui;
}
