#include <cmath>
#include <fstream>
#include <sstream>
#include <string>

#include "Datum.h"


[[nodiscard]] Vector<Datum> readData(std::istream& file) {

    bool debug = false; 

    if (debug) cout << endl << endl << "HERE " << endl; 
    

    std::string temp; 
    getline(file, temp); 
    if (debug) cout << "Throw away" << temp << endl;

    Vector<Datum> data;     
    std::string sentence; 
    std::string temp_neg; 
    std::string temp_pos;
    std::string temp_tot;  
    std::string temp_plus;  
    // if (file.eof()) {
    //     cout << "Empty file" << endl; 
    // }

    while (std::getline(file, sentence)) {

        Datum d;
        std::istringstream str(sentence);

        std::getline(str, d.week, ','); 
        // if (debug) cout << "week: " << d.week << endl; 
        
        std::getline(str, temp_neg, ','); 
        d.negative = std::stoul(temp_neg); 
        // if (debug) cout << temp_neg << " , " << "negative: " << d.negative << endl; 
        
        std::getline(str, temp_pos, ','); 
        d.positive = stoul(temp_pos); 
        // if (debug) cout << "positive: " << d.positive << endl; 
        
        std::getline(str, temp_tot, ','); 
        d.total = stoul(temp_tot);
        // if (debug) cout << "total: " << d.total << endl; 

        std::getline(str,temp_plus); 
        temp_plus = temp_plus.substr(0, temp_plus.length()-1); 
        d.positivity = stof(temp_plus); 
        // if (debug) cout << "Percent: " <<  d.positivity << endl; 
        
        data.push_back(d); 
    }


    if (debug) cout << endl << endl << "END" << endl; 

    return data; 
}

// You may want to write this function, but you do not have to
[[nodiscard]] bool isBadDataEntry(const Datum& datum) {
    // Description: Return a Vector containing only the entries whose total does not match the computed total 
    // whose positivity does not match the computed positivity to within 0.1.

    if (datum.compute_total() != datum.total) {
        return true; 
    }
    else if (((datum.positivity-0.1) < (datum.compute_positivity()*100)) && ((datum.positivity+0.1) > (datum.compute_positivity() * 100)) ) {
        return false; 
    }
    else {
        return true; 
    }
}


[[nodiscard]] Vector<Datum> badDataEntries(const Vector<Datum>& data) noexcept{
    
    Vector<Datum> bad_entries; 

    for (size_t i = 0; i < data.size(); i++) {
        if (isBadDataEntry(data[i])) {
            bad_entries.push_back(data[i]); 
        }
    }

    return bad_entries; 

}



[[nodiscard]] unsigned int Datum::compute_total() const noexcept {
    return this->positive + this->negative; 
}

[[nodiscard]] float Datum::compute_positivity() const noexcept {
    return (float)(this->positive) / this->compute_total(); // * 100; 
}

/*

std::string week;
    unsigned int negative;
    unsigned int positive;
    unsigned int total;
    float positivity;

*/

std::ostream& operator<<(std::ostream& out, const Datum& datum) {
    out << "--- Datum --- \n" << "Week: " << datum.week << endl 
    << "Negative: " << datum.negative << endl << "Positive: " << datum.positive << endl
    << "Total: " << datum.total << endl << "Positivity: " << datum.positivity << endl;  

    return out; 
}

std::istream& operator>>(std::istream& in, Datum& datum) {
    
    std::string temp_neg; 
    std::string temp_pos;
    std::string temp_tot;  
    std::string temp_plus;  

    std::getline(in, datum.week, ','); 
    // if (debug) cout << "week: " << d.week << endl; 
    
    std::getline(in, temp_neg, ','); 
    datum.negative = std::stoul(temp_neg); 
    // if (debug) cout << temp_neg << " , " << "negative: " << d.negative << endl; 
    
    std::getline(in, temp_pos, ','); 
    datum.positive = stoul(temp_pos); 
    // if (debug) cout << "positive: " << d.positive << endl; 
    
    std::getline(in, temp_tot, ','); 
    datum.total = stoul(temp_tot);
    // if (debug) cout << "total: " << d.total << endl; 

    std::getline(in,temp_plus); 
    temp_plus = temp_plus.substr(0, temp_plus.length()-1); 
    datum.positivity = stof(temp_plus); 
    // if (debug) cout << "Percent: " <<  d.positivity << endl; 

    return in; 
}

[[nodiscard]] bool goodData(const Vector<Datum>& data) noexcept {
    return badDataEntries(data).empty(); 
}

