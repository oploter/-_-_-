#include <iostream>

int main(){
    int32_t num; // исходное число
    std::cin >> num;
    
    // Частный случай: num = 0
    if (num == 0){
        std::cout << "0*10^0\n";
        std::exit(0);
    }
    
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
    numOfDigits--;
    
    //Выводим число
    int cnt = 0;
    while (reverseNum > 0){
        
        int dig = reverseNum % 10;
        reverseNum /= 10;
        // Частный случай: цифра = 0
        if (dig == 0){
            numOfDigits--;
            cnt++;
            continue;
        }
        
        if (isNegative){
            std::cout << '-';
        }else if(!isNegative && cnt != 0){
            std::cout << '+';
        }
        
        std::cout << dig << "*10^" << numOfDigits;
        
        numOfDigits--;
        cnt++;
    }
    std::cout << "\n";
}
