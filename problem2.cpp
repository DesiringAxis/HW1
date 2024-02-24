#include <iostream>
#include <map>
#include <string>
using namespace std;
int main () {
    map<string, map<string, int>> flights;
    // Store info
    flights["SCE"]["PHL"] = 160;
    flights["SCE"]["ORD"] = 640;
    flights["SCE"]["EWR"] = 220;
    // Print info
    cout << "Distance between SCE and PHL: " << flights["SCE"]["PHL"] << " miles" << endl;
    cout << "Distance between SCE and ORD: " << flights["SCE"]["ORD"] << " miles" << endl;
    cout << "Distance between SCE and EWR: " << flights["SCE"]["EWR"] << " miles" << endl;
    return 0;
}