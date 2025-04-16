#include <stdio.h>

int main()
{
    int arr[20][25];
    for (int i = 0; i < 20; i++)
    {
        for (int j = 0; j < 25; j++)
        {
            if ((i * i + j * j) == 512)
            {
                printf("大礼包在第%d排,第%d列\n", i + 1, j + 1);
            }
        }
    }
    return 0;
}