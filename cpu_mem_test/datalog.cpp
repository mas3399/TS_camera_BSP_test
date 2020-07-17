#include "datalog.h"
const int datalog:: TIME_LEN_F = 10;
const int datalog:: CPU_LEN_F = 8;//8
const int datalog:: MEM_LEN_F = 8;//8



void pushBlack(string &s,int num){
    for(;num > 0; --num) s.push_back(' ');
}
void pushTab(string &s){
    s.push_back('\t');
}

datalog::datalog(){
}


datalog::datalog(QString path):log(path){
   bool ok= log.open(QIODevice::WriteOnly);
   cout<<ok<<endl;;

}

void datalog::printHead(int cpuNum){
    int nowLen = 0;
    string info = "Time";
    pushBlack(info,TIME_LEN_F - info.size());
    pushTab(info);
    nowLen = info.size();

    //CPU
    info += "CPU AVG";
    pushBlack(info,CPU_LEN_F-(info.size() - nowLen));
    pushTab(info);
    nowLen = info.size();

    for(int i = 0;i < cpuNum;++i) {
        info += "CPU"+to_string(i);
        pushBlack(info,CPU_LEN_F-(info.size() - nowLen));
        pushTab(info);
        nowLen = info.size();
    }

    // TODO 内存
    info += "Tot MEM";
    pushBlack(info,(MEM_LEN_F-(info.size()-nowLen)));
    pushTab(info);
    nowLen = info.size();
    info += "Used MEM";
    pushBlack(info,(MEM_LEN_F-(info.size()-nowLen)));
    pushTab(info);
    nowLen = info.size();

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
    data += Utils::DoubleToString(vb.at(pos++),2);
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
    if(pos == vb.size()) return;

    //MEM
    data += Utils::DoubleToString(vb.at(pos++),2);
    pushBlack(data,MEM_LEN_F-(data.size()-nowLen)),pushTab(data);
    nowLen = data.size();
    data += Utils::DoubleToString(vb.at(pos++),2);
    pushBlack(data,MEM_LEN_F-(data.size()-nowLen));
    nowLen = data.size();

    log.write(data.c_str());
    log.flush();
    cout<<data<<endl;
}

void datalog::write(QVector<double> &v){
     printOneData(v);
}

datalog::~datalog(){
    log.close();
}

