#include "compilo.h"

using namespace std;

C::~C()
{
    while(_phrases!=0)
    {
        sentence *tmp=_phrases->next;
        delete _phrases;
        _phrases=tmp;
    }
}

C::C(string a):_phrases(0)
{
    if(a=="no file")
        return;

    ifstream file(a.c_str());
    string tmp;

    while(getline(file,tmp))
    {
        c_tok tok(tmp,boost::char_separator<char>(" "));
        c_tok::iterator it2=tok.begin();
        for(c_tok::iterator it=tok.begin();it!=tok.end();++it)
            _map_conf[*it2]=*it;
            ++it2;
    }
}

void C::compilation(const string &a,const string &b)
{
    _codeH.clear();
    while(_phrases!=0)
    {
        sentence *tmp=_phrases->next;
        delete _phrases;
        _phrases=tmp;
    }
    lectureF(a); //on lit le fichier d'entree
    couper(); //on decoupe les phrases en mots
    /*verif test(_coupe,maps::_map_normal,maps::_map_special,maps::_map_regs,_map_conf); //on verifie la syntaxe
    if(test.verification())
        cout<<"code OK";
    else
    {
        cout<<"erreur code !"<<endl;
        vector<string> a=test.correction(); //on tente une correction automatique
        for(unsigned int i=0;i<a.size();++i)
            cout<<a[i]<<" ";
        return;
    }*/
    labels();
    compiler();//on compile
    recoller(); //on regoupe tout
    ecrireF(b); //on ecrit la sortie
}

void C::lectureF(const string &a)
{
    ifstream file(a.c_str());
    string tmp;
    while(getline(file,tmp))
    {
        if(!_phrases)
        {
            _phrases=new struct sentence;
            _phrases->before=tmp;
            _phrases->next=0;
            _phrases->nbmots=0;
            _phrases->dat=false;
        }else
        {
            sentence *tmp2=_phrases;
            while(tmp2->next!=0)
                tmp2=tmp2->next;
            sentence* a=new struct sentence;
            a->before=tmp;
            a->next=0;
            a->nbmots=0;
            a->dat=false;
            tmp2->next=a;
        }
    }
}

void C::couper()
{
    sentence* ph2=_phrases;
    for(sentence* ph=_phrases; ph!=0;ph=ph->next)
    {
        size_t c=(ph->before).find_first_of(';');
        if(c||c==(ph->before).npos)
        {
            string d=(ph->before).substr(0,c);
            transform(d.begin(),d.end(),d.begin(),my_tolower());
            int tmp=0;
            while(d[tmp]==' '||d[tmp]=='\t')
                tmp++;
            c_tok tok2(d,boost::char_separator<char>(" ,\t+-"));
            for(c_tok::iterator jt=tok2.begin();jt!=tok2.end();++jt)
            {
                if((*jt)[0]=='[')
                {
                    (ph->coupe).push_back("[");
                    if((*jt)[(*jt).size()-1]==']')
                    {
                        (ph->coupe).push_back((*jt).substr(1,(*jt).size()-2));
                        (ph->coupe).push_back("]");
                    }else
                    {
                        (ph->coupe).push_back((*jt).substr(1));
                        if(d[tmp+(*jt).size()]=='+')
                            (ph->coupe).push_back("+");
                        else if(d[tmp+(*jt).size()]=='-')
                            (ph->coupe).push_back("-");
                    }
                }else if((*jt)[(*jt).size()-1]==']')
                {
                    (ph->coupe).push_back((*jt).substr(0,(*jt).size()-1));
                    (ph->coupe).push_back("]");
                }else if((*jt).find_first_of('\"')!=(*jt).npos)
                {
                    unsigned int i=(*jt).find_first_of('\"');
                    ph->coupe.push_back((*jt).substr(0,i));
                    for(;i<(*jt).size();)
                    {
                        unsigned int j=(*jt).find_first_of('\"',i+1);
                        if((*jt)[i]=='\"')
                        {
                            i++;
                            while(i!=(*jt).size()&&(*jt)[i]!='\"')
                            {
                                 ph->coupe.push_back(string(1,(*jt)[i]));
                                 i++;
                            }
                        }else
                            ph->coupe.push_back((*jt).substr(i,j));
                    }
                }else
                    (ph->coupe).push_back(*jt);
                tmp+=(*jt).size()+1;
            }
        }else if(ph!=_phrases)
        {
            ph2->next=ph->next;
            delete ph;
            ph=ph2;
        }else
        {
            _phrases=ph->next;
            delete ph;
            ph=_phrases;
        }
        ph2=ph;
    }
}

