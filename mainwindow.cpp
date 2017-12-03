#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    showPorts();

       if(serial_init()){
           ui->connectLabel->setText("Связь установлена");
       }
       else{
           ui->connectLabel->setText("Связь потеряна");
           qDebug() << "Error opening serial port, timer not started";
       }
}

MainWindow::~MainWindow()
{
    serial.close();
    delete ui;
}

bool MainWindow::serial_init()
{
    serial.setPortName(ui->portsBox->currentText());
    serial.setBaudRate(QSerialPort::Baud9600);
    serial.setDataBits(QSerialPort::Data8);
    serial.setParity(QSerialPort::NoParity);
    serial.setStopBits(QSerialPort::OneStop);

    if(serial.open(QSerialPort::WriteOnly)){
        return true;
    }
    else {
        serial.close();
        return false;
    }
}

void MainWindow::showPorts()
{
    QList<QSerialPortInfo> ports = QSerialPortInfo::availablePorts();

    for (int i = 0; i <= ports.length() - 1; i++){
        ui->portsBox->addItem(ports[i].portName());
    }

}

void MainWindow::on_connectButton_clicked()
{
    serial_init();

       if(serial_init()){
           ui->connectLabel->setText("Связь установлена");
       }
       else{
           ui->connectLabel->setText("Связь потеряна");
           qDebug() << "Error opening serial port, timer not started";
       }
}
