#include<stdio.h>
#include<stdbool.h>

int main(){

    int fault=0,buf[3],seq[10];
    printf("Enter the sequence :");
    for(int i=0; i<10; i++){
        scanf("%d",&seq[i]);
    }
    for(int i=0; i<3; i++){
        buf[i]=-1;
    }
    int buf_index = 0;
    for(int x=0; x<10; x++){
        int current_pg = seq[x];
        bool found = false;
// check if the current frame is already in the buffer
        for(int y=0; y<3; y++){
            if(buf[y]==current_pg){
                found = true;
                break;
            }
        }
       // printf("%d",current_pg);
        if(!found){
            buf[buf_index]=current_pg; 
            buf_index = (buf_index+1)%3;
            fault++;
            printf("[");
            for (int j = 0; j < 3; j++) {
                if (buf[j] != -1) {
                    printf("%d ", buf[j]);
                } else {
                    printf("- ");
                }
            }
            printf("] | (Fault)\n");
            }
        else{
            printf("[");
            for (int j = 0; j < 3; j++) {
                if (buf[j] != -1) {
                    printf("%d ", buf[j]);
                } else {
                    printf("- ");
                }
            }
            printf("] | (Hit)\n");
        }
        
        }
    
    printf("No. of faults : %d\n",fault);     
    return 0;
}