void C::labels()
{
    sentence* tmp=_phrases;
    int i=0;
    while(tmp!=0)
    {
        if(tmp->coupe[0]=="dat")
        {
            for(vector<string>::iterator it=tmp->coupe.begin()+2;it!=tmp->coupe.end();++it)
            {
                tmp->hex.push_back(nombre(*it));
                tmp->nbmots++;
            }
            tmp->dat=true;
        }else if((tmp->coupe[0]).substr(0,1)==":"||(tmp->coupe[0]).substr(0,1)==".")
        {
            tmp->islabel=true;
            tmp->label=tmp->coupe[0];
            _map_labels[(tmp->coupe[0]).substr(1,(tmp->coupe[0]).size())]=i;
            if(tmp->coupe.size()>3&&tmp->coupe[1]=="dat")
                for(vector<string>::iterator it=tmp->coupe.begin()+2;it!=tmp->coupe.end();++it)
                {
                    tmp->hex.push_back(nombre(*it));
                    tmp->nbmots++;
                }
        }else
        {
            tmp->islabel=false;
            tmp->nbmots++;
            if(tmp->coupe[1]=="["&&(!maps::_map_regs.count(tmp->coupe[2])||tmp->coupe[3]=="+"))
                tmp->nbmots++;
            else if(!maps::_map_regs.count(tmp->coupe[1])&&nombre(tmp->coupe[1])>30&&nombre(tmp->coupe[1])<0)
                tmp->nbmots++;
            if(maps::_map_normal.count(tmp->coupe[0]))
            {
                int b=2;
                if(tmp->coupe[1]=="[")
                    b+=2;
                if(tmp->coupe[1]=="["&&tmp->coupe[3]=="+")
                    b+=2;
                if(tmp->coupe[b]=="["&&(!maps::_map_regs.count(tmp->coupe[b+1])||tmp->coupe[b+2]=="+"))
                    tmp->nbmots++;
                else if(!maps::_map_regs.count(tmp->coupe[b])&&(nombre(tmp->coupe[b])>30||nombre(tmp->coupe[b])<0)
                        &&(_map_labels.count(tmp->coupe[b])&&getlabel(_map_labels[tmp->coupe[b]])>30))
                    tmp->nbmots++;
            }

        }
        tmp=tmp->next;
        i++;
    }
}

void C::compiler()
{
    struct sentence *tmp;

    for(tmp=_phrases;tmp!=0;tmp=tmp->next)
    {
        if(tmp->islabel)
            continue;
        if(maps::_map_normal.count(tmp->coupe[0]))
            opcode_normal(tmp);
        if(maps::maps::_map_special.count(tmp->coupe[0]))
            opcode_special(tmp);
    }
}

int C::getlabel(int a)
{
    struct sentence* tmp=_phrases;
    int i=0;
    while(a!=0)
    {
        i+=tmp->nbmots;
        tmp=tmp->next;
        if(!tmp)
            return -1;
        a--;
    }
    return i;
}

