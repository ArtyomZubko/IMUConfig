#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    showPorts();
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

void MainWindow::on_transmitMatrixButton_clicked()
{
   QByteArray outPacket;
   QString matrix[3][3];
   QString i, a;

   if (serial.isOpen()){
       matrix[1][1] = ui->m11lineEdit->text();
       matrix[1][2] = ui->m12lineEdit->text();
       matrix[1][3] = ui->m13lineEdit->text();
       matrix[2][1] = ui->m21lineEdit->text();
       matrix[2][2] = ui->m22lineEdit->text();
       matrix[2][3] = ui->m23lineEdit->text();
       matrix[3][1] = ui->m31lineEdit->text();
       matrix[3][2] = ui->m32lineEdit->text();
       matrix[3][3] = ui->m33lineEdit->text();

       serial.write("m"); // отправка стартового байта

//       foreach (i, matrix) { //отправка матрицы
//           foreach (a, i) {
//               outPacket.append((unsigned char)a);
//           }
//       }
   } else{
       QMessageBox::warning(0,"Ошибка", "Устройтсво не подключено");
   }
}
