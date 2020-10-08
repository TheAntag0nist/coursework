#ifdef _WIN32
    #include <Windows.h>
#endif

#include <time.h>
#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <string.h>

#define SIZE_MESS 128

// ONLY WINDOWS VERSION
#ifdef _WIN32
enum ConsoleColor {
Black = 0,
Blue = 1,
Green = 2,
Cyan = 3,
Red = 4,
Magenta = 5,
Brown = 6,
LightGray = 7,
DarkGray = 8,
LightBlue = 9,
LightGreen = 10,
LightCyan = 11,
LightRed = 12,
LightMagenta = 13,
Yellow = 14,
White = 15
};


void SetColor(int ForgC)
{
    WORD wColor;
    // we will need this handle to get the current background attribute
    HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFO csbi;
 
    // we use csbi for the wAttributes word.
    if(GetConsoleScreenBufferInfo(hStdOut, &csbi))
    {
        // mask out all but the background attribute, and add in the forgournd color
        wColor = (csbi.wAttributes & 0xF0) + (ForgC & 0x0F);
        SetConsoleTextAttribute(hStdOut, wColor);
    }
     
    return;
}
#endif
//-------------------------------------------------------------------------
//-------------------------------------------------------------------------
void inf_message(char* message,char flag_sym,char* middle_str){
    char inform[20];
    int color;

    switch (flag_sym)
    {
    // + - successful execution  
    case '+':
        strcpy(inform, "[+] Info: ");
        color = LightBlue;
        break;
    // - - not successful execution
    case '-':
        strcpy(inform, "[-] Info: ");
        color = Cyan;
        break;
    // c - close    
    case 'c':
        strcpy(inform,"[EXIT] Info: ");
        color = Cyan;
        break;
    // d - debug
    case 'd':
        strcpy(inform,"[DEBUG] Info: ");
        color = Cyan;
        break;
    // e - enter data
    case 'e':
        strcpy(inform,"[DATA] Info: ");
        color = LightGreen;
        break;
    case 't':
        strcpy(inform,"[TIME] --> ");
        color = Cyan;
        break;
    // default
    default:
        break;
    }   

    #ifdef _WIN32
        SetColor(color);
    #endif

    printf("%s",inform);

    #ifdef _WIN32
        SetColor(White);
    #endif

    printf("%s %s\n", middle_str, message);
}
//-------------------------------------------------------------------------
//-------------------------------------------------------------------------
void fatal(char* message){
    char err_mess[SIZE_MESS];

    #ifdef _WIN32
        SetColor(Red);
    #endif

    strcpy(err_mess,"[!!] Critical Error: ");
    printf("%s",err_mess);

    #ifdef _WIN32
        SetColor(White);
    #endif

    strcpy(err_mess,message);
    printf(err_mess);

    printf("\n");
    inf_message(" press ENTER for exit",'c',"");

    _flushall();
    getchar();
    exit(0);
}
//-------------------------------------------------------------------------
//-------------------------------------------------------------------------
void* errch_malloc(unsigned int mem_size){
    void* ptr = malloc(mem_size);
    if(ptr == 0)
        fatal("can't allocate memory");
    return ptr;
}
//-------------------------------------------------------------------------
//-------------------------------------------------------------------------
int arg_prog(char* message){
    if(!strcmp(message,"-version")){
        inf_message("  dt_compress (DT_COMPRESS) v1.1.8\n\t\t Project for encoding, decoding and archive data.",'d',"");
        return 0;
    }
    else if(!strcmp( message, "--src") || !strcmp( message, "src"))
        return 1;
    else if(!strcmp( message, "--time") || !strcmp( message, "time"))
        return 2;
    else if(!strcmp( message, "--mtf") || !strcmp( message, "mtf"))
        return 4;
    else if(!strcmp( message, "--mtf_list") || !strcmp( message, "mtf_list"))
        return 8;
    else if(!strcmp( message, "--mtf_decode") || !strcmp( message, "mtf_decode"))
        return 16;
    else if(!strcmp( message, "--f_name") || !strcmp( message, "f_name"))
        return 256;
    else if(!strcmp( message, "--exit") || !strcmp( message, "exit")){
        inf_message("exit from program",'c',"");
        getchar();
        return 512; 
    }
    else if(!strcmp( message, "--help") || !strcmp( message, "help")){
        inf_message("this is list of commands (commands are entered sequentially and separately)",'+',"");
        printf("\t--src (src) - source on file that need compress or transform\n\t--f_name (f_name) - set your own filename\n\t--mtf (mtf) - transform file (src) using move-to-front(stack of books)\n\t--mtf_decode (mtf_decode) - decode using simple way with mass\n\t--mtf_list (mtf_list) - transform file (src) using move-to-front(stack of books) with list\n\t--help (help) - display info about commands\n\t--exit (exit) - exit from programm\n");
    }
    else
        return 1024;
}
//-------------------------------------------------------------------------
//-------------------------------------------------------------------------
int get_time(char* time_tmp){
    time_t timer; 
    struct tm* tm_info;
    char tmp[5]; 

    // get current time
    time(&timer); 
    tm_info = localtime(&timer); 
 
    // get time info
    // and save info in my own format
    strftime(tmp, 3, "%d", tm_info);

    strcpy(time_tmp,"[");
    strcat(time_tmp, tmp);

    strftime(tmp, 3, "%m", tm_info); 

    strcat(time_tmp,":");
    strcat(time_tmp, tmp);

    strftime(tmp, 5, "%Y", tm_info);

    strcat(time_tmp,":");
    strcat(time_tmp, tmp);

    strftime(tmp, 3, "%H", tm_info);

    strcat(time_tmp, " ");
    strcat(time_tmp, tmp);

    strftime(tmp, 3, "%M", tm_info); 

    strcat(time_tmp,":");
    strcat(time_tmp, tmp);

    strftime(tmp, 3, "%S", tm_info); 

    strcat(time_tmp,":");
    strcat(time_tmp, tmp);

    strcat(time_tmp, tmp);
    strcat(time_tmp,"] ");

    return 0;
}