void C::opcode_special(struct sentence* a)
{
    int tmp=maps::_map_special[a->coupe[0]]<<5;
    int tmp2=0;
    if(a->coupe[1]=="[")
    {
        tmp|=(adresse(a->coupe,&tmp2,false)<<5); //c'est une adresse
        a->hex.push_back(tmp);
        if(tmp2)
        {
            a->hex.push_back(tmp2);
        }
        return;
    }else if(maps::_map_regs.count(a->coupe[1]))
    {
        tmp|=(maps::_map_regs[a->coupe[1]])<<10; //c'est un registre
        a->hex.push_back(tmp);
        return;
    }
    else
    {
        if(_map_labels.count(a->coupe[1])) //c'est un label
            tmp2=getlabel(_map_labels[a->coupe[1]]);
        else //c'est un nombre en hexa/autre
            tmp2=nombre(a->coupe[1]);
        if(tmp2<31&&tmp2>=0) //si le nombre est en dessous de 31
        {
            for(int j=-1,k=0x20;j<=30;j++,k++)
                if(tmp2==j)
                {
                    tmp|=k<<10;
                    break;
                }
            a->hex.push_back(tmp);
        }else
        {
            tmp|=(0x1f)<<10;
            a->hex.push_back(tmp);
            a->hex.push_back(tmp2);
        }
    }
}
void C::opcode_normal(struct sentence* a)
{
    int tmp=maps::_map_normal[a->coupe[0]];
    int j=0;
    bool second=false;
    bool third=false;
    for(int i=0;i!=2;i++)
    {
        int tmp2=0;
        if(a->coupe[1+j]=="[")
        {
            tmp|=adresse(a->coupe,&tmp2,!j?false:true); //c'est une adresse
            if(tmp2)
            {
                a->hex.push_back(tmp2);
                if((unsigned int)j+3<a->coupe.size()&&a->coupe[3+j]=="+")
                    j+=2;
                !second?second=true:third=true;
            }
            j+=3;
            continue;
        }else if(maps::_map_regs.count(a->coupe[1+j]))
            tmp|=(maps::_map_regs[a->coupe[1+j]])<<(5+(!i?0:5)); //c'est un registre
        else
        {
            if(_map_labels.count(a->coupe[1+j])) //c'est un label
                tmp2=getlabel(_map_labels[a->coupe[1+j]]);
            else //c'est un nombre en hexa/autre
                tmp2=nombre(a->coupe[1+j]);
            if(tmp2<31&&tmp2>=0&&j) //si le nombre est en dessous de 31
            {
                for(int j=-1,k=0x20;j<=30;j++,k++)
                    if(tmp2==j)
                    {
                        tmp|=k<<(10-(!i?5:0));
                        break;
                    }
            }else
            {
                tmp|=(0x1f)<<(10-(!i?5:0));
                a->hex.push_back(tmp2);
                !second?second=true:third=true;
            }
        }
        j++;
    }
    if(!second&&!third)
        a->hex.push_back(tmp);
    else if(!third)
    {
        int tmp2=a->hex[a->hex.size()-1];
        a->hex[a->hex.size()-1]=tmp;
        a->hex.push_back(tmp2);
    }else
    {
        int tmp2=a->hex[a->hex.size()-1];
        int tmp3=a->hex[a->hex.size()-2];
        a->hex[a->hex.size()-2]=tmp;
        a->hex[a->hex.size()-1]=tmp3;
        a->hex.push_back(tmp2);
    }
}

int C::nombre(string &it)
{
    int tmp2;
    istringstream iss(it);
    if((it).find("0x")!=(it).npos)
        iss>>hex>>tmp2;
    else if((it).find("0o")!=(it).npos)
        iss>>oct>>tmp2;
    else
        iss>>dec>>tmp2;
    return tmp2;
}

