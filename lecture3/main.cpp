#include "question.h"
#include <iostream>
#include <string>
#include <sstream>
#include <fstream>

/*
argv[1] | int   | variant
argv[2] | string | file name
*/
int main(int argc, char* argv[]){
    if(argc != 3){
        std::cerr << "Invalid number of arguments\n";
        return 1;
    }
    int var = std::stoi(argv[1]);
    std::string fileName(argv[2]);
    std::ifstream inpFile(fileName);
    std::vector<Question> questions;  
    if(inpFile.is_open()){
        std::string line;
        while (inpFile){
            std::stringstream ss;
            do{
                std::getline(inpFile, line);
                ss << line;
            }while(inpFile && line != "");
            questions.push_back((var == 1 ? Question::fromTxt(ss.str()) : Question::fromGift(ss.str())));
        }
    }
    inpFile.close();

    auto dotPos = fileName.rfind('.');
    std::string ext = fileName.substr(dotPos + 1);
    std::string newFileName = fileName.substr(0, dotPos) + "-out." + ext;
    std::ofstream outFile(newFileName);
    if(outFile.is_open()){
        for(const auto& q : questions){
            if(var == 1){
                outFile << q.toGiftPretty() << '\n';
            }else{
                outFile << q.toTxtPretty() << '\n';
            }
        }
    }
    outFile.close();
}