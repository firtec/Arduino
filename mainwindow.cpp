#include "mainwindow.h"
#include "ui_mainwindow.h"
//#include <QThread>
#include <QDebug>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)  // Crea el objeto de la ventana
{
    ui->setupUi(this);
    sample_palette.setColor(QPalette::WindowText, Qt::blue);
    ui->t->setPalette(sample_palette);
    ui->t->setText("00.0");
    ui->p->setPalette(sample_palette);
    ui->p->setText("0000.0");

    //serialData1.clear();

       Q_FOREACH(QSerialPortInfo port, QSerialPortInfo::availablePorts()) {
              ui->puerto->addItem(port.portName());
          }
    ui->baudBox->addItem(QStringLiteral("1200"), QSerialPort::Baud1200);
    ui->baudBox->addItem(QStringLiteral("2400"), QSerialPort::Baud2400);
    ui->baudBox->addItem(QStringLiteral("4800"), QSerialPort::Baud4800);
    ui->baudBox->addItem(QStringLiteral("9600"), QSerialPort::Baud9600);
    ui->baudBox->addItem(QStringLiteral("2400"), QSerialPort::Baud19200);
    ui->baudBox->addItem(QStringLiteral("38400"), QSerialPort::Baud38400);
    ui->baudBox->addItem(QStringLiteral("57600"), QSerialPort::Baud57600);
    ui->baudBox->addItem(QStringLiteral("115200"), QSerialPort::Baud115200);

       statusBar()->showMessage(tr("Desconectado!"));

}

MainWindow::~MainWindow()   // Destructor de la ventana
{      
  delete ui;
}

/**************************************************************
*   Esta función procesa el estado del botón para conectar con
*   el puerto COM seleccionado.
***************************************************************/
void MainWindow::on_pushButton_clicked()
{
        if(bandera == false){
            //arduino = new QSerialPort(this);
         // arduino->setPortName(ui->puerto->currentText());
           arduino = new QSerialPort(ui->puerto->currentText()); // Puerto asignado con el combo BOX     
            arduino->open(QIODevice::ReadWrite);
            if(!arduino->isOpen())
            {
                error = true;
                QMessageBox::warning(this, "ERROR", "EL PUERTO YA ESTA ABIERTO O NO EXISTE!!!");
            }

    if(error == false){
        arduino->clear(QSerialPort::AllDirections);  // Limpar buffer del puerto COMx
        arduino->open(QIODevice::ReadWrite);
        arduino->setBaudRate(ui->baudBox->currentData().toInt());
        //arduino->setBaudRate(QSerialPort::Baud9600);
        arduino->setDataBits(QSerialPort::Data8);
        arduino->setFlowControl(QSerialPort::NoFlowControl);
        arduino->setParity(QSerialPort::NoParity);
        arduino->setStopBits(QSerialPort::OneStop);
        QObject::connect(arduino, SIGNAL(readyRead()), this, SLOT(LeerSerial()));
        ui->puerto->setEnabled(false);
        ui->baudBox->setEnabled(false);
        bandera = true;
        arduino->write("c");
        statusBar()->showMessage(tr("Conectado %1 a %2 baudios, %3 bits, %4 stop, s/p")
         .arg(arduino->portName()).arg(arduino->baudRate()).arg(arduino->dataBits()).arg(arduino->stopBits()));//.arg(arduino->parity()));

        ui->pushButton->setText("Desconectar");
        serialData1.clear();
        //arduino->clear(QSerialPort::AllDirections);
        connect(timer,SIGNAL(timeout()),this,SLOT(cambiarBandera()));
        estado = 0;
        timer->start(1000);
       }
    error = false;
    }else{
            arduino->write("c");
            arduino->clear(QSerialPort::AllDirections);   // Limpar buffer del puerto COMx
            arduino->close();   // Cerrar el puerto COMx
            bandera = false;    // Cambiar bandera de estado
            ui->pushButton->setText("Conectar");    // Cambiar texto del boton
            statusBar()->showMessage(tr("Desconectado!"));  // Cambiar texto en barra de estado
            ui->t->setText("00.0");         // Limpiar indicadores
            ui->p->setText("0000.0");
            serialData1.clear();            // Limpiar buffer
            timer->stop();                  // Detener el timer
            ui->puerto->setEnabled(true);   // Activar selección de puertos
            ui->baudBox->setEnabled(true);  // Activar selección de baudios
         }
  }
/**************************************************************
*   Esta función se ejecuta cada vez que el timer se desborda.
*   Su trabajo es enviar los caracteres de control para que
*   Arduino transmita la temperatura o la presión según sea el
*   caso.
***************************************************************/
void MainWindow::cambiarBandera()
{
if(estado == 0){
    arduino->write("c");
    arduino->write("a");
    //arduino->flush();
    estado = 1;
}
else if(estado == 2) {
//else{
    arduino->write("c");
    arduino->write("b");
    // arduino->flush();
 }
}
/**************************************************************
*   Esta función procesa los datos recibidos desde el puerto
*   COM seleccionado.
*   Dependendiendo de la bandera "estado" los datos se ven en
*   la posición correspondiente en la ventana.
***************************************************************/
void MainWindow::LeerSerial()
{

 if(estado == 1){
    //serialData1 = arduino->readAll();
    serialData1 = arduino->read(4);
    ui->t->setText(serialData1);
    serialData1.clear();
    serialData2.clear();
    estado = 2;
  }
    //else{
 else if(estado == 2) {
      // serialData2 = arduino->readAll();
       serialData2 = arduino->read(6);
       ui->p->setText(serialData2);
       estado = 0;
       serialData1.clear();
       serialData2.clear();

    }
}
//****************************************************************************

