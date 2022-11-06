#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setWindowTitle(tr("SPECTRO - Version Software"));

    // Tool bar, file read
    connect(ui->actionLoad, SIGNAL(triggered()), this, SLOT(loadFile()));

    // Original Data
    ui->qw_ori->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom);
    ui->qw_ori->addGraph();
    ui->qw_ori->graph(0)->setPen(QPen(Qt::black));
    ui->qw_ori->xAxis->setLabel("Data(#)");
    ui->qw_ori->yAxis->setLabel("Amplitude");

    // Power Spectogram
    ui->qw_pow->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom);
    ui->qw_pow->axisRect()->setupFullAxesBox(true);
    ui->qw_pow->xAxis->setLabel("Time(sec)");
    ui->qw_pow->yAxis->setLabel("Frequency(Hz)");
    this->colorMap = new QCPColorMap(ui->qw_pow->xAxis,ui->qw_pow->yAxis);

    // Density Spectogram
    ui->qw_den->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom);
    ui->qw_den->axisRect()->setupFullAxesBox(true);
    ui->qw_den->xAxis->setLabel("Time(sec)");
    ui->qw_den->yAxis->setLabel("Power(dB)");
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pb_run_clicked()
{
    this->data = new double[this->length];
    this->M = (this->length - this->N) / this->H;

    // FILE IO
    QFile file(INFILE);

    if(!file.open(QFile::ReadOnly | QFile::Text))
    {
        qDebug() << "Could not open the file for reading";
        return;
    }

    QTextStream in(&file);
    for(int i=0; i<this->length; i++)
    {
        this->str_data = in.readLine();
        this->data[i] = this->str_data.toDouble();
    }
    ui->brow_text->append("\nData Loaded");
    file.close();

    // Plot
    plotori();
    plotpow();
    plotden();

    delete[] data;
}

void MainWindow::on_pb_sr_clicked()
{
    bool ok;
    this->Fs = QInputDialog::getInt(this,"Sample Rate","Hz",0,0,2147483647,1,&ok);
    if(ok == true)
    {
    QString SR;
    SR.prepend("Sample Rate: ");
    SR.append(QString::number(this->Fs));
    ui->brow_text->append(SR);
    }
}

void MainWindow::on_pb_length_clicked()
{
    bool ok;
    this->length = QInputDialog::getInt(this,"Sample Length", "#", 0, 0, 2147483647, 1, &ok);
    if(ok == true)
    {
    QString SL;
    SL.prepend("Sample Length: ");
    SL.append(QString::number(this->length));
    ui->brow_text->append(SL);
    }
}

void MainWindow::on_pb_point_clicked()
{
    QStringList items;
    items << "8" << "16" << "32" << "64" << "128" << "256" << "512" << "1024" << "2048" <<"4096";
    bool ok;
    QString item = QInputDialog::getItem(this,"FFT point", "#", items, 0, false, &ok);
    this->N = item.toInt(&ok);
    if(ok == true)
    {
    QString FP;
    FP.prepend("FFT point: ");
    FP.append(QString::number(this->N));
    ui->brow_text->append(FP);
    }
}

void MainWindow::on_pb_hope_clicked()
{
    bool ok;
    this->H = QInputDialog::getInt(this,"Hope Size","#",0,0,this->N,1,&ok);
    if(ok == true)
    {
    QString HS;
    HS.prepend("Hope Size: ");
    HS.append(QString::number(this->H));
    ui->brow_text->append(HS);
    }
}

void MainWindow::loadFile()
{
    INFILE = QFileDialog::getOpenFileName(this,"파일 선택","C:\\","Files(*.txt)");
    ui->edit->setText(INFILE);
    if(INFILE != "")
        ui->brow_text->append("File Loaded");
}

void MainWindow::plotori()
{
    QVector<double> x(this->length), y(this->length);
    for(int i=0; i<this->length;i++)
    {
        x[i] = i;
        y[i] = this->data[i];
    }
    ui->qw_ori->graph(0)->setData(x,y);
    ui->qw_ori->graph(0)->rescaleAxes();
    ui->qw_ori->replot();
    ui->brow_text->append("Original Data Plotted");
}

