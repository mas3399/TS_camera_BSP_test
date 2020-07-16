#include<string>
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
        return "cat /proc/stat";
    }
    static std::string getShellCPUCmd(){
        return "adb shell \"cat /proc/stat \"";
    }
};
