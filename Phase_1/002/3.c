#include <stdio.h>

int main()
{
    int CallDurationSeconds;
    printf("Enter call duration in seconds: ");
    scanf("%d", &CallDurationSeconds);
    printf("Call duration in minutes: %dm %ds\n", CallDurationSeconds / 60,CallDurationSeconds % 60);
    return 0;
}