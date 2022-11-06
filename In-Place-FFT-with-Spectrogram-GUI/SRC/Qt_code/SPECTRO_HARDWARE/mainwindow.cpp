#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow), settingWindow(new SettingDialog), dataWindow(new qDatainfo)
{
    ui->setupUi(this);
    setWindowTitle(tr("SPECTRO - Version Hardware"));

    // Default setting
    ui->pb_run->setEnabled(false);
    this->cnt = 0;
    this->init = 1;
    this->cnt_index = 0;
    this->xIndex = 0;
    this->yIndex = 0;
    this->cntfft = 0;
    this->xIndexpc = 0;
    this->yIndexpc = 0;

    // Original Plot setting
    ui->qw_ori->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom);
    ui->qw_ori->addGraph();
    ui->qw_ori->graph(0)->setPen(QPen(Qt::black));
    ui->qw_ori->xAxis->setLabel("Data(#)");
    ui->qw_ori->yAxis->setLabel("Amplitude");

    // Power Spectogram setting(PC)
    ui->qw_spec_pc->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom);
    ui->qw_spec_pc->axisRect()->setupFullAxesBox(true);
    ui->qw_spec_pc->xAxis->setLabel("Time(sec)");
    ui->qw_spec_pc->yAxis->setLabel("Frequency(Hz)");
    this->colorMap2 = new QCPColorMap(ui->qw_spec_pc->xAxis,ui->qw_spec_pc->yAxis);
    this->colorScale2 = new QCPColorScale(ui->qw_spec_pc);
    ui->qw_spec_pc->plotLayout()->addElement(0,1,this->colorScale2);
    this->colorScale2->setType(QCPAxis::atRight);
    this->colorMap2->setColorScale(this->colorScale2);
    this->colorMap2->setGradient(QCPColorGradient::gpPolar);
    this->marginGroup2 = new QCPMarginGroup(ui->qw_spec_pc);
    ui->qw_spec->axisRect()->setMarginGroup(QCP::msBottom | QCP::msTop, this->marginGroup2);
    this->colorScale2->setMarginGroup(QCP::msBottom|QCP::msTop, this->marginGroup2);


    // Power Spectogram setting(FPGA)
    ui->qw_spec->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom);
    ui->qw_spec->axisRect()->setupFullAxesBox(true);
    ui->qw_spec->xAxis->setLabel("Time(sec)");
    ui->qw_spec->yAxis->setLabel("Frequency(Hz)");
    this->colorMap = new QCPColorMap(ui->qw_spec->xAxis,ui->qw_spec->yAxis);
    this->colorScale = new QCPColorScale(ui->qw_spec);
    ui->qw_spec->plotLayout()->addElement(0,1,this->colorScale);
    this->colorScale->setType(QCPAxis::atRight);
    this->colorMap->setColorScale(this->colorScale);
    this->colorMap->setGradient(QCPColorGradient::gpPolar);
    this->marginGroup = new QCPMarginGroup(ui->qw_spec);
    ui->qw_spec->axisRect()->setMarginGroup(QCP::msBottom | QCP::msTop, this->marginGroup);
    this->colorScale->setMarginGroup(QCP::msBottom|QCP::msTop, this->marginGroup);

    // button checked
    this->pb_run_ischecked = false;

    // UART Setting
    this->m_SerialPort = new QSerialPort(this);
    connect(this->m_SerialPort, SIGNAL(readyRead()), this, SLOT(read_Serial_Port_Data()));

    // DataInfo and Setting
    connect(this->dataWindow,SIGNAL(applied_data()),this,SLOT(set_datainfo()));
    connect(this->settingWindow,SIGNAL(applied_setting()),this,SLOT(set_setting()));
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_pb_run_clicked()
{
    QString Cmd_Str;
    QByteArray Cmd;
    if(ui->pb_connect->text() == "Disconnect")
    {
        // it can be clicked when uart is connect
        if(ui->pb_run->text() == "Run")
        {
            ui->pb_run->setToolTip("Click to Stop Sensors");
            ui->pb_run->setText("Stop");
            ui->pb_run->setEnabled(true);
            ui->pb_connect->setEnabled(false);
            ui->pb_set->setEnabled(false);
            ui->pb_data->setEnabled(false);
            this->pb_run_ischecked = true;
            Cmd_Str = "R"; // 0x52
            Cmd = Cmd_Str.toLocal8Bit();
            this->m_SerialPort -> write(Cmd);
            ui->textBrowser->append("<Run>");
        }
        else
        {
            ui->pb_run->setToolTip("Click to Run Sensors");
            ui->pb_run->setText("Run");
            ui->pb_run->setEnabled(true);
            ui->pb_connect->setEnabled(true);
            ui->pb_set->setEnabled(true);
            ui->pb_data->setEnabled(true);
            this->pb_run_ischecked = false;
            Cmd_Str = "S"; // 0x53
            Cmd = Cmd_Str.toLocal8Bit();
            this->m_SerialPort -> write(Cmd);
            ui->textBrowser->append("<Stop>");
        }
        return ;
    }
    else return ;
}

