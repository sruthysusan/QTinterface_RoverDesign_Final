#include "dialog.h"
#include "ui_dialog.h"
#include "mytimer.h"


Dialog::Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog)
{
    ui->setupUi(this);



  connect(ui->speedScrollBar,SIGNAL(actionTriggered(int)),this, SLOT(on_verticalScrollBar_rangeChanged()));
  connect(ui->setRoverRange,SIGNAL(actionTriggered(int)),this, SLOT(on_setRoverRange_rangeChanged()));
  connect(ui->mySerialPort,SIGNAL(readyRead()),this,SLOT(read_StackReceivedData()));


}

MyTimer :: MyTimer ()
{
    timer = new QTimer(this);
    // setup signal and slot
    connect(timer, SIGNAL(timeout()),
          this, SLOT(MyTimerSlot()));

    // msec
    timer->start(1000);
}

void MyTimer::MyTimerSlot()
{
    qDebug() << "Timer...";
}

Dialog::~Dialog()
{
    delete ui;
}




void Dialog:: read_StackReceivedData()
{
//https://www.qtcentre.org/threads/68698-Read-data-from-serial-port
       *ui->receivedData = ui->mySerialPort->readAll();
       qDebug() <<  *ui->receivedData;
       //sleep(1);
  //     ui->Receive->insertPlainText(data);

}

void Dialog::on_verticalScrollBar_rangeChanged()
{


//https://www.programiz.com/cpp-programming/library-function/cmath/round
   int speed =round (ui->speedScrollBar->value()/25);
//https://stackoverflow.com/questions/7011447/concatenating-two-qstrings-with-an-integer
   ui->label->setText(QString("SPEED %1").arg(speed));
}

void Dialog::on_setRoverRange_rangeChanged()
{
   ui->setRRLabel->setText(QString("ROV_RANG_LMT-> %1").arg(ui->setRoverRange->value()));
}




