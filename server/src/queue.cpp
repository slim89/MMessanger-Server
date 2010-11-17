#include "queue.h"
#include "message.h"
//.....................................................................определение самой очереди
AQueue::AQueue(int max)
{
	maxcount=max;
	mas= new IMessage*[maxcount];
	for (int i=0;i<maxcount;i++)
		mas[i]=NULL;			
	iterread=0;
	iterwrite=0;
	notEmpty=0;
}
AQueue::AQueue()
{
	maxcount=1;
	mas= new IMessage*[maxcount];
	for (int i=0;i<maxcount;i++)
		mas[i]=NULL;	
	iterread=0;
	iterwrite=0;
	notEmpty=0;
}
AQueue::~AQueue()
{
	cout<<"maxcount  "<<maxcount<<endl;
	for(int i=0;i<maxcount;i++)				
		if (mas[i]!=NULL)	
			delete mas[i];
	cout<<"FREE "<<endl;
	if (mas!=NULL)
		delete [] mas;						
}
IMessage* AQueue::Read()
{
	if (notEmpty==0)
	{
		return NULL;
	}
	int retindex=iterread;
	if(iterread==maxcount-1) //конец очереди? 
	{
		iterread=0;				
	}
	else
	{
		iterread++;
	}
	IMessage* ret=mas[retindex];
	mas[retindex]=NULL;
	notEmpty--;//уменьшим реальную длину
	return ret;
}
void AQueue::Write(IMessage* rm)
{
	if (iterwrite==iterread && notEmpty!=0)
		{
			printf("Count not Empty   %d\n",notEmpty);
			return;
		}
	//printf("test1 %s\n",rm->GetBuf());
 	mas[iterwrite]=rm->Copy();
	//printf("test2 %s\n",mas[iterwrite]->GetBuf());
	notEmpty++;
	if(iterwrite==maxcount-1) //конец очереди? 
	{
		iterwrite=0;				
	}
	else
	{
		iterwrite++;
	}
}
