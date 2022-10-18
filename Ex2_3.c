void arrayPrintHex( unsigned char data[], int start, int size ){
    printf("{");
    for(int i = 0;i<size;i++){
        if(i==0){ printf("%x",data[start]); }
        else{ printf(" %.2x",data[start + i]);}
    }
    printf("}");
    return ;
}
