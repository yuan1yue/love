#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/select.h>
#include<sys/time.h>
int main()
{
	int pi[2];
	pipe(pi);
	pid_t pid = fork();
	if(0 == pid)
	{
		close(pi[0]);
		FILE *fp;
		const char* p[3]={"p1","p2","p3"};
		fd_set set;
		struct timeval time;
		time.tv_sec = 0;
		time.tv_usec = 0;
	//	FD_ZERO(&set);
	//	FD_SET(pi[1],&set);
	//	select(1,&set,0,0,0);
		for(int i=0;;i=(i+1)%3)
		{
			fp = fopen(p[i],"r+");
			while(!feof(fp))
			{
				printf("%c",fgetc(fp));
			}
			fclose(fp);
			sleep(2);
			system("clear");
			FD_ZERO(&set);
			FD_SET(pi[1],&set);
			select(pi[1]+1,&set,NULL,NULL,&time);
			if(FD_ISSET(pi[1],&set))
				break;
                
		}
	}
	close(pi[1]);
	if(getchar())
		write(pi[0],'a',1);
	
	return 0;
}
