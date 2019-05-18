#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>
#include <stdint.h>
#define RXDATASIZE 6
#define PACKET_START 77
#define PACKET_STOP  70
#define RESET 0

enum {RSSI=1,DIST_2_OBST,GEAR,ROV_SPEED};
enum {SPEED=1,SET_OBST,A_M_RSSI,L_R_STR};

enum{NO_DIRECTION, LEFT_TURN, RIGHT_TURN, AUTO, MANUAL, RSSI_READ};

namespace Ui {
class Dialog;
}

class Dialog : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog(QWidget *parent = 0);
    ~Dialog();

private slots:
    void on_verticalScrollBar_rangeChanged();
    void on_setRoverRange_rangeChanged();
    void read_StackReceivedData();
    void myLabelUpdateThread();
    void setDrive_ReadMode();
    void sendOutBluetoothData();
    void liveControl_Rover();

signals:
    void updateLabelLists();


private:
    Ui::Dialog *ui;
    QTimer *timer_;
    uint8_t count,roverSpeed;
    QByteArray Rxinputs;
    bool initSet[RXDATASIZE];
    QByteArray SendData;

    void setDriveValues();

};

#endif // DIALOG_H
