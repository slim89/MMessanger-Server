#include <string>
#include <time.h>
#include <iostream>
#include <stdio.h>
using namespace std;

struct SockNick
{
	int socket;
	string nick;
};

class ActiveClients
{	
private:	
	SockNick sockPair[50];
	int realclient;
	unsigned int tmpnumber;
	const static int size_socket_array=50;
public: 
	int GetSocket(string, int*);//возвращает сокет по имени
	string GetNick(int);//возвращает имя по сокету	
	bool WriteNew(int);//принимает дескриптор и записывает в свободное место в массиве сокетов
	ActiveClients();
	void setNick(int,string);
	void setSocket(int,int);	
	int Socket(int);
	string Nick(int); 
	int Size();
	int RealClient();
};
