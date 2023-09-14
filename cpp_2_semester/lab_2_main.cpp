#include <iostream>
#include <vector>
#include <exception>
#include <fstream>

std::vector<int> ks;
int F_0(int n){
    ks[0]++;
    if(n <= 3){
        return 1;
    }
    return F_0(n - 1) + F_0(n / 2) * 2;
}

int F_1(int n){
    ks[1]++;
    std::vector<int> count_1(n + 1, 0);
    count_1[1] = 1;
    count_1[2] = 1;
    count_1[3] = 1;
    for(int i = 2; i < n; i++){
        int k = count_1[i];
        if(i + 1 > 3){
            count_1[i + 1] += k;
        }
        if(i * 2 + 1 <= n){
            count_1[i * 2] += 2 * k;
            count_1[i * 2 + 1] += 2 * k;
        }else if(i * 2 <= n){
            count_1[i * 2] += 2 * k;
        }
    }
    return count_1[n];
}

std::vector<int> count_2;
int F_2(int n){
    ks[2]++;
    int& num = count_2[n];
    if(num > -1){
        return num;
    }
    num = F_2(n - 1) + 2 * F_2(n / 2);
    return num;
}

void setCount(int n){
    count_2.clear();
    count_2.resize(n + 1, -1);
    count_2[1] = 1;
    count_2[2] = 1;
    count_2[3] = 1;
}
void setKs(){
    ks[0] = 0;
    ks[1] = 0;
    ks[2] = 0;
}


int main(){
    ks.resize(3, 0);
    std::ofstream myfile;
    myfile.open("res.txt");
    myfile<<"n,alg_1,alg_2\n";
    for (int i = 4; i < 100; i++){
        setKs();
        setCount(i);
        int f_0 = F_0(i);
        int f_1 = F_1(i);
        int f_2 = F_2(i);
        bool eq = (f_0 == f_1) && (f_1 == f_2);
        if(eq == false){
            throw std::exception();
        }
        myfile<<i<<','<<ks[0]<<','<<ks[2]<<'\n';
    }
    myfile.close();
    return 0;
}
