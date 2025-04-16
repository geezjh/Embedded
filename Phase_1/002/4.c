#include <stdio.h>

int main() {
    float hight;
    printf("Enter your height in meters: ");
    scanf("%f", &hight);
    printf("Your height in inches is: %.2f\n", hight / 2.54);
    return 0;
}