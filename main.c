#include "bigint.h"
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define INPUT_SIZE 1000
int main(){
    while(1){
        int choice;
        printf("Select Operation on Big Integers\n");
        printf("1. Addition\n");
        printf("2. Subtraction\n");
        printf("3. Multiplication\n");
        printf("4. Division\n");   
        printf("Press 0 to Exit\n");
        scanf("%d",&choice);
        if(choice==0) 
        break;
        char str1[INPUT_SIZE];
        char str2[INPUT_SIZE];
        printf("Enter Big Integer 1 : ");
        scanf("%s",str1);
        printf("Enter Big Integer 2 : ");
        scanf("%s",str2);
        struct node *result = NULL;
        switch(choice){
            case 1:  result = add(str1,str2);
            break;
            case 2:  result = subtract(str1,str2);
            break;
            case 3:  result = multiply(str1,str2);
            break;
            case 4:  printf("Can not Process!!\nTry Another Operation\n");
        //  result = divide(str1,str2);
           break;
            default: printf("Enter Valid Choice!!\n");
            break;
        }
        printf("Answer : ");
        display(result);
    }
    return (0);
}
//  gcc main.c functions.c -o main
//  ./main