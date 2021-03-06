#include "queue.h"
#include "message.h"
#include "activeclients.h"
#include "allthread.h"
#include "typemesparser.h"
#include <string.h>
#include <stdlib.h>

//--------------------Global var
string _s="s",_r="r",_m="m",_l="l",_p="p",_o="o",_typeSend="send",_typeLog="log",_typeNotify="notify";
int size_que=10;
int size_buf=1024;
AQueue* Send_que;
AQueue* Log_que;
AQueue *Conn_que;
ActiveClients cl;
int max_count_prefix=10;
QueTypeParser* type_parser;

//-----------------------------

int mymax()
{
	int max =cl.Socket(0);
	int i;
	for (i=1; i<cl.RealClient();i++)
	{
		if (cl.Socket(i)>max)
			max=cl.Socket(i);		
	}		    
	return max;
}

int thread_start()
{
//**************************  threads	BEGIN
	int thr0_err=0,thr1_err=0,thr2_err=0;
	
	pthread_t Handlers[3];
 	pthread_attr_t ta,tb,tc;
//--------------------------------------------
// Sender Thread
 	pthread_attr_init(&ta);
 	thr0_err=pthread_create(&Handlers[0], &ta, Parsing, NULL);
  	pthread_attr_destroy(&ta);

//--------------------------------------------
// Connect/Disconnect Thread
	pthread_attr_init(&tc);
 	thr1_err=pthread_create(&Handlers[2], &ta, Conndiscon, NULL);
  	pthread_attr_destroy(&tc);

//--------------------------------------------
// Log-register Thread
	pthread_attr_init(&tb);			// Login-Register Thread
 	thr2_err=pthread_create(&Handlers[1], &tb, LogRegistration, NULL);
	pthread_attr_destroy(&tb);
//**************************  threads   END
	if (thr0_err==0 && thr1_err==0 && thr2_err==0)
		return 0;
}

