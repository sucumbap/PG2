#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#define ARRAY_SIZE 7
#define BIT_SIZE 8
#define POSITIVE 1

enum ClassId { S_ASC, S_INIT, S_CONT };
struct fieldParams { int size; int pos; unsigned char val; int arr[ARRAY_SIZE]; } param;

int bitField( int siz, int pos, unsigned char val );
int printBit(int pos, unsigned char val);
int invokeQuestions();
int error(char *message);
int convertToDecimal( unsigned char val, int siz );
unsigned char workByte( int siz, int pos, unsigned char val );
enum ClassId utf8Class( unsigned char *c );
int utf8Print( unsigned char data[], int start);
void arrayPrintHex( unsigned char data[], int start, int size );
void ex1();
void ex22();

int main() {
    //ex1();
    //ex22();
    //printf("\n%d\n", utf8Class("高"));
    unsigned char x[] = { 0x61, 0xc3, 0xa7, 0xc3, 0xa3, 0x6f };
    arrayPrintHex ( x, 3, 5 );
    return 0;
    
}

void arrayPrintHex( unsigned char data[], int start, int size ){
    if (start + size > strlen(data)) error("arrayPrintHex valores"); return;
    printf("{ ");
    for (int i = 0; i < size; i++) {
        int j = i+1;
        if (j < size) {
            printf("%x, ", data[start + i]);
        } else {
            printf("%x ", data[start + i]);
        }
    }
    printf("}\n");

}


void ex1() {
    invokeQuestions();
    int res = bitField(param.size, param.pos, param.val);
    printf("Result: %d\n", res);
}
void ex22() {
    utf8Print("#Fs+Tsd", 4);
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
int printBit(int pos, unsigned char val) {
    for(int i = ARRAY_SIZE, j = 0; pos <= i; i --, j++) {
        param.arr[i] = (val >> i) & 0x01;
        printf(" %d ", param.arr[i]);
    }
    printf("\n");
    return 0;
}
int utf8Print( unsigned char data[], int start){
    printf(" %c\n", data[start]);
    return strlen(data);
}