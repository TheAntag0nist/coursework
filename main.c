//====================================================
// ©Antag0nist (Князюк Рюрик Александрович), 2020
//====================================================
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "headers/message.h"
#include "headers/compress.h"
//-------------------------------------------------------------------------
//___________________________DEFINE__ZONE__________________________________
//-------------------------------------------------------------------------
#define SRC_SIZE 256
#define TIME_SIZE 22
#define COMM_SIZE 32
#define true 1
#define false 0
#define null 0
//-------------------------------------------------------------------------
//___________________________GLOBAL__ZONE__________________________________
//-------------------------------------------------------------------------
char* time;
//-------------------------------------------------------------------------
//_________________________PROTOTYPE__ZONE_________________________________
//-------------------------------------------------------------------------
int compress(char *src, char flag);
//-------------------------------------------------------------------------
//-------------------------------------------------------------------------
int main(int argc,char* argv[]){
    char *source,
         *command;
    int reaction = 0,
        i = 0;

    // allocate memory for src
    source = errch_malloc(SRC_SIZE);
    command = errch_malloc(COMM_SIZE);
    time = errch_malloc(TIME_SIZE);

    inf_message("start work dt_compress",'+',"");

    // read commands
    if(argc < 2){
        inf_message(" wait commands (for more information enter --help or help)",'d',"");
        
        // while not exit command
        while(true){
            printf("dt_compress > ");
            scanf("%s",command);

            // save reaction on command
            reaction += arg_prog(command);

            // reaction --> get source of file
            if(reaction & 1){
                inf_message("enter src",'e',"");
                printf("\tsrc --> ");
                scanf("%s",source);
                
                reaction &= ~1;
            }

            if(reaction & 2){
                continue;
            }

            // reaction --> starts transform file
            if((reaction & 4) || (reaction & 8)){
                inf_message(source, '+', "source -> ");

                if((reaction & 8) == 8)
                    compress(source, 'l');
                else if((reaction & 4) == 4){
                    compress(source, 's');
                }

                reaction &= ~8;
                reaction &= ~4;
            }
                
            // reaction --> exit reaction
            if(reaction & 512)
                break;

            if(reaction & 1024){
                inf_message("unknown command", 'd', "");
                reaction &= ~1024; 
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
        }

        // reaction --> starts transform file
        if((reaction & 4) || (reaction & 8)){
            inf_message(source, '+', "source -> ");

            // priority
            // 1. list
            // 2. simple
            if((reaction & 8) == 8)
                compress(source, 'l');
            else if((reaction & 4) == 4){
                compress(source, 's');
            }
        }
    }

    inf_message("free memory", '+', "");
    printf("==================================");
    // freee mem
    free(source);
    free(command);
    free(time);
}
//-------------------------------------------------------------------------
//__________________________COMPRESS___FUNCTION____________________________
//-------------------------------------------------------------------------
int compress(char *src, char flag){
    FILE* cmp_file;
    int size_of_file = 0;
    char byte;

    // open fo read as byte file
    cmp_file = fopen(src,"rb");

    if(cmp_file == null)
        fatal("can't open file");

    inf_message("open file successfull",'+',"");

    open_file();
    inf_message("create file for writting successfull",'+',"");
    
    if(flag == 'l'){
        create_list();
        inf_message("successfull create list",'+',"");
    }

    //if(!get_time(time))
    //    fatal("can't get time...");
    //inf_message(time,'t', "");

    // write bytes from file in console
    while(fread( &byte, sizeof(byte), 1, cmp_file) != 0){
        printf("\t%c",byte);

        // s - simple encode (mtf)
        // w - simple decode 
        // l - encode using list
        // o - decode using list

        if(flag == 's')
            mtf_encode_simple(byte);
        else if(flag == 'l')
            mtf_encode_list(byte);
        else if(flag == 'o')
            break;
        else if(flag == 'w')
            break;
    }

    free_data(flag);

    printf("\n");
    inf_message("successful transform",'+',"");
    // end programm
    fclose(cmp_file);
    return 0;
}
//-------------------------------------------------------------------------
//-------------------------------------------------------------------------