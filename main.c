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
#define TIME_SIZE 32
#define COMM_SIZE 32
#define NAME_FILE_SIZE 64
#define true 1
#define false 0
#define null 0
//-------------------------------------------------------------------------
//_________________________PROTOTYPE__ZONE_________________________________
//-------------------------------------------------------------------------
int compress(char *src, char *file_name, char flag);
//-------------------------------------------------------------------------
//-------------------------------------------------------------------------
int main(int argc,char* argv[]){
    char *source,
         *command;
    char file_name[NAME_FILE_SIZE];
    int reaction = 0,
        i = 0;

    // allocate memory for src
    source = errch_malloc(SRC_SIZE);
    command = errch_malloc(COMM_SIZE);

    file_name[0] = null;
    inf_message("start work dt_compress",'+',"");

    // read commands
    if(argc < 2){
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
            if((reaction & 4) || (reaction & 8) || (reaction & 16)){
                inf_message(source, '+', "source -> ");

                if((reaction & 8) == 8)
                    compress(source, file_name, 'l');
                else if((reaction & 4) == 4)
                    compress(source, file_name, 's');
                
                if(reaction & 16)
                    compress(source, file_name, 'w');
                
                reaction &= ~16;
                reaction &= ~8;
                reaction &= ~4;
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

        if(reaction & 256){
            strcpy( file_name,argv[i+1]);

            reaction &= ~256;
        }

        // reaction --> starts transform file
        if((reaction & 4) || (reaction & 8)){
            inf_message(source, '+', "source -> ");

            // priority
            // 1 - encode
            // 1.1 list
            // 1.2 simple
            // 2 - decode
            // 2.1 - mtf_decode
            if(reaction & 8)
                compress(source, file_name, 'l');
            else if(reaction & 4)
                compress(source, file_name, 's');
            else if(reaction & 16)
                compress(source, file_name, 'w');
        }
    }

    inf_message("free memory", '+', "");
    printf("==================================");
    // freee mem
    free(source);
    free(command);
}
//-------------------------------------------------------------------------
//__________________________COMPRESS___FUNCTION____________________________
//-------------------------------------------------------------------------
int compress(char *src, char* file_name, char flag){
    FILE* cmp_file;
    char* time;
    int size_of_file = 0;
    char byte;

    // allocate memory for time
    time = errch_malloc(TIME_SIZE);

    // open fo read as byte file
    cmp_file = fopen(src,"rb");

    if(cmp_file == null)
        fatal("can't open file");

    inf_message("open file successfull",'+',"");

    open_file(file_name);
    inf_message("create file for writting successfull",'+',"");
    
    if(flag == 'l'){
        create_list();
        inf_message("successfull create list",'+',"");
    }

    // display current time
    get_time(time);
    inf_message(time,'t', "");

    // write bytes from file in console
    while(fread( &byte, sizeof(byte), 1, cmp_file) != 0){
        printf("\tbyte = %d\t",byte);
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
            break;
    }

    file_name[0] = null;
    free_data(flag);

    printf("\n");
    inf_message("successful transform",'+',"");
    // end programm
    free(time);
    fclose(cmp_file);
    return 0;
}
//-------------------------------------------------------------------------
//-------------------------------------------------------------------------