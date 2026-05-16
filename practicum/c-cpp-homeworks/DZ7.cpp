#include <iostream>
#include <string>
using std::cout, std::cin, std::cerr, std::endl, std::ostream, std::istream, std::string;
enum codes{NUMBER_ERR, OVERFLOW_ERR, NAME_ERR, REPEAT_ERR};

class Player_exc{
    int errcode;
    string name;
    int number;
public:
    Player_exc(int errcode_inp, const string &name_inp, int number_inp = 0):errcode(errcode_inp), name(name_inp), number(number_inp){};
    void print() const;
};

void Player_exc::print() const {
    cerr<<"Exception: ";
    switch(errcode){
        case NUMBER_ERR: {
            cerr << "Wrong number in team " << name << " Error number: " << number << endl;
            break;
        }
        case OVERFLOW_ERR: {
            cerr << "Too many players in team " << name << endl;
            break;
        }
        case NAME_ERR: {
            cerr << "Wrong name in team " << name << endl;
            break;
        }
        case REPEAT_ERR: {
            cerr << "Double number in team " << name << " Error number: " << number << endl;
            break;
        }
    }
}

class Player{
    int number;
    string name;
    static int zenit[11];
    static int cska[11];
    void addPlayerToTeam(int* team, const string& teamName, int number_inp);
public:
    Player(const string &name_, int number_);
    void Print() const;
    static void Print_teams() const;
    ~Player();
};

int Player::zenit[11]={0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
int Player::cska[11]={0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};

Player::Player(const string &name_inp, int number_inp) {
    name = name_inp;
    number = -1;
    if(name == "Zenit"){
        addPlayerToTeam(zenit, "Zenit", number_inp);
    }
    else if(name == "CSKA"){
        addPlayerToTeam(cska, "CSKA", number_inp);
    }
    else {
        throw(Player_exc(NAME_ERR, name_inp));
    }
}

void Player::addPlayerToTeam(int* team, const string& teamName, int number_inp) {
    bool duplicate_flag = false;

    for(int i = 0; i < 11; i++) {
        if (team[i] == number_inp) {
            duplicate_flag = true;
            break;
        }
    }
    for(int i = 0; i < 11; i++){
        if(team[i] == 0) {
            team[i] = number = number_inp;
            break;
        }
    }
    if(number < 0) throw(Player_exc(OVERFLOW_ERR, teamName));
    if(number_inp < 1) throw(Player_exc(NUMBER_ERR, teamName, number_inp));
    if(duplicate_flag) throw(Player_exc(REPEAT_ERR, teamName, number_inp));
}

void Player::Print() const {
    cout << name << " " << number << endl;
}

void Player::Print_teams() {
    bool endflag[2] = {false, false};
    for (int i = 0; i < 11; i++) {
        if (zenit[i] != 0) endflag[0] = true;
        if (cska[i] != 0) endflag[1] = true;
    }

    if (endflag[0]){
        cout << "Zenit: ";
        for(int i = 0; i < 10; i++) if (zenit[i] != 0) cout << zenit[i] << " ";
        if (zenit[10] != 0) cout << zenit[10];
        cout << endl;
    }

    if (endflag[1]){
        cout << "CSKA: ";
        for(int i = 0; i < 10; i++) if (cska[i] != 0) cout << cska[i] << " ";
        if (cska[10] != 0) cout << cska[10];
        cout << endl;
    }
}

Player::~Player() {
    if(name == "Zenit") {
        for(int i = 0; i < 11; i++) {
            if(zenit[i] == number) {
                zenit[i] = 0;
                break;
            }
        }
    }
    else if(name == "CSKA") {
        for(int i = 0; i < 11; i++) {
            if(cska[i] == number) {
                cska[i] = 0;
                break;
            }
        }
    }
}

int main(){
    try{
        test_players();
    }
    catch(Player_exc &errrrrror){
        errrrrror.print();
    }
    catch(...){

    }
    return 0;
}