#include "Datum.h"
#include "Vector.h"
#include <fstream>
#include <iostream> 
using std::cout;
using std::endl; 

int main() {


    Vector<Datum> data;
    std::string filepath;

    std::ifstream file("../covid-weekly-fall2021.csv");

    if(!file.is_open()) {
        std::cerr << "Could not open the file " << filepath << std::endl;
        return 1;
    }
    cout << "Read data" << endl;
    try {
        data = readData(file);
    } catch (const std::exception& e) {
        std::cerr << e.what() << std::endl;
        std::cerr << "It appears that the file could not be read." << std::endl;
        return 1;
    }


    cout << "Hey there! Testing" << endl; 

    Vector <int> vec{}; 
    //Vector::iterator it{vec.getArr()}; 

    vec.push_back(1);
    vec.push_back(5);
    vec.push_back(10);
    vec.insert(vec.begin(), 500);

    for (size_t i = 0; i < vec.size(); i++)
        cout << "In for loop" << vec.at(i) << endl; 

    int A [3] = {5, 3, 8};

    cout << "A  " << *A << endl; // 5 
    //cout << "*A++  " << *(A++) << endl; // pointer to 3, prints 5 bc dereferences old pointer
    return 1;


}


int main2() {
    Vector<Datum> data;
    std::string filepath;
    std::cout << "Enter Path to COVID-19 Data File: ";
    std::cin >> filepath;

    std::ifstream file(filepath.c_str());

    if(!file.is_open()) {
        std::cerr << "Could not open the file " << filepath << std::endl;
        return 1;
    }
    cout << "Read data" << endl;
    try {
        //data = readData(file);
    } catch (const std::exception& e) {
        std::cerr << e.what() << std::endl;
        std::cerr << "It appears that the file could not be read." << std::endl;
        return 1;
    }

    // bool dataIsGood = goodData(data);
    // std::cout << "Data Audit for '" << filepath << '\''
    //         << "\n\tNumber of Entries: " << data.size()
    //         << "\n\tAll Entries Are Good?: " << std::boolalpha << dataIsGood
    //         << (dataIsGood ? "" : "\n\tListing Bad Entries:");
    // if (!dataIsGood) {
    //     for (auto& entry : badDataEntries(data)) {
    //         std::cout << "\n\t\t" << entry;
    //     }
    // }
    return 0;
}
