#include <iostream>
#include <vector>
#include <string>
#include "../include/alert_module.h"

using namespace std;

void sendAlert(const string &guardianName, const string &guardianContact, int currentLocation, int safeLocation, const vector<string> &locationNames)
{
    cout << "[MODULE 5] Alert and Notification Module\n";
    cout << "Sending alert...\n\n";

    cout << "----- ALERT MESSAGE -----\n";
    cout << "To: " << guardianName << " (" << guardianContact << ")\n";
    cout << "Emergency Alert! User may be in danger.\n";
    cout << "Current Location: " << locationNames[currentLocation] << endl;
    cout << "Nearest Safe Location: " << locationNames[safeLocation] << endl;
    cout << "Please respond immediately.\n";
    cout << "-------------------------\n\n";
}