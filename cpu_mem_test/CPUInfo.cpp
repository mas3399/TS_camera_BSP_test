#include<string>
#include<iostream>
#include<vector>
#include<sstream>
#include<QString>
#include<QDebug>
using namespace std;
typedef long long ll;
class CPUInfo{
public:

    CPUInfo(){
    }
    void setInfo(std::string info){
        this->info = info;
    }
    ll changeInt(string s){
        ll base = 0;
        for(auto i:s) {
            base = base*10 + i-'0';
        }
        return base;
    }
    double calOneCpu(string oneInfo){
        int p = -1;
        ll sum = 0, one4 = 0,index = 0;
        for(;p < oneInfo.size();) {
            int pre = p+1;
            p = oneInfo.find_first_of(" ",pre);
            ll xc = changeInt(oneInfo.substr(pre,p));
            sum += xc;
            if(index == 3) {
                one4 += xc;
            }
            index ++;
        }
        return 1-1.0*one4/sum;
    }
    vector<double> cal(){
        vector<double> v;
        if(info.size() == 0) return v;
        int pos = 0;
        for(;pos != info.size();) {
            int pre = pos;
            readLine(pos);
            double bisx = calOneCpu(info.substr(pre,pos));
            v.push_back(bisx);
            qDebug()<<bisx<<"\n";
        }
        return v;
    }

private:
    std::string info;

    string readLine(int &pos){
        string res = "";
        while(info[pos]!='\n')res += info[pos++];
        return res;
    }
};
