#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#define ARRAY_SIZE 7
#define BIT_SIZE 8
#define POSITIVE 1

enum ClassId { S_ASC, S_INIT, S_CONT };
enum ClassId utf8Class( unsigned char *c );
struct fieldParams { int size; int pos; unsigned char val; int arr[ARRAY_SIZE]; } param;

int utf8Print( unsigned char data[], int start ); 
int bitField( int siz, int pos, unsigned char val );
int printBit(int pos, unsigned char val);
int invokeQuestions();
int error(char *message);
int covertDecimal(int siz, unsigned char val );

int main() {
    invokeQuestions();
    int res = convertDecimal(param.size, param.pos, param.val);
    printf("Result: %d\n", res);
    printf("\n%d\n", utf8Class("高"));
    return res;
}
int bitField( int siz, int pos, unsigned char val ) {
    val = val >> BIT_SIZE - (pos + siz);
    val = val << BIT_SIZE - siz;
    
    
}
int covertDecimal(int siz, unsigned char val ) {
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
enum ClassId utf8Class( unsigned char *c ) {
//     int i;
//     enum ClassId class;
//     for(i = 0; i < strlen(c); i++){
//         class = (0xFF & c[i]);
//         printf("%02X\n", class);
//     }
//     return i++;







}

