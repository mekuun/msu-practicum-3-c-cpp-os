#include <iostream>
#include <cstring>

using std::cout, std::cin, std::cerr, std::endl, std::ostream;

class event {
private:
    int year_, month_, day_;
    char* name_;
public:
    int get_year() {return year_;}
    int get_month() {return month_;}
    int get_day() {return day_;}
    char* get_name() {return name_;}

    const virtual void print_res() = 0;
    virtual void change_grade(int new_grade) = 0;
    void change_date(int new_year ,int new_month ,int new_day);
    virtual ~event(){
        delete [] name_;
    };
    event(const char* new_name, int new_year, int new_month, int new_day);
    event(const event &my_event);
};

void event ::change_date(int new_year, int new_month, int new_day) {
    year_ = new_year;
    month_ = new_month;
    day_ = new_day;
}

event :: event(const char* new_name, int new_year ,int new_month ,int new_day){
    name_ = new char[strlen(new_name)];
    strcpy(name_, new_name);
    year_ = new_year;
    month_ = new_month;
    day_ = new_day;
}

event :: event(const event &my_event){
    name_ = new char[strlen(my_event.name_)];
    strcpy(name_, my_event.name_);
    year_ = my_event.year_;
    month_ = my_event.month_;
    day_ = my_event.day_;
}

class test : public event {
private:
    bool pass_status_;
public:
    test(const char* new_name, int new_year, int new_month, int new_day, bool new_pass_status):event(new_name, new_year ,new_month ,new_day), pass_status_(new_pass_status){};
    test(const char* new_name, int new_year, int new_month, int new_day, int new_pass_status):event(new_name, new_year ,new_month ,new_day), pass_status_(new_pass_status > 2){};
    virtual void change_grade(int new_grade);
    const virtual void print_res();
};

void test :: change_grade(int new_grade){
    pass_status_ = new_grade > 2;
}

const void test :: print_res() {
    cout << get_name() << ' ' << get_year() << ' ' << get_month() << ' ' << get_day() << ' ' << (pass_status_ ? "true":"false") << endl;
}

class exam : public event {
private:
    int mark_;
public:
    exam(const char* new_name, int new_year, int new_month, int new_day, int new_mark):event(new_name, new_year ,new_month ,new_day), mark_(new_mark){};
    const virtual void print_res();
    virtual void change_grade(int new_grade);
};

void exam :: change_grade(int new_grade){
    mark_ = new_grade;
}

const void exam :: print_res() {
    cout << get_name() << ' ' << get_year() << ' ' << get_month() << ' ' << get_day() << ' ' << "Grade" << ' ' << mark_ << endl;
}
