#include "dialog.h"
#include "ui_dialog.h"

Dialog::Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog)
{
    ui->setupUi(this);

  connect(ui->speedScrollBar,SIGNAL(actionTriggered(int)),this, SLOT(on_verticalScrollBar_rangeChanged()));
  connect(ui->setRoverRange,SIGNAL(actionTriggered(int)),this, SLOT(on_setRoverRange_rangeChanged()));
}

Dialog::~Dialog()
{
    delete ui;
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
