#include "data_struct.h"
#include <sstream>

DataStruct::DataStruct() : field0(0), field1(0) {}

int DataStruct::read_field(int index) const {
    if (index == 0) {
        std::lock_guard<std::mutex> lock(mtx0);
        return field0;
    }
    else {
        std::lock_guard<std::mutex> lock(mtx1);
        return field1;
    }
}

void DataStruct::write_field(int index, int value) {
    if (index == 0) {
        std::lock_guard<std::mutex> lock(mtx0);
        field0 = value;
    }
    else {
        std::lock_guard<std::mutex> lock(mtx1);
        field1 = value;
    }
}

std::string DataStruct::to_string() const {
    std::lock_guard<std::mutex> lock0(mtx0);
    std::lock_guard<std::mutex> lock1(mtx1);
    std::ostringstream out;
    out << "Field0=" << field0 << ", Field1=" << field1;
    return out.str();
}
