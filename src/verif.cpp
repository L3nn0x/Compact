#include "verif.h"

using namespace std;

verif::verif(vector<string> &a,QMap<string,string> &e):_code(a),_map_conf(e)
{}

bool verif::verification()
{
    for(vector<string>::iterator it=_code.begin();it!=_code.end();++it)
    {
        if(_map_normal.count(*it))
        {
            bool addr=false;
            bool add=false;
            for(int i=2;i!=0;--i)
            {
                ++it;
                if(it==_code.end())
                    return false;
                if(*it=="[")
                {
                    addr=true;
                    i+=2;
                }else if(*it=="+"||*it=="-")
                {
                    add=true;
                    i+=2;
                }else if(*it=="")
                    return false;
                else if(*it=="]"&&!addr)
                    return false;
            }
            ++it;
            if(it==_code.end())
                break;
            if(!_map_normal.count(*it)&&!_map_special.count(*it)&&(*it).substr(0,1)!=":")
                return false;
            --it;
        }else if(_map_special.count(*it))
        {
            bool addr=false;
            bool add=false;
            for(int i=1;i!=0;--i)
            {
                ++it;
                if(it==_code.end())
                    return false;
                if(*it=="[")
                {
                    addr=true;
                    i+=2;
                }else if(*it=="+"||*it=="-")
                {
                    add=true;
                    i+=2;
                }else if(*it=="")
                    return false;
                else if(*it=="]"&&!addr)
                    return false;
            }
            ++it;
            if(it==_code.end())
                break;
            if(!_map_normal.count(*it)&&!_map_special.count(*it)&&(*it).substr(0,1)!=":")
                return false;
            --it;
        }else if((*it).substr(0,1)!=":")
            return false;
    }
    return true;
}

vector<string> verif::correction()
{
    vector<string> a;
    for(vector<string>::iterator it=_code.begin();it!=_code.end();++it)
    {
        if(_map_normal.count(*it))
        {
            a.push_back(*it);
            bool addr=false;
            bool add=false;
            for(int i=2;i!=0;--i)
            {
                ++it;
                if(it==_code.end())
                    return a;
                if(*it=="[")
                {
                    addr=true;
                    i+=2;
                }else if(*it=="+"||*it=="-")
                {
                    add=true;
                    i+=2;
                }else if(*it=="")
                    a.push_back("a");
                if(*it!="")
                    a.push_back(*it);
                if(addr&&(i==2)&&*it!="]")
                    a.push_back("]");
                else if(addr&&add&&(i==2)&&*it!="]")
                    a.push_back("]");
            }
        }else if(_map_special.count(*it))
        {
            a.push_back(*it);
            bool addr=false;
            bool add=false;
            for(int i=1;i!=0;--i)
            {
                ++it;
                if(it==_code.end())
                    return a;
                if(*it=="[")
                {
                    addr=true;
                    i+=2;
                }else if(*it=="+"||*it=="-")
                {
                    add=true;
                    i+=2;
                }else if(*it=="")
                    a.push_back("a");
                if(addr&&(i==2||i==1)&&*it!="]")
                    a.push_back("]");
                else if(addr&&add&&(i==2||i==1)&&*it!="]")
                    a.push_back("]");
                a.push_back(*it);
            }
        }else if((*it).substr(0,1)!=":")
            return a;
        a.push_back(*it);
    }
    return a;
}
