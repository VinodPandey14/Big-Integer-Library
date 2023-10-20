#include "bigint.h"
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
// CREATING LINKED LIST FROM INPUTED STRING IN REVERSE ORDER
void create_node(struct node **head,char str[]) {
for(int i=0; i<strlen(str); i++) {
int value = str[i] - 48;
if((*head)==NULL) {
struct node *temp = (struct node*)malloc(sizeof(struct node));
temp->data = value;
temp->next = *head;
*head = temp;
} else {
struct node *temp =(struct node*)malloc(sizeof(struct node));           
temp->data = value;
temp->next = *head;
*head = temp;
}
}
}
// DE-ALLOCATING THE MEMORY TO AVOID MEMORY LEAKS
void freeList(struct node* head) {
    struct node* current = head;
    while (current != NULL) {
        struct node* temp = current;
        current = current->next;
        free(temp);
    }
}
void display(struct node *temp) {
while(temp) {
printf("%d",temp->data);
temp = temp->next;
}
printf("\n");
}
int compare(char str1[],char str2[]) {
int a = strlen(str1);
int b = strlen(str2);
if(a > b) return 1;
else if(a < b) return 2;
for(int i=0; i<a; i++) {
if(str1[i] > str2[i]) return 1;
else if(str1[i] < str2[i]) return 2;
}
return 0;
}
struct node* reverse(struct node *curr){
    struct node *prev=NULL,*forward=NULL;
    while(curr){
        forward=curr->next;
        curr->next=prev;
        prev=curr;
        curr=forward;
    }
    return prev;
}

// ADDITION OF BIG INTEGERS

struct node* add(char str1[],char str2[]) {
struct node *num1 = NULL,*num2 = NULL,*ans =  NULL;
create_node(&num1,str1);
create_node(&num2,str2);
int sum=0,carry=0;
while(num1 && num2) { 
sum = carry + num1->data + num2->data;
carry = sum / 10;
sum = sum % 10;
struct node *temp = (struct node*)malloc(sizeof(struct node));
temp->data = sum;
temp->next = ans;
ans = temp;
num1 = num1->next;
num2 = num2->next;
}
while(num1 || num2) {
if(num1) {
sum = carry + num1->data;
carry = sum / 10;
sum = sum % 10;
num1 = num1->next;
}
if(num2)  {
sum = carry + num2->data;
carry = sum / 10;
sum = sum % 10;
num2 = num2->next;             
}
struct node *temp = (struct node*)malloc(sizeof(struct node));
temp->data = sum;
temp->next = ans;
ans = temp;
}
// IF AFTER ADDING ALL THE DIGITS STILL LAST CARRY IS REMAINING
if(carry!=0) {
struct node *temp = (struct node*)malloc(sizeof(struct node));
temp->data = carry;
temp->next = ans;
ans = temp;
}
// REMOVING EXTRA ZEROS FROM THE FRONT (eg. 00001 = 1 )
while (ans && ans->data == 0 && ans->next != NULL) {
        struct node* temp = ans;
        ans = ans->next;
        free(temp);
    } 
freeList(num1);
freeList(num2);
return ans;
}

// SUBTRACTION OF BIG INTEGERS

struct node* subtract(char str1[],char str2[]) {
struct node *num1 = NULL,*num2 = NULL,*ans =  NULL;
int minus_sign = 0;
int flag = compare(str1,str2);
if(flag==0) {
struct node *temp = (struct node*)malloc(sizeof(struct node));
temp->data = 0;
temp->next = NULL;
ans = temp;
return ans;
}
else if(flag==1) {
create_node(&num1,str1);
create_node(&num2,str2);
} else {
minus_sign = 1;
create_node(&num1,str2);
create_node(&num2,str1);   
}
    int borrow = 0;
    while (num1 || num2) {
        int data1 = num1 ? num1->data : 0;
        int data2 = num2 ? num2->data : 0;
        int diff = data1 - data2 - borrow;
        if (diff < 0) {
            diff += 10;
            borrow = 1;
        } else { 
            borrow = 0;
        }
        struct node* temp = (struct node*)malloc(sizeof(struct node));
        temp->data = diff;
        temp->next = ans;
        ans = temp;
        if (num1) num1 = num1->next;
        if (num2) num2 = num2->next;
    }
while (ans && ans->data == 0 && ans->next != NULL) {
        struct node* temp = ans;
        ans = ans->next;
        free(temp);
    } 
    if(minus_sign == 1)
    ans->data = -(ans->data);
    freeList(num1);
    freeList(num2);
return ans;
}

