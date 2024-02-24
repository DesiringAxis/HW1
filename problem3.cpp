#include <iostream>
#include <string>
#include <map>
using namespace std;
// New class "Plane"
class Plane {
// Use container from Q2 and introduces new variables
private:
    double pos;
    double vel;
    double distance;
    bool at_SCE;
    string origin;
    string destination;
    map<string, map<string, int>> flights;
// Public members with constuctor, deconstructor, new operate function, and get functions
public:
    Plane(const string& from, const string& to) : origin(from), destination(to) {
        pos = 0.0;
        vel = 0.0;
        distance = 0.0;
        at_SCE = (origin == "SCE");
        flights["SCE"]["PHL"] = 160;
        flights["SCE"]["ORD"] = 640;
        flights["SCE"]["EWR"] = 220;
    }
    ~Plane() {}
    void operate(double dt) {
    if (origin == destination) {
        cout << "Error: Plane is already at its destination." << endl;
        return;
    }
    distance = dt * vel;
    cout << "Distance traveled: " << distance << " miles" << endl;
    if (origin == "SCE") {
        pos += distance;
        if (pos >= flights[origin][destination]) {
            pos = flights[origin][destination];
            origin = destination;
            cout << "Plane arrived at destination " << destination << endl;
        }
    } else {
        pos -= distance;
        if (pos <= 0) {
            pos = 0;
            cout << "Plane arrived at SCE" << endl;
        }
    }
    at_SCE = (pos == 0);
}
    double getPos() const { return pos; }
    double getVel() const { return vel; }
    double getDistance() const { return distance; }
    bool isAtSCE() const { return at_SCE; }
    string getOrigin() const { return origin; }
    string getDestination() const { return destination; }
    void setVel(double velocity) { vel = velocity; }
    void setDestination(const string& dest) { destination = dest; }
};
// Prints current info for plane
int main() {
    Plane plane("SCE", "EWR");
    plane.setVel(100);
    plane.operate(1.1);
    cout << "Current position: " << plane.getPos() << " miles" << endl;
    cout << "At SCE: " << (plane.isAtSCE() ? "Yes" : "No") << endl;
    cout << "Origin: " << plane.getOrigin() << endl;
    cout << "Destination: " << plane.getDestination() << endl;
    return 0;
}