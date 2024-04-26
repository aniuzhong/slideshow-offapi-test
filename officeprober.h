#ifndef OFFICEPROBER_H
#define OFFICEPROBER_H

#include <string>

class OfficeProber
{
public:
    OfficeProber();

    int64_t getSOfficeBinPid();
    void    killSOfficeBin();
    int64_t getSOfficeExePid();

private:
    int64_t getProcessPid(const std::string&);
};

#endif // OFFICEPROBER_H
