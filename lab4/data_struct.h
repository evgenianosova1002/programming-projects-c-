#ifndef DATA_STRUCT_H
#define DATA_STRUCT_H

#include <mutex>
#include <string>

class DataStruct {
private:
    int field0;
    int field1;
    mutable std::mutex mtx0;
    mutable std::mutex mtx1;

public:
    DataStruct();

    int read_field(int index) const;
    void write_field(int index, int value);

    std::string to_string() const;
};

#endif


