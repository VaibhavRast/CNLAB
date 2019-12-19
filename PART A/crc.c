#include <string.h>
#include <stdio.h>
#define N strlen(g)

char t[28],cs[28],aug[28];
char g[]="10001000000100001";
//char g[]="1011";
int a,e,c,d,k;

void xor()
{
	for(c=1;c<N;c++)
	{
		cs[c]=((cs[c]==g[c])?'0':'1');
	}
}


void crc()
{
	for(e=0;e<N;e++)
		cs[e]=aug[e];
	do
	{
		if(cs[0]=='1')
			xor();
		for(c=0;c<N-1;c++)
			cs[c]=cs[c+1];
		cs[c]=aug[e++];

	}while(e<=a+N-1);
}


void main()
{
	int choice;
	printf("Enter dataword\n");
	scanf("%s",t);
	a=strlen(t);
	strcpy(aug,t);

	for(e=a;e<a+N-1;e++)
	{
		aug[e]='0';
	}

	printf("Augmented dataword %s\n",aug);

	printf("Divisor %s \n",g);

	crc();


	//Result
	printf("Remainder bits %s\n",cs );
	strcat(t,cs);
	printf("Codeword is %s \n",t);


	//Error Detection
	printf("1:Detect 0:Exit\n");
	scanf("%d",&choice);
	if(choice==1)
	{
		printf("Enter number of errors to be intoduced\n");
		scanf("%d",&d);
		for(int j=0;j<d;j++)
		{
			k=rand()%strlen(t)-1;
			printf("pos:%d\n",k );
			t[k]=((t[k]=='0')?'1':'0');
		}
		
        printf("\n----------------------------------------");
        printf("\nErroneous data : %s\n",t);
        strcpy(aug,t);
		 crc();
	 	for(e=0;(e<N-1) && (cs[e]!='1');e++){}
	 		if(e<N-1)
            	printf("\nError detected\n\n");
        	else
            	printf("\nNo error detected\n\n");
	}
	
}
