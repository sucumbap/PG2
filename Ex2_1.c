enum ClassId utf8Class( unsigned char c ){
    if(c<0){printf("ERROR");return -1;}
    if(c>=0 && c<=127){
        printf("S_ASC\n");
        return Me = S_ASC;
    }
    if(c>=128 && c<=191){
        printf("S_CONT\n");
        return Me = S_CONT;
    }
    if(c>=194 && c<=255){
        printf("S_INIT\n");
        return Me = S_INIT;
    }
}
