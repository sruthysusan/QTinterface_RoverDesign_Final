#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>

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


private:
    Ui::Dialog *ui;
    QTimer *timer_;
};

#endif // DIALOG_H
