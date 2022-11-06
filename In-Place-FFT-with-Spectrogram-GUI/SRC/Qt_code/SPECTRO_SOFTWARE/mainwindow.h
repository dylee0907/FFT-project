#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QInputDialog>
#include <QString>
#include <QFileDialog>
#include <QFile>
#include <radix2.h>
#include <qcustomplot.h>
QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    int Fs;
    int N;
    int H;
    int length;
    int M;

    QString INFILE;
    QString str_data;
    QCPColorMap *colorMap;
    double *data;
    t_complex *out;

private slots:
    void on_pb_run_clicked();
    void on_pb_sr_clicked();
    void on_pb_point_clicked();
    void on_pb_hope_clicked();
    void on_pb_length_clicked();
    void loadFile();
    void plotori();
    void plotpow();
    void plotden();
};
#endif // MAINWINDOW_H
