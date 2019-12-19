#include <stdio.h>
#include <stdlib.h>
#define SIZE 3

int high[SIZE],hf=0,hr=0,low[SIZE],lf=0,lr=0,temp;

void insert(int pri,int val)
{
	if(pri==1)
	{
		if(hr<SIZE)
		{
			printf("Insertion in higher priority queue\n");
			high[hr++]=val;
		}

		else
			printf("Queue Full\n");
	}

	else if(pri==2)
	{
		if(lr<SIZE)
		{
			printf("Insertion in lower priority queue\n");
			low[lr++]=val;
		}

		else
			printf("Queue Full\n");
	}


	else
		printf("Invalid Priority Request\n");

}


void process()
{
	if(hf!=hr)
	{
		printf("Processing Higher Priority Queue\n");
		temp=high[hf++];
		printf("Processed:%d \n",temp);

	}

	else if(lf!=lr)
	{
		printf("Processing Lower Priority Queue\n");
		temp=low[lf++];
		printf("Processed:%d \n",temp);
		
	}

	else
	{
		hf=hr=lf=lr=0;
		printf("No processes remaining\n");
	}
}

void display(int q[],int f , int r)
{
	if(f!=r)
	{
		for (int i = 0; i < r; i++)
			printf("%d\n",q[i] );
	}
	else
		printf("Empty\n");
}



void main()
{
	int val,pri,ch=1;
  while(ch!=5)
  {
	    printf("Enter 1 for insertion,2 to process, 3 to display higher pri queue , 4 to display lower pri queu , 5 to exit\n");
	    scanf("%d",&ch);
	    if(ch==1)
	    {
	      //printf("Enter the packet value and priority\n");
	      printf("add value");
	      scanf("%d",&val);
	      printf("priority");
	      scanf("%d",&pri);
	      insert(pri,val);
	    }
	    else if(ch==2)
	    {
	      process();
	    }

	    else if(ch==3)
	    {
	    	display(high,hf,hr);
	    }

	    else if(ch==4)
	    {
	    	display(low,lf,lr);
	    }

	    else
	    	break;

    }
}
