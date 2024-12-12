#include <stdio.h>
#include <stdlib.h>

#include "define.h"
#include "simulate.h"

void sortUserValues(follow_cicle_inf *user)
{
    // 一時的な配列に値を格納
    int temp[3] = {user->a, user->b, user->c};

    // 選択ソートを使用して整列（簡単なソート例）
    for (int i = 0; i < 2; i++)
    {
        for (int j = i + 1; j < 3; j++)
        {
            if (temp[i] > temp[j])
            {
                int tmp = temp[i];
                temp[i] = temp[j];
                temp[j] = tmp;
            }
        }
    }

    // 整列された値を元の変数に戻す
    user->a = temp[0];
    user->b = temp[1];
    user->c = temp[2];
}