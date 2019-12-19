#include<stdio.h>


	struct node
	{
		int distance[20];
		int from[20];
	}rt[10];
void main()
{
	int n,i,j,k;
	int costmat[20][20];
	int count=0;
	printf("Enter n \n");
	scanf("%d",&n);
	printf("Enter weighted adjacency matrix\n");

	for(i=0;i<n;i++)
	{
		for(j=0;j<n;j++)
		{
			scanf("%d",&costmat[i][j]);
			costmat[i][i]=0;
			rt[i].distance[j]=costmat[i][j];
			rt[i].from[j]=j;
		}
	}


	do
	{
		count=0;
		for(i=0;i<n;i++)
			for(j=0;j<n;j++)
				for(k=0;k<n;k++)
					if(rt[i].distance[j]>costmat[i][k]+rt[k].distance[j])
					{
						rt[i].distance[j]=rt[i].distance[k]+rt[k].distance[j];
						rt[i].from[j]=k;
						count++;
					}
	}while(count!=0);


	for(i=0;i<n;i++)
	{
		printf("For Router %d\n",i);
		printf("To \t Cost \t Next Node \n");
			for(j=0;j<n;j++)
			{
				printf("%d \t %d \t   %d        \n",j,rt[i].distance[j],rt[i].from[j]);
			}
	}


}

