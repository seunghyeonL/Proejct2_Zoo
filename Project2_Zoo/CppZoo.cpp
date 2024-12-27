#include <iostream>
#include <random>
#include <string>
#define INITIAL_ZOO_SIZE 10

using namespace std;

enum AnimalType { DOG, CAT, COW };

class Animal {
public:
    Animal() {
        cout << "Animal 생성자" << endl;
    }
    virtual ~Animal() {
        cout << "Animal 소멸자" << endl;
    };
    virtual void makeSound() = 0;
};

class Dog : public Animal {
private:
    AnimalType type;

public:
    Dog() : type{ DOG } {
        cout << "강아지 생성" << endl;
    }
    ~Dog() {
        cout << "강아지 소멸" << endl;
    }
    void makeSound() {
        cout << "왈왈컹컹" << endl;
    }
};

class Cat : public Animal {
private:
    AnimalType type;

public:
    Cat() : type{ CAT } {
        cout << "고양이 생성" << endl;
    }
    ~Cat() {
        cout << "고양이 소멸" << endl;
    }
    void makeSound() {
        cout << "야아옹" << endl;
    }
};

class Cow : public Animal {
private:
    AnimalType type;

public:
    Cow() : type{ COW } {
        cout << "소 생성" << endl;
    }
    ~Cow() {
        cout << "소 소멸" << endl;
    }
    void makeSound() {
        cout << "음머어어" << endl;
    }
};

class Zoo {
private:
    Animal** animals;
    int zooSize;
    int animalCount;

public:
    Zoo() : animals{ nullptr, }, zooSize{ INITIAL_ZOO_SIZE }, animalCount{ 0 } {
        animals = new Animal * [INITIAL_ZOO_SIZE];
    };
    ~Zoo() {
        for (int i = 0; i < animalCount; i++) {
            delete animals[i];
        }
        delete[] animals;
    };
    void addAnimal(Animal* animal);
    void performActions();
};

void Zoo::addAnimal(Animal* animal) {
    animals[animalCount] = animal;
    animalCount++;

    if (animalCount == zooSize) {
        zooSize *= 2;
        Animal** tmpAnimals = new Animal * [zooSize] { nullptr, };

        for (int i = 0; i < animalCount; i++) {
            tmpAnimals[i] = animals[i];
        }

        delete[] animals;
        animals = tmpAnimals;
    }
}

void Zoo::performActions() {
    for (int i = 0; i < animalCount; i++) {
        animals[i]->makeSound();
    }
}

class Main {
private:
    static int getRandomInt0To2();

public:
    static Animal* createRandomAnimal(Zoo& zoo);
};

int Main::getRandomInt0To2() {
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> dis(0, 2);
    return dis(gen);
}

Animal* Main::createRandomAnimal(Zoo& zoo) {
    AnimalType type = AnimalType(getRandomInt0To2());
    Animal* createdAnimal = nullptr;

    switch (type) {
    case DOG:
        createdAnimal = new Dog();
        break;
    case CAT:
        createdAnimal = new Cat();
        break;
    case COW:
        createdAnimal = new Cow();
        break;
    }

    zoo.addAnimal(createdAnimal);

    return createdAnimal;
}

int main() {
    // Zoo zoo
    Zoo* zoo = new Zoo();

    for (int i = 0; i < 30; i++) {
        Main::createRandomAnimal(*zoo);
    }

    cout << endl;

    zoo->performActions();

    cout << endl;

    delete zoo;

    return 0;
}