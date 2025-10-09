#include<stdio.h>
#include<unistd.h>
#include<sys/stat.h>
#include<stdlib.h>
#include<string.h>
#include<dirent.h>

void recur(char*);

int main(int argc, char*argv[]){

	char*path;
	path = argv[1];
	recur(path);

return 0;}

void recur(char*base_path){
	DIR*dp = NULL;
	char new_path[1024];
	struct dirent *ent;
	dp = opendir(base_path);

	if(dp == NULL ){
		printf("Directory not opened.\n");
		exit(1);
	}
	while((ent=readdir(dp))!=NULL){
		if(strcmp(ent->d_name,".")==0 || strcmp(ent->d_name,"..")==0)
			continue;
		else
		{	 if(ent->d_type == 4){
				printf("Dir : %s\n",ent->d_name);
				snprintf(new_path, sizeof(new_path), "%s/%s", base_path, ent->d_name);
				recur(new_path);
				printf("-----------------\n");
			}
			else
				printf("File : %s\n",ent->d_name);
		}
	}
	closedir(dp);
}
