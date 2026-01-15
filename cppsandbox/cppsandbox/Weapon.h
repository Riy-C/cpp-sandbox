//#pragma
//#pragma is a non-standard but widely supported preprocessor directive. it is used to provide additional information to the compiler, often to control specific compiler behaviors or optimizations.
//"#pragma once" is a common use of this directive, which tells the compiler to include the file only once during the compilation process, preventing multiple inclusions that could lead to errors.
#pragma once
#include <string>

enum class WeaponClass {
    Physical,
    Neo,
    Occult,
    Spiritbound
};

enum class Rarity {
    Junk,
    Common,
    Uncommon,
    Rare,
    Signature,
    Forbidden
};

//struct
//struct is a user-defined data type that allows you to group related variables together under a single name. Essentially, it is a way to create your own custom "basket" of data types.
struct Weapon {
    //std
    //means Standard. It is a namespace that contains all the standard C++ library functions and classes. Think of it like the standard loadout of a video game; all the tools you need off the bat. 
    std::string name;
    std::string size;
    WeaponClass weaponClass;
    std::string Shape;
    Rarity rarity;
    int dmg;
    int ndmg;
    int odmg;
    int price;
    std::string description;

};