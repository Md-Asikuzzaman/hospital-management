#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <windows.h>

using namespace std;

class Hospital {
private:
    string Name, Address, BloodGrp, Age;

public:
    // Constructor
    Hospital() {
        Name = "Empty";
        Address = "Empty";
        BloodGrp = "Empty";
        Age = "Empty";
    }

    Hospital(string name, string address, string bloodGrp, string age) {
        Name = name;
        Address = address;
        BloodGrp = bloodGrp;
        Age = age;
    }

    // Setters
    void setName(string name) { Name = name; }
    void setAddress(string address) { Address = address; }
    void setBloodGrp(string bloodGrp) { BloodGrp = bloodGrp; }
    void setAge(string age) { Age = age; }

    // Getters
    string getName() const { return Name; }
    string getAddress() const { return Address; }
    string getBloodGrp() const { return BloodGrp; }
    string getAge() const { return Age; }
};

// function to read patient data from file
vector<Hospital> readPatientsFromFile() {
    vector<Hospital> patients;
    ifstream fileIn("patients.txt");
    if (!fileIn.is_open()) {
        cout << "File does not exist!";
        return patients;
    }

    string line;
    while (getline(fileIn, line)) {
        stringstream ss(line);
        string name, address, bloodGrp, age;
        getline(ss, name, '|');
        getline(ss, address, '|');
        getline(ss, bloodGrp, '|');
        getline(ss, age);
        patients.push_back(Hospital(name, address, bloodGrp, age));
    }
    fileIn.close();
    return patients;
}




// function to write patient data to file
void writePatientsToFile(const vector<Hospital>& patients) {
    ofstream fileOut("patients.txt");
    if (!fileOut.is_open()) {
        cout << "File does not exist!";
        return;
    }

    for (size_t i = 0; i < patients.size(); ++i) {
    const auto& patient = patients[i];
    fileOut << patient.getName() << "," << patient.getAddress() << "," << patient.getBloodGrp() << "," << patient.getAge() << endl;
}

    fileOut.close();
}





// function to admit a patient
void admitPatient(vector<Hospital>& patients) {
    string name, address, bloodGrp, age;

    cout << "\t Enter Patient Name: ";
    cin.ignore();
    getline(cin, name);

    cout << "\t Enter Patient Address: ";
    getline(cin, address);

    cout << "\t Enter Patient Blood Group: ";
    getline(cin, bloodGrp);

    cout << "\t Enter Patient Age: ";
    getline(cin, age);

    // Create a new patient object and add it to the vector
    Hospital newPatient(name, address, bloodGrp, age);
    patients.push_back(newPatient);

    // Update the file with the modified list of patients
    writePatientsToFile(patients);

    cout << "\t Patient Data Saved Successfully!!!" << endl;
}



// function to discharge a patient
void dischargePatient(vector<Hospital>& patients) {
    if (patients.empty()) {
        cout << "No patients to discharge!" << endl;
        return;
    }

    cout << "\t List of Patients:" << endl;
    for (size_t i = 0; i < patients.size(); ++i) {
        cout << "\t " << i + 1 << ". " << patients[i].getName() << endl;
    }

    int choice;
    cout << "\t Enter the number of the patient to discharge: ";
    cin >> choice;

    if (choice < 1 || choice > static_cast<int>(patients.size())) {
        cout << "\t Invalid choice!" << endl;
        return;
    }

    cout << "\t The Patient " << patients[choice - 1].getName() << ", is Discharged!!!" << endl;

    // Erase the discharged patient from the vector
    patients.erase(patients.begin() + choice - 1);

    // Update the file with the modified list of patients
    writePatientsToFile(patients);
}




int main() {
    bool isExit = false;
    vector<Hospital> patients;

    // Load patients from file
    patients = readPatientsFromFile();

    while (!isExit) {
        system("cls");

        int userVal;
        cout << "\t ~ Hospital Management System ~" << endl;
        cout << "\t ===============================" << endl << endl;

        cout << "\t 1. Admit Patient" << endl;
        cout << "\t 2. Discharge Patient" << endl;
        cout << "\t 3. See All Patients" << endl;
        cout << "\t ====================" << endl << endl;

        cout << "\t Enter your choice: ";
        cin >> userVal;


        int s = 1;

        switch (userVal) {
            case 1:
                system("cls");
                admitPatient(patients);
                Sleep(3000);
                break;
            case 2:
                system("cls");
                dischargePatient(patients);
                Sleep(3000);
                break;
            case 3:
                system("cls");
                // Display all patients
                for (size_t i = 0; i < patients.size(); ++i) {
                    const auto& patient = patients[i];
                    cout << "\t" << i+1 << ". Name: " << patient.getName() << " | Address: " << patient.getAddress()
                         << " | Blood Group: " << patient.getBloodGrp() << endl;
                }
                cout << endl;
                system("pause");
                break;
            default:
                isExit = true;
                break;
        }
    }

    return 0;
}
