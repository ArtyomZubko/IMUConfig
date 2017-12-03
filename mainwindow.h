#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtSerialPort/QSerialPort>
#include <QSerialPortInfo>

#include <QDebug>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    bool serial_init();
    void showPorts();


private slots:
    void on_connectButton_clicked();

private:
    Ui::MainWindow *ui;

    QSerialPort serial;
};

#endif // MAINWINDOW_H
