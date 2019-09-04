#include "libraries.h"

void pwd(){
    char wd[2048];
    char *check = getcwd(wd, sizeof(wd));
    if(check == NULL){
        perror("print_prompt : getcwd() error");
        exit(1);
    }
    else{
        printf("%s\n", wd);
    }
}

// int main(){
//     printf("Pwd:\n");
//     pwd();
//     return 0;
// }