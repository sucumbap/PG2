#include <stdio.h>
#include <ctype.h>
#include "Ex2.h"
#include "Ex3.h"



//3.1
int normSymb( char str[], int idx ){
	
	int i = utf8Print( str, idx );
		
	if(i == 1){
		if(str[idx] <= 0x5A && str[idx] >= 0x41){
			str[idx] = str[idx] + 0x20;
			}
	}
	else{
		if(i==2){
			idx++;
			if(str[idx] < 0xa0){
				str[idx] = str[idx] + 0x20;
			}			
		}	
	}
	return i;
}


//3.2
void normString( char str [] ){
	
	int z = 0;
	int idx = 0;
	int x = 0;
	
	for (idx; str[idx] != '\0' ; idx = idx + x) {
		
		x = normSymb( str, idx );
		
		if(str[idx] == 0x2D){ //verificar se é hifen
			
			//se a seguir for espaço ou se o anterior for espaço ou se a seguir for o fim do str ou se estivermos no primeiro str
			if (str[idx + x] ==  0x20 || str[idx - z] == 0x20 || str[idx + x] == '\0' || idx==0){
				
				str[idx] = 0x20; //entao substituir o hifen por espaço
			}	
		}
		z = x;	// guardar valor bytes	
	}
}