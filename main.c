//====================================================
// ©Antag0nist (Князюк Рюрик Александрович), 2020
//====================================================
#include <Windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h> 
#include "headers/message.h"
#include "headers/compress.h"
#include "headers/archive.h"
//-------------------------------------------------------------------------
//___________________________DEFINE__ZONE__________________________________
//-------------------------------------------------------------------------
#define SRC_SIZE 256
#define TIME_SIZE 32
#define COMM_SIZE 32
#define NAME_FILE_SIZE 64
#define true 1
#define false 0
#define null 0
//-------------------------------------------------------------------------
//___________________________GLOBAL__ZONE__________________________________
//-------------------------------------------------------------------------

//-------------------------------------------------------------------------
//____________________________PROGRESS_BAR_________________________________
//-------------------------------------------------------------------------
//threads zone
HANDLE thread;
long int num_cur_sym = 0;
long int size_of_file = 0;
char ProgressBar = true;
//-------------------------------------------------------------------------
//_________________________PROTOTYPE__ZONE_________________________________
//-------------------------------------------------------------------------
int compress(char *src, char *file_name, char flag);
DWORD WINAPI thread_2(LPVOID t);
BOOL ShowConsoleCursor(BOOL bShow);
//-------------------------------------------------------------------------
//-------------------------------------------------------------------------
int main(int argc,char* argv[]){
    // data zone
    char *source,
         *command;
    char file_name[NAME_FILE_SIZE],
         ch = 0;
    int reaction = 0,
        i = 0;

    // allocate memory for src
    source = errch_malloc(SRC_SIZE);
    command = errch_malloc(COMM_SIZE);

    file_name[0] = null;
    inf_message("start work dt_compress",'+',"");

    // read commands
    if(argc < 4){
        inf_message(" wait commands (for more information enter --help or help)",'d',"");
        
        // while not exit command
        while(true){
            printf("dt_compress > ");
            if(scanf("%s",command) == EOF)
                fatal("error in command");

            // save reaction on command
            reaction += arg_prog(command);

            // reaction --> get source of file
            if(reaction & 1){
                inf_message("enter src",'e',"");
                printf("\tsrc --> ");
                if(scanf("%s",source) == EOF){
                    fatal("error in input data");
                }
                
                reaction &= ~1;
            }

            if(reaction & 2){
                continue;
            }

            // reaction --> starts transform file
            if((reaction & 4) || (reaction & 8) || (reaction & 16) || (reaction & 32)){
                inf_message(source, '+', "source -> ");

                if(reaction & 8)
                    compress(source, file_name, 'l');
                else if(reaction & 4)
                    compress(source, file_name, 's');
                
                if(reaction & 16)
                    compress(source, file_name, 'w');
                else if(reaction & 32)
                    compress(source, file_name, 'o');
                
                reaction &= ~32;
                reaction &= ~16;
                reaction &= ~8;
                reaction &= ~4;
            }

            if(reaction & 64){
                if(ProgressBar == false)
                    printf("\tProgressBar = false");
                else
                    printf("\tProgressBar = true");

                printf("\n\tEnter num (true = 1, false = 0)...\n\tProgressBar = ");
                if(scanf("%d" , &ch) == EOF)
                    fatal("error in input data");

                if(ch == 0)
                    ProgressBar = false;
                else if(ch == 1)
                    ProgressBar = true;

                reaction &= ~64;
            }

            if(reaction & 256){
                inf_message("enter file_name",'e',"");
                printf("\tf_name --> ");
                if(scanf("%s",file_name) == EOF)
                    fatal("error in input data");

                reaction &= ~256;
            }
                
            // reaction --> exit reaction
            if(reaction & 512)
                break;

            if(reaction & 1024){
                printf("console> ");
                _flushall();
                gets(command);
                system(command);

                reaction &= ~1024;
            }

            if(reaction & 2048){
                inf_message("function of archivating...",'+',"");
                
                archive( file_name);
                reaction &= ~2048;
            }

            if(reaction & 4096){
                inf_message("unknown command", 'd', "");
                reaction &= ~4096; 
            }
        }
    // if program has arguments then read and exec them
    }else{
        for(i = 0; i < argc; ++i){ 
            reaction += arg_prog(argv[i]);

            if((reaction & 1) == 1 && (i + 1) != argc){
                source = argv[i+1];

                reaction &= ~1;
            }

            if(reaction & 256){
                strcpy( file_name,argv[i+1]);

                reaction &= ~256;
            }
        }

        // reaction --> starts transform file
        if((reaction & 4) || (reaction & 8) || (reaction & 16) || (reaction & 32)){
            inf_message(source, '+', "source -> ");

            // priority
            // 1 - encode
            // 1.1 list
            // 1.2 simple
            // 2 - decode
            // 2.1 - mtf_decode_list
            // 2.2 - mtf_decode
            if(reaction & 8)
                compress(source, file_name, 'l');
            else if(reaction & 4)
                compress(source, file_name, 's');
            else if(reaction & 16)
                compress(source, file_name, 'w');
            else if(reaction & 32)
                compress(source, file_name, 'o');
        }
    }


    inf_message("free memory", '+', "");
    printf("================================\nPress any key...");
    _flushall();
    getchar();
    // freee mem
    free(source);
    free(command);
    return 0;
}
//-------------------------------------------------------------------------
//__________________________COMPRESS___FUNCTION____________________________
//-------------------------------------------------------------------------
int compress(char *src, char* file_name, char flag){
    // data zone
    FILE* cmp_file;
    char* time;
    char byte;

    //================
    //___DEBUG_INFO___
    clock_t start,
            end;
    double seconds;
    //=================

    // allocate memory for time
    time = errch_malloc(TIME_SIZE);

    // open fo read as byte file
    cmp_file = fopen(src,"rb");

    if(cmp_file == null)
        fatal("can't open file");

    // get size of file
    fseek(cmp_file, 0L, SEEK_END);
    size_of_file = ftell(cmp_file);
    fseek(cmp_file, 0L, SEEK_SET);

    inf_message("open file successfull",'+',"");

    open_file(file_name);
    inf_message("create file for writting successfull",'+',"");
    
    if(flag == 'l' || flag == 'o'){
        create_list();
        inf_message("successfull create list",'+',"");
    }

    // display current time
    get_time(time);
    inf_message(time,'t', "");

    // create thread
    if(ProgressBar == true){
        thread = CreateThread(NULL,0,thread_2,NULL, 0, NULL);
        if(thread == NULL)
            fatal("can't create thread...");
        ShowConsoleCursor(false);
    }

    // save time_of_start
    start = clock();

    // write bytes from file in console
    while(fread( &byte, sizeof(byte), 1, cmp_file) != 0){
        // s - simple encode (mtf)
        // w - simple decode 
        // l - encode using list
        // o - decode using list

        if(flag == 's')
            mtf_encode_simple( byte);
        else if(flag == 'l')
            mtf_encode_list(byte);
        else if(flag == 'w')
            mtf_decode_simple(byte);
        else if(flag == 'o')
            mtf_decode_list(byte);

        num_cur_sym++;
    }
    // save time_of_end
    end = clock();

    // close thread
    if(ProgressBar == true){
        ShowConsoleCursor(true);
        printf("\n");
    }
    
    num_cur_sym = 0;
    size_of_file = 0;

    seconds = (double) (end - start) / CLOCKS_PER_SEC;
    sprintf(time, "%f", seconds);
    inf_message(time,'t',"time of work --> ");

    // display current time
    get_time(time);
    inf_message(time,'t', "");

    file_name[0] = null;
    free_data(flag);
    
    inf_message("successful transform",'+',"");
    // end programm
    free(time);
    fclose(cmp_file);
    return 0;
}
//-------------------------------------------------------------------------
//-------------------------------------------------------------------------
BOOL ShowConsoleCursor(BOOL bShow){
    CONSOLE_CURSOR_INFO cci;
    HANDLE hStdOut;

    hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
    
    if(hStdOut == INVALID_HANDLE_VALUE)
        return FALSE;
    if(!GetConsoleCursorInfo(hStdOut, &cci))
        return FALSE;
    cci.bVisible = bShow;
    if(!SetConsoleCursorInfo(hStdOut,&cci))
        return FALSE;
    
    return TRUE;
}
//-------------------------------------------------------------------------
//____________________________PROGRESS_THREAD______________________________
//-------------------------------------------------------------------------
DWORD WINAPI thread_2(LPVOID t){
    int res;
    // show progress bar
    while(res != 100 && size_of_file != 0)
        res = progress_bar( num_cur_sym, size_of_file);

    return 0;
}
