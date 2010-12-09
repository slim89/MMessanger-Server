#include "activeclients.h"
ActiveClients::ActiveClients()
{
	int i;
	for(i=0;i<size_socket_array; i++)
	{
		sockPair[i].socket=-1;
		sockPair[i].nick="";
	}
	realclient=0;
	tmpnumber=0;
}

int ActiveClients::GetSocket(string name, int* index)
{
	int i;
	for(i=0;i<size_socket_array; i++)
	{
		if(sockPair[i].nick==name)
		{
			
			if(index!=NULL)
				*index=i;
			return sockPair[i].socket;
		}
	}
	return 0;//возвращем 0 в случае если не нашли нужной пары
}
string ActiveClients::GetNick(int s)
{
	int i;
	for(i=0;i<size_socket_array; i++)
	{
		if(sockPair[i].socket==s)
		{
			return sockPair[i].nick;
		}
	}
	return "";//возвращем NULL в случае если не нашли нужной пары
}

bool ActiveClients::WriteNew(int s)
{
	int i=0;
	int flag=0;
	int j=0;
	tmpnumber++;
	for (j=0;j<realclient;j++)
	{
		if (sockPair[j].socket==-1)	
		{
			flag=1;
			break;
		}
	}
	string str;
	string s1="#tmp";
	char number[11];
        sprintf(number,"%i\0",tmpnumber);
	str=s1+number;
	
	if (flag)// добавление вместо ранее отключенного сокета 
	{
		sockPair[j].nick=str;
		sockPair[j].socket=s;		
		
	}

        else 
	{

		sockPair[realclient].nick=str;
		sockPair[realclient].socket=s;
	    	realclient++;
		
	}
}

void ActiveClients::setNick(int i,string str)
{
	sockPair[i].nick=str;
}

void ActiveClients::setSocket(int i,int fd)
{
	sockPair[i].socket=fd;
}

string ActiveClients::Nick(int i)
{
	return sockPair[i].nick;
}

int ActiveClients::Socket(int i)
{
	return sockPair[i].socket;
}

int ActiveClients::Size()
{
	return size_socket_array;
}

int ActiveClients::RealClient()
{
	return realclient;
}
