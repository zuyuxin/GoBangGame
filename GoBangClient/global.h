#ifndef GLOBAL_H
#define GLOBAL_H
#include<QString>
class util
{
public:
    util(){};
    QString intToString(int num){
        QString res="";
        if(num==0)
            return "0";
        while(num){
            res.append(num%10+'0');
            num=num/10;
        }
        QString ret;
        int j=0;
        for(int i=res.size()-1;i>=0;i--)
            ret[j++]=res[i];

        return ret;
    }

};
#endif // GLOBAL_H