void MainWindow::on_pb_data_clicked()
{
    this->dataWindow->show();
}

void MainWindow::on_pb_set_clicked()
{
    this->settingWindow->show();
}

void MainWindow::on_pb_connect_clicked()
{
    if (ui->pb_connect->text()=="Connect")
    {
        // have not connected
        // DataInfo
        data_setting tempData = this->dataWindow->getdata();
        this->mRate = tempData.getRate();
        this->mPrecision = tempData.getPrecision();
        this->mLength = tempData.getLength();

        // Another Things

        // Serial port Setting
        UART temp = this->settingWindow->getUART();
        this->m_SerialPort->setPortName(temp.getName());
        this->m_SerialPort->setBaudRate(temp.getBaudRate());
        this->m_SerialPort->setDataBits(temp.getDataBits());
        this->m_SerialPort->setParity(temp.getParity());
        this->m_SerialPort->setStopBits(temp.getStopBits());
        this->m_SerialPort->setFlowControl(temp.getFlowControl());
        // open Serial Port
        if(this->m_SerialPort->open(QIODevice::ReadWrite))
        {
            // serial port is opened
            ui->pb_connect->setToolTip("Click to Disconnect UART");
            ui->pb_connect->setText("Disconnect");
            ui->pb_run->setEnabled(true); // make runPB enable
            //Debug, check its property
            QSerialPortInfo port_info_debug(*this->m_SerialPort);
            ui->textBrowser->append("<Connected>");
            QString Name = "Name: ";
            Name.append(port_info_debug.portName());
            ui->textBrowser->append(Name);
        }
        else
        {
            // serial port is not opened
            QMessageBox::critical(this, tr("Error"), this->m_SerialPort->errorString());
            ui->textBrowser->append("<Connect Fail>");
        }
    }
    else
    {
        // connected already
        QMessageBox msgBox;
        msgBox.setText("Disconnect serial port");
        msgBox.setInformativeText("Are you sure?");
        msgBox.setStandardButtons(QMessageBox::Yes | QMessageBox::Cancel);
        msgBox.setDefaultButton(QMessageBox::Cancel);
        int ret = msgBox.exec();
        switch (ret)
        {
          case QMessageBox::Yes:
            // Yes was clicked--> disconnect
            if (this->m_SerialPort->isOpen())
            {
                this->m_SerialPort->close();
            }
            //console->setEnabled(false);
            ui->pb_connect->setText("Connect");
            ui->pb_connect->setToolTip("Click to connect UART.");
            ui->pb_run->setEnabled(false);
            ui->textBrowser->append("<Disconnected>");
            break;
          case QMessageBox::Cancel:
            // Cancel was clicked
            break;
          default:
            // should never be reached
            break;
        }
    }
}

