#include <iostream>

int main(){
    // Читаем число
    int32_t num;
    std::cin >> num;
    
    // Частный случай: num = 0
    if (num == 0){
        std::cout << "0*10^0\n";
        std::exit(0);
    }
    
    // Знак числа
    bool isNegative = (num < 0);
    num = std::abs(num);
    
    // В reverseNum записываем перевернутое num; numOfDigits - считаем число разрядов
    int32_t reverseNum = 0;
    int numOfDigits = 0;
    while (num > 0){
        reverseNum += (num % 10);
        numOfDigits++;
        num /= 10;
        if (num > 0){
            reverseNum *= 10;
        }
    }
    
    
    //Выводим число
    while (reverseNum > 0){
        int dig = reverseNum % 10;
        reverseNum /= 10;
        numOfDigits--;
        // Частный случай: цифра = 0
        if (dig == 0){
            continue;
        }
        
        if (isNegative){
            std::cout << '-';
        }
        
        std::cout << dig << "*10^" << numOfDigits;
        
        if (!isNegative && numOfDigits > 0){
            std::cout << '+';
        }
        
    }
    std::cout << "\n";
}
