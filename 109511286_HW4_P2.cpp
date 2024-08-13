#include <iostream>
#include <unordered_map>
#include <vector>
#include <queue>
#include <sstream>

using namespace std;

// Define logic gate functions
inline bool INV(bool input) {
    return !input;
}

inline bool NAND(bool input1, bool input2) {
    return !(input1 && input2);
}

inline bool NOR(bool input1, bool input2) {
    return !(input1 || input2);
}

int main() {
    unordered_map<string, bool> wireValues;
    unordered_map<string, vector<string>> connections;
    vector<string> inputWires;
    vector<string> outputWires;
    queue<string> gateInputs; // Queue to hold gates with missing inputs
    
    // Read input wire names and initial logic values
    string wires, wire, values;
    getline(cin, wires);
    getline(cin, values);
    stringstream iss1(wires), iss2(values);
    int value;
    while (iss1 >> wire && iss2 >> value) {
        inputWires.push_back(wire);
        wireValues[wire] = value;
    }

    // Read output wire names
    getline(cin, wires);
    stringstream iss3(wires);
    while (iss3 >> wire) {
        outputWires.push_back(wire);
    }

    // Process gates and their connections
    string gateType, gateName, inWire1, inWire2, outWire;
    while (cin >> gateType) {
        if (gateType == "INV") {
            cin >> gateName >> inWire1 >> outWire;
            if (wireValues.find(inWire1) != wireValues.end()) {
                wireValues[outWire] = INV(wireValues[inWire1]);
                connections[outWire].push_back(gateName);
            } else {
                // If input is missing, push it back to the queue
                gateInputs.push(gateType + " " + gateName + " " + inWire1 + " " + outWire);
            }
        } else if (gateType == "NAND") {
            cin >> gateName >> inWire1 >> inWire2 >> outWire;
            if (wireValues.find(inWire1) != wireValues.end() && wireValues.find(inWire2) != wireValues.end()) {
                wireValues[outWire] = NAND(wireValues[inWire1], wireValues[inWire2]);
                connections[outWire].push_back(gateName);
            } else {
                // If inputs are missing, push it back to the queue
                gateInputs.push(gateType + " " + gateName + " " + inWire1 + " " + inWire2 + " " + outWire);
            }
        } else if (gateType == "NOR") {
            cin >> gateName >> inWire1 >> inWire2 >> outWire;
            if (wireValues.find(inWire1) != wireValues.end() && wireValues.find(inWire2) != wireValues.end()) {
                wireValues[outWire] = NOR(wireValues[inWire1], wireValues[inWire2]);
                connections[outWire].push_back(gateName);
            } else {
                // If inputs are missing, push it back to the queue
                gateInputs.push(gateType + " " + gateName + " " + inWire1 + " " + inWire2 + " " + outWire);
            }
        }
    }

    // Process gates with missing inputs again
    while (!gateInputs.empty()) {
        stringstream ss(gateInputs.front());
        ss >> gateType >> gateName >> inWire1;
        if (gateType == "INV") {
            ss >> outWire;
            if (wireValues.find(inWire1) != wireValues.end()) {
                wireValues[outWire] = INV(wireValues[inWire1]);
                connections[outWire].push_back(gateName);
                gateInputs.pop();
            } else {
                // If input is still missing, put it back to the queue
                gateInputs.push(gateType + " " + gateName + " " + inWire1 + " " + outWire);
                gateInputs.pop();
            }
        } else if (gateType == "NAND") {
            ss >> inWire2 >> outWire;
            if (wireValues.find(inWire1) != wireValues.end() && wireValues.find(inWire2) != wireValues.end()) {
                wireValues[outWire] = NAND(wireValues[inWire1], wireValues[inWire2]);
                connections[outWire].push_back(gateName);
                gateInputs.pop();
            } else {
                // If inputs are still missing, put it back to the queue
                gateInputs.push(gateType + " " + gateName + " " + inWire1 + " " + inWire2 + " " + outWire);
                gateInputs.pop();
            }
        } else if (gateType == "NOR") {
            ss >> inWire2 >> outWire;
            if (wireValues.find(inWire1) != wireValues.end() && wireValues.find(inWire2) != wireValues.end()) {
                wireValues[outWire] = NOR(wireValues[inWire1], wireValues[inWire2]);
                connections[outWire].push_back(gateName);
                gateInputs.pop();
            } else {
                // If inputs are still missing, put it back to the queue
                gateInputs.push(gateType + " " + gateName + " " + inWire1 + " " + inWire2 + " " + outWire);
                gateInputs.pop();
            }
        }
    }

    // Print output wire values
    for (const auto &outWire : outputWires) {
        cout << outWire << " " << wireValues[outWire] << endl;
    }

    return 0;
}