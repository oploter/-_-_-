#include <iostream>
#include <iomanip>
#include <cmath>

int main(){
    int num; // исходное число
    std::cin >> num;
    int reverseNum = 0; // перевернутое число
    
    // Переворачиваем исходное число
    int cnt = 4;
    while (num > 0){
        int nextDigit = num % 10;
        num /= 10;
        reverseNum += nextDigit * std::pow(10, cnt);
        cnt--;
    }
    
    // Выводим перевернутое число в нужном формате
    cnt = 4;
    while (reverseNum > 0){
        std::cout << (reverseNum % 10) << "*10^" << cnt;
        if (cnt > 0){
            std::cout << '+';
        }else{
            std::cout << "\n";
        }
        cnt--;
        reverseNum /= 10;
    }
}
