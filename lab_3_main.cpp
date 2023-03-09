#include <iostream>
#include <cmath>
#include <vector>
#include <utility>
#include <fstream>
#include <cstdlib>
#include <ctime>

int mult = 20;

std::vector<std::vector<float>> gen_sin(int num_of_values){
    float step = 3.14159 / 100;
    std::vector<std::vector<float>> ans(num_of_values);
    float curr_val = 0;
    for(int i = 0; i < num_of_values; i++){
        ans[i] = {curr_val, mult * std::sin(curr_val)};
        curr_val += step;
    }
    return ans;
}

float randMToN(float M, float N)
{
    return M + (rand() / ( RAND_MAX / (N-M) ) ) ;
}
void gen_rand(std::vector<std::vector<float>>& v){
    float range = mult * 0.15;
    for(int i = 0; i < (int)v.size(); i++){
        auto& k = v[i];
        k.push_back(k[1] + randMToN(-1 * range, range));
    }
}


void write_to_file(const std::vector<std::vector<float>>& v){
    std::ofstream myfile;
    myfile.open("out.csv");
    myfile << "X,Y,Filtered\n";
    for(int i = 0; i < (int)v.size(); i++){
        const auto& k = v[i];
        for(int j = 0; j < (int)k.size(); j++){
            myfile << k[j];
            if(j < (int)k.size() - 1){
                myfile << ',';
            }else{
                myfile << "\n";
            }
        }
    }
    myfile.close();
}

int main(){
    std::vector<std::vector<float>> ans = gen_sin(400);
    gen_rand(ans);
    write_to_file(ans);
}
