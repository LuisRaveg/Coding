#ifndef ANIMAL_H
#define ANIMAL_H
#include <iostream>
#include <string>
using namespace std;
class Animal
{
public:
    Animal();
    virtual void setSonido()=0;
    virtual string getSonido()=0;
    virtual void come()=0;
    virtual void muevete()=0;
    virtual void duerme()=0;
    virtual ~Animal()=0;
protected:
    string sound;
private:
};
#endif