/*
   who1.c - a first version of the who program
			open, read UTMP file, and show results
	Writer : ChangJin Lee (ckdwls525@gmail.com)
*/
#include <stdio.h>
#include <stdlib.h>
#include <utmp.h>
#include <fcntl.h>
#include <unistd.h>

#define SHOWHOST 1

void show_info(struct utmp* utbufp);

int main(){
	struct utmp current_record;
	int  utmpfd;
	int reclen = sizeof(current_record);

	if((utmpfd = open(UTMP_FILE, O_RDONLY)) ==-1) {
		perror(UTMP_FILE);
		exit(1);
	}

	while(read(utmpfd, &current_record, reclen) == reclen)
		show_info(&current_record);
	close(utmpfd);
	return 0;
}
/* show info()
   - displays contents of the utmp struct in human readable form
   - note : these sizes shouldn't be hardcoded.
*/


void show_info(struct utmp* utbufp){
	printf(" %-8.8s", utbufp->ut_name); // the login name
	printf(" ");

	printf(" %-8.8s", utbufp->ut_line); // the tty
	printf(" ");
	 
	printf(" %10d", utbufp->ut_time); // login time
	printf(" ");

#ifdef SHOWHOST
	printf(" (%s)", utbufp->ut_host); //the host
#endif
	printf("\n"); // new line
}


