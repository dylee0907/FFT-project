#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMessageBox>
#include <QString>
#include <QThread>
#include <QtSerialPort/QSerialPort>
#include "settingdialog.h"
#include "qdatainfo.h"
#include "qcustomplot.h"
#include "radix2.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_pb_run_clicked();
    void on_pb_data_clicked();
    void on_pb_set_clicked();
    void on_pb_connect_clicked();
    void read_Serial_Port_Data();
    void set_datainfo();
    void set_setting();
private:
    // UI
    Ui::MainWindow *ui;
    SettingDialog *settingWindow;
    qDatainfo *dataWindow;
    // Series Connection
    QSerialPort *m_SerialPort;
    // button checked
    bool pb_run_ischecked;
    // Data Info
    QString mRate;
    QString mLength;
    QString mPrecision;
    QString mPoint;
    // DataControl
    int cntfft;
    double* data;
    double* data2;
    t_complex* bf;
    int cnt;
    int init;
    int xIndex;
    int yIndex;
    int cnt_index;
    int xIndexpc;
    int yIndexpc;
    QVector<double> qv_x, qv_y;
    // qcustom
    QCPColorMap *colorMap;
    QCPColorMap *colorMap2;
    QCPColorScale *colorScale;
    QCPColorScale *colorScale2;
    QCPMarginGroup *marginGroup;
    QCPMarginGroup *marginGroup2;
    // JUST TEST
    double w0cos;
    double w0sin;
    double w1bfcos;
    double w1bfsin;
    double w1cos;
    double w1sin;
};
#endif // MAINWINDOW_H
