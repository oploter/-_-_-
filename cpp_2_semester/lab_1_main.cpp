#include <iostream>
#include <cstdint>

void fromDecToto(int to, int numDec){
    int numNew = 0;
    while (numDec > 0){
        numNew += (numDec % to);
        numNew *= to;
        numDec /= to;
    }
    numNew /= to;
    while (numNew > 0){
        int res = numNew % to;
        if (res < 10){
            std::cout << res;
        }else{
            std::cout << (char)(55 + res);
        }
        numNew /= to;
    }
    std::cout << "\n";
}

int fromFromToDec(int from){
    int numDec = 0;
    char c;
    std::cin >> c;
    while (c != ';'){
        numDec *= from;
        if (std::isdigit(c)){
            numDec += (int)c - 48;
        }else if (std::isalpha(c)){
            numDec += (int)c - 'A'+10;
        }
        std::cin >> c;
    }
    return numDec;
}

int main(){
    int from;
    std::cin >> from;
    int numDec = fromFromToDec(from);
    std::cout << numDec << "\n";
    int to;
    std::cin >> to;
    fromDecToto(to, numDec);
}

