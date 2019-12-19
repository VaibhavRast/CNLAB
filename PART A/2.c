#include <stdio.h>
#include <stdlib.h>
#define MIN(x,y) x>y?y:x
void main()
{
	int cap,orate,count=0,x,sent=0,drop=0;
	int inp[100]={0},nsec,i=0,ch;

	printf("Enter bucket capacity\n");
	scanf("%d",&cap);

	printf("Enter output rate\n");
	scanf("%d",&orate);

	do
	{
		printf("Enter no of packets coming in at second %d \n",i+1 );
		scanf("%d",&inp[i++]);
		printf("1.To continue 0 to exit\n");
		scanf("%d",&ch);
	}while(ch!=0);

	nsec=i;
    printf("SEC \t RECEIVED \t SENT \t DROP \t REMAINED \n");
	for(i=0;count || nsec>i; i++)
	{
		sent=MIN(inp[i]+count,orate);

		x=inp[i]+count-orate;

			if(x>0)
			{
				if(x>cap)
				{
					count=cap;
					drop=x-cap;
				}
				else
				{
					count=x;
					drop=0;
				}
			}
			else
			{
				drop=0;
				count=0;
			}
			
		printf("%d  \t %d       \t %d   \t %d   \t   %d     \n",i+1,inp[i],sent,drop,count);
	}
}