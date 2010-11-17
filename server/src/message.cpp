#include "message.h"
#include "queue.h"
extern int max_count_prefix;	
MessageWithQue::MessageWithQue(string buf,AQueue* que):Message(buf)
{
    if (que!=NULL)
    {
        mes_que=que;
    }
    else
    {
        mes_que=TypeParse();
    }
}
MessageWithQue::MessageWithQue(const MessageWithQue &obj):Message(obj)
{
    mes_que=obj.mes_que;
}

IMessage* MessageWithQue::Copy()
{
    IMessage* newmes=new MessageWithQue(*this);
    return newmes;
}
Message::Message(string buf)
{
    unparse_buf=buf;
    prefix=new string[max_count_prefix];
    value=new string[max_count_prefix];
    real_size=0;
}
Message::Message(const Message &obj)
{
    unparse_buf=obj.unparse_buf;
    real_size=obj.real_size;
    prefix=new string[max_count_prefix];
    value=new string[max_count_prefix];
    for (int i=0;i<real_size;i++)
    {
        prefix[i]=obj.prefix[i];
        value[i]=obj.value[i];
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
        if (prefix[i]==_prefix)
        {
            value[i]=_value;flag=1;
        }
    }
    if (flag==0)
        AddPart(_prefix,_value);
}


void Message::AddPart(string _prefix,string _value)
{
    prefix[real_size]=_prefix;
    value[real_size]=_value;
    real_size++;
}


string Message::GetPart(string prefix)
{
    for (int i=0;i<real_size;i++)
    {
        if (this->prefix[i]==prefix)
        {
            return this->value[i];
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
            prefix[j]=prefix[j]+unparse_buf[i];
            i++;
        }
        i++;
        while((unparse_buf[i]!='#')&&(unparse_buf[i]!='\0'))
        {
            value[j]=value[j]+unparse_buf[i];
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
        str=str+'#'+prefix[i]+'/'+value[i];
    return str;
}


Message::~Message()
{
    delete [] value;
    delete [] prefix;
}


void MessageWithQue::Write()
{
    if (mes_que!=NULL)
    {
        mes_que->Write(this);
    }
}



AQueue* MessageWithQue::TypeParse()
{
    if (unparse_buf.length()<1)
        return NULL;

    string val="#type/";
    size_t i=unparse_buf.find(val);
    size_t startpos=i+ val.length();
    i=startpos;
    while (i<unparse_buf.length())
    {
        if (unparse_buf[i]=='#')
            break;
        i++;
    }
    string newstr=unparse_buf.substr(startpos,i-startpos);
    if (newstr=="send")
	{
	    return Send_que;
	}   
    if (newstr== "log")
        {
            return Log_que;           
        }
    if (newstr== "Notify")
        {
            return Conn_que;        
        }
 
    return NULL;
}
