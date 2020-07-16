#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QChart>
#include <QChartView>
#include <QTimer>
#include <QSplineSeries>
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
    ~Widget();
public slots :
   void update();
private:
    Ui::Widget *ui;
    QTimer *timer;
    QSplineSeries *data;
    QChart *m_chart;
};
#endif // WIDGET_H
