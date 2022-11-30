#include<stdio.h>
int main(){
    int j;
    int i;

    i = 2;
    for(i=2; i <= 100; i++){
        j = 2;
        while (j<i && i%j != 0){
            j = j+1;
        }
        if (i==j){
            printf("%d \n", i);
        }
    }
}