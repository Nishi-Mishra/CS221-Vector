#include "executable.h"
#include "datum_utils.h"
#include <sstream>
#include <fstream>
using namespace std; 

TEST(datum_read_data) {
    Typegen t;
    for(int i = 0; i < 100; i++) {
        std::vector<DatumGT> gt_data = generate_file_data(t);
    
        std::stringstream ss;
        ss << gt_data;
        // std::ifstream file("../covid-weekly-fall2021.csv"); // DEBUG 
        Vector<Datum> data = readData(ss);

        //cout << data.size() << " = size " << endl;
        ASSERT_EQ(gt_data.size(), data.size());
        
        // cout << gt_data[0].datum.negative << ", " << data[0].negative << endl;
        // cout << gt_data[1].datum.negative << ", " << data[1].negative << endl;
        // cout << gt_data[2].datum.negative << ", " << data[2].negative << endl;
        // for(size_t j = 0; j < gt_data.size(); j++) {
        //     cout << gt_data[j].negative << ", " << data[j].negative << endl;
        // }
        
        for(size_t i = 0; i < gt_data.size(); i++) {
            Datum const & datum = data[i];
            Datum const & gt_datum = gt_data[i].datum;

            ASSERT_TRUE(gt_datum.week == datum.week);
            ASSERT_EQ(gt_datum.negative,   datum.negative);
            ASSERT_EQ(gt_datum.positive,   datum.positive);
            ASSERT_EQ(gt_datum.total,      datum.total);
            ASSERT_NEAR(gt_datum.positivity, datum.positivity, 1e-2);
        }
    }
}
