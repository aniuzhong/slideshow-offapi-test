#ifndef OFFICEPROBER_H
#define OFFICEPROBER_H

#include <string>

class OfficeProber
{
public:
    OfficeProber();

    int64_t getSOfficeBinPid();
    void    killSOfficeBin();

private:
    int64_t getProcessPid(const std::string&);
};

#endif // OFFICEPROBER_H
