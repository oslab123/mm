#include<stdio.h>

void main ()
{
	int n,tq,a[20],b[20],p[20],remainingBurst[20],t[20],w[20];
	float avgt=0,avgw=0;
	printf("Enter the no of processes\n: ");
	scanf("%d" ,&n);

	printf("Enter the time quantum\n: ");
	scanf("%d",&tq);

	for(int i=0;i<n;i++)
	{
		printf("Process ID: ");
		scanf("%d",&p[i]);
		printf("Arrival Time: ");
		scanf("%d",&a[i]);
		printf("Burst Time: ");
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
		remainingBurst[i] = b[i];
	}
	int currentT = 0;
	printf("\nGantt Chart:\n");
	printf("| Time |");
	while(1)
	{
		int allProcessDone = 1;
		for(int i=0;i<n;i++)
		{
			if(remainingBurst[i]>0)

			{
				allProcessDone = 0;
				if(remainingBurst[i]<=tq)
				{
					printf("%d |P %d",currentT,p[i]);
					currentT+=remainingBurst[i];
					t[i] = currentT - a[i];
					w[i] = t[i] - b[i];
					avgw+=w[i];
					avgt+=t[i];
					remainingBurst[i] = 0;

				}
				else {
					printf("%d |P %d",currentT,p[i]);
					currentT+=tq;
					remainingBurst[i]-=tq;
				}

			}
		}
		if(allProcessDone)
			break;
	}
	printf("\n");
	avgt = avgt/n;
	avgw = avgw/n;

	 printf("\nPROCESS ID \t AT\t BT\t CT\t TAT\t WT\n");
    for (int i = 0; i < n; i++) {
        printf("%d\t\t%d\t%d\t%d\t%d\t%d\n", p[i], a[i], b[i], t[i] + a[i], t[i], w[i]);
    }

    printf("\nAverage Turnaround Time = %f\n", avgt);
    printf("Average Waiting Time = %f\n", avgw);

}
