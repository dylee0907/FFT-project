#ifndef DATA_H
#define DATA_H

#include <QString>

class data_setting{
private:


public:
    data_setting(QString t_samplerate="8000", QString t_samplelength="81921", QString t_precision="8bit", QString t_point = "32"); //Constructor
    virtual ~data_setting(); //Destructor

    /*
     * get & set Method
    */

    QString m_samplerate;
    QString m_samplelength;
    QString m_precision;
    QString m_point;

    QString getRate() const;
    QString getPrecision() const;
    QString getLength() const;
    QString getPoint() const;

    void set_samplerate(QString t_samplerate = "8000");
    void set_samplelength(QString t_samplelength = "81921");
    void set_precision(QString t_precision = "8bit");
    void set_point(QString t_point = "32");
};

#endif // DATA_H
