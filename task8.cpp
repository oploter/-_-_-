#include <fstream>
#include <unordered_map>
#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <algorithm>
#include <utility>
#include "avl_tree.h"
#include "task8.h"


std::ostream& operator<<(std::ostream& os, const Component& c){
    os << "C{" << c.name << ' ' << c.type << ' ' << c.x_high << ' ' << c.x_low << ' ' << c.y_high << ' ' << c.y_low << "}";
    return os;
}

struct Size{
    float w = 0;
    float h = 0;
    Size(float w_, float h_) : w(w_), h(h_){}
    Size(){}
};

std::unordered_map<std::string, Size> load_csv(std::string file_name){
    std::unordered_map<std::string, Size> map;
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
            map[component_name] = Size(w, h);
		}
    }
    return map;
}

Component create_component(std::string name, std::string type, float x_center, float y_center, std::unordered_map<std::string, Size>& component_info){
    Size size = component_info.at(type);
    float x_low = x_center - size.w/2;
    float x_high = x_center + size.w/2;
    float y_low = y_center - size.h/2;
    float y_high = y_center + size.h/2;
    return Component(x_low, x_high, y_low, y_high, name, type[0]);
    //return std::make_pair<>(Component(x_open, y_low, y_high, true, name),
    // Component(x_close, y_low, y_high, false, name));
}

std::vector<std::string> compute(std::istream& is){
    static std::unordered_map<std::string, Size> component_info = load_csv("components.csv");
    std::vector<std::string> ans;
    float W, H;
    is >> W >> H;
    int N;
    is >> N;
    std::string line;
    std::getline(is, line);
    std::string component_name, type;
    float x_center, y_center;
    std::vector<Component> components;
    std::vector<std::string> out_of_bounds_str;
    for(int i = 0; i < N; ++i){
        std::getline(is, line);
        std::stringstream stream(line);
        stream >> component_name >> type >> x_center >> y_center;
        components.push_back(create_component(component_name, type, x_center, y_center, component_info));
        auto& comp = components.back();
        if(comp.x_low < 0 || comp.x_high > W || comp.y_low < 0 || comp.y_high > H){
            out_of_bounds_str.push_back(comp.name);
        }
    }
    std::sort(out_of_bounds_str.begin(), out_of_bounds_str.end(), [](const std::string& lhs, const std::string& rhs){
        if(lhs[0] == rhs[0]){
            return lhs < rhs;
        }else{
            if(lhs[0] == 'R' || (lhs[0] == 'L' && rhs[0] == 'C')){
                return true;
            }
            return false;
        }
    });
    std::sort(components.begin(), components.end(), [](const Component& lhs, const Component& rhs){
        return lhs.x_low < rhs.x_low;
    });
    
    Heap heap;
    std::unordered_map<std::string, std::vector<std::string>> results;
    for(const Component& c : components){
        while(heap.getMinX() < c.x_low){
            heap.extractMin();
        }
        std::unordered_map<char, std::vector<std::string>> intersections = heap.intersections(c);
        auto& r_res = results[std::string({'R', c.type})];
        for(const std::string& other : intersections['R']){
            if(other[0] == c.name[0]){
                r_res.push_back((other < c.name ? other + " " + c.name : c.name + " " + other));
            }else{
                r_res.push_back(other + " " + c.name);
            }
        }
        auto& l_res = results[(c.type == 'R' ? "RL" : std::string({'L', c.type}))];
        for(const std::string& other : intersections['L']){
            if((other[0] == c.name[0] && other >= c.name) || c.name[0] == 'R'){
                l_res.push_back(c.name + " " + other);
            }else{
                l_res.push_back(other + " " + c.name);
            }
        }
        auto& c_res = results[std::string({c.type, 'C'})];
        for(const std::string& other : intersections['C']){
            if((other[0] == c.name[0] && other < c.name)){
                c_res.push_back(other + " " + c.name);
            }else{
                c_res.push_back(c.name + " " + other);
            }
        }
        heap.add(c);
    }
    
    for(const std::string& name : out_of_bounds_str){
        ans.push_back("out_of_bounds " + name);
    }
    for(const std::string& key : std::vector<std::string>{"RR", "RL", "RC", "LL", "LC", "CC"}){
        for(const std::string& s : results[key]){
            ans.push_back("intersection " + s);
        }
    }
    if(ans.size() == 0){
        ans.push_back("OK");
    }else{
        ans.insert(ans.begin(), "ERROR");
    }
    return ans;
}
