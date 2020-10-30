#include <stdio.h>
#include <string.h>
#include "message.h"

void archive(char* name_of_archive){
    if(strcmp(name_of_archive, ""))
        strcat(name_of_archive, ".arch");
    else
        strcpy(name_of_archive, "archive.arch");    
        
    inf_message( name_of_archive, '+', "name_of_archive = ");
}