int C::adresse(vector<string> &a,int* tmp2,bool second)
{
    int tmp=0;
    *tmp2=0;
    vector<string>::iterator it=a.begin();
    ++it;
    ++it;
    if(second)
    {
        ++it;
        if(*it=="+")
            it+=2;
        it+=2;
    }

    if(*it=="a"&&*(it+1)=="]") //[a]
        tmp|=(0x08)<<(5+5*second);
    else if(*it=="b"&&*(it+1)=="]") //[b]
        tmp|=(0x09)<<(5+5*second);
    else if(*it=="c"&&*(it+1)=="]") //[c]
        tmp|=(0x0a)<<(5+5*second);
    else if(*it=="x"&&*(it+1)=="]") //[x]
        tmp|=(0x0b)<<(5+5*second);
    else if(*it=="y"&&*(it+1)=="]") //[y]
        tmp|=(0x0c)<<(5+5*second);
    else if(*it=="z"&&*(it+1)=="]") //[z]
        tmp|=(0x0d)<<(5+5*second);
    else if(*it=="i"&&*(it+1)=="]") //[i]
        tmp|=(0x0e)<<(5+5*second);
    else if(*it=="j"&&*(it+1)=="]") //[j]
        tmp|=(0x0f)<<(5+5*second);
    else if(*(it+1)=="+")
    {
        if(*it=="a"||*(it+2)=="a") //[a+next]
        {
            tmp|=(0x10)<<(5+5*second);
            if(*it=="a")
                it+=2;
            *tmp2=nombre(*it);
            if(*it!="a")
                it+=2;
        }else if(*it=="b"||*(it+2)=="b") //[b+next]
        {
            tmp|=(0x11)<<(5+5*second);
            if(*it=="b")
                it+=2;
            *tmp2=nombre(*it);
            if(*it!="b")
                it+=2;
        }else if(*it=="c"||*(it+2)=="c") //[c+next]
        {
            tmp|=(0x12)<<(5+5*second);
            if(*it=="c")
                it+=2;
            *tmp2=nombre(*it);
            if(*it!="c")
                it+=2;
        }else if(*it=="x"||*(it+2)=="x") //[x+next]
        {
            tmp|=(0x13)<<(5+5*second);
            if(*it=="x")
                it+=2;
            *tmp2=nombre(*it);
            if(*it!="x")
                it+=2;
        }else if(*it=="y"||*(it+2)=="y") //[y+next]
        {
            tmp|=(0x14)<<(5+5*second);
            if(*it=="y")
                it+=2;
            *tmp2=nombre(*it);
            if(*it!="y")
                it+=2;
        }else if(*it=="z"||*(it+2)=="z") //[z+next]
        {
            tmp|=(0x15)<<(5+5*second);
            if(*it=="z")
                it+=2;
            *tmp2=nombre(*it);
            if(*it!="z")
                it+=2;
        }else if(*it=="i"||*(it+2)=="i") //[i+next]
        {
            tmp|=(0x16)<<(5+5*second);
            if(*it=="i")
                it+=2;
            *tmp2=nombre(*it);
            if(*it!="i")
                it+=2;
        }else if(*it=="j"||*(it+2)=="j") //[j+next]
        {
            tmp|=(0x17)<<(5+5*second);
            if(*it=="j")
                it+=2;
            *tmp2=nombre(*it);
            if(*it!="j")
                it+=2;
        }
    }else
    {
        tmp|=(0x1e)<<(5+5*second);
        *tmp2=nombre(*it);
    }
    return tmp;
}

void C::recoller()
{
    ostringstream oss;
    for(struct sentence* a=_phrases;a!=0;a=a->next)
    {
        for(vector<int>::iterator it=a->hex.begin();it!=a->hex.end();++it)
        {
            oss<<hex<<*it;
            oss<<" ";
        }
    }
    _codeH=oss.str();
}

void C::ecrireF(const string &a)
{
    ofstream file(a.c_str());
    file<<_codeH;
}

string C::compilation(const string &a)
{
    _codeH.clear();
    while(_phrases!=0)
    {
        sentence *tmp=_phrases->next;
        delete _phrases;
        _phrases=tmp;
    }
    int i=0;
    while(a.find('\n',i)!=a.npos)
    {
        string tmp;
        int j;
        for(j=i;(unsigned int)j<a.find('\n',i);j++)
            tmp.push_back(a[j]);
        i=j+1;
        if(tmp.empty())
            continue;
        if(!_phrases)
        {
            _phrases=new struct sentence;
            _phrases->before=tmp;
            _phrases->next=0;
            _phrases->nbmots=0;
            _phrases->dat=false;
        }else
        {
            sentence *tmp2=_phrases;
            while(tmp2->next!=0)
                tmp2=tmp2->next;
            sentence* b=new struct sentence;
            b->before=tmp;
            b->next=0;
            b->nbmots=0;
            b->dat=false;
            tmp2->next=b;
        }
    }
    couper(); //on decoupe les phrases en mots
    labels();
    compiler();//on compile
    recoller(); //on regoupe tout
    return _codeH;
}

void C::deplaceLabels()
{
    sentence *tmp=_phrases;
    while(tmp)
    {
        if(!tmp->dat)
        {
            if(!tmp->islabel&&tmp->nbmots>2)
            {
               if(_map_labels.count(tmp->coupe[2]))
                   if(getlabel(_map_labels[tmp->coupe[2]])<30||
                          getlabel(_map_labels[tmp->coupe[2]])<31)
                        tmp->nbmots--;
            }else if(!tmp->islabel&&tmp->nbmots>1)
            {
                1;  /* WTF */
            }
        }
        tmp=tmp->next;

    }
}
