#include "qdatainfo.h"
#include "ui_qdatainfo.h"

qDatainfo::qDatainfo(QWidget *parent)
    : QDialog(parent)
    , m_data(new data_setting), ui(new Ui::qDatainfo)
{
    ui->setupUi(this);
    setWindowTitle(tr("DataInfo"));

    this->setDefaultSetting();
    this->updateSetting();
}

qDatainfo::~qDatainfo()
{
    delete ui;
}

data_setting qDatainfo::getdata()
{
    return *this->m_data;
}


void qDatainfo::on_pb_continue_clicked()
{
    this->updateSetting();
    //qDebug() << "Data Information";
    //qDebug() << "Sample Rate: " << this->m_data->getRate();
    //qDebug() << "Sample Length: " << this->m_data->getLength();
    //qDebug() << "Bit Precision: " << this->m_data->getPrecision();
    applied_data();
    hide();
    return ;
}

void qDatainfo::setDefaultSetting()
{
    ui->cb_rate->setCurrentIndex(0);
    ui->cb_precision->setCurrentText(0);
    ui->cb_point->setCurrentText(0);
    ui->line_length->setText("");
}

void qDatainfo::updateSetting()
{
    this->m_data->set_samplerate(ui->cb_rate->currentText());
    this->m_data->set_precision(ui->cb_precision->currentText());
    this->m_data->set_precision(ui->cb_point->currentText());
    this->m_data->set_samplelength(ui->line_length->text());
}
