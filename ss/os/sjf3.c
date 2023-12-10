#include<stdio.h>
#include<stdlib.h>

void main() 
{
	int n,a[20], b[20], p[20], g[20], w[20], t[20];
	float avgt = 0;
	float avgw = 0;
	int btime = 0,k=1;
	int min;
	printf("Enter the number of processes: ");
	scanf("%d",&n);
	printf("Enter the arrival time,burst time and process id :");
	for(int i=0;i<n;i++)
	{
		printf("ProcessID :");
		scanf("%d",&p[i]);

		printf("Arrival time :");
		scanf("%d",&a[i]);

		printf("burst time :");
		scanf("%d",&b[i]);
	}

	int temp = 0;
	for(int i=0;i<n-1;i++)
	{
		for(int j=0;j<n-1;j++)
		{
			if(a[j]>a[j+1])
			{
				temp = a[j];
				a[j] = a[j+1];
				a[j+1] = temp;

				temp = b[j];
				b[j] = b[j+1];
				b[j+1] = temp;

				temp = p[j];
				p[j] = p[j+1];
				p[j+1] = temp;
			}


		}
	}

	for(int i=0;i<n;i++)
	{
		btime = btime + b[i];
		min = b[k];

		for(int j=k;j<n;j++)
		{
			if(btime>=a[j] && b[j]<min)
			{
				temp = a[j];
				a[j] = a[j-1];
				a[j-1] = temp;

				temp = b[j];
				b[j]  = b[j-1];
				b[j-1] = temp;

				temp = p[j];
				p[j] = p[j-1];
				p[j-1] = temp;
			}
		}
			k++;

	}


	g[0] = a[0];
	for(int i =0;i<n;i++)
	{
		g[i+1] = g[i] + b[i];
	}

	for(int i=0;i<n;i++)
	{
		t[i] = g[i+1] - a[i];
		w[i] = t[i] - b[i];
		avgw = avgw + w[i];
		avgt = avgt + t[i];
	}

	avgw = avgw/n;
	avgt = avgt/n;

		printf("pid\tarrivalT\tBrustT\tCompletionT\tWaitingtime\tTurnaroundTi\n");
			for(int i=0;i<n;i++)
			{
				printf("%d\t%d\t\t%d\t%d\t\t%d\t\t\t%d\n",p[i],a[i],b[i],g[i+1],w[i],t[i]);
			}
			printf("\nAverage Waitingtime %f",avgw);
			printf("/nAverage TurnaroundTi %f",avgt);


}
