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
#include "datalog.h"
#include <bits/stdc++.h>
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
    ~Widget();
public slots :
   void update();
private:
    Ui::Widget *ui;
    QTimer *timer;
    QSplineSeries *data;
    QChart *m_chart;
    CPUInfo cpuInfoBefore;
    datalog log;
    static const string DATA_FILE_NAME;
    static const string DATA_DIR;
};
#endif // WIDGET_H
