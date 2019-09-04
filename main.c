#include "libraries.h"

char HOME_DIR[1000000];
char* CUR_USER;
char* CUR_SYSTEM;
char ABS_PATH[1000000];
char PATH_NAME[100000] = "~";
DIR *PATH_CHECK;

struct utsname UName;

int number_of_arguments;
char **tokens;
char *token_pointers;

void clear_screen()
{
  const char *CLEAR_SCREEN = "\e[1;1H\e[2J";
  write(1, CLEAR_SCREEN, 11);
}

void print_prompt(){

}

char *read_input(void){
    // Allocate size to buffer
    // Read character in loop
    // Replace EOF with null characters
    // Increase allocated space when buffer limit is exceeded

    // Use getline() function --> allocates appropriate buffer size
    int buffer_size = 0;
    char *input_line = NULL;
    getline(&input_line, &buffer_size, stdin);
    return input_line;
}

#define DELIMITERS " \t\r\n\a"
#define BUFFER_SIZE 128

void check_validity_parse(char *check_for){
// Checks if (check_for) parameter has been allocated memory correctly
    if(!check_for){
        fprintf(stderr, "parse_line : allocation error\n");
        exit(EXIT_FAILURE);
    }
}

char **parse_line(char *input){

    free(tokens);
    token_pointers = NULL;
    
    // Allocate buffer size and memory
    int buffer_size = BUFFER_SIZE;
    tokens = malloc(buffer_size * sizeof(char*));

    check_validity_parse(tokens);

    // Split input line into words
    // token_pointers --> gives the pointers to beginning of each token
    // tokens --> saves the list of pointers in array of pointers
    token_pointers = strtok(input, DELIMITERS);
    number_of_arguments = 0;
    while(token_pointers != NULL){
        tokens[number_of_arguments] = token_pointers;
        number_of_arguments++;

        // Reallocate memory when necessary
        if(number_of_arguments>=buffer_size){
            buffer_size += BUFFER_SIZE;
            tokens = realloc(tokens, buffer_size*sizeof(char*));
            check_validity_parse(tokens);
        }

        token_pointers = strtok(NULL, DELIMITERS);
    }
    tokens[number_of_arguments] = NULL;
    return tokens;
}

void validity(char* valid){
    if(valid == NULL){
        perror("Error : ");
        exit(1);
    }
}

int main(){

    // Clear screen
    clear_screen();

    // Check UNAME
    int check = uname(&UName);
    if(check != 0  ){
        perror("Error\n");
        exit(1);
    }

    // Set system constants
    char* valid_check = NULL;

    // HOME_DIR
    valid_check = getcwd(HOME_DIR, 1000000);
    validity(valid_check);
    //printf("%s\n", HOME_DIR);

    // CUR_USER
    CUR_USER = getenv("USER");
    validity(CUR_USER);
    //printf("%s\n", CUR_USER);

    //CUR_SYSTEM
    CUR_SYSTEM = UName.nodename;
    //printf("%s\n", CUR_SYSTEM);

    //ABS_PATH
    valid_check = getcwd(ABS_PATH, 1000000);
    validity(valid_check);

    //REL_PATH
    DIR* directory;
    directory = opendir(ABS_PATH);
    if(directory == NULL){
        perror("Error : ");
    }

    // Run command loop
    char *input_line;
    char **parsed_line;
    int valid = 1 ;

    while(valid){
        // Print prompt

        char* result = NULL;
        result = getcwd(ABS_PATH, 1000000);
        //printf("Abs Path : %s\n", ABS_PATH);
        validity(result);

        // PROMPT PATH

        if (strlen(HOME_DIR) > strlen(ABS_PATH))
        {
            strcpy(PATH_NAME, ABS_PATH);
        }
        else if (!strcmp(HOME_DIR, ABS_PATH))
        {
            strcpy(PATH_NAME, "~");
        }

        int flag = 1;
        int i = 0;
        for (i = 0; i < strlen(HOME_DIR); ++i)
        {
            if (ABS_PATH[i] != HOME_DIR[i])
            {
                flag = 0;
                break;
            }
        }

        if (flag == 1)
        {
            strcpy(PATH_NAME, "~");
            char temp[1];
            for (; i < strlen(ABS_PATH); ++i)
            {
                temp[0] = ABS_PATH[i];
                strcat(PATH_NAME, temp);
            }
        }
        else
        {
            strcpy(PATH_NAME, ABS_PATH);
        
        }

        printf("%s%s@%s%s : %s%s ", GREEN,CUR_USER, BLUE, CUR_SYSTEM, CYAN, PATH_NAME);
        printf(RESET);

        // Read
        input_line = read_input();

        // Parse
        parsed_line = parse_line(input_line);
        //printf("%s, %d\n", parsed_line[0], number_of_arguments);
            
        // Execute

        // Check first token (command)
        if(strcmp(parsed_line[0], "cd") == 0){
            cd(parsed_line, number_of_arguments);
        }
        else if(strcmp(parsed_line[0], "pwd") == 0){
            if(number_of_arguments > 1){
                fprintf(stderr, "Too many arguments for command : pwd\n");
                exit(EXIT_FAILURE);
            }
            pwd();
        }
        else if(!strcmp(parsed_line[0], "echo")){
                //printf("entered echo\n");
                int i = 1;
                for(; i<number_of_arguments; i++){
                    printf("%s ", parsed_line[i]);
                }
                printf("\n");
        }
        else if(!strcmp(parsed_line[0], "ls")){
            // ls(number_of_arguments, parsed_line);
        }
        else if(!strcmp(parsed_line[0], "vim")){
        }
        else if(!strcmp(parsed_line[0], "pinfo")){
        }
        else if(!strcmp(parsed_line[0], "quit")){
            if(number_of_arguments > 1){
                fprintf(stderr, "Too many arguments for command : quit\n");
                exit(EXIT_FAILURE);
            }
            // Change validity to break out of loop and exit shell
            valid = 0;
        }

    }

    // Perform shutdown/cleanup

    return EXIT_SUCCESS;
}