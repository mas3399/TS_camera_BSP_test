#ifndef UTILS_H
#define UTILS_H
#include <string>
#include <iostream>
class Utils
{
public:
    Utils();
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
        return res;
    }
    static std::string getAndroidPhoneMemCmd(){
        return "adb shell \"cat /proc/meminfo \"";
    }
    static std::string getLinuxPCMemCmd(){
        return "cat /proc/meminfo";
    }

};

#endif // UTILS_H
