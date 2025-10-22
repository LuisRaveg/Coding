#include <stdio.h>
#include <stdbool.h>
void primos(int n,FILE *fptr){
    bool resultado;
    for (int i=2;i<=n;i++){
        resultado=true;
        for(int j=2;j<i;j++){
            if(i%j==0){
                resultado=false;
                break;
            }
        }
        if(resultado){
            fprintf(fptr,"%d \n",i);
        }
    }
}

int factorial(int k){
    if(k>1){
        return k*factorial(k-1);
    }else{
        return 1;
    }
}


int main(){
    int n;
    printf("Introduce un numero entero: ");
    scanf("%d",&n);
    FILE* fptr;
    fptr=fopen("archivo.txt","w");
    fprintf(fptr,"El numero introducido fue: %d \n",n);
    fprintf(fptr,"El factorial de %d es: %d \n",n,factorial(n));
    fprintf(fptr,"Los numeros primos de 2 hasta %d son : \n",n);
    primos(n,fptr);
    fclose(fptr);
    fptr=fopen("archivo.txt","r");
    char text[100] ;
    while(fgets(text,100,fptr)){
        printf(text);
    }
    
}