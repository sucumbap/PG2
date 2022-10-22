#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>
#include <locale.h>


#define ARRAY_SIZE 7
#define BIT_SIZE 8
#define POSITIVE 1

enum ClassId { S_ASC, S_INIT, S_CONT };
struct fieldParams { int size; int pos; unsigned char val; int arr[ARRAY_SIZE]; } param;
struct Sentence { unsigned char str[200]; int size; }sentence, phrase;

int flag = 0;
int bitField( int siz, int pos, unsigned char val );
int printBit(int pos, unsigned char val);
int invokeQuestions();
int error(char *message);
int convertToDecimal( unsigned char val, int siz );
unsigned char workByte( int siz, int pos, unsigned char val );
enum ClassId utf8Class( unsigned char c );
int utf8Print( unsigned char data[], int start);
void arrayPrintHex( unsigned char data[], int start, int size );
int inquireWords();
int convertSConSentence();
int normSymb( char str[], int idx );
void ex1();
void ex21();
void ex22();
void ex23();
void ex24();
void ex31();

int main() {
    //ex1();
    //ex21();
    //ex22();
    //ex23();
    //ex24();
    ex31();
    return 0;
}








void ex1() {
    invokeQuestions();
    int res = bitField(param.size, param.pos, param.val);
    printf("Result: %d\n", res);
}
void ex21() {
    utf8Class(sentence.str[2]);
}
void ex22() {
    utf8Print("#Fs+Tsd", 4);
}
void ex23() {
    unsigned char x[] = { 0x61, 0xc3, 0xa7, 0xc3, 0xa3, 0x6f };
    arrayPrintHex( x, 0, 5 );
}
void ex24() {
    inquireWords();
    
    convertSConSentence();
}
void ex31() {
    char a[] = {"ERAM UMA VEZ UMINDSFVBOIWEDOFPIONB ING UI DSGÇÇ"};
    for (int i = 0; i < strlen(a); i++) {

        normSymb(a, i);
    }
    
}
int bitField( int siz, int pos, unsigned char val ) {
    val = workByte(siz, pos, val);
    return convertToDecimal(val, siz); 
}
unsigned char workByte( int siz, int pos, unsigned char val ) {
    val = val >> BIT_SIZE - (pos + siz);
    val = val << BIT_SIZE - siz;
    return val;
}
int convertToDecimal( unsigned char val, int siz ) {
    int result = 0;
    for (int i = ARRAY_SIZE; i > ARRAY_SIZE - siz; i--) {
        result *= 2;
        result += (val >> i) & 0x01;        
    }
    return result;
}
int invokeQuestions() {
    printf("\nColoque o num de bits requesitados\n");
    if(scanf("%d", &param.size) != POSITIVE) return error("Numero de bits");
    if(param.size <= 0) return error("Numero de bits tem que ser maior que 0");
    printf("\nA posiçao onde comecar a leitura\n");
    if(scanf("%d", &param.pos) != POSITIVE) return error("Posição");
    printf("\nE um char\n");
    if(scanf("%s", &param.val) != POSITIVE) return error("Char");
    return 1;
}
int error(char *message) {
    printf("\nError: %s Inválido\n", message);
    return 0;
}
int utf8Print( unsigned char data[], int start ) {
    unsigned char Masc,temp;                                        // byte para mascara
    enum ClassId Me = utf8Class(data[start]);
    
    if(Me == S_ASC) {
        printf("%c",data[start]);
        return 1;
    }else if(Me == S_INIT){
        Masc = 224; temp = 192;
            if ((data[start] & Masc) == temp){
                printf("%c%c",data[start],data[start+1]);
                return 2;
            }
            Masc = 240; temp = 224;
            if((data[start] & Masc) == temp){
                printf("%c%c%c",data[start],data[start+1],data[start+2]);
                return 3;
            }
            Masc = 248; temp = 240;
            if((data[start] & Masc) == temp){
                printf("%c%c%c%c",data[start],data[start+1],data[start+2],data[start+3]);
                return 4;
            }
    }
    return 0;
}
enum ClassId utf8Class( unsigned char c ) {
    enum ClassId Me;
    if(c<0){error("ERROR");return -1;}
    if(c>=0 && c<=127){
        //printf("S_ASC\n");
        Me = S_ASC;
    }
    if(c>=128 && c<=191){
        //printf("S_CONT\n");
        Me = S_CONT;
    }
    if(c>=194 && c<=255){
        //printf("S_INIT\n");
        Me = S_INIT;
    }
    return Me;
}
void arrayPrintHex( unsigned char data[], int start, int size ){
     if (size == 2){
        printf("{%.2x %.2x}",data[start],data[start+1]);
        return;
    }
    if(size == 3){
        printf("{%.2x %.2x %.2x}",data[start],data[start+1],data[start +2]);
        return;
    }
    if(size == 4){
        printf("{%.2x %.2x %.2x %.2x}",data[start],data[start+1],data[start+2],data[start+3]);
        return;
    }
    return ;
}
int convertSConSentence() {
    for (int i = 0, j = 1; i < sentence.size; i++) {
        if(utf8Class(sentence.str[i]) == S_INIT || utf8Class(sentence.str[i]) == S_CONT) {         
            j = utf8Print(sentence.str,i);
            arrayPrintHex(sentence.str, i, j);
        } else {
            printf("%c", sentence.str[i]);
        }
    }
    return 0;
}
int inquireWords() {
    int j = 0;
    printf("\nColoque uma frase com no maximo 200 chars:\n");
    for(int i = 0; i < 200; i++) {
        scanf("%c", &sentence.str[i]);        
        if(sentence.str[i] =='\n') {i = 300;} else {j++;}
    }
    sentence.size = j;
    return j;
}

int normSymb( char str[], int idx ) {
    // char *p = &str[idx];
    // *p = *p > 0x40 && *p < 0x5b ? *p | 0x60 : *p;
    enum ClassId Me = utf8Class(str[idx]);
    switch (Me) {
        case S_ASC:
            printf("%c", tolower(str[idx]));
        break;
        default:
            utf8Print(str, idx);
            //printf("%c", str[idx] & 0x40);
            if(str[idx] >= 'A' && str[idx] <= 'Z') {
                str[idx] ^= 32;
                utf8Print(str, idx);

            } else if(str[idx] >= 'a' && str[idx] <= 'z') {
                utf8Print(str, idx);
            } else {
                utf8Print(str, idx);
            }


        break;
    }

    
    return 0;
}