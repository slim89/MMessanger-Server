#include "queue.h"
#include "message.h"
#include "activeclients.h"
#include <string>
using namespace std;
extern string _s,_l,_r,_m;
extern ActiveClients cl;
//...........................................поток отсылающий сообщения
void* Parsing(void *arg)
{
	IMessage *mes,*outmes;
	string sender,recver,message,send_str;
	
	while(1)
	{	
		
		mes = Send_que->Read();	
		if (mes!=NULL)
		{
			cout<<"**********************message.c*************************************"<<endl;
//			cout<<"**message.c: RecBuf read из очереди:: "<<mes->GetBuf()<<" Его длина + '0'  "<<mes->BufSize<<endl;
			mes->Parse();
			sender=mes->GetPart(_s);
			recver=mes->GetPart(_r);
			message=mes->GetPart(_m);
	
		     	cout<<"**message.c: Nick отправителя: "<<sender<<endl;			
			cout<<"**message.c: parse name is: "<<recver<<endl;
			//----------------
			
			//временным пользователям отправить нельзя
			if(sender[0]=='#')
			{
				cout<<"--server.c: uncorrect sender "<<sender<<endl;
				continue;
			}
			if(recver[0]=='#')
			{
				cout<<"**message.c: uncorrect user: "<<recver<<endl;
				continue;
			}	
			
			cout<<"**message.c: parse message is: "<<message<<endl;
				
 			int sock=cl.GetSocket(recver,NULL);
			outmes=new Message("");
			outmes->AddPart(_s,sender);
			outmes->AddPart(_m,message);
			send_str=outmes->Unparse();
			cout<<"sender.cc : str  "<<send_str<<"      "<<send_str.length()<<endl;
			send(sock,send_str.c_str(),send_str.length()+1,NULL);  //возможно + 1			
			delete mes;
			delete outmes;
		}
	}
}
