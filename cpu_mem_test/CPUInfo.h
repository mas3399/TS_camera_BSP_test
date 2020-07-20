#include<string>
#include<iostream>
#include<vector>
#include<sstream>
#include<QString>
#include<QDebug>
#include<QThread>
#include "Utils.h"
using namespace std;
typedef long long ll;
class CPUInfo{
public:
    class OneCPU{
        public:
        ll totTime,freeTime;
        static double calOneCPU(OneCPU c1,OneCPU c2){
            if(c2.totTime == c1.totTime) return 0.0;
            if((c2.freeTime - c1.freeTime)/(c2.totTime - c1.totTime) < 0) {
         //       cout<<"MMP laji dongxi ~!~~~~~!!!!!!!!!!!!!!!!!!!!!!!!!!!!!\n";
            }
            return 1 - 1.0*(c2.freeTime - c1.freeTime)/(c2.totTime - c1.totTime);
        }

        OneCPU(){}
        ll changeInt(string s){
            ll base = 0;
            for(auto i:s) {
                base = base*10 + i-'0';
            }
            return base;
        }
        OneCPU(string oneInfo) {
            int p = -1;
            ll sum = 0, one4 = 0,index = 0;
            p = oneInfo.find_first_of(" ");
            while(oneInfo[p+1] == ' ') p++;
            for(;p < oneInfo.size();) {
                int pre = p+1;
                p = oneInfo.find_first_of(" ",pre);
                ll xc = changeInt(oneInfo.substr(pre,(p-pre)));
          //      qDebug()<<xc<<",";
                sum += xc;
                if(index == 3) {
                    one4 += xc;
                }
                index ++;
            }
            totTime = sum;
            freeTime = one4;
        }
    };

    static vector<double> calOneUsge(CPUInfo c1,CPUInfo c2){
        vector<double> res;
        if(c1.listCPU.size() != c2.listCPU.size()) return res;
        int sz = c1.listCPU.size();
        for(int i =0;i < sz; ++i) {
            res.push_back(100.0*OneCPU::calOneCPU(c1.listCPU[i],c2.listCPU[i]));
        }
        return res;
    }


    CPUInfo(){
    }
    void setInfo(std::string info){
        this->info = info;
    }

    void cal(){
        vector<double> v;
        if(info.size() == 0) return ;
        int pos = 0;
        for(;pos != info.size();) {
            int pre = pos;
            readLine(pos);
            listCPU.push_back(OneCPU(info.substr(pre,pos-pre)));
            pos++;
        }
    }

    string readLine(int &pos){
        string res = "";
        while(info[pos]!='\n')res += info[pos++];
        return res;
    }
    vector<OneCPU> listCPU;
private:
    std::string info;
};
