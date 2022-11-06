#include "data.h"

data_setting::data_setting(QString t_samplerate, QString t_samplelength, QString t_precision, QString t_point)
{
    this->set_samplerate(t_samplerate);
    this->set_samplelength(t_samplelength);
    this->set_precision(t_precision);
    this->set_point(t_point);
}

data_setting::~data_setting(){}

QString data_setting::getRate() const
{
    return this->m_samplerate;
}

QString data_setting::getPrecision() const
{
    return this->m_precision;
}

QString data_setting::getLength() const
{
    return this->m_samplelength;
}

QString data_setting::getPoint() const
{
    return this->m_point;
}

void data_setting::set_samplerate(QString t_samplerate)
{
    this->m_samplerate = t_samplerate;
}

void data_setting::set_samplelength(QString t_samplelength)
{
    this->m_samplelength = t_samplelength;
}

void data_setting::set_precision(QString t_precision)
{
    this->m_precision = t_precision;
}
void data_setting::set_point(QString t_point)
{
    this->m_point = t_point;
}
