#include "queue.h"
#include "message.h"
#include "activeclients.h"
//программа потока рассылки клиентам появившихся или отключившихся клиентов
extern ActiveClients cl;
extern string _s;
extern AQueue* Conn_que;
void* Conndiscon(void *arg)
{
	IMessage *mes;
	while(1)
	{	
		
		mes =Conn_que->Read();
		if (mes!=NULL)
		{
			string my_nick = mes->GetPart(_s);
			int socket = cl.GetSocket(my_nick,NULL);
			string buf=mes->Unparse();
			
			
			
			for(int i=0;i<cl.size_socket_array;i++)
			{	
				
				if((cl.socket[i]==-1)||(cl.nick[i]=="")||(cl.nick[i][0]=='#'))//если сокет не пустой
				{
					continue;	
				}
				
				cout<<"!!Conndiscon.c  "<<"buf = "<<buf<<"  length  "<<buf.length()<<endl;
				cout<<"Komu"<<cl.socket[i]<<endl;
		     		send(cl.socket[i],buf.c_str(),buf.length()+1,NULL);
				

			
			}
			
			for(int i=0;i<cl.size_socket_array;i++)
			{	
				
				if((cl.socket[i]==-1)||(cl.nick[i]=="")||(cl.nick[i][0]=='#'))//если сокет не пустой
				{
					continue;	
				}
				mes->ReplacePart(_s,cl.nick[i]);
				buf=mes->Unparse();
				cout<<"!!Conndiscon.c  "<<"buf12 = "<<buf<<"  length  "<<buf.length()<<endl;
				cout<<"Komu"<<socket<<endl;
				//sleep(2);
				send(socket,buf.c_str(),buf.length()+1,NULL);
				//send(socket,"victory",8,NULL);
				/*send(socket,buf.c_str(),buf.length()+1,NULL);
				send(socket,buf.c_str(),buf.length()+1,NULL);*/
				
			}
			delete mes;
		}

	}
	return 0;	
}
