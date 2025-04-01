#include <iostream>
#include <vector>
#include <memory>

using namespace std;

class Herbivore {
public:
    virtual void eatGrass() = 0;
    virtual int getWeight() = 0;
    virtual bool isAlive() = 0;
    virtual ~Herbivore() = default;
};

class Carnivore {
public:
    virtual void eat(Herbivore* herbivore) = 0;
    virtual int getPower() = 0;
    virtual ~Carnivore() = default;
};

class Wildebeest : public Herbivore {
private:
    int weight;
    bool life;
public:
    Wildebeest() : weight(100), life(true) {}
    void eatGrass() override { weight += 10; }
    int getWeight() override { return weight; }
    bool isAlive() override { return life; }
};

class Bison : public Herbivore {
private:
    int weight;
    bool life;
public:
    Bison() : weight(200), life(true) {}
    void eatGrass() override { weight += 10; }
    int getWeight() override { return weight; }
    bool isAlive() override { return life; }
};

class Elk : public Herbivore {
private:
    int weight;
    bool life;
public:
    Elk() : weight(300), life(true) {}
    void eatGrass() override { weight += 10; }
    int getWeight() override { return weight; }
    bool isAlive() override { return life; }
};

class Lion : public Carnivore {
private:
    int power;
public:
    Lion() : power(150) {}
    void eat(Herbivore* herbivore) override {
        if (power > herbivore->getWeight()) power += 10;
        else power -= 10;
    }
    int getPower() override { return power; }
};

class Wolf : public Carnivore {
private:
    int power;
public:
    Wolf() : power(80) {}
    void eat(Herbivore* herbivore) override {
        if (power > herbivore->getWeight()) power += 10;
        else power -= 10;
    }
    int getPower() override { return power; }
};

class Tiger : public Carnivore {
private:
    int power;
public:
    Tiger() : power(120) {}
    void eat(Herbivore* herbivore) override {
        if (power > herbivore->getWeight()) power += 10;
        else power -= 10;
    }
    int getPower() override { return power; }
};

class Continent {
public:
    virtual unique_ptr<Herbivore> createHerbivore() = 0;
    virtual unique_ptr<Carnivore> createCarnivore() = 0;
    virtual ~Continent() = default;
};

class Africa : public Continent {
public:
    unique_ptr<Herbivore> createHerbivore() override { return make_unique<Wildebeest>(); }
    unique_ptr<Carnivore> createCarnivore() override { return make_unique<Lion>(); }
};

class NorthAmerica : public Continent {
public:
    unique_ptr<Herbivore> createHerbivore() override { return make_unique<Bison>(); }
    unique_ptr<Carnivore> createCarnivore() override { return make_unique<Wolf>(); }
};

class Eurasia : public Continent {
public:
    unique_ptr<Herbivore> createHerbivore() override { return make_unique<Elk>(); }
    unique_ptr<Carnivore> createCarnivore() override { return make_unique<Tiger>(); }
};

class AnimalWorld {
private:
    unique_ptr<Continent> continent;
    vector<unique_ptr<Herbivore>> herbivores;
    vector<unique_ptr<Carnivore>> carnivores;
public:
    AnimalWorld(unique_ptr<Continent> c) : continent(move(c)) {}
    void initializeAnimals() {
        herbivores.push_back(continent->createHerbivore());
        carnivores.push_back(continent->createCarnivore());
    }
    void feedHerbivores() {
        for (auto& herbivore : herbivores) herbivore->eatGrass();
    }
    void feedCarnivores() {
        for (auto& carnivore : carnivores) {
            for (auto& herbivore : herbivores) {
                if (herbivore->isAlive()) carnivore->eat(herbivore.get());
            }
        }
    }
};

int main() {
    AnimalWorld africa(make_unique<Africa>());
    africa.initializeAnimals();
    cout << "Africa: Herbivores and carnivores interact\n";
    africa.feedHerbivores();
    africa.feedCarnivores();

    AnimalWorld northAmerica(make_unique<NorthAmerica>());
    northAmerica.initializeAnimals();
    cout << "\nNorth America: Herbivores and carnivores interact\n";
    northAmerica.feedHerbivores();
    northAmerica.feedCarnivores();

    AnimalWorld eurasia(make_unique<Eurasia>());
    eurasia.initializeAnimals();
    cout << "\nEurasia: Herbivores and carnivores interact\n";
    eurasia.feedHerbivores();
    eurasia.feedCarnivores();

    return 0;
}
