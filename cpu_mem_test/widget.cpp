#include "widget.h"
#include "ui_widget.h"

#include <QSplineSeries>
#include <QValueAxis>
#include <QDebug>
#include<time.h>
#include<QDateTime>
static const int MAX_WIN_TIME = 30;
static const int TIMER_C = 150;
static long long firstTime = 0;
string const Widget:: DATA_FILE_NAME="cpuAndMemData.txt";
string const Widget:: DATA_DIR = "data";

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget),log(QString::fromStdString(DATA_DIR+"/"+DATA_FILE_NAME))
{
    //
    firstTime = QDateTime::currentDateTime().toMSecsSinceEpoch();
    ui->setupUi(this);

    btstate = 0;
    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(update()));
    connect(ui->pushButton,&QPushButton::clicked,this,&Widget:: startAndStopButton);
    ui->pushButton->setStyleSheet ("background-color: rgb(220, 220, 220);");

    creatImg();
}

/**
 *
 * @brief Widget::update
 */
void Widget::update(){
    CPUInfo now;


    now.setInfo(Utils::getCmdResult(Utils::getLinuxCPUCmd()));
    now.cal();
    long long nowTime = QDateTime::currentDateTime().toMSecsSinceEpoch();
    auto v = CPUInfo::calOneUsge(cpuInfoBefore,now);
    cpuInfoBefore = now;
    QVector<double> qv;
    qv.push_back((nowTime-firstTime)/1000.0);
    for(auto &u:v) qv.push_back(u);
    log.write(qv);
    if(qv.size() >= 2)
    addCPUData(QPointF(0,qv.at(1)),(nowTime - preTime)/1000.0);
    preTime = nowTime;
//    addMEMData(QPointF(0,qv.at(1)),(nowTime-firstTime)/1000.0);

}

void Widget::startAndStopButton(){
    btstate ^= 1;
    if(btstate) {
        startButton();
    }else {
        stopButton();
    }
}
void Widget::startButton(){
    cout<<"start!\n";
    if(timer->isActive()) return ;
    CPUdata.clear();
    MEMdata.clear();
    ui->pushButton->setText("stop");
    ui->pushButton->setStyleSheet
            ("background-color: rgb(238, 99, 99);");
    timer->start(TIMER_C);
}


void Widget::stopButton(){
    cout<<"stop!\n";
    if(!timer->isActive()) return ;
    timer->stop();
    ui->pushButton->setStyleSheet
            ("background-color: rgb(220, 220, 220);");
    ui->pushButton->setText("start");
}

void Widget:: addCPUData(QPointF p,double offset){
    p.rx() = 0;
    cout<<offset<<" ";
    for(auto &u:CPUdata)  u.rx()+=offset;
    CPUdata.append(p);
    while(CPUdata.first().rx()>MAX_WIN_TIME) CPUdata.remove(0);
    cout<<CPUdata.size()<<endl;
    QSplineSeries * cpuLine = (QSplineSeries*)m_chart->series().first();
    cpuLine->replace(CPUdata);
}

void Widget:: addMEMData(QPointF p,double offset){
    p.rx() = 0;
    for(auto &u:MEMdata)  u.rx()+=offset;
    CPUdata.append(p);
    while(CPUdata.first().rx()>MAX_WIN_TIME) CPUdata.remove(0);
    QSplineSeries * cpuLine = (QSplineSeries*)m_chart->series().last();
    cpuLine->replace(MEMdata);
}

void Widget:: creatImg(){
    m_chart = new QChart();

    QSplineSeries *cpuLine = new QSplineSeries();//实例化一个QLineSeries对象
    QSplineSeries *memLine = new QSplineSeries();//实例化一个QLineSeries对象
    cpuLine->setName("cpu");
    cpuLine->setUseOpenGL(true);
    cpuLine->setColor(QColor(255,0,0));
    memLine->setName("memory");
    memLine->setUseOpenGL(true);
    m_chart->addSeries(cpuLine);
    m_chart->addSeries(memLine);

    QValueAxis *axisX = new QValueAxis;
    axisX->setRange(0,MAX_WIN_TIME);    //默认则坐标为动态计算大小的
   // axisX->setLabelFormat("%d S");
    QValueAxis *axisY = new QValueAxis;
    axisY->setRange(0,100);    //默认则坐标为动态计算大小的
    axisY->setTitleText("CPU");
    m_chart->setAxisX(axisX,cpuLine);
    m_chart->setAxisY(axisY,cpuLine);

    /*series1->setColor(QColor(0,100,255));
    series1->setName("cpu");

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
    axisX->setRange(0,60);    //默认则坐标为动态计算大小的
    axisX->setLabelFormat("%dS");
    QValueAxis *axisY = new QValueAxis;
    axisY->setRange(0,100);    //默认则坐标为动态计算大小的
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
    */
    QChartView *chartView = new QChartView(m_chart);
    chartView->setRenderHint(QPainter::Antialiasing);

    ui->verticalLayout->addWidget(chartView);
}
Widget::~Widget()
{
    delete ui;
}

