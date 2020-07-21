#ifndef MEMINFO_H
#define MEMINFO_H
#include<bits/stdc++.h>
#include "Utils.h"
using namespace std;
typedef long long ll;
class MEMinfo{
    ll totMem,avMem;//ke yong
public:
    ll getTotMem(){
        return totMem;
    }
    ll getAvMem(){
        return avMem;
    }
    MEMinfo(){

    }
    MEMinfo(string info){
        int cnt = 0;
        for(int i = 0;i < info.size();++i) {
            string s = "";
            while(i < info.size() && info[i] != '\n')s += info[i++];
            if(cnt == 0) calTotMem(s);
            if(cnt == 2) calAvMem(s);
            if(cnt >= 3) break;
            cnt++;
        }
    }
    ll getLLfromString(string &s,int p){
        ll meg=0;
        for(;p < s.size() && isdigit(s[p]); ++p) {
            meg = meg*10 + s[p]-'0';
        }return meg;
    }
    void calTotMem(string line){
        int enp = string("MemTotal:").size();

        while(line[enp] == ' '){
            enp++;
        }
        cout<<endl;
        totMem = getLLfromString(line,enp);
    }
    void calAvMem(string line){
    //    cout<<line<<endl;
        int enp = string("MemAvailable:").size();
        while(line[enp] == ' ') enp++;
        avMem = getLLfromString(line,enp);
    }

    static MEMinfo calMem(){
        return MEMinfo(Utils::getCmdResult(Utils::getShellMemCmd()));
    }
};

#endif // MEMINFO_H
