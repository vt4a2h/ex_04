#include <iostream>
#include <stdio.h>
#include <cstring>

class Unit
{
public:
    Unit(const char* name, int hitpoints, int damage)
        : name_ (new char[strlen(name) + 1]) // +1 потому что в "сырых" строках есть "терминатор" -- '\0'
        , hitpoints_(hitpoints)
        , damage_(damage)
    {
        strcpy(name_, name);
    }

    Unit(const Unit &src)
        : name_(nullptr)
    {
        Unit tmp(src.name_, src.hitpoints_, src.damage_);
        this->swap(tmp);
    }

    Unit &operator =(const Unit &rhs)
    {
        if (this != &rhs) {
            Unit tmp(rhs);
            this->swap(tmp);
        }

        return *this;
    }

    void swap(Unit &src)
    {
        std::swap(name_, src.name_);
        std::swap(hitpoints_, src.hitpoints_);
        std::swap(damage_, src.damage_);
    }

    ~Unit()
    {
        delete [] name_;
    }

    char* name_;
    int   hitpoints_;
    int   damage_;
};

// если бы передали по const-ссылке (как это и положено в данном случае),
// то программа не вылетала бы и в первоначальном варианте.
void ShowStats(Unit unit)
{
    printf("%s - %d - %d", unit.name_, unit.hitpoints_, unit.damage_);
}

int main()
{
    Unit marine("marine", 45, 6);

    ShowStats(marine);
    // Game cycle...
    ShowStats(marine);

    return 0;
}

