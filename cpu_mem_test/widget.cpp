#include "widget.h"
#include "ui_widget.h"

#include <QSplineSeries>
#include <QValueAxis>
#include <QDebug>
Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
    creatImg();
    timer = new QTimer(this);
    //timer->start(500);
    connect(timer, SIGNAL(timeout()), this, SLOT(update()));
}
void Widget::update(){
    static int x = 0;
    data->append(x++,qrand()%200);
    qDebug()<<x<<"\n";

    if(x >=20) {
        static int  index = 0;
        data->remove(index);
        m_chart->scroll(10,0);
    }
}
void Widget:: creatImg(){
    m_chart = new QChart();

    QSplineSeries *series1 = new QSplineSeries();//实例化一个QLineSeries对象
 //   series1->setColor(QColor(0,100,255));
//    series1->append(QPointF(0,qrand()%200)) ;
//    series1->append(QPointF(30,qrand()%200)) ;
//    series1->append(QPointF(60,qrand()%200)) ;
//    series1->append(QPointF(90,qrand()%200)) ;
//    series1->append(QPointF(120,qrand()%200)) ;
    series1->setName("线条1");

    data = series1;
   // series1->setVisible(true);
    series1->setPointLabelsFormat("(@xPoint,@yPoint)");
    series1->setPointLabelsVisible(true); //show point


//    m_chart->setTheme(QChart::ChartThemeLight);//设置白色主题
  //  m_chart->setDropShadowEnabled(true);//背景阴影    m_chart->setAutoFillBackground(true);  //设置背景自动填充
    m_chart->addSeries(series1);//添加系列到QChart上


  //  m_chart->setTitleBrush(QBrush(QColor(0,0,255)));//设置标题Brush
  //  m_chart->setTitleFont(QFont("微软雅黑"));//设置标题字体
    m_chart->setTitle("曲线图");
    //创建X轴和Y轴
    QValueAxis *axisX = new QValueAxis;
    axisX->setRange(0,22);    //默认则坐标为动态计算大小的
    axisX->setLabelFormat("%dS");
    QValueAxis *axisY = new QValueAxis;
    axisY->setRange(0,250);    //默认则坐标为动态计算大小的
    axisY->setTitleText("value值");

    m_chart->setAxisX(axisX,series1);
    m_chart->setAxisY(axisY,series1);
    //m_chart->createDefaultAxes();             //或者创建默认轴

    //修改说明样式
  //  m_chart->legend()->setVisible(true);
 //   m_chart->legend()->setAlignment(Qt::AlignBottom);//底部对齐
//    m_chart->legend()->setBackgroundVisible(true);//设置背景是否可视
 //   m_chart->legend()->setAutoFillBackground(true);//设置背景自动填充
  //  m_chart->legend()->setColor(QColor(222,233,251));//设置颜色
//    m_chart->legend()->setLabelColor(QColor(0,100,255));//设置标签颜色
   // m_chart->legend()->setMaximumHeight(50);
    QChartView *chartView = new QChartView(m_chart);
    chartView->setRenderHint(QPainter::Antialiasing);

    ui->verticalLayout->addWidget(chartView);
}
Widget::~Widget()
{
    delete ui;
}

