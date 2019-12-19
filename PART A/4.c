#include <stdio.h>
#include <stdlib.h>

int mat[100][100],visited[100]={0},distance[100],src,i,j,k,n,min,nextNode;

void getMat()
{
	printf("Enter the number of nodes\n");
	scanf("%d",&n);
	printf("Enter the weighted adjacency matrix\n");

	for (i = 0; i <n ; i++)
	{
		for (j= 0; j<n; j++)
		{
			scanf("%d",&mat[i][j]);
		}
	}

}

void djikstras()
{
	printf("Enter the source node\n");
	scanf("%d",&src);
	visited[src]=1;

	for (i = 0; i <n; i++)
		distance[i]=mat[src][i];



	for (i = 0; i < n; i++)
	{
		min=999;
		for (j = 0; j<n; j++)
		{
			if(min>distance[j] && visited[j]!=1)
			{
				min=distance[j];
				nextNode=j;
			}
		}

	visited[nextNode]=1;

		for (k = 0; k < n; k++)
		{
			if(distance[k]>min+mat[nextNode][k] && visited[k]!=1)
			{
				distance[k]=min+mat[nextNode][k];
			}
		}

	}
}


void disp()
{
	printf("From %d \n",src);
	printf("To \t Cost \n");
	for (i = 0; i < n; i++)
	{
		if(i!=src)
		printf("%d \t %d \n",i,distance[i]);
	}

}


void main()
{
	getMat();
	djikstras();
	disp();
}