struct node* addDigit(struct node *num1,struct node *num2,int k) {
    struct node *result=NULL;
    for(int i=0; i<k; i++){
        struct node *new = (struct node*)malloc(sizeof(struct node));
        new->data = num2->data;
        num2 = num2->next;
        if(!result)
        result = new;
        else{
            new->next = result;
            result = new;
        }
    }
    int carry=0,sum=0;
    while(num1 && num2){
        sum=(num1->data)+(num2->data)+carry;
        carry=sum/10;
        sum=sum%10;
        struct node *temp = (struct node*)malloc(sizeof(struct node));
        temp->data=sum;
        temp->next=result;
        result=temp;
        num1 = num1->next;
        num2 = num2->next;
    }
    while(num1){
        sum=num1->data+carry;
        num1=num1->next;
        carry=sum/10;
        sum=sum%10;
struct node *temp = (struct node*)malloc(sizeof(struct node));
        temp->data=sum;
        temp->next=result;
        result=temp;
    }
    while(num2){
        sum=num2->data+carry;
        num2=num2->next;
        carry=sum/10;
        sum=sum%10;
       struct node *temp = (struct node*)malloc(sizeof(struct node));
        temp->data=sum;
        temp->next=result;
        result=temp;
    }
   return result;      
}

// Multiplication of Big Integers

struct node* multiply(char str1[],char str2[]) {
struct node *num1 = NULL,*num2 = NULL,*ans =  NULL,*temp = NULL;
int carry = 0,prod = 0;
if(strlen(str1) >= strlen(str2)) {
create_node(&num1,str1);
create_node(&num2,str2);
} else {
create_node(&num1,str2);
create_node(&num2,str1);  
}
struct node *head1 = num1;
struct node *head2 = num2;
         while(head1){
        prod=(head1->data)*(head2->data)+carry;
            if(prod>9){
                carry=prod/10;
                prod=prod%10;
            }
            else carry=0;
            struct node *ptr = (struct node*)malloc(sizeof(struct node));
            ptr->data = prod;
            ptr->next = temp;
            temp = ptr;
            head1=head1->next;
        }
        if(carry){
            struct node *ptr = (struct node*)malloc(sizeof(struct node));
            ptr->data = carry;
            ptr->next = temp;
            temp = ptr;
            carry=0;
        }
        head2=head2->next;
        ans = temp;
        if(!head2){
            return ans;
        }
        ans = reverse(ans);
    int postion = 0;
    while(head2){
        postion++;
        temp =NULL;
        head1=num1;
        while(head1){
            prod=(head1->data)*(head2->data)+carry;
            if(prod>9){
                carry=prod/10;
                prod=prod%10;
            }
            else carry=0; 
            struct node *ptr = (struct node*)malloc(sizeof(struct node));
            ptr->data = prod;
            ptr->next = temp;
            temp = ptr;
            head1 = head1->next;
        }
        if(carry){
            struct node *ptr = (struct node*)malloc(sizeof(struct node));
            ptr->data = carry;
            ptr->next = temp;
            temp = ptr;
            carry=0;
        }
        temp = reverse(temp);
        ans = addDigit(temp,ans,postion);
        ans = reverse(ans);
        head2=head2->next;
    } 
freeList(head1);
freeList(head2);
      ans = reverse(ans);
    return ans;
}

// DIVISION OF BIG INTEGERS

struct node* divide(char str1[],char str2[]) {
struct node *num1 = NULL,*num2 = NULL,*ans =  NULL;
create_node(&num1,str1);
create_node(&num2,str2);


freeList(num1);
freeList(num2);
return ans;
}