#ifndef DEFINE_H
#define DEFINE_H

typedef struct
{
    int a;
    int b;
    int c;
} follow_cicle_inf;

typedef struct
{
    int *follow_usr;
    follow_cicle_inf *hozon;
    int user_cicle_flag;
} user_inf;

#endif