void MainWindow::read_Serial_Port_Data()
{
    QByteArray Data = this->m_SerialPort->read(8);
    QString str0 = "Point: ";
    QString str1 = "Real: ";
    QString str2 = "Imag: ";
    std::reverse(Data.begin(),Data.end());
    QByteArray Data1 = Data.mid(0,4);
    QByteArray Data2 = Data.mid(4);
    float cos;
    float sin;
    double X;
    double XX;
    memcpy(&sin,Data.data(),4);
    memcpy(&cos,Data2.data(),4);
    str0.append(QString::number(this->cnt));
    str1.append(QString::number(cos));
    str2.append(QString::number(sin));
    if(this->init)
    {
        this->data[this->cntfft] = cos;
        if(this->cntfft == this->mPoint.toInt()-1)
        {
            radix2(this->data,this->bf,this->mPoint.toInt());
            for(int i=0;i<this->mPoint.toInt();i++)
            {
                QString strfftp = "Point: ";
                QString strcos = "Real: ";
                QString strsin = "Imag: ";
                strfftp.append(QString::number(this->cnt-(this->mPoint.toInt()-1)+i));
                strcos.append(QString::number(this->bf[i].r));
                strsin.append(QString::number(this->bf[i].i));
                ui->textBrowser->append(strfftp);
                ui->textBrowser->append(strcos);
                ui->textBrowser->append(strsin);
            }
            for(this->yIndexpc=0;this->yIndexpc<=this->mPoint.toInt()/2;this->yIndexpc++)
            {
                XX=pow(bf[yIndexpc].r,2)+pow(bf[yIndexpc].i,2);
                XX=10*log10(XX);
                this->colorMap2->data()->setCell(xIndexpc,yIndexpc,XX);
                this->colorMap2->rescaleDataRange();
                ui->qw_spec_pc->rescaleAxes();
                ui->qw_spec_pc->replot();
                ui->qw_spec_pc->update();
            }
            this->xIndexpc++;
        }
        qv_x.append(this->cnt);
        qv_y.append(cos);
        ui->qw_ori->graph(0)->setData(qv_x,qv_y);
        ui->qw_ori->graph(0)->rescaleAxes();
        ui->qw_ori->replot();
        ui->qw_ori->update();
        if(this->cnt == this->mLength.toInt()-1)
        {
            ui->textBrowser->append("<FFT by PC>");
            this->init = 0;
            qv_x.clear();
            qv_y.clear();
            Data.clear();
        }
    }
    else
    {
        ui->textBrowser->append(str0);
        ui->textBrowser->append(str1);
        ui->textBrowser->append(str2);
        if(this->cnt_index == this->mPoint.toInt()-1)
        {
            this->cnt_index = 0;
            this->xIndex++;
            this->yIndex=0;
        }
        else
        {
            if(this->cnt_index <= this->mPoint.toInt()/2)
            {
                X = pow(cos,2)+pow(sin,2);
                X = 10*log10(X);
                this->colorMap->data()->setCell(xIndex,yIndex,X);
                this->colorMap->rescaleDataRange();
                ui->qw_spec->rescaleAxes();
                ui->qw_spec->replot();
                ui->qw_spec->update();
            }
            this->cnt_index++;
            this->yIndex++;
        }
        if(this->cnt == this->mLength.toInt()-1) ui->textBrowser->append("<FFT by FPGA>");
    }
    if(this->cnt == this->mLength.toInt()-1) this->cnt = 0;
    else this->cnt++;
    if(this->cntfft == this->mPoint.toInt()-1) this->cntfft = 0;
    else this->cntfft++;
    QString Cmd_Str = "R"; // 0x52
    QByteArray Cmd = Cmd_Str.toLocal8Bit();
    QThread::msleep(1);
    this->m_SerialPort -> write(Cmd);
}

void MainWindow::set_datainfo()
{
    this->mRate = this->dataWindow->m_data->m_samplerate;
    this->mLength = this->dataWindow->m_data->m_samplelength;
    this->mPrecision = this->dataWindow->m_data->m_precision;
    this->mPoint = this->dataWindow->m_data->m_point;
    this->data = new double[this->mPoint.toInt()];
    this->data2 = new double[this->mPoint.toInt()];
    this->bf = new t_complex[this->mPoint.toInt()];
    QString str0 = "FFT point(#): ";
    QString str1 = "Sample Rate(Hz): ";
    QString str2 = "Sample Length(#): ";
    QString str3 = "Bit Precision: ";
    str0.append(this->mPoint);
    str1.append(this->mRate);
    str2.append(this->mLength);
    str3.append(this->mPrecision);
    ui->textBrowser->append("<Data Information>");
    ui->textBrowser->append(str0);
    ui->textBrowser->append(str1);
    ui->textBrowser->append(str2);
    ui->textBrowser->append(str3);
    int N = this->mPoint.toInt();
    int length = this->mLength.toInt();
    int Fs = this->mRate.toInt();
    int M = (length-N)/N;
    this->colorMap->data()->setSize(M+1,N/2+1);
    this->colorMap->data()->setRange(QCPRange(0,(double)length/Fs), QCPRange(0,(double)Fs/2));
    ui->qw_spec->rescaleAxes();
    ui->qw_spec->replot();
    this->colorMap2->data()->setSize(M+1,N/2+1);
    this->colorMap2->data()->setRange(QCPRange(0,(double)length/Fs),QCPRange(0,(double)Fs/2));
    ui->qw_spec_pc->rescaleAxes();
    ui->qw_spec_pc->replot();
    this->init = 1;
}

void MainWindow::set_setting()
{
    QString str1 = "Name: ";
    QString str2 = "BaurdRate: ";
    QString str3 = "DataBits: ";
    QString str4 = "Parity: ";
    QString str5 = "StopBits: ";
    QString str6 = "FlowControl: ";
    QString str7 = "LocalEchoEnabled: ";
    str1.append(this->settingWindow->m_UART->getName());
    str2.append(this->settingWindow->m_UART->getBaudRateStr());
    str3.append(this->settingWindow->m_UART->getDataBitsStr());
    str4.append(this->settingWindow->m_UART->getParityStr());
    str5.append(this->settingWindow->m_UART->getStopBitsStr());
    str6.append(this->settingWindow->m_UART->getFlowControlStr());
    str7.append(this->settingWindow->m_UART->getLocalEchoEnabled());
    ui->textBrowser->append("<UART Settings>");
    ui->textBrowser->append(str1);
    ui->textBrowser->append(str2);
    ui->textBrowser->append(str3);
    ui->textBrowser->append(str4);
    ui->textBrowser->append(str5);
    ui->textBrowser->append(str6);
    ui->textBrowser->append(str7);
}


