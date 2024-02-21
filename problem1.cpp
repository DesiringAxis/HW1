#include <iostream>
#include <vector>
#include <iomanip>
using namespace std;
int main() {
    // Initialize Variables
    int front_occupants, rear_occupants, gallons_of_fuel;
    double empty_weight, empty_weight_moment, front_moment_arm, rear_moment_arm, fuel_weight_per_gallon, fuel_tank_moment_arm, baggage_weight, baggage_moment_arm;
    vector<double> front_occupant_weights, rear_occupant_weights;
    // Ask user to enter information
    cout << "Enter airplane empty weight (pounds): ";
    cin >> empty_weight;
    cout << "Enter airplane empty-weight moment (pounds-inches): ";
    cin >> empty_weight_moment;
    cout << "Enter the number of front seat occupants: ";
    cin >> front_occupants;
    for (int i = 0; i < front_occupants; ++i) {
        double weight;
        cout << "Enter weight of front seat occupant " << i + 1 << " (pounds): ";
        cin >> weight;
        front_occupant_weights.push_back(weight);
    }
    cout << "Enter front seat moment arm (inches): ";
    cin >> front_moment_arm;
    cout << "Enter the number of rear seat occupants: ";
    cin >> rear_occupants;
    for (int i = 0; i < rear_occupants; ++i) {
        double weight;
        cout << "Enter weight of rear seat occupant " << i + 1 << " (pounds): ";
        cin >> weight;
        rear_occupant_weights.push_back(weight);
    }   
    cout << "Enter rear seat moment arm (inches): ";
    cin >> rear_moment_arm;
    cout << "Enter the number of gallons of usable fuel: ";
    cin >> gallons_of_fuel;
    cout << "Enter usable fuel weight per gallon (pounds): ";
    cin >> fuel_weight_per_gallon;
    cout << "Enter fuel tank moment arm (inches): ";
    cin >> fuel_tank_moment_arm;
    cout << "Enter baggage weight (pounds): ";
    cin >> baggage_weight;
    cout << "Enter baggage moment arm (inches): ";
    cin >> baggage_moment_arm;
    // Calculations
    double total_weight = empty_weight;
    double total_moment = empty_weight_moment;
    for (double weight : front_occupant_weights) {
        total_weight += weight;
        total_moment += weight * front_moment_arm;
    }
    for (double weight : rear_occupant_weights) {
        total_weight += weight;
        total_moment += weight * rear_moment_arm;
    }
    total_weight += gallons_of_fuel * fuel_weight_per_gallon + baggage_weight;
    total_moment += gallons_of_fuel * fuel_weight_per_gallon * fuel_tank_moment_arm + baggage_weight * baggage_moment_arm;
    // Design Limit
    if (total_weight <= 2950 && total_moment >= 82.1 && total_moment <= 84.7) {
        cout << "The aircraft is within design limits.\n";
    }
    else {
        cout << "The aircraft exceeds design limits.\n";
        // Fuel adjustment if needed
        double max_weight = 2950;
        double max_cg = total_moment > 84.7 ? 84.7 : total_moment < 82.1 ? 82.1 : total_moment;
        double deficit_weight = total_weight > max_weight ? total_weight - max_weight : 0;
        double required_fuel_adjustment = deficit_weight / fuel_weight_per_gallon;
        if (total_weight > max_weight) {
            gallons_of_fuel -= required_fuel_adjustment;
        }
        else {
            gallons_of_fuel += required_fuel_adjustment;
        }
        // Recalculate
        total_weight = empty_weight;
        total_moment = empty_weight_moment;
        for (double weight : front_occupant_weights) {
            total_weight += weight;
            total_moment += weight * front_moment_arm;
        }
        for (double weight : rear_occupant_weights) {
            total_weight += weight;
            total_moment += weight * rear_moment_arm;
        }
        total_weight += gallons_of_fuel * fuel_weight_per_gallon + baggage_weight;
        total_moment += gallons_of_fuel * fuel_weight_per_gallon * fuel_tank_moment_arm + baggage_weight * baggage_moment_arm;
        cout << "New gross weight: " << total_weight << " lbs\n";
        cout << "New CG location: " << total_moment / total_weight << " inches\n";
        cout << "Fuel adjustment: ";
        if (required_fuel_adjustment > 0)
            cout << "+" << fixed << setprecision(2) << required_fuel_adjustment << " gallons\n";
        else
            cout << fixed << setprecision(2) << required_fuel_adjustment << " gallons\n";
    }
    return 0;
}