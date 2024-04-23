#ifndef OFFICEPROBER_H
#define OFFICEPROBER_H

#include <stdint.h>

class OfficeProber
{
public:
    OfficeProber();

    int64_t getSOfficeBinPID();
    void    killSOfficeBin();
};

#endif // OFFICEPROBER_H
