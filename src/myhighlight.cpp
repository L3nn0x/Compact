#include "myhighlight.h"

MyHighlight::MyHighlight(QTextDocument *document): QSyntaxHighlighter(document)
{
    QTextCharFormat entityFormat;
    entityFormat.setForeground(QColor(0, 0, 255));
    //entityFormat.setFontWeight(QFont::Bold);
    setFormatFor(Entity, entityFormat);

    QTextCharFormat RegFormat;
    RegFormat.setForeground(QColor(255, 0, 255));
    //RegFormat.setFontWeight(QFont::Bold);
    setFormatFor(Reg, RegFormat);

    QTextCharFormat BraFormat;
    BraFormat.setForeground(QColor(255, 0, 0));
    //BraFormat.setFontWeight(QFont::Bold);
    setFormatFor(Bra, BraFormat);

    QTextCharFormat NumberFormat;
    NumberFormat.setForeground(QColor(75,0,130));
    setFormatFor(Number,NumberFormat);

    QTextCharFormat LabelFormat;
    LabelFormat.setForeground(QColor(0,0,0));
    LabelFormat.setFontWeight(QFont::Bold);
    setFormatFor(Label,LabelFormat);

    QTextCharFormat commentFormat;
    commentFormat.setForeground(QColor(0, 128, 0));
    //commentFormat.setFontWeight(QFont::Bold);
    setFormatFor(Comment, commentFormat);
}

MyHighlight::~MyHighlight()
{
}

void MyHighlight::setFormatFor(Construct construct,const QTextCharFormat &format)
{
    m_formats[construct] = format;
    rehighlight();
}

void MyHighlight::highlightBlock(const QString &text)
{
    int state = previousBlockState();
    int len = text.length();
    int pos = 0;
    int start;
    QString tmp=text;
    tmp=tmp.toLower();

    switch(state)
    {
    case NormalState:
    default:
        while(pos<len)
        {
            QChar ch=tmp.at(pos);
            QString ch2="0";
            ch2[0]=ch;
            QString se=tmp.mid(pos,3);
            QString pop=tmp.mid(pos,4);
            QString ex=tmp.mid(pos,2);
            if(ch==';')
            {
                setFormat(pos,len-pos,m_formats[Comment]);
                break;
            }else if(ch=='['||ch==']')
            {
                setFormat(pos,1,m_formats[Bra]);
                pos++;
            }
            else if(ch==':')
            {
                start=pos;
                while(pos<len&&tmp.at(pos)!=' '&&tmp.at(pos++)!='\t');
                setFormat(start,pos-start,m_formats[Label]);
            }else if(_map_normal.contains((char*)se.constData())||
                     _map_special.contains((char*)se.constData()))
            {
                setFormat(pos,3,m_formats[Entity]);
                pos+=3;
            }else if(_map_regs.count((char*)ch2.constData())&&
                     (pos!=0&&(tmp.at(pos-1)==' '||tmp.at(pos-1)=='\t'
                               ||tmp.at(pos-1)=='['||tmp.at(pos-1)==',')))
            {
                setFormat(pos,1,m_formats[Reg]);
                pos++;
            }else if(_map_regs.count((char*)ex.constData()))
            {
                setFormat(pos,2,m_formats[Reg]);
                pos+=2;
            }else if(_map_regs.count((char*)se.constData()))
            {
                setFormat(pos,3,m_formats[Reg]);
                pos+=3;
            }else if(_map_regs.count((char*)pop.constData()))
            {
                setFormat(pos,4,m_formats[Reg]);
                pos+=4;
            }else if(ex=="0b"||ex=="0x"||ex=="0o")
            {
                setFormat(pos,2,m_formats[Number]);
                pos+=2;
            }else if(ch>='0'&&ch<='9')
            {
                setFormat(pos,1,m_formats[Number]);
                pos++;
            }else
            pos++;
        }
        break;
    }
    setCurrentBlockState(state);
}
