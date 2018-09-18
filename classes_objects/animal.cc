/**
* an insight into class constructors, copy & move constructors
* and destructor
*/

#include <iostream>
#include <string>

class Animal {
public:
    explicit Animal(const std::string & given_name) : name(given_name), weight(0) 
    {
        std::cout << "animal construct "  << name << ", " << weight << std::endl;
    }
    void echo() const {
        std::cout << name << " says hi" << std::endl;
    }
    Animal(const Animal & w) : name(w.name), weight(w.weight) {
        std::cout << "copy construct " << name << ", " << weight << std::endl;
    }

    Animal(Animal &&w) : name(w.name), weight(w.weight) {
        std::cout << "move construct " <<  name << ", " << weight << std::endl;
    }
    ~Animal() {
        std::cout << "destruct animal " << name << std::endl;
    }
    Animal &operator=(const Animal &w) = default;
    Animal &operator=(Animal &&w) = default;

    std::string getName() { return name;}
    int getWeight() { return weight;}


private:
    std::string name;
    int weight;
};


class Bird : public Animal {
public:
    Bird(const std::string & given_name) : Animal(given_name) {
        std::cout << "bird construct "  << getName() << ", " << getWeight() << std::endl;
    }
    ~Bird() {
        std::cout << "destruct bird " << getName() << std::endl;
    }
};



class Mammal : public Animal {
public:
    // inherited constructor
    using Animal::Animal;
};


int main(int argc, char **argv) {

    // only construct call, no destruct call
    const Animal cat("black cat");
    cat.echo();

    std::cout << "-------------------" << std::endl;

    // only construct call, no destruct call
    Bird sparrow("gray sparrow");
    sparrow.echo();
    std::cout << "-------------------" << std::endl;


    // casting from superclass to subclass and the other way around is generally
    // a bad idea. This is only for illustration
    Animal * pidgeon = new Bird("white pidgeon");
    pidgeon->echo();
    std::cout << "-------------------" << std::endl;


    Bird * eagle = static_cast<Bird *>(new Animal("bald eagle"));
    eagle->echo();
    std::cout << "-------------------" << std::endl;

    // destruct all objects
    return 0;
}