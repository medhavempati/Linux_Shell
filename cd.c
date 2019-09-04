#include "libraries.h"

extern char HOME_DIR[1000000];
extern char* CUR_USER;
extern char* CUR_SYSTEM;
extern char ABS_PATH[1000000];
extern char REL_PATH_NAME[1000000];
extern DIR *REL_PATH;

struct utsname UName;

// extern int number_of_arguments;
// extern char **tokens;
// extern char *token_pointers;

void chck(char *check_for){
// Checks if (check_for) parameter has been allocated memory correctly
    if(check_for){
        perror("Error changing directory");
    }
}

void cd(char* parsed_line[], int number_of_arguments ){
    
    // HOME dir
    if(strcmp(parsed_line[1], "~") == 0 || number_of_arguments < 2){
        int chk = chdir(HOME_DIR);
        chck(chk);

    }
    // Current dir
    else if(strcmp(parsed_line[1], ".") == 0){
        return;
    }

    // Regular Case

    char* new_dir[1000000];

    // From ~
    if(parsed_line[1][0] == "~"){
        parsed_line[1][0] = ".";

        new_dir[0] = HOME_DIR;
        strcpy(new_dir, "/");
        strcpy(new_dir, parsed_line[1]);
    }

    // If relative path is given
    else if(parsed_line[1][0] == "/"){
        strcpy(new_dir, parsed_line[1]);
    }

    // Else
    else{
        strcpy(new_dir, ABS_PATH);
        strcpy(new_dir, "/");
        strcpy(new_dir, parsed_line[1]);
    }

    // Check if valid
    int chk = chdir(new_dir);
    chck(chk);

}