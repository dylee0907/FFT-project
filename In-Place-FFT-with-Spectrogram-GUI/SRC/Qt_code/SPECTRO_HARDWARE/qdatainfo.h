#ifndef QDATAINFO_H
#define QDATAINFO_H

#include <QDialog>
#include <QDebug>
#include "data.h"

QT_BEGIN_NAMESPACE
namespace Ui { class qDatainfo; }
QT_END_NAMESPACE

class qDatainfo : public QDialog
{
    Q_OBJECT

public:
    qDatainfo(QWidget *parent = nullptr);
    ~qDatainfo();
    data_setting *m_data;
    // get mothod
    data_setting getdata();
signals:
    void applied_data();
private slots:
    void on_pb_continue_clicked();
    void setDefaultSetting();
    void updateSetting();

private:
    Ui::qDatainfo *ui;


};
#endif // QDATAINFO_H
