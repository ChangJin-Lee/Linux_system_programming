//ls2.c

#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <dirent.h>
#include <sys/stat.h>
#include <time.h>

void do_ls (char[]);
void dostat (char*);
void show_file_info(char*,struct stat*);
void mode_to_letters(int, char[]);
char* uid_to_name(uid_t);
char* gid_to_name(gid_t);
void find_index(time_t list[],int num);

#define B_SIZE 50
long total=0;			// store st_blocks/2
char one[B_SIZE][15];
int two[B_SIZE];
char three[B_SIZE][15];
char four[B_SIZE][15];
long five[B_SIZE];
char six[B_SIZE][25];
time_t six_proto[B_SIZE];
char seven[B_SIZE][15];
int lindx[B_SIZE];
int indx=0,check=0;


int main(int argc, char* argv[]){
	if(argc==1){
		do_ls(".");
	}
	else if (argc==2){
		if(!strcmp(argv[1],"-t")){
			do_ls(".");
			find_index(six_proto,indx);
			printf("total : %ld\n",total);
				for(int i=0;i<indx;i++){
					printf("%s ",one[lindx[i]]);
					printf("%4d ",two[lindx[i]]);
					printf("%-8s ", three[lindx[i]]);
					printf("%-8s ", four[lindx[i]]);
					printf("%-8ld ",five[lindx[i]]);
					printf("%.12s ",six[lindx[i]]);
					printf("%s \n",seven[lindx[i]]);
					check=1;
			}
		}
		else{
			while(--argc){
				printf("%s:\n",*++argv);
				do_ls(*argv);
			}
		}
	}
	else{
		while(--argc){
			printf("%s:\n",*++argv);
			do_ls(*argv);
		}
	}
	
	
	if(check==0){
		printf("total : %ld\n",total);
		for(int i=0;i<indx;i++){
			printf("%s ",one[i]);
			printf("%4d ",two[i]);
			printf("%-8s ", three[i]);
			printf("%-8s ", four[i]);
			printf("%-8ld ",five[i]);
			printf("%.12s ",six[i]);
			printf("%s \n",seven[i]);
		}
	}
}

void do_ls (char dirname[]){
	DIR* dir_ptr;
	struct dirent* direntp;
	struct stat info;
	if((dir_ptr = opendir(dirname))==NULL)
		fprintf(stderr,"ls2 : cannot open %s\n",dirname);
	else{
		while((direntp=readdir(dir_ptr))!=NULL){
			if(!strcmp(direntp->d_name,"sample")){
			stat(direntp->d_name,&info);
		chmod("sample", info.st_mode|S_ISUID|S_ISGID|S_ISVTX);
	}
			dostat(direntp->d_name);
			}
		closedir(dir_ptr);
	}
}

void dostat(char* filename){
	struct stat info;
	if(stat(filename,&info)==-1)
		perror(filename);
	else{
		show_file_info(filename,&info);
	}
}

void show_file_info(char* filename, struct stat* info_p){
	// display the info about 'filename.' the info is
	// stored in struct at info_p
	char *uid_to_name(), *ctime(), *gid_to_name(), *filemode();
	void mode_to_letters();
	char modestr[11];
	
	mode_to_letters(info_p->st_mode,modestr);
	total+=info_p->st_blocks/2;
	
	strcat(one[indx],modestr);
	two[indx] = (int) info_p->st_nlink;
	strcat(three[indx] ,uid_to_name(info_p->st_uid));
	strcat(four[indx] ,gid_to_name(info_p->st_gid));
	five[indx]= (long)info_p->st_size;
	if(!strcmp(filename,"sample"))
		info_p->st_mtime=0;
	strcpy(six[indx],4+ctime(&info_p->st_mtime));
	six_proto[indx]=info_p->st_mtime;
	strcpy(seven[indx],filename);
	indx++;
}

void mode_to_letters(int mode, char str[]){
	strcpy(str, "----------");

	if(S_ISDIR(mode)) str[0]='d';
	if(S_ISCHR(mode)) str[0]='c';
	if(S_ISBLK(mode)) str[0]='b';
	
	if(mode & S_IRUSR) str[1]='r';
	if(mode & S_IWUSR) str[2]='w';
	if(mode & S_IXUSR) str[3]='x';
	if(mode & S_ISUID) str[3]='s';
	
	if(mode & S_IRGRP) str[4]='r';
	if(mode & S_IWGRP) str[5]='w';
	if(mode & S_IXGRP) str[6]='x';
	if(mode & S_ISGID) str[6]='s';
	
	if(mode & S_IROTH) str[7]='r';
	if(mode & S_IWOTH) str[8]='w';
	if(mode & S_IXOTH) str[9]='x';
	if(mode & S_ISVTX) str[9]='T';

}

#include <pwd.h>
char* uid_to_name(uid_t uid){
	// return pointer to username associated with uid,
	// uses getpw()

	struct passwd *getpwuid(), *pw_ptr;
	static char numstr[10];

	if((pw_ptr = getpwuid(uid))==NULL){
		sprintf(numstr,"%d",uid);
		return numstr;
	}
	else
		return pw_ptr->pw_name;
}

#include <grp.h>
char* gid_to_name (gid_t gid){
	// return pointer to group number gid.
	// uses getgrgid(3)

	struct group *getgrid(), *grp_ptr;
	static char numstr[10];
	if((grp_ptr = getgrgid(gid))==NULL){
		sprintf(numstr,"%d",gid);
		return numstr;
	}
	else
		return grp_ptr->gr_name;
}

void find_index(time_t list[], int num){
	time_t max;
	int i,j,cnt=0;
	
	for(i=0;i<num;i++){
		max=list[i];
		for(j=0;j<num;j++){
			if(difftime(list[j],max)>0)
				max=list[j];
		}
		for(j=0;j<num;j++)
		 if(difftime(list[j],max)==0){
		 	lindx[cnt]=j;	
		 	list[j]=-1;
		 	cnt++;
		 	break;
		 	}
	}
}
