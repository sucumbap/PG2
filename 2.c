#include <stdio.h>
#include <ctype.h>
#include <string.h>
#define MAX_LINE_LENGTH 200
#define ARRAY_SIZE 7
#define BIT_SIZE 8
#define POSITIVE 1

enum ClassId { S_ASC, S_INIT, S_CONT };
struct fieldParams { int size; int pos; unsigned char val; int arr[ARRAY_SIZE]; } param;
struct Sentence { unsigned char str[200]; int size; }sentence, phrase;
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
int utf8PrintLower( unsigned char data[], int start );
void normString( char str [] );
int getTestValuesFromTxt(int index);
void ex1(); void ex21(); void ex22(); void ex23(); void ex24(); void ex31(); void ex32();

int main() {
    //ex1(); //ex21(); //ex22(); //ex23(); //ex24(); //ex31(); //ex32();
    getTestValuesFromTxt(3);
    return 0;
}
void ex1() {
    invokeQuestions();
    int res = bitField(param.size, param.pos, param.val);
    printf("Result: %d\n", res);
}
void ex21() {utf8Class(sentence.str[2]);}
void ex22() {utf8Print("#Fs+Tsd", 4);}
void ex23() {
    unsigned char x[] = { 0x61, 0xc3, 0xa7, 0xc3, 0xa3, 0x6f };
    arrayPrintHex( x, 0, 5 );
}
void ex24() {
    inquireWords(); convertSConSentence();
}
void ex31() {
    char a[] = {"Permite- usAR a-centuaÇÃO e outros- sÍmbolos com-o- «E-uro« €."};
    for (int i = 0; i < strlen(a); i++) { normSymb(a, i); } 
}
void ex32() {
    char a[] = {"Permite- usAR a-centuaÇÃO e outros- sÍmbolos com-o- «E-uro« €."};
    normString(a);
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
    } return result;
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
int error(char *message) { printf("\nError: %s Inválido\n", message); return 0; }
int utf8Print( unsigned char data[], int start ) {
    unsigned char Masc,temp;
    enum ClassId Me = utf8Class(data[start]);
    if(Me == S_ASC) {
        printf("%c",data[start]); return 1;
    }else if(Me == S_INIT){
        Masc = 224; temp = 192;
        if ((data[start] & Masc) == temp){ printf("%c%c",data[start],data[start+1]); return 2; }
        Masc = 240; temp = 224;
        if((data[start] & Masc) == temp){ printf("%c%c%c",data[start],data[start+1],data[start+2]); return 3; }
        Masc = 248; temp = 240;
        if((data[start] & Masc) == temp){ printf("%c%c%c%c",data[start],data[start+1],data[start+2],data[start+3]); return 4; }
    } return 0;
}
enum ClassId utf8Class( unsigned char c ) {
    enum ClassId Me;
    if(c<0){error("ERROR");return -1; }
    if(c>=0 && c<=127){ Me = S_ASC; }
    if(c>=128 && c<=191){ Me = S_CONT; }
    if(c>=194 && c<=255){ Me = S_INIT; }
    return Me;
}
void arrayPrintHex( unsigned char data[], int start, int size ){
    if (size == 2){ printf("{%.2x %.2x}",data[start],data[start+1]); return; }
    if(size == 3){ printf("{%.2x %.2x %.2x}",data[start],data[start+1],data[start +2]); return; }
    if(size == 4){ printf("{%.2x %.2x %.2x %.2x}",data[start],data[start+1],data[start+2],data[start+3]); return;}
}
int convertSConSentence() {
    for (int i = 0, j = 1; i < sentence.size; i++) {

        if(utf8Class(sentence.str[i]) == S_INIT || utf8Class(sentence.str[i]) == S_CONT) {         
            j = utf8Print(sentence.str,i);
            arrayPrintHex(sentence.str, i, j);
        } else { printf("%c", sentence.str[i]); }
    } return 0;
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
int utf8PrintLower( unsigned char data[], int start ) {
    unsigned char Masc,temp;
    enum ClassId Me = utf8Class(data[start]);    
    Masc = 224; temp = 192;
    if ((data[start] & Masc) == temp){
        printf("%c%c",data[start],data[start+1]+32); return 2;
    }
    Masc = 240; temp = 224;
    if((data[start] & Masc) == temp){
        printf("%c%c%c",data[start],data[start+1]+32,data[start+2]); return 3;
    }
    Masc = 248; temp = 240;
    if((data[start] & Masc) == temp){
        printf("%c%c%c%c",data[start],data[start+1]+32,data[start+2],data[start+3]); return 4;
    } return 0;
}
int normSymb( char str[], int idx ) {
    unsigned char c = str[idx];
    enum ClassId Me = utf8Class(c);
    str[idx] = tolower(c);
    if((str[idx] == 45) && ((str[idx + 1] == 32) || str[idx -1] == 32)) str[idx] = 32;
    if(Me == S_CONT || Me == S_INIT) {
        if( c < 195 || c > 8000) str[idx] = 32;
        return utf8PrintLower(str, idx);
    } else { return utf8Print(str, idx); }
}
void normString( char str [] ) {
    for (int i = 0; i < strlen(str); i++) { normSymb(str, i); } 
}
int getTestValuesFromTxt(int index) {
    FILE    *textfile;
    unsigned char    line[MAX_LINE_LENGTH];
    switch (index) {
    case 1: textfile = fopen("1.txt", "r"); break;
    case 2: textfile = fopen("2.txt", "r");break;
    case 3: textfile = fopen("3.txt", "r"); break;
    default: error("test index"); break; }
    if(textfile == NULL) error("test file not found");
    switch (index) {
        case 1:
            while(fgets(line, MAX_LINE_LENGTH, textfile)){
                int res = bitField(line[0], line[2], line[4]);
                printf("Result: %d vs Valor dado: %d\n", res, line[6]);
            } break;
        case 2:
            int i = 1, j = 0;
            while(fgets(sentence.str, MAX_LINE_LENGTH, textfile)){
                if (i > 0) {
                    printf("Sentence recolhida: %s\n", sentence.str);
                    printf("Sentence gerada: ");
                    sentence.size = strlen(sentence.str);
                    convertSConSentence();
                    printf("\n");
                } else if (i < 0) {
                    printf("Sentence correta recolhida: %s\n", sentence.str);
                } i *= -1;
            } break;
        case 3:
            i = 1;
            while(fgets(line, MAX_LINE_LENGTH, textfile)) {
                if(i > 0) {
                    printf("Sentence recolhida: %s\n", line);
                    printf("Sentence gerada: ");
                    normString(line);
                    printf("\n");
                } else if (i < 0) { printf("Sentence esperaca: %s\n", line); }
                
                i *= -1;
            }
            break;
    }
    fclose(textfile);
    return 0;
}