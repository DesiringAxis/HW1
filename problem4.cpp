#include <iostream>
#include <string>
#include <map>
using namespace std;
class Plane {
private:
    double pos;
    double vel;
    double distance;
    bool at_SCE;
    string origin;
    string destination;
    map<string, map<string, int>> flights;
public:
    Plane(const string& from, const string& to) : origin(from), destination(to) {
        pos = 0.0;
        vel = 0.0;
        at_SCE = (from == "SCE");
        flights["SCE"]["PHL"] = 160;
        flights["SCE"]["ORD"] = 640;
        flights["SCE"]["EWR"] = 220;
        distance = flights[from][to];
        cout << "Plane Created at " << this << endl;
    }
    ~Plane() {
        cout << "Plane Destroyed" << endl;
    }
    double getPos() const { return pos; }
    void setPos(double p) { pos = p; }
    double getVel() const { return vel; }
    void setVel(double v) { vel = v; }
    double getDistance() const { return distance; }
    bool isAtSCE() const { return at_SCE; }
    void setAtSCE(bool a) { at_SCE = a; }
    string getOrigin() const { return origin; }
    void setOrigin(const string& o) { origin = o; }
    string getDestination() const { return destination; }
    void setDestination(const string& d) { destination = d; }
    // flowchart implementation
    void operate(double dt) {
        if (pos < distance) {
            pos += vel * dt;
            at_SCE = false;
        } else {
            if (destination == "SCE") {
                at_SCE = true;
                swap(origin, destination);
                pos = 0.0;
            } else {
                swap(origin, destination);
                pos = 0.0;
            }
        }
    }
};
// prints out information on plane and allows to change velocity and time elasped
int main() {
    Plane plane("SCE", "ORD");
    cout << "Current position: " << plane.getPos() << " miles" << endl;
    cout << "At SCE: " << (plane.isAtSCE() ? "Yes" : "No") << endl;
    cout << "Distance: " << plane.getDistance() << " miles" << endl;
    plane.setVel(200);
    plane.operate(2.5);
    cout << "After operation:" << endl;
    cout << "Current position: " << plane.getPos() << " miles" << endl;
    cout << "At SCE: " << (plane.isAtSCE() ? "Yes" : "No") << endl;
    return 0;
}