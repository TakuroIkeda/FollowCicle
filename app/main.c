#include <stdio.h>
#include <stdlib.h>

#include "define.h"
#include "simulate.h"

int main(void)
{

    int a, b;
    int n, m;

    FILE *file;

    for (int x = 1; x <= 100; x++)
    {
        char filename[256];
        // ファイルを開く
        // ファイル名を動的に生成
        sprintf(filename, "./input/input%d.in", x);

        // fopenに生成したファイル名を渡す
        file = fopen(filename, "r");
        if (file == NULL)
        {
            perror("ファイルを開けませんでした");
            return 1;
        }

        // 読み取る行を格納するためのバッファ
        char buffer[100];

        // 最初の行を読み取る (例: "3 6")
        if (fgets(buffer, sizeof(buffer), file) != NULL)
        {
            sscanf(buffer, "%d %d", &n, &m); // 数値を抽出
            // printf("n = %d, m = %d\n", n, m);
        }

        user_inf user[n + 1];

        for (int h = 0; h <= n; h++)
        {
            user[h].follow_usr = (int *)malloc((N) * sizeof(int));
            user[h].hozon = (follow_cicle_inf *)malloc((N) * sizeof(follow_cicle_inf));
        }

        for (int h = 0; h <= n; h++)
        {
            for (int j = 0; j <= n; j++)
            {
                user[h].hozon[j].a = 0;
                user[h].hozon[j].b = 0;
                user[h].hozon[j].c = 0;
            }
            user[h].user_cicle_flag = 0;
            for (int i = 0; i <= n; i++)
            {
                user[h].follow_usr[i] = 0;
            }
        }

        char data[100];

        // 残りの行を読み取る
        while (fgets(data, sizeof(data), file) != NULL)
        {
            sscanf(data, "%d %d", &a, &b); // 数値を抽出
            // printf("a = %d, b = %d\n", a, b);
            if (a != b)
            {
                user[a].follow_usr[b] = 1;
            }
        }

        // ファイルを閉じる
        fclose(file);

        int counter = 0;
        for (int h = 1; h <= n; h++)
        {
            for (int i = 1; i <= n; i++)
            {
                if (user[h].follow_usr[i] == 1 && h != i)
                {
                    for (int j = 1; j <= n; j++)
                    {
                        if (user[i].follow_usr[j] == 1 && i != j)
                        {
                            if (user[j].follow_usr[h] == 1)
                            {
                                user[h].user_cicle_flag++;
                                user[h].hozon[user[h].user_cicle_flag].a = h;
                                user[h].hozon[user[h].user_cicle_flag].b = i;
                                user[h].hozon[user[h].user_cicle_flag].c = j;
                            }
                        }
                    }
                }
            }
        }

        for (int h = 1; h <= n; h++)
        {
            for (int i = 1; i < N; i++)
            {
                sortUserValues(&user[h].hozon[i]);
            }
        }

        for (int h = 1; h <= n; h++)
        {
            for (int i = 1; i < N; i++)
            {
                if (user[h].hozon[i].a > 0 && user[h].hozon[i].b > 0 && user[h].hozon[i].c > 0)
                {
                    for (int j = 1; j < N; j++)
                    {
                        if (i != j)
                        {
                            if (user[h].hozon[i].a == user[h].hozon[j].a && user[h].hozon[i].b == user[h].hozon[j].b && user[h].hozon[i].c == user[h].hozon[j].c)
                            {
                                user[h].user_cicle_flag--;
                                user[h].hozon[j].a = 0;
                                user[h].hozon[j].b = 0;
                                user[h].hozon[j].c = 0;
                            }
                        }
                    }
                }
            }
        }

        for (int h = 1; h <= n; h++)
        {
            for (int i = 1; i < N; i++)
            {
                if (user[h].hozon[i].a > 0 && user[h].hozon[i].b > 0 && user[h].hozon[i].c > 0)
                {
                    for (int j = 1; j <= n; j++)
                    {
                        for (int k = 1; k < N; k++)
                        {
                            if (user[h].hozon[i].a == user[j].hozon[k].a && user[h].hozon[i].b == user[j].hozon[k].b && user[h].hozon[i].c == user[j].hozon[k].c && h != j)
                            {
                                user[j].user_cicle_flag--;
                                user[j].hozon[k].a = 0;
                                user[j].hozon[k].b = 0;
                                user[j].hozon[k].c = 0;
                            }
                        }
                    }
                }
            }
        }

        for (int h = 1; h <= n; h++)
        {
            if (user[h].user_cicle_flag > 0)
            {
                counter += user[h].user_cicle_flag;
            }
        }

        if (counter != 0)
        {
            printf("%d回目 = %d\n", x, counter);
        }

        for (int h = 0; h <= n; h++)
        {
            free(user[h].follow_usr);
            free(user[h].hozon);
        }
    }

    return 0;
}