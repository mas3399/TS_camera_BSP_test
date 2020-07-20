#include "datalog.h"

#include <QCoreApplication>
#include <qdir.h>
const int datalog:: TIME_LEN_F = 10;
const int datalog:: CPU_LEN_F = 12;//8
const int datalog:: MEM_LEN_F = 12;//12
static const string DATA_DIR = "data";
static const string DATA_FILE_NAME = "cpuAndMemData.txt";
void creatFile() {

    QString sAppPath = QCoreApplication::applicationDirPath();
    string filepath = sAppPath.toStdString() +"/"+ DATA_DIR+"/"+DATA_FILE_NAME;
    QDir dir(QString::fromStdString(sAppPath.toStdString()+"/"+DATA_DIR));
    if(!dir.exists()) {
        bool ok = dir.mkdir(QString::fromStdString(sAppPath.toStdString()+"/"+DATA_DIR));
    }
    cout<<filepath<<endl;
    QFile file(QString::fromStdString(filepath));
    file.open(QIODevice::WriteOnly);
    if(!file.exists()) {

    }
    file.close();
}

void pushBlack(string &s,int num){
    for(;num > 0; --num) s.push_back(' ');
}
void pushTab(string &s){
    s.push_back('\t');
}

datalog::datalog(){
}


datalog::datalog(QString path):log(path){
    creatFile();
    bool ok= log.open(QIODevice::WriteOnly);
    cout<<ok<<endl;;
}
void datalog::open(){
    if(!log.isOpen()) log.open(QIODevice::WriteOnly);
}
void datalog::close(){
    if(log.isOpen()) log.close();
}

void datalog::printHead(int cpuNum){
    int nowLen = 0;
    string info = "Time";
    pushBlack(info,TIME_LEN_F - info.size());
    pushTab(info);
    nowLen = info.size();

    //CPU
    info += "CPU-AVG(%)";
    pushBlack(info,CPU_LEN_F-(info.size() - nowLen));
    pushTab(info);
    nowLen = info.size();

    for(int i = 0;i < cpuNum;++i) {
        info += "CPU"+to_string(i)+"(%)";
        pushBlack(info,CPU_LEN_F-(info.size() - nowLen));
        pushTab(info);
        nowLen = info.size();
    }

    // TODO 内存
    info += "TotMEM(kB)";
    pushBlack(info,(MEM_LEN_F-(info.size()-nowLen)));
    pushTab(info);
    nowLen = info.size();
    info += "Used-MEM(KB)";
    info +="\n";
    log.write(info.c_str());
    cout<<info<<endl;
}

void datalog::printOneData(QVector<double> &vb){
    int nowLen = 0,pos = 0,numCPU = vb.size()-4;
    string data = "";

    if(numCPU<=0) return ;
    if(log.size() == 0) {
        printHead(numCPU);
    }

    //TIME
    data += Utils::DoubleToString(vb.at(pos++),3);
    pushBlack(data,TIME_LEN_F-(data.size()-nowLen)),pushTab(data);
    nowLen = data.size();

    //CPU
    data += Utils::DoubleToString(vb.at(pos++),2);
    pushBlack(data,CPU_LEN_F-(data.size()-nowLen)),pushTab(data);
    nowLen = data.size();
    for(int i = 0;i < numCPU;++i) {
        data += Utils::DoubleToString(vb.at(pos++),2);
        pushBlack(data,CPU_LEN_F-(data.size()-nowLen)),pushTab(data);
        nowLen = data.size();
    }
    if(pos != vb.size()) {
        //MEM
        data += Utils::DoubleToString(vb.at(pos++),0);
        pushBlack(data,MEM_LEN_F-(data.size()-nowLen)),pushTab(data);
        nowLen = data.size();
        data += Utils::DoubleToString(vb.at(pos++),0);
        nowLen = data.size();
    }
    if(data.size()) {
        data+="\n";
        log.write(data.c_str());
        log.flush();
        cout<<data<<endl;
    }
}

void datalog::write(QVector<double> &v){
    printOneData(v);
}

datalog::~datalog(){
    log.close();
}

