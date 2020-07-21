#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QChart>
#include <QChartView>
#include <QTimer>
#include <QVector>
#include <QSplineSeries>
#include "CPUInfo.h"
#include "Utils.h"
#include <QDir>
#include <QFile>
#include <qvalueaxis.h>
#include "datalog.h"
#include <bits/stdc++.h>
#include "MEMinfo.h"
QT_BEGIN_NAMESPACE
namespace Ui { class Widget; }
QT_END_NAMESPACE
using namespace QtCharts;
class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    void creatImg();
    void creatFile();
    void startButton();
    void addMEMData(QPointF p,double offset);
    void addCPUData(QPointF p,double offset);
    ~Widget();
public slots :
   void update();
   void startAndStopButton();
   void stopButton();
private:
    Ui::Widget *ui;
    QTimer *timer,*ctrTimer;
    QSplineSeries *data;
    QChart *m_chart;
    CPUInfo cpuInfoBefore;
    bool btstate;
    datalog log;
    long long preTime;
    QVector<QPointF> CPUdata,MEMdata;    static const string DATA_FILE_NAME;
    static const string DATA_DIR;
    QValueAxis *memY;
};
#endif // WIDGET_H