int main()
{   	
	Send_que=new AQueue(size_que);
	Log_que=new AQueue(size_que);
	Conn_que=new AQueue(size_que);

	type_parser=new QueTypeParser(3);
	type_parser->AddPair(&_typeSend,Send_que);
	type_parser->AddPair(&_typeLog,Log_que);
	type_parser->AddPair(&_typeNotify,Conn_que);
	
	
    	int listener;
	int qwe=0;//-----------------?????????????????????
   	struct sockaddr_in addr;

   	char buf[size_buf];//--for recv
    	int bytes_read;//-- for recv

	
	
    	listener = socket(AF_INET, SOCK_STREAM, 0);

    	if(listener < 0)
    	{
       		 perror("socket");
        	 return 1;
   	 }

    
    	fcntl(listener, F_SETFL, O_NONBLOCK);//non-block

   
    	addr.sin_family = AF_INET;
   	addr.sin_port = htons(3425);
   	//addr.sin_addr.s_addr = 0x6C000D0A;
	//addr.sin_addr.s_addr = 0x0100007F;
	addr.sin_addr.s_addr=INADDR_ANY;
    

   	 if(bind(listener, (struct sockaddr *)&addr, sizeof(addr)) < 0)
    	 {
        	perror("bind");
        	return 2;
    	 }
	
    	listen(listener, 2);


//**************************  threads	BEGIN

	cout<<thread_start()<<"   -  result creating thread"<<endl;

//**************************  threads   END

	int k=0;
    	while(1)
    	{
		k++;
        	// Заполняем множество сокетов
        	fd_set readset;
        	FD_ZERO(&readset);
        	FD_SET(listener, &readset);

		for (int i=0;i<cl.RealClient();i++)
		{
			FD_SET(cl.Socket(i), &readset);		
		}
     
       		// Задаём таймаут
        	/*timeval timeout;
        	timeout.tv_sec = 15;
        	timeout.tv_usec = 0;*/

		int mx;
        
		if (listener>mymax())
			mx=listener;
		else 
			mx=mymax();     
   
		// Ждём события в одном из сокетов
        	if(select(mx+1, &readset, NULL, NULL, NULL) <= 0)
        	{
           		perror("select");
            		return 3;
        	}
        
       		// Определяем тип события и выполняем соответствующие действия
        	if(FD_ISSET(listener, &readset))
        	{
            	// Поступил новый запрос на соединение, используем accept
            		int sock = accept(listener, NULL, NULL);
	
            		if(sock < 0)
            		{
            			perror("accept");
                		return 3;
            		}
            
        		fcntl(sock, F_SETFL, O_NONBLOCK);
			
			int flag=0; 

	
			cout<<"--------------ДО добавления-----------------\n";
			for (int qq=0;qq<cl.RealClient();qq++)
			{
				if (cl.Nick(qq)=="")
					cout<<"server.c: sock "<<cl.Socket(qq)<<" nick "<<"NULL"<<endl;
				else
					cout<<"server.c: sock "<<cl.Socket(qq)<<" nick "<<cl.Nick(qq)<<endl;
			}
			cout<<"-----------------------------------------------\n";
			
			cl.WriteNew(sock);// проверить return

			cout<<"--------------После добавления-----------------\n";
			for (int qq=0;qq<cl.RealClient();qq++)
			{
		
				if (cl.Nick(qq)=="")
					cout<<"server.c: sock "<<cl.Socket(qq)<<" nick "<<"NULL"<<endl;
				else
					cout<<"server.c: sock "<<cl.Socket(qq)<<" nick "<<cl.Nick(qq)<<endl;
			}
			cout<<"-----------------------------------------------\n";

        	}


		//создаем обьекты для постановки их в очереди.................

		

				
		for (int i=0;i<cl.RealClient();i++)
        	{
		
           		 if(FD_ISSET(cl.Socket(i), &readset))
            		{
                		// Поступили данные от клиента, читаем их
               			bytes_read = recv(cl.Socket(i), buf, size_buf, 0);//реально вернет кол-во байт указанных на стoроне клиента!!!!!
				cout<<"--server.c: socket RECV:  "<<cl.Socket(i)<<"  byte RECV:  "<<bytes_read<<endl;
				buf[bytes_read]='\0';
				if(bytes_read <= 0)
                		{
                    			// Соединение разорвано, удаляем сокет из множества
					close(cl.Socket(i));			
                  			cl.setSocket(i,-1);
					
					
					//рассылка юзерам о дисконнекте пользователя
					if(cl.Nick(i)[0]!='#')
					{	
						IMessage* connmes=new Message("");
						connmes->AddPart(_o,"disconnect");
						connmes->AddPart(_s,cl.Nick(i));
						Conn_que->Write(connmes);						
						delete connmes;						
					}
					cl.setNick(i,"");

					//-----------------------------------------
					cout<<"--------------После закрытия-----------------\n";
					for (int qq=0;qq<cl.RealClient();qq++)
					{
			
						if (cl.Nick(qq)=="")
							cout<<"server.c: sock "<<cl.Socket(qq)<<" nick "<<"NULL"<<endl;
						else
							cout<<"server.c: sock "<<cl.Socket(qq)<<" nick "<<cl.Nick(qq)<<endl;
					}
					cout<<"-----------------------------------------------\n";     
		
                    			continue;
              			}
		
				else
				{	
					Message* msg;
					string buffer=buf;
					cout<<" length bufer  "<<buffer.length()<<endl;
					msg=new Message(buffer);
					cout<<buffer<<endl;
					cout<<"TEST NICK"<<cl.Nick(i)<<endl;
					msg->AddPart(_s,cl.Nick(i));
					AQueue* tmp=type_parser->TypeParse(buffer);
					if (tmp!=NULL)
					tmp->Write(msg);
					delete msg;					
	   			}    
            		}//if
        	}//for
    	}//while    
   	return 0;
}
