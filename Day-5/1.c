#include<stdio.h>
#include<stdlib.h>
#include<dirent.h>
#include<unistd.h>
#include<sys/stat.h>
#include<string.h>

int main(int argc, char *argv[])
{
	int count =1;
	char *path;
	DIR *p1 = NULL;
	DIR *p2 = NULL;
	struct dirent *ent;
	struct dirent *ent1;
	char cwd[40];
	if(argc != 2)
	{
		printf("Directory path is not mentioned...\n");
		printf("Run as : %s <dir path>\n", argv[0]);
		exit(1);
	}
	
	path = argv[1];
	
	p1 = opendir(path);
	if(p1 == NULL)
	{
		printf("Directory is not opened...\n");
		exit(1);
	}

	printf("\nDirectory content with details : \n");
	while((ent = readdir(p1)) != NULL)
	{
		if((strcmp(ent->d_name,".")&& strcmp(ent->d_name,".."))==0)
			continue;
	
		struct stat st;
		
		int ret = stat(ent->d_name, &st);
		if(ret == -1)
		{
			printf("stat() is failed \n");
			exit(ret);
		}
		
		printf("\n");
		printf("File-%d\n",count);
		printf("Filename- = %s\n",ent->d_name);
		printf("inode = %lu\n", st.st_ino);
		printf("mode = %u\n", st.st_mode);
		printf("nlink = %lu\n", st.st_nlink);
		printf("size = %lu\n", st.st_size);
		printf("Type = %u\n", ent->d_type);
		count++;
	}
	
	closedir(p1);

	return 0;
}















