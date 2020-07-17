#ifndef UTILS_H
#define UTILS_H
#include<string>
#include <bits/stdc++.h>


class Utils
{
public:
    Utils(){}
    static std::string getCmdResult(const std::string &cmd){
        if(cmd.size()==0) return "";
        FILE *fft = nullptr;
        //std::cout<<"open start!\n";
        if((fft = popen(cmd.c_str(),"r"))==nullptr){
            return "";
        }
        //std::cout<<"open end!\n";
        char buff[4096];
        std::string res = "";
        while(fgets(buff,sizeof(buff),fft)) {
            res += buff;
        }
        pclose(fft);
        return res;
    }
    static std::string preAdbRootCmd(){
        return "adb root && adb remount";
    }
    static std::string getShellMemCmd(){
        return "adb shell \"cat /proc/meminfo \"";
    }
    static std::string getLinuxMemCmd(){
        return "cat /proc/meminfo";
    }
    static std::string getLinuxCPUCmd(){
        return "cat /proc/stat | grep \"cpu\"";
    }
    static std::string getShellCPUCmd(){
        return "adb shell \"cat /proc/stat \"";
    }

    static std::string DoubleToString(const double value, unsigned int precisionAfterPoint)
    {
        std::ostringstream out;
        // 清除默认精度
        out.precision(std::numeric_limits<double>::digits10);
        out << value;

        std::string res = std::move(out.str());
        auto pos = res.find('.');
        if (pos == std::string::npos)
            return res+".00";

        auto splitLen = pos + 1 + precisionAfterPoint;
        if (res.size() <= splitLen)
            return res;
        res = res.substr(0,splitLen);
        //std::cout<<res<<std::endl;
        return res;
    }
};
#endif
