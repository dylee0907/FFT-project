#ifndef SETTINGDIALOG_H
#define SETTINGDIALOG_H

#include <QDialog>
#include <QtSerialPort/QSerialPortInfo>
#include <QDebug>
#include "uart.h"

namespace Ui {
class SettingDialog;
}

class SettingDialog : public QDialog
{
    Q_OBJECT

public:
    explicit SettingDialog(QWidget *parent = 0);
    ~SettingDialog();

    //get method
    UART getUART();
    UART *m_UART;
signals:
    void applied_setting();
private:
    Ui::SettingDialog *ui;
    // UART - Serial Connection


private slots:

    // Serial port info
    void fillPortsParameters();
    void fillPortsInfo();
    void setDefaultConnectSetting();
    void updateConnectSetting();
    void showPortInfo(int index);

    //Common Function
    void on_applyPB_clicked();
};

#endif // SETTINGDIALOG_H
