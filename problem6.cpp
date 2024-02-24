#include <iostream>
#include <string>
class Plane;
//New Pilot class
class Pilot {
// new string variable "name"
private:
    std::string name;
    Plane* myPlane;
// contains a constructor, deconstructor, get function, and pointer
public:
    Pilot(const std::string& pilotName, Plane* plane) : name(pilotName), myPlane(plane) {
        std::cout << name << " is at the gate, ready to board the plane." << std::endl;
        std::cout << "Memory Address: " << this << std::endl;
    }
    ~Pilot() {
        std::cout << name << " is out of the plane." << std::endl;
    }
    std::string getName() const {
        return name;
    }
};