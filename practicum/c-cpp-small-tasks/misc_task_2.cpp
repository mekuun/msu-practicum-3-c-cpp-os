#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
using namespace std;

class Lemming {
public:
    std::string name;
    Lemming(std::string mama) {name = mama;}

    void doManicure() {
        int glamour = rand() % 2;
        if (glamour == 0) {
            std::cout << name << " говорит: 'Я такой гламурный после маникюра! 💖💅💖\n";
            shopping();
        } else {
            std::cout << name << " говорит: 'О нет! Мой маникюр такой не гламурный! 😱💔👠\n";
            jumpFromCliff();
        }
    }

    void shopping() {
        int scenario = rand() % 3;
        switch(scenario) {
            case 0:
                std::cout << name << " говорит: 'Этот консультант такой грубый! 😡👜🛍\n";
                std::cout << name << " сбросил консультанта со скалы! 💔😱💔\n";
                break;
            case 1:
                std::cout << name << " говорит: 'О нет, нет моего размера! 😱👠😭\n";
                jumpFromCliff();
                break;
            case 2:
                std::cout << name << " говорит: 'Я нашла свои гуччи тапки! Я начинаю тверкать! 👡💕💃\n";
                break;
        }
        gossip();
    }

    void jumpFromCliff() {
        std::cout << name << " говорит: 'Это просто не терпимо! Я прыгаю со скалы! 💔\n";
    }

    void gossip() {
        int friendCount = rand() % 5; // получаем количество друзей
        if(friendCount == 0){
            std::cout << name << " говорит: 'О нет! Я одна! Я тверкаю в одиночестве! 😔💃👯‍♀️\n";
        } else {
            std::cout << name << " говорит: 'Ха-ха, я тверкаю со своими друзьями! 🎉💃🥳\n";
        }
    }
};

int main() {
    srand(time(0));
    std::vector<Lemming> lemmings;
    lemmings.push_back(Lemming("Пушистик"));
    lemmings.push_back(Lemming("Мурлыка"));
    lemmings.push_back(Lemming("Разгулин"));



    for (auto& lemming : lemmings) {
        lemming.doManicure();
    }
}