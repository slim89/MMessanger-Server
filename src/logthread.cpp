#include "queue.h"
#include "message.h"
#include "activeclients.h"
extern ActiveClients cl;
extern string _s,_l,_p,_o;
extern AQueue* Log_que;
extern AQueue* Conn_que;
void* LogRegistration(void * arg)
{

	IMessage *mes;
	string login,pass,tmpnick,operation;
	int lenbuf=1024;
	char* filedata;
	FILE *contacts;


	while(1)
	{	
		mes=Log_que->Read();		
		
		if (mes!=NULL)
		{
			cout<<"+++++++++++++++++++++++++login.c+++++++++++++++++++++++++++++++++++"<<endl;
			mes->Parse();
			cout<<"OK!!"<<endl;
			login=mes->GetPart(_l);
			pass=mes->GetPart(_p);
			tmpnick=mes->GetPart(_s);
			operation=mes->GetPart(_o);
			int i,k; 	
			int z=0;	//Условие, если файл пуст или не создан	
			filedata=new char[lenbuf];	

			cout<<"++login.c: Обработанный логин:: "<<login<<endl;
			cout<<"++login.c: Обработанный пароль:: "<<pass<<endl;			
			cout<<"++login.c: Временный ник:: "<<tmpnick<<endl;
			cout<<"++login.c: Операция:: "<<operation<<endl;
			int *index=new int(0) ;
			int sock;
			int tmpsock=cl.GetSocket(tmpnick,index);// 
			if(tmpsock==0)
			{
				continue;	//сокет был закрыт до нас
			}
			//----------------

			//отличия лишь в работе с файлом: 
			//	1)Логин ищет запись и сверяет пароль
			//	2)Регистрация если не находит запись, то добавляет новую
			if(operation=="login")
			{	
				
				//Логин-------------------------------------------------------------------
				sock=cl.GetSocket(login,NULL);				
				if(sock!=0){send(tmpsock,"*login is already used",23,NULL);continue;}

				contacts=fopen("/usr/share/contacts.txt","a+");
				fseek(contacts, 0, SEEK_SET);

				while(!feof(contacts))
				{
					fscanf(contacts,"%s",filedata);
					i=0;
					k=0;			
					//сравнение логинов
					string tmp=filedata;
					cout<<"FILE READ  "<<tmp<<endl;
					int qq=0;
					if(tmp[qq]=='\0'){z=1;break;}
					string flogin,fpass;
					while (tmp[qq]!='/')
						{

							flogin+=tmp[qq];
							qq++;
							
						}
					cout<<" FLOG "<<flogin.length()<<endl;
					qq++;
					for (qq;qq<tmp.length();qq++)
						{
							fpass+=tmp[qq];
						}
					
					if(flogin!=login)					
					{
						continue;
					}

					else			//логин найден. проверяем пароль
					{
						if(pass!=fpass)	//если пароль неверен
						{
							printf("Error of password!\n");
							//отправить "пароль неверен"!!!!!!!!!!!!!!!!!!!!!!!
							send(tmpsock,"*Error of password!",20,NULL);
						}
						else		//пароль верен
						{
							printf("good login/password\n");
							//отправить "логирование прошло успешно"!!!!!!!!!!!!!!!!!!!!!!!!
							send(tmpsock,"*good login/password",21,NULL);
							
							//printf("1-%s\n",cl.nick[*index]);						
							cout<<"*index "<<*index<<endl;	
							cl.nick[*index]=login;
							//printf("3-%s\n",cl.nick[*index]);


							//рассылка юзерам о коннекте пользователя
							IMessage* connmes=new Message("");
							connmes->AddPart(_o,"connect");
							connmes->AddPart(_s,cl.nick[*index]);
							Conn_que->Write(connmes);						
							delete connmes;
							
							//-----------------------------------------
						}
						break;		//завершаем просмотр файла
					}
				}//while
				if(feof(contacts)||(z==1))	//если подобного логина не найдено или файл пуст(отсутствовал)
				{
					printf("Error of login!\n");
					//отправить "данного логина не найдено"!!!!!!!!!!!!!!!!!!!!!!!!!!!!
					send(tmpsock,"*Error of login!",17,NULL);
					//close(sock);
				}
				fclose(contacts);
				z=0;				//обнуляем состояние на всякий случай
			}//if login
			if(operation=="registration")
			{
				string flogin;
				//Регистрация---------------------------------------------------------------
				printf("2--------------\n");
				contacts=fopen("/usr/share/contacts.txt","a+");
				fseek(contacts, 0, SEEK_SET);
				while(!feof(contacts))
				{
					fscanf(contacts,"%s",filedata);
					printf("%s\n",filedata);

					string tmp=filedata;
					int qq=0;
					if(tmp[qq]=='\0'){z=1;break;}
					while (tmp[qq]!='/')
						{
							flogin+=tmp[qq];
							qq++;
						}
					//сравнение логинов
					
					if(flogin!=login)		//если текущий логин не совпадает с введенным
					{
						flogin="";
						continue;	//продолжаем просмотр файла
					}
					else			//логин найден. надо придумать другой логин
					{
						break;
					}
				}
				if(feof(contacts)||(z==1))	//если подобного логина не найдено то сохраним его (если нет файла либо он пуст)
				{
					fprintf( contacts, "%s/%s\n",login.c_str(),pass.c_str());
					printf("good registration\n");
					//отправить "регистрация прошла успешно"!!!!!!!!!!!!!!!!!!!!!!!!!!
					send(tmpsock,"*good registration",19,NULL);
				}
				else
				{
					printf("Login already exist\n");
					//отправить "придумайте новый логин"!!!!!!!!!!!!!!!!!!!!!!!!!!!
					send(tmpsock,"*Login already exist",21,NULL);
				}
				fclose(contacts);
				z=0;
			}//if reg
			delete mes;
			delete index;
		}
	}
}
