#include <stdio.h>
#include <stdbool.h>
#include <math.h>

bool is_reverse_equal(int n);
int is_prime(int n);
int next_prime(int n);
int show_prime_divisors(int n);
double calc_fees(int total_years, double initial, double tax);

int main() {
  char Exercise;
  printf("Insira a,b,c,d,e consoante o exercício a testar: ");
  scanf("%c",&Exercise);

  if(Exercise == 'a'){
    int n,Result;
    printf("Insira um inteiro: ");
    scanf("%d", &n);
    Result=is_reverse_equal(n);
    if (Result == 1){ printf("%d é uma capicua.\n",n); }
    else{ printf("%d não é uma capicua.\n", n); }
    return 0;
  }
  if(Exercise == 'b'){
    int n,Flag;
    printf("Enter a positive integer: ");
    scanf("%d", &n);
    Flag = is_prime(n);
    if(Flag == 1){ printf("%d é um número primo.\n",n);}
    else { printf("%d não é número primo.\n",n);}
    return 0;
  }
  if(Exercise == 'c'){
    int n,Result;
    printf("Enter a positive integer: ");
    scanf("%d", &n);
    Result = next_prime(n);
    printf("O primo a seguir de %d é %d\n",n,Result);
    return 0;
  }
  if(Exercise == 'd'){
    int n,Result;
    printf("Enter a positive integer: ");
    scanf("%d",&n);
    Result = show_prime_divisors(n);
    printf("\n");
    return 0;
  }
  if(Exercise == 'e'){
    int Anos,ERRO;
    double Init,Tax,Result;
    printf("Insira o total de anos,o valor inicial e a taxa: ");
    ERRO = scanf("%d %lf %lf",&Anos,&Init,&Tax);
    if(ERRO!= 3){
      printf("Erro na leitura de valores!");
    }
    Result = calc_fees(Anos,Init,Tax);
    printf("O montante em juros complexos é: %.2lf.\n",Result);
    return 0;
  }
  printf("Erro na alínea\n");
  return 0;  
}

bool is_reverse_equal(int n){
  int reversed = 0, original=n;
  while (n != 0) {
        reversed = reversed * 10 + n % 10;
        n /= 10;
  }
  if (original == reversed){ return true; }
  else{ return false; }
}

int is_prime(int n){
  if (n == 0 || n == 1) return 0;
  for (int i = 2; i <= n / 2; ++i) {
    if (n % i == 0) {
      return 0;
    }
  }
  return 1;
}

int next_prime(int n){
  int Flag=0;
  int NextPrime = n;
  if (n <= 1){return 2;}
  while(Flag == 0){
    NextPrime++;
    if (is_prime(NextPrime) == 1){
      Flag = 1;
    }             
  }
  return NextPrime;
}

int show_prime_divisors(int n){
  int Result = 0,k=2;
  printf("Os fatores primos deste número são: ");
  for(int i=2; i<=n ; i++){
    if( n%i == 0){
      if( is_prime(i) == 1 ){
        printf("%d ", i);
        Result++;
      } 
    }
  }
  return Result;
}

double calc_fees(int total_years, double initial, double tax){
  double Result=initial;
  for(int i=0;i<total_years;i++){
    Result+= (Result * tax)/100;
  }
  return Result;
}
