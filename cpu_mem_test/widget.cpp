#include "widget.h"
#include "ui_widget.h"

#include <QSplineSeries>
#include <QValueAxis>
#include <QDebug>

string const Widget:: DATA_FILE_NAME="cpuAndMemData.txt";
string const Widget:: DATA_DIR = "data";
Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget),log(QString::fromStdString(DATA_DIR+"/"+DATA_FILE_NAME))
{
    ui->setupUi(this);
    creatFile();
//    creatImg();
    timer = new QTimer(this);
    timer->start(500);
    connect(timer, SIGNAL(timeout()), this, SLOT(update()));
}


void Widget::update(){
    CPUInfo now;
    now.setInfo(Utils::getCmdResult(Utils::getLinuxCPUCmd()));
    now.cal();
    auto v = CPUInfo::calOneUsge(cpuInfoBefore,now);
    cpuInfoBefore = now;

    QVector<double> qv;
    qv.push_back(clock()/1000.0);
    for(auto &u:v) qv.push_back(u);

    log.write(qv);

    for(int i = 0;i < (int)v.size(); ++i) {
    //    cout<<"CPU "<<i<<":"<<v[i]<<",";
    }
//    cout<<endl;
}
void Widget::creatFile() {

    QString sAppPath = QCoreApplication::applicationDirPath();
    string filepath = sAppPath.toStdString() +"/"+ DATA_DIR+"/"+DATA_FILE_NAME;
    QDir dir(QString::fromStdString(sAppPath.toStdString()+"/"+DATA_DIR));
    if(!dir.exists()) {
        bool ok = dir.mkdir(QString::fromStdString(sAppPath.toStdString()+"/"+DATA_DIR));
    }
    QFile file(QString::fromStdString(filepath));
    file.open(QIODevice::WriteOnly);
    if(!file.exists()) {

    }
    file.close();
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

