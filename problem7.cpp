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
    Pilot(const string& pilotName, const string& certNumber, Plane* plane) : name(pilotName), certificateNumber(certNumber), myPlane(plane) {
        cout << "Pilot " << name << " with certificate number: " << certificateNumber << " is at the gate, ready to board the plane." << endl;
    }
    ~Pilot() {
        cout << "Pilot " << name << " is out of the plane." << endl;
    }
    string getName() const {
        return name;
    }
    string getCertificateNumber() const {
        return certificateNumber;
    }
    void setPlane(Plane* plane) {
        myPlane = plane;
    }
    Plane* getPlane() const {
        return myPlane;
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
    Plane(const string& from, const string& to) : origin(from), destination(to), pilot(nullptr) {
        pos = 0.0;
        vel = 0.0;
        at_SCE = (from == "SCE");
        flights["SCE"]["PHL"] = 160;
        flights["SCE"]["ORD"] = 640;
        flights["SCE"]["EWR"] = 220;
        distance = flights[from][to];
        cout << "Plane created with a tail number: " << this << endl;
    }
    ~Plane() {
        cout << "Plane destroyed" << endl;
    }
    double getPos() const { return pos; }
    double getVel() const { return vel; }
    double getDistance() const { return distance; }
    bool isAtSCE() const { return at_SCE; }
    string getOrigin() const { return origin; }
    string getDestination() const { return destination; }
    void setVel(double velocity) { vel = velocity; }
    void operate(double dt, Pilot* pilot1, Pilot* pilot2) {
    double distanceCovered = vel * dt / 3600;
    if (pos + distanceCovered < distance) {
        pos += distanceCovered;
        at_SCE = false;
    } else {
        // Plane will reach or pass SCE in this step
        at_SCE = true;
        if (destination == "SCE") {
            swap(origin, destination);
            pos = 0.0;
            cout << "The plane (" << this << ") is at SCE" << endl;
            if (pilot) {
                pilot->setPlane(nullptr);
                if (pilot->getName() == "Pilot in command") {
                    pilot = nullptr; // Pilot in command is out of the plane
                }
            }
            // Check if there is a pilot to take control
            if (pilot && pilot->getName() != "Pilot in command") {
                cout << "Pilot " << pilot->getName() << " with certificate number: " << pilot->getCertificateNumber() << " is in control of the plane: " << static_cast<const void*>(this) << endl;
            }
        } else {
            swap(origin, destination);
            pos = 0.0;
            if (pilot && pilot->getName() != "Pilot in command") {
                cout << "Pilot " << pilot->getName() << " with certificate number: " << pilot->getCertificateNumber() << " is in control of the plane: " << static_cast<const void*>(this) << endl;
            }
        }
        // Toggle between Pilot A and Pilot B
        if (pilot && pilot->getName() != "Pilot in command") {
            pilot = (pilot == pilot1) ? pilot2 : pilot1;
            cout << "Switching back to " << pilot->getName() << endl;
            setPilot(pilot);
        }
    }
}
    void setPilot(Pilot* p) {
        pilot = p;
        if (p) {
            cout << "Pilot " << p->getName() << " with certificate number: " << p->getCertificateNumber() << " is in control of the plane: " << static_cast<const void*>(this) << endl;
        }
    }
};
int main() {
    Pilot* pilot1;
    Pilot* pilot2;
    Pilot pilotA("Pilot A", "123456789", nullptr);
    Pilot pilotB("Pilot B", "987654321", nullptr);
    pilot1 = &pilotA;
    pilot2 = &pilotB;
    Plane plane("SCE", "PHL");
    pilotA.setPlane(&plane);
    plane.setPilot(&pilotA);
    double speed = 450;
    double timestep = 10;
    int max_iterations = 2000;
    plane.setVel(speed);
    double elapsedTime = 0.0;
    for (int i = 0; i < max_iterations; ++i) {
        plane.operate(timestep, pilot1, pilot2);
        elapsedTime += timestep;
        if (plane.isAtSCE() && plane.getDestination() == "SCE" && plane.getOrigin() != "SCE") {
            if (plane.getOrigin() == "PHL") {
                plane.setPilot(&pilotB);
                cout << "Switching to Pilot B" << endl;
            } else {
                plane.setPilot(&pilotA);
                cout << "Switching to Pilot A" << endl;
            }
        }
        // Check if both pilots have taken their turn
        if (pilot1->getPlane() == nullptr && pilot2->getPlane() == nullptr) {
            cout << "Both pilots have completed their turn." << endl;
            break;
        }
    }
    return 0;
}