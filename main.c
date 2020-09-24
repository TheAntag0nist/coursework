#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "headers/message.h"
#include "headers/compress.h"
//-------------------------------------------------------------------------
//___________________________DEFINE__ZONE__________________________________
//-------------------------------------------------------------------------
#define SRC_SIZE 64
#define TIME_SIZE 16
#define COMM_SIZE 32
#define true 1
#define null 0
//-------------------------------------------------------------------------
//_________________________PROTOTYPE__ZONE_________________________________
//-------------------------------------------------------------------------
int compress(char *src, char flag);
//-------------------------------------------------------------------------
//-------------------------------------------------------------------------
int main(int argc,char* argv[]){
    char *source,
         *type_compress,
         *command;
    int reaction = 0,
        i = 0;

    // allocate memory for src
    source = errch_malloc(SRC_SIZE);
    type_compress = errch_malloc(SRC_SIZE);
    command = errch_malloc(COMM_SIZE);

    inf_message("start work dt_compress",'+',"");

    // read commands
    if(argc < 2){
        inf_message(" wait commands (for more information enter -help)",'d',"");
        
        while(true){
            printf("dt_compress > ");
            scanf("%s",command);

            reaction += arg_prog(command);

            if((reaction & 1) == 1){
                inf_message("enter src",'e',"");
                printf("\tsrc --> ");
                scanf("%s",source);
                
                reaction &= ~1;
            }
        }
    }else{
        for(i = 0; i < argc; ++i){ 
            reaction += arg_prog(argv[i]);

            if((reaction & 1) == 1 && ( i + 1) != argc){
                source = argv[i+1];

                reaction &= ~1;
            }
        }
    }

    inf_message(source, '+', "source -> ");

    if((reaction & 8) == 8)
        compress(source, 'l');
    else if((reaction & 4) == 4){
        compress(source, 's');
    }
    else
        inf_message("need more data",'c',"");
}
//-------------------------------------------------------------------------
//-------------------------------------------------------------------------
int compress(char *src, char flag){
    FILE* cmp_file;
    char* time;
    int size_of_file = 0;
    char byte;

    time = errch_malloc(TIME_SIZE);

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

    time = get_time();
    inf_message(time,'t', "");

    // write bytes from file in console
    while(fread( &byte, sizeof(byte), 1, cmp_file) != 0){
        printf("\t%c",byte);

        if(flag == 's')
            mtf_encode_simple(byte);
        else if(flag == 'l')
            mtf_encode_list(byte);
    }

    free_data();
    printf("\n");

    inf_message("successful transform",'+',"");
    // end programm
    fclose(cmp_file);
    system("pause");
    return 0;
}
//-------------------------------------------------------------------------
//-------------------------------------------------------------------------