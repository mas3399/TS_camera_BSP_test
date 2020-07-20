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
static int TIME_DEBUT = 3*1000;
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
    ctrTimer= new QTimer(this);
    ctrTimer->setSingleShot(true);
    connect(ctrTimer,SIGNAL(timeout()), this, SLOT(stopButton()));

    connect(ui->pushButton,&QPushButton::clicked,this,&Widget:: startAndStopButton);
    ui->pushButton->setStyleSheet ("background-color: rgb(220, 220, 220);");
    update();
    CPUdata.clear();
    MEMdata.clear();
    creatImg();
}

/**
 *
 * @brief Widget::update
 */
void Widget::update(){

    //cpu
    CPUInfo now;
    now.setInfo(Utils::getCmdResult(Utils::getLinuxCPUCmd()));
    now.cal();
    long long nowTime = QDateTime::currentDateTime().toMSecsSinceEpoch();
    auto v = CPUInfo::calOneUsge(cpuInfoBefore,now);
    cpuInfoBefore = now;

    //mem
    MEMinfo mem = MEMinfo :: calMem();

    //set on text
    QString totMem = "0",avMem = "0",totCPU = "0";
    totMem = QString::fromStdString(Utils::DoubleToString(mem.getTotMem()/1024.0/1024,1));
    avMem = QString::fromStdString(Utils::DoubleToString(mem.getAvMem()/1024.0,1));
    if(v.size() > 0) totCPU = QString::fromStdString(Utils::DoubleToString(v[0],1));
    ui->label->setText("Total memory: "+totMem +"GB");
    ui->label_2->setText("Available memory: "+avMem +"MB");
    ui->label_3->setText("Total CPU usage: "+totCPU+"%");

    //jia dao img
    QVector<double> qv;
    qv.push_back((nowTime-firstTime)/1000.0);
    for(auto &u:v) qv.push_back(u);
    if(qv.size() >= 2) {
        qv.append(mem.getTotMem());
        qv.append(mem.getAvMem());
        log.write(qv);
        addCPUData(QPointF(0,qv.at(1)),(nowTime - preTime)/1000.0);
        addMEMData(QPointF(0,qv.at(qv.size()-1)/1024.0),(nowTime-preTime)/1000.0);
    }
    preTime = nowTime;
}

void Widget::startAndStopButton(){
    if(!btstate) {
        startButton();
    }else {
        stopButton();
    }
}
void Widget::startButton(){
    cout<<"start!\n";

    if(timer->isActive()) return ;
    firstTime = QDateTime::currentDateTime().toMSecsSinceEpoch();
    log.open();
    ctrTimer->start(TIME_DEBUT);
    update();
    btstate ^= 1;
    CPUdata.clear();
    MEMdata.clear();
    ui->pushButton->setText("stop");
    ui->pushButton->setStyleSheet
            ("background-color: rgb(238, 99, 99);");
    timer->start(TIMER_C);
}


void Widget::stopButton(){
    if(!timer->isActive()) return ;
    cout<<"stop!\n";
    btstate ^= 1;
    if(ctrTimer->isActive()) {
        ctrTimer->stop();
    }
    timer->stop();
    ui->pushButton->setStyleSheet
            ("background-color: rgb(220, 220, 220);");
    ui->pushButton->setText("start");
    log.close();
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
    cout<<offset<<' '<<MEMdata.size()<<endl;
    for(auto &u:MEMdata)  u.rx()+=offset;
    MEMdata.append(p);
    while(MEMdata.first().rx()>MAX_WIN_TIME) MEMdata.remove(0);
    QSplineSeries * memLine = (QSplineSeries*)m_chart->series().last();
    memLine->replace(MEMdata);
}

void Widget:: creatImg(){
    m_chart = new QChart();

    m_chart->setDropShadowEnabled(true);

    QSplineSeries *cpuLine = new QSplineSeries();//实例化一个QLineSeries对象
    QSplineSeries *memLine = new QSplineSeries();//实例化一个QLineSeries对象
    cpuLine->setName("cpu");
    cpuLine->setUseOpenGL(true);
    cpuLine->setColor(QColor(255,0,0));
    memLine->setName("memory");
    memLine->setUseOpenGL(true);
    memLine->setColor(QColor(0,45,245));
    m_chart->addSeries(cpuLine);
    m_chart->addSeries(memLine);

    QValueAxis *axisX = new QValueAxis;
    axisX->setRange(0,MAX_WIN_TIME);    //默认则坐标为动态计算大小的
    axisX->setTickCount(5);
    axisX->setLinePenColor(QColor(0,0,0));
    // axisX->setLabelFormat("%d S");
    QValueAxis *axisY = new QValueAxis;
    axisY->setRange(0,100);    //默认则坐标为动态计算大小的
    axisY->setTitleText("CPU");
    axisY->setLinePenColor(cpuLine->pen().color());

    m_chart->addAxis(axisX,Qt::AlignBottom);
    m_chart->addAxis(axisY,Qt::AlignLeft);
    cpuLine->attachAxis(axisY);
    cpuLine->attachAxis(axisX);

    QValueAxis *y2 = new QValueAxis;
    y2->setRange(0,1000);
    y2->setTitleText("memory");
    y2->setLinePenColor(memLine->pen().color());
    m_chart->addAxis(y2,Qt::AlignRight);
    memLine->attachAxis(axisX);
    memLine->attachAxis(y2);


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