void MainWindow::plotpow()
{
    double **X = new double*[this->M+1];
    for(int m=0;m<=this->M;m++)
        X[m] = new double[this->N/2+1];

    // STFT
    STFT(X,this->data,this->N,this->H,this->M);
    STFT_dB(X,this->M,this->N);

    // Spectogram

    this->colorMap->data()->setSize(this->M+1,this->N/2+1);
    this->colorMap->data()->setRange(QCPRange(0,(double)this->length/this->Fs), QCPRange(0,(double)this->Fs/2));

    // here!!
    for(int xIndex=0;xIndex<this->M+1;++xIndex)
    {
        for(int yIndex=0;yIndex<this->N/2+1;++yIndex)
        {
            this->colorMap->data()->setCell(xIndex,yIndex,X[xIndex][yIndex]);
        }
    }

    QCPColorScale *colorScale = new QCPColorScale(ui->qw_pow);
    // Layout for right side
    ui->qw_pow->plotLayout()->addElement(0,1,colorScale);
    // Layout text for right side
    colorScale->setType(QCPAxis::atRight);
    this->colorMap->setColorScale(colorScale);
    this->colorMap->setGradient(QCPColorGradient::gpPolar);
    this->colorMap->rescaleDataRange();

    QCPMarginGroup *marginGroup = new QCPMarginGroup(ui->qw_pow);
    ui->qw_pow->axisRect()->setMarginGroup(QCP::msBottom | QCP::msTop, marginGroup);
    colorScale->setMarginGroup(QCP::msBottom|QCP::msTop, marginGroup);
    ui->qw_pow->rescaleAxes();
    ui->qw_pow->replot();
    ui->brow_text->append("Power Spectogram Plotted");

    // delete
    for(int m=0;m<=this->M;m++)
            delete [] X[m];
    delete []X;
}

void MainWindow::plotden()
{
    double **X = new double*[this->M+1];

    for(int m=0;m<=this->M;m++)
        X[m] = new double[this->N/2+1];

    // STFT
    STFT(X,this->data,this->N,this->H,this->M);
    STFT_dB(X,this->M,this->N);

    // Spectogram
    QCPColorMap *colorMap = new QCPColorMap(ui->qw_den->xAxis,ui->qw_den->yAxis);
    colorMap->data()->setSize(this->M+1,this->N/2+1);
    colorMap->data()->setRange(QCPRange(0,(double)this->length/this->Fs), QCPRange(min2(X,this->N,this->M),max2(X,this->N,this->M)));

    // PDF
    Power_dist(X,this->M,this->N);
    for(int xIndex=0;xIndex<this->M+1;++xIndex)
    {
        for(int yIndex=0;yIndex<this->N/2+1;++yIndex)
        {
            colorMap->data()->setCell(xIndex,yIndex,X[xIndex][yIndex]);
        }
    }

    QCPColorScale *colorScale = new QCPColorScale(ui->qw_den);
    ui->qw_den->plotLayout()->addElement(0,1,colorScale);
    colorScale->setType(QCPAxis::atRight);
    colorMap->setColorScale(colorScale);

    colorMap->setGradient(QCPColorGradient::gpPolar);
    colorMap->rescaleDataRange();

    QCPMarginGroup *marginGroup = new QCPMarginGroup(ui->qw_den);
    ui->qw_den->axisRect()->setMarginGroup(QCP::msBottom | QCP::msTop, marginGroup);
    colorScale->setMarginGroup(QCP::msBottom|QCP::msTop, marginGroup);
    ui->qw_den->rescaleAxes();
    ui->qw_den->replot();
    ui->brow_text->append("Density Spectogram Plotted\n");

    // delete
    for(int m=0;m<=this->M;m++)
            delete [] X[m];
    delete []X;
}

