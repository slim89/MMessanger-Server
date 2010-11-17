#include <sys/types.h>
#include <sys/socket.h>
#include <sys/select.h>
#include <sys/time.h>
#include <netinet/in.h>
#include <stdio.h>
#include <string>
#include <unistd.h>
#include <fcntl.h>
#include <pthread.h>
#include <iostream>
class IMessage;
using namespace std;
class AQueue
{
public:
		int notEmpty;//количество доступных элементов
		int iterwrite;
		int iterread;
		IMessage **mas;		
		int count; // длина очереди
		int maxcount;

		int maxlenmessage;

		AQueue(int);	
		AQueue();
		~AQueue();
		IMessage* Read();
		void Write(IMessage*);	
};

extern AQueue* Send_que;
extern AQueue* Log_que;
extern AQueue *Conn_que;
