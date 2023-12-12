#include "task8.h"
#include <iostream>
#include <fstream>
#include <string>
#include <vector>

int main(){
    std::vector<int> tests_to_run{7};
    for(int i : tests_to_run){
        std::string file_name = "tests/" + std::to_string(i) + ".txt";
        std::ifstream file(file_name);
        if(file.is_open()){
            std::vector<std::string> res = compute(file);
            std::string line;
            std::getline(file, line);
            std::vector<std::string> check;
            while(std::getline(file, line)){
                check.push_back(line);
            }
            std::cout << "+++++++RESULT+++++++\n";
            for(const std::string& s : res){
                std::cout << s << '\n';
            }
            std::cout << "+++++++CHECK++++++++\n";
            for(const std::string& s : check){
                std::cout << s << '\n';
            }
            std::cout << "file " << i << " " << (check == res) << '\n';
            std::cout << "=====================\n";
        }        
    }
}