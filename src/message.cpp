#include "message.h"
#include "queue.h"
extern int max_count_prefix;
Message::Message(string buf)
{
    unparse_buf=buf;
    /*prefix=new string[max_count_prefix];
    value=new string[max_count_prefix];*/
    pair=new ValPref[max_count_prefix];
    real_size=0;
}
Message::Message(const Message &obj)
{
    unparse_buf=obj.unparse_buf;
    real_size=obj.real_size;
    /*prefix=new string[max_count_prefix];
    value=new string[max_count_prefix];*/
    pair=new ValPref[max_count_prefix];
    for (int i=0;i<real_size;i++)
    {
        pair[i].prefix=obj.pair[i].prefix;
        pair[i].value=obj.pair[i].value;
    }
}
IMessage* Message::Copy()
{
    IMessage* newmes=new Message(*this);
    return newmes;
}


void Message::ReplacePart(string _prefix,string _value)
{
    int flag=0;
    for(int i=0;i<real_size;i++)
    {
        if (pair[i].prefix==_prefix)
        {
            pair[i].value=_value;flag=1;
        }
    }
    if (flag==0)
        AddPart(_prefix,_value);
}


void Message::AddPart(string _prefix,string _value)
{
    pair[real_size].prefix=_prefix;
    pair[real_size].value=_value;
    real_size++;
}


string Message::GetPart(string prefix)
{
    for (int i=0;i<real_size;i++)
    {
        if (this->pair[i].prefix==prefix)
        {
            return this->pair[i].value;
        }
    }
    return "";
}


void Message::Parse()
{
    int i=0,j;
    string str;
    j=real_size;
    while (unparse_buf[i]!='#')
        i++;
    for(i;i<unparse_buf.length();i++)
    {
        if(unparse_buf[i]=='#')
        {
            continue;
        }
        while((unparse_buf[i]!='/')&&(unparse_buf[i]!='\0'))
        {
            pair[j].prefix=pair[j].prefix+unparse_buf[i];
            i++;
        }
        i++;
        while((unparse_buf[i]!='#')&&(unparse_buf[i]!='\0'))
        {
            pair[j].value=pair[j].value+unparse_buf[i];
            i++;
        }
        j++;
    }
    real_size=j;
}


string Message::Unparse()
{
    string str;
    for (int i=0;i<real_size;i++)
        str=str+'#'+pair[i].prefix+'/'+pair[i].value;
    return str;
}


Message::~Message()
{
    /*delete [] value;
    delete [] prefix;*/
    delete[] pair;
}
