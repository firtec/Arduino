#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtSerialPort/QSerialPort>
#include <QtSerialPort/QSerialPortInfo>
#include <QMessageBox>  // Necesario para QMessageBox
#include <QPushButton>
# include <QTimer>
#include <QByteArray>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
     QTimer *timer = new QTimer(this); // Constructor del Temporizador
     QSerialPort *arduino;
     unsigned char estado = 0;
    // char prueba;

private slots:
    void on_pushButton_clicked();
    void LeerSerial();
    void cambiarBandera();

private:
    Ui::MainWindow *ui;
    QPalette sample_palette;
    //QSerialPort *arduino;
    QByteArray serialData1;
    QByteArray serialData2;
    //unsigned char estado = 0;
    bool bandera = false;
    bool error = false;

};

#endif // MAINWINDOW_H
