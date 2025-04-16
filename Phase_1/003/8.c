#include <stdio.h>

// 定义起征点和税率表
#define START_POINT 3500

// 计算应纳税额的函数
float calculateTax(float taxableIncome) {
    float taxAmount;
    
    // 根据不同的应纳税所得额计算应纳税额
    if (taxableIncome <= 0) {
        taxAmount = 0;
    } else if (taxableIncome <= 36000) {
        taxAmount = taxableIncome * 0.03 - 0;
    } else if (taxableIncome <= 144000) {
        taxAmount = taxableIncome * 0.10 - 2520;
    } else if (taxableIncome <= 300000) {
        taxAmount = taxableIncome * 0.20 - 16920;
    } else if (taxableIncome <= 420000) {
        taxAmount = taxableIncome * 0.25 - 31920;
    } else if (taxableIncome <= 660000) {
        taxAmount = taxableIncome * 0.30 - 52920;
    } else if (taxableIncome <= 960000) {
        taxAmount = taxableIncome * 0.35 - 85920;
    } else {
        taxAmount = taxableIncome * 0.45 - 181920;
    }
    
    return taxAmount;
}

int main() {
    float salary, socialInsurance, taxableIncome, taxAmount;
    
    // 获取用户输入的工资总额
    printf("请输入您的工资总额: ");
    scanf("%f", &salary);
    
    // 获取用户输入的社会保险费用
    printf("请输入您的社会保险费用: ");
    scanf("%f", &socialInsurance);
    
    // 计算应纳税所得额
    taxableIncome = salary - socialInsurance - START_POINT;
    
    // 计算应纳税额
    taxAmount = calculateTax(taxableIncome);
    
    // 输出应纳税所得额和应纳税额
    printf("您的应纳税所得额为: %.2f 元\n", taxableIncome);
    printf("您的应纳税额为: %.2f 元\n", taxAmount);
    
    return 0;
}