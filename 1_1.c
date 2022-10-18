int bitField( int siz, int pos, unsigned char val){
    int Result = 0;
    unsigned char temp;
    for(int i=0;i<siz;i++){
        temp = pow(2,pos+i);
        if((temp & val) != 0) Result+= pow(2,i);                     
    }
    return Result;
}
