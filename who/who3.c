// ChangJin Lee
#include<stdio.h>
#include<utmp.h>
#include<fcntl.h>
#include<unistd.h>
#include<stdlib.h>
#include<time.h>
#include<sys/types.h>

#define SHOWHOST

void showtime(long);
void show_info(struct utmp *);

int main(){
	struct utmp *utbufp;
	struct utmp *utmp_next();

	if(utmp_open(UTMP_FILE)==-1){
		perror(UTMP_FILE);
		exit(1);
	}

	while((utbufp=utmp_next())!=((struct utmp*)NULL))
		show_info(utbufp);
	utmp_close();
	return 0;
}

void show_info(struct utmp* utbufp){
	if(utbufp->ut_type!=USER_PROCESS)
		return;

	printf("%-8.8s", utbufp->ut_name);		// users only
	printf(" ");

	printf("%-8.8s", utbufp->ut_line);		// the login name
	printf(" ");

	showtime( utbufp->ut_time);				//display time
	printf(" ");

	#ifdef SHOWHOST
		printf(" (%s)", utbufp->ut_host);	//the host
	#endif
		printf("\n");		//new line
}

void showtime(long timeval){
	char* cp;					// to hold address of time
	cp = ctime(&timeval);		// convert time to a string

	printf("%12.12s",cp+4);		// pick 12 chars from pos 4
}

