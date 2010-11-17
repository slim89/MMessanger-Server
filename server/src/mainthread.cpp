#include "queue.h"
#include "message.h"
#include "activeclients.h"
#include "allthread.h"
#include <string.h>
#include <stdlib.h>

//--------------------Global var
string _s="s",_r="r",_m="m",_l="l",_p="p",_o="o";
int size_que=10;
int size_buf=1024;
AQueue* Send_que;
AQueue* Log_que;
AQueue *Conn_que;
ActiveClients cl;
int max_count_prefix=10;

//-----------------------------

int mymax()
{
	int max =cl.socket[0];
	int i;
	for (i=1; i<cl.realclient;i++)
	{
		if (cl.socket[i]>max)
			max=cl.socket[i];		
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

		for (int i=0;i<cl.realclient;i++)
		{
			FD_SET(cl.socket[i], &readset);		
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
			for (int qq=0;qq<cl.realclient;qq++)
			{
				if (cl.nick[qq]=="")
					cout<<"server.c: sock "<<cl.socket[qq]<<" nick "<<"NULL"<<endl;
				else
					cout<<"server.c: sock "<<cl.socket[qq]<<" nick "<<cl.nick[qq]<<endl;
			}
			cout<<"-----------------------------------------------\n";
			
			cl.WriteNew(sock);// проверить return

			cout<<"--------------После добавления-----------------\n";
			for (int qq=0;qq<cl.realclient;qq++)
			{
		
				if (cl.nick[qq]=="")
					cout<<"server.c: sock "<<cl.socket[qq]<<" nick "<<"NULL"<<endl;
				else
					cout<<"server.c: sock "<<cl.socket[qq]<<" nick "<<cl.nick[qq]<<endl;
			}
			cout<<"-----------------------------------------------\n";

        	}


		//создаем обьекты для постановки их в очереди.................

		

				
		for (int i=0;i<cl.realclient;i++)
        	{
		
           		 if(FD_ISSET(cl.socket[i], &readset))
            		{
                		// Поступили данные от клиента, читаем их
               			bytes_read = recv(cl.socket[i], buf, size_buf, 0);//реально вернет кол-во байт указанных на стoроне клиента!!!!!
				cout<<"--server.c: socket RECV:  "<<cl.socket[i]<<"  byte RECV:  "<<bytes_read<<endl;
				buf[bytes_read]='\0';
				if(bytes_read <= 0)
                		{
                    			// Соединение разорвано, удаляем сокет из множества
					close(cl.socket[i]);			
                  			cl.socket[i]=-1;
					
					
					//рассылка юзерам о дисконнекте пользователя
					if(cl.nick[i][0]!='#')
					{	
						IMessage* connmes=new Message("");
						connmes->AddPart(_o,"disconnect");
						connmes->AddPart(_s,cl.nick[i]);
						Conn_que->Write(connmes);						
						delete connmes;						
					}
					cl.nick[i]="";

					//-----------------------------------------
					cout<<"--------------После закрытия-----------------\n";
					for (int qq=0;qq<cl.realclient;qq++)
					{
			
						if (cl.nick[qq]=="")
							cout<<"server.c: sock "<<cl.socket[qq]<<" nick "<<"NULL"<<endl;
						else
							cout<<"server.c: sock "<<cl.socket[qq]<<" nick "<<cl.nick[qq]<<endl;
					}
					cout<<"-----------------------------------------------\n";     
		
                    			continue;
              			}
		
				else
				{	
					MessageWithQue* msg;
					string buffer=buf;
					cout<<" length bufer  "<<buffer.length()<<endl;
					msg=new MessageWithQue(buffer,NULL);
					cout<<buffer<<endl;
					cout<<"TEST NICK"<<cl.nick[i]<<endl;
					msg->AddPart(_s,cl.nick[i]);
					msg->Write();
					delete msg;					
	   			}    
            		}//if
        	}//for
    	}//while    
   	return 0;
}
