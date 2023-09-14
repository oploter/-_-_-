#include <string>
#include <iostream>

struct Person{
private:
    std::string name_m;
    std::string surname_m;
public:
    Person(const std::string& name, const std::string& surname) : name_m(name), surname_m(surname){}
    const std::string& name() const {return name_m;}
    const std::string& surname() const {return surname_m;}
};

unsigned get_option_1(const Person& person, unsigned num_of_options){
    unsigned sum = 0;
    for(char letter : person.surname()){
        sum += (unsigned)letter;
    }
    return sum % num_of_options;
}

unsigned get_option_2(const Person& person, unsigned num_of_options){
    return (person.name()[0]) % num_of_options;
}

int main(){
    /*
     name: "Abcde"          код первой буквы    65
     surname: "Fghijk"      сумма всех букв     595
     */
    {
        Person p("Abcde", "Fghijk");
        std::cout << get_option_1(p, 2) << ' ' << get_option_2(p, 2) << '\n'; // Ожидаемый результат: 1, 1
    }
    {
        Person p("Abcde", "Fghijk");
        std::cout << get_option_1(p, 3) << ' ' << get_option_2(p, 3) << '\n'; // Ожидаемый результат: 1, 2
    }
    {
        Person p("Abcde", "Fghijk");
        std::cout << get_option_1(p, 4) << ' ' << get_option_2(p, 4) << '\n'; // Ожидаемый результат: 3, 1
    }
}

