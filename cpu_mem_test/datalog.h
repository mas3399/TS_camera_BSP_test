#ifndef DATALOG_H
#define DATALOG_H
#include <QFile>
#include <utility>
#include <bits/stdc++.h>
#include <Utils.h>
#include <QVector>
using namespace std;
class datalog
{
public:
    datalog();
    datalog(QString path);
    void write(QVector<double> &v);
    void printOneData(QVector<double> &vb);
    void printHead(int x);
    void open();
    void close();
    ~datalog();
private:
    QFile log;
    static const int TIME_LEN_F;//10
    static const int CPU_LEN_F;//8
    static const int MEM_LEN_F;//8
};

#endif // DATALOG_H
