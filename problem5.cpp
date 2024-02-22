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
        cout << "Plane Created with a tail number " << this << endl;
    }
    ~Plane() {
        cout << "Plane Destroyed" << endl;
    }
    double getPos() const { return pos; }
    double getVel() const { return vel; }
    double getDistance() const { return distance; }
    bool isAtSCE() const { return at_SCE; }
    string getOrigin() const { return origin; }
    string getDestination() const { return destination; }
    void setVel(double velocity) { vel = velocity; }
    void operate(double dt) {
        double distanceCovered = vel * dt / 3600;
        if (pos < distance) {
            pos += distanceCovered;
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
int main() {
    string origin, destination;
    cout << "Enter origin airport: ";
    cin >> origin;
    cout << "Enter destination airport: ";
    cin >> destination;
    Plane plane(origin, destination);
    double speed;
    cout << "Enter flight speed (between 400-500 mph): ";
    cin >> speed;
    plane.setVel(speed);
    double timestep;
    cout << "Enter timestep (between 10-100 seconds): ";
    cin >> timestep;
    int max_iterations;
    cout << "Enter maximum number of iterations (between 1000-2000): ";
    cin >> max_iterations;
    double elapsedTime = 0.0;
    for (int i = 0; i < max_iterations; ++i) {
        plane.operate(timestep);
        elapsedTime += timestep;
        cout << "Time elapsed: " << elapsedTime << " seconds, Current position: " << plane.getPos() << " miles" << endl;
        if (plane.isAtSCE()) {
            cout << "At SCE" << endl;
        }
    }
    return 0;
}