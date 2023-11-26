#include <fstream>
#include <unordered_map>
#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <utility>

struct Component{
    float x;
    float y_low;
    float y_high;
    bool open_bracket;
    std::string name;
    Component(){}
    Component(float x_, float y_low_, float y_high_, bool open_bracket_, std::string name_) : 
    x(x_), y_low(y_low_), y_high(y_high_), open_bracket(open_bracket_), name(name_){}
};

float W, H;

typedef std::unordered_map<std::string, std::pair<float, float>> Mymap;

std::ostream& operator<<(std::ostream& os, std::pair<float, float>& component){
    os << "C{" << component.first << ',' << component.second << "}";
    return os;
}

Mymap load_csv(std::string file_name){
    Mymap map;
    std::fstream file(file_name);
    std::string line, component_name, param;
    if(file.is_open()){
        while(std::getline(file, line)){
			std::stringstream str(line);
            float w, h;
            std::getline(str, component_name, ',');
            std::getline(str, param, ',');
            w = std::stof(param);
            std::getline(str, param, ',');
            h = std::stof(param);
            map[component_name] = std::make_pair<>(w, h);
		}
    }
    return map;
}

Mymap component_info = load_csv("components.csv");

std::pair<Component, Component> create_rectangle(std::string name, std::string type, float x_center, float y_center){
    auto size = component_info[type];
    float x_open = x_center - size.first/2;
    float x_close = x_center + size.first/2;
    float y_low = y_center - size.second/2;
    float y_high = y_center + size.second/2;
    return std::make_pair<>(Component(x_open, y_low, y_high, true, name),
     Component(x_close, y_low, y_high, false, name));
}

int main(){
    std::cin >> W >> H;
    int N;
    std::cin >> N;
    std::string line;
    std::getline(std::cin, line);
    std::string component_name, type;
    float center_x, center_y;
    std::vector<Component> components;
    for(int i = 0; i < N; ++i){
        std::getline(std::cin, line);
        std::stringstream stream(line);
        stream >> component_name >> type >> center_x >> center_y;
    }
}