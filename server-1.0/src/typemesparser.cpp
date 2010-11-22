#include "typemesparser.h"
#include "iostream"
using namespace std;
QueTypeParser::QueTypeParser(int count)
{
	cout<<"construct"<<endl;
	max_count_que=count;
	count_que=0;
	prefix=new string*[max_count_que];
	que=new AQueue*[max_count_que];	
}
QueTypeParser::~QueTypeParser()
{
	delete[] prefix;
	delete[] que;
}
void QueTypeParser::AddPair(string* pref,AQueue* realque)
{
	if (count_que<max_count_que)
		{
			prefix[count_que]=pref;
			que[count_que]=realque;
			count_que++;
		}
}
/*AQueue* QueTypeParser::TypeParse(Message* msg)
{
	TypeParse
}*/
AQueue* QueTypeParser::TypeParse(string& buf)
{
	 if (buf.length()<1)
        return NULL;
	cout<<"LAST"<<buf<<endl;
    string val="#type/";
    size_t i=buf.find(val);
    size_t startpos=i+ val.length();
    i=startpos;
    while (i<buf.length())
    {
        if (buf[i]=='#')
            break;
        i++;
    }
	cout<<count_que<<endl;
	for(int i=0;i<count_que;i++)
	{
		cout<<*(prefix[i])<<endl;
	}
    string newstr=buf.substr(startpos,i-startpos);
    for(int i=0;i<count_que;i++)
	{
		if ((*(prefix[i]))==newstr)
			return que[i];
	}
    cout<<"BAG"<<endl;
    return NULL;
}
