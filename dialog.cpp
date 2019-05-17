#include "dialog.h"
#include "ui_dialog.h"
#include <QTimer>
#include <QThread>

Dialog::Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog)
{
    timer_ = new QTimer(this);
    ui->setupUi(this);
    timer_->start(1000);


  connect(ui->speedScrollBar,SIGNAL(actionTriggered(int)),this, SLOT(on_verticalScrollBar_rangeChanged()));
  connect(ui->setRoverRange,SIGNAL(actionTriggered(int)),this, SLOT(on_setRoverRange_rangeChanged()));
  connect(ui->mySerialPort,SIGNAL(readyRead()),this,SLOT(read_StackReceivedData()));
 // connect(timer_, SIGNAL(timeout()),this, SLOT(myLabelUpdateThread()));
  connect( this,SIGNAL(updateLabelLists()),this,SLOT( myLabelUpdateThread() ) );

}


Dialog::~Dialog()
{
    delete ui;
}



void Dialog:: read_StackReceivedData()
{
//https://www.qtcentre.org/threads/68698-Read-data-from-serial-port
//    *ui->receivedData = ui->mySerialPort->readAll();

    Rxinputs.append(ui->mySerialPort->readAll());

   if(Rxinputs.size() >= RXDATASIZE)   // when all data received
   {
       if( (Rxinputs[0]==PACKET_START ) && (Rxinputs[RXDATASIZE-1]==PACKET_STOP ) )
       {
         memcpy(ui->receivedData, &Rxinputs, RXDATASIZE);
       }
       Rxinputs[0] = Rxinputs[RXDATASIZE-1] = RESET;  // to lock from read while list updation
      // emit updateLabelLists();
       myLabelUpdateThread();
   }

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

void Dialog:: myLabelUpdateThread()
 {
     // compute rssi to approx distance


     char *m = new char[Rxinputs.size()];
     memcpy( m, Rxinputs.data() ,Rxinputs.size());

 for( int i=0; i < RXDATASIZE-2; i++)
 {
     QString sValue = QChar(int(m[1+i]));
     unsigned char datas;
     memcpy( &datas, sValue.toStdString().c_str() ,sValue.size());
     qDebug() << datas ;//<<c;

     QString g = (ui->roverConsoleLabels[i]->text());
     g.chop( g.size() - ui->roverConsoleLabels_SIZES[i] );   // current str len - initial str len
     ui-> roverConsoleLabels[i]->setText( g + QString::number(datas));
     Rxinputs.clear();
  }
 delete []m;
 }



