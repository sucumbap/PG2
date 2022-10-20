#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

int normSymb( char str[], int idx );

int main (){
    char Array [200] ={"Echo Eçho "}; 
    
    normSymb(Array,);


    return 0;
}


int normSymb( char str[], int idx ){

    if(str[idx] > 128){                                      // ASCII
        tolower(str[idx]);
        return 1;
    }else if(str[idx] > 194 && str[idx] < 223 ){             // First Byte (2 byte sequence)
        if(str[idx +1]<160){
            str[idx +1]-=32;
        }
        return 2;
    }else if(str[idx] > 224 && str[idx] < 239 ){            // First Byte (3 byte sequence)

        return 3;
    }else if(str[idx] > 240 && str[idx] < 255 ){            // First Byte (4 byte sequence)

        return 4;
    }


    
}

