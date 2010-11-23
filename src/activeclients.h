#include <string>
#include <time.h>
#include <iostream>
#include <stdio.h>
using namespace std;
class ActiveClients
{	
	
public: 
	const static int size_socket_mass=50;
	int realclient;
	unsigned int tmpnumber;
	int socket[50];
	string nick[50];
	int GetSocket(string, int*);//возвращает сокет по имени
	string GetNick(int);//возвращает имя посокету	
	bool WriteNew(int);//принимает дескриптор и записывает в свободное место в массиве сокетов
	ActiveClients();	
};
