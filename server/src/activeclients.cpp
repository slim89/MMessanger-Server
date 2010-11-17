#include "activeclients.h"
ActiveClients::ActiveClients()
{
	int i;
	for(i=0;i<size_socket_mass; i++)
	{
		socket[i]=-1;
		nick[i]="";
	}
	realclient=0;
	tmpnumber=0;
}

int ActiveClients::GetSocket(string name, int* index)
{
	int i;
	for(i=0;i<size_socket_mass; i++)
	{
		if(nick[i]==name)
		{
			
			if(index!=NULL)
				*index=i;
			return socket[i];
		}
	}
	return 0;//возвращем 0 в случае если не нашли нужной пары
}
string ActiveClients::GetNick(int s)
{
	int i;
	for(i=0;i<size_socket_mass; i++)
	{
		if(socket[i]==s)
		{
			return nick[i];
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
		if (socket[j]==-1)	
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
		nick[j]=str;
		socket[j]=s;		
		
	}

        else 
	{

		nick[j]=str;
		socket[realclient]=s;
	    	realclient++;
		
	}
	
}
