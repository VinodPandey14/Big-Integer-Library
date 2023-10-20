#ifndef BIGINT_H
#define BIGINT_H

struct node{
    int data;
    struct node *next;
};

struct node* add(char str1[],char str2[]);
struct node* subtract(char str1[],char str2[]);
struct node* multiply(char str1[],char str2[]);
//struct node* divide(char str1[],char str2[]);
void display(struct node *head);

#endif
// gcc -o mylibrary main.c bigint.c
