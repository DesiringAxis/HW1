#include <iostream>
#include <string>
#include <map>
using namespace std;
class Plane; // Forward declaration
class Pilot {
private:
    string name;
    string certificateNumber;
    Plane* myPlane;
public:
    Pilot(const string& pilotName, const string& certNumber) 
        : name(pilotName), certificateNumber(certNumber), myPlane(nullptr) {
        cout << "Pilot " << name << " with certificate number: " << certificateNumber << " is at the gate, ready to board the plane." << endl;
    }
    ~Pilot() {
        cout << "Pilot " << name << " is out of the plane." << endl;
    }
    void setPlane(Plane* plane) {
        myPlane = plane;
    }
    string getName() const {
        return name;
    }
    string getCertificateNumber() const {
        return certificateNumber;
    }
};
class Plane {
private:
    double pos;
    double vel;
    double distance;
    bool at_SCE;
    string origin;
    string destination;
    map<string, map<string, int>> flights;
    Pilot* pilot;
public:
    Plane(const string& from, const string& to) 
        : origin(from), destination(to), pilot(nullptr), pos(0.0), vel(0.0), at_SCE(from == "SCE") {
        flights["SCE"]["PHL"] = 160;
        flights["SCE"]["ORD"] = 640;
        flights["SCE"]["EWR"] = 220;
        distance = flights[from][to];
        cout << "Plane created with a tail number: " << this << endl;
    }
    ~Plane() {
        cout << "Plane destroyed" << endl;
    }
    void setVel(double velocity) {
        vel = velocity;
    }
    void operate(double dt, Pilot* pilot1, Pilot* pilot2) {
        double distanceCovered = vel * dt / 3600;
        pos += distanceCovered;
        if (pos >= distance || at_SCE) {
            at_SCE = true;
            cout << "The plane (" << this << ") is at SCE" << endl;
            swap(pilot, pilot == pilot1 ? pilot2 : pilot1);
            if (pilot) {
                cout << "Pilot " << pilot->getName() << " with certificate number: " << pilot->getCertificateNumber() << " is in control of the plane: " << this << endl;
            }
        }
    }
    void setPilot(Pilot* p) {
        pilot = p;
        p->setPlane(this);
        cout << "Pilot " << p->getName() << " with certificate number: " << p->getCertificateNumber() << " is in control of the plane: " << this << endl;
    }
};
int main() {
    Pilot* pilotA = new Pilot("A", "123456789");
    Pilot* pilotB = new Pilot("B", "987654321");
    Plane* plane = new Plane("SCE", "PHL");
    plane->setPilot(pilotA); // Pilot A initially in control
    plane->setVel(450); // Set flight speed
    // Simulate flight operations
    const int iterations = 10; // Example simulation length
    const double timestep = 10.0; // Time step in seconds
    for (int i = 0; i < iterations; ++i) {
        plane->operate(timestep, pilotA, pilotB);
    }
    // Ensure both pilots and the plane are destructed
    delete pilotA;
    delete pilotB;
    delete plane;
    return 0;
}