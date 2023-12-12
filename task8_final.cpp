#include <fstream>
#include <unordered_map>
#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <algorithm>
#include <utility>

struct Component{
    float x_low;
    float x_high;
    float y_low;
    float y_high;
    std::string name;
    char type;  
    Component(){}
    Component(float x_low_, float x_high_, float y_low_, float y_high_, std::string name_, char type_) : 
    x_low(x_low_), x_high(x_high_), y_low(y_low_), y_high(y_high_), name(name_), type(type_){}
    
    bool intersects(const Component& c) const ;
};

struct Heap{
    std::vector<Component> heap;
    int n = 0;
    Heap() : heap(std::vector<Component>(1)), n(0){}
    void siftUp(int i);
    void siftDown(int i);
    void add(const Component& i);
    float getMinX();
    void extractMin();
    std::unordered_map<char, std::vector<std::string>> intersections(const Component& c);
};


void Heap::siftUp(int i){
    while(i > 1 && heap[i/2].x_high > heap[i].x_high){
        std::swap(heap[i], heap[i/2]);
        i /= 2;
    }
}

void Heap::siftDown(int i){
    while(1){
        int l = 2 * i;
        if(l + 1 <= n && heap[l + 1].x_high < heap[l].x_high) ++l;
        if(!(l <= n && heap[l].x_high < heap[i].x_high)) break;
        std::swap(heap[l], heap[i]);
        i = l;
    }
}

void Heap::add(const Component& c){
    ++n;
    if((int) heap.size() <= n){
        heap.push_back(c);
    }else{
        heap[n] = c;
    }
    siftUp(n);
}

float Heap::getMinX(){
    return n == 0 ? 100000000 : heap[1].x_high;
}

void Heap::extractMin(){
    std::swap(heap[1], heap[n--]);
    siftDown(1);
}

std::unordered_map<char, std::vector<std::string>> Heap::intersections(const Component& c){
    std::unordered_map<char, std::vector<std::string>> ans;
    for(int i = 1; i <= n; ++i){
        if(c.intersects(heap[i])){
            ans[heap[i].type].push_back(heap[i].name);
        }
    }
    return ans;
}


bool Component::intersects(const Component& c) const {
    return !(y_low > c.y_high || c.y_low > y_high);
}

float W, H;

std::ostream& operator<<(std::ostream& os, std::pair<float, float>& component){
    os << "C{" << component.first << ',' << component.second << "}";
    return os;
}

struct Size{
    float w = 0;
    float h = 0;
    Size(float w_, float h_) : w(w_), h(h_){}
    Size(){}
};

std::unordered_map<std::string, Size> component_info {
    {"R01005", Size(4, 2)},
    {"R0201", Size(6, 3)},
    {"R0402", Size(10, 5)},
    {"R0603", Size(155, 85)},
    {"R0805", Size(20, 12)},
    {"R0808", Size(0, 0)},
    {"R1020", Size(50, 25)},
    {"R1206", Size(32, 16)},
    {"R1210", Size(32, 25)},
    {"R1812", Size(32, 46)},
    {"R2010", Size(50, 25)},
    {"R2512", Size(63, 32)},
    {"L2835", Size(28, 35)},
    {"L3014", Size(30, 14)},
    {"L3528", Size(35, 28)},
    {"L5050", Size(50, 50)},
    {"L5630", Size(56, 30)},
    {"L5730", Size(57, 30)},
    {"L5", Size(50, 50)},
    {"C5", Size(5, 5)},
    {"C8", Size(8, 8)},
    {"C10", Size(10, 10)},
    {"C16", Size(16, 16)},
    {"C18", Size(18, 18)},
    {"C20", Size(20, 20)},
    {"C22", Size(22, 22)},
    {"C25", Size(25, 25)}
};

Component create_component(std::string name, std::string type, float x_center, float y_center){
    auto size = component_info[type];
    float x_low = x_center - size.w/2;
    float x_high = x_center + size.w/2;
    float y_low = y_center - size.h/2;
    float y_high = y_center + size.h/2;
    return Component(x_low, x_high, y_low, y_high, name, type[0]);
    //return std::make_pair<>(Component(x_open, y_low, y_high, true, name),
    // Component(x_close, y_low, y_high, false, name));
}

int main(){
    std::cin >> W >> H;
    int N;
    std::cin >> N;
    std::string line;
    std::getline(std::cin, line);
    std::string component_name, type;
    float x_center, y_center;
    std::vector<Component> components;
    std::vector<std::string> out_of_bounds_str;
    for(int i = 0; i < N; ++i){
        std::getline(std::cin, line);
        std::stringstream stream(line);
        stream >> component_name >> type >> x_center >> y_center;
        components.push_back(create_component(component_name, type, x_center, y_center));
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
        if(heap.getMinX() < c.x_low){
            while(heap.getMinX() < c.x_low){
                heap.extractMin();
            }
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
    
    std::stringstream ss;
    for(const std::string& name : out_of_bounds_str){
        ss << "out_of_bounds " << name << '\n';
    }
    for(const std::string& key : std::vector<std::string>{"RR", "RL", "RC", "LL", "LC", "CC"}){
        for(const std::string& s : results[key]){
            ss << "intersection " << s << "\n";
        }
    }
    if(ss.str() == ""){
        std::cout << "OK\n";
    }else{
        std::cout << "ERROR\n";
        std::cout << ss.str() << '\n';
    }
}