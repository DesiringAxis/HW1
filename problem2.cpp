#include <iostream>
#include <map>
#include <string>
using namespace std;
int main () {
    map<string, map<string, int>> flights;
    flights["SCE"]["PHL"] = 160;
    flights["SCE"]["ORD"] = 640;
    flights["SCE"]["EWR"] = 220;
    return 0;
}