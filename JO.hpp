#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Window.hpp>
#include <iostream>
#include <string>
#include <vector>



class MUSICIEN

{
    private:
    int __positionx;
    int __positiony;

    public:
    MUSICIEN();
    ~MUSICIEN();
    void setpositionx(int positionx);
    void setpositiony(int positiony);
    int getpositionx();
    int getpositiony();
    int distance(MUSICIEN musicien);    
};

class Vent : public MUSICIEN
{
    private:
    int puissance_souffle;

};
/*
class Percussion : public MUSICIEN
{
    private:
    int puissance_frappe;
    public:
    Percussion();
    ~Percussion();
    void setpuissance_frappe(int puissance_frappe);
    int getpuissance_frappe();
     

};

class Corde : public MUSICIEN
{
    private:
    int accord;
    public:
    Corde();
    ~Corde();
    void setaccord(int accord);
    int getaccord();




    
};
*/


