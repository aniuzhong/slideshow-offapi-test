#include <windows.h>
#include <TlHelp32.h>

#include <map>
#include <string>
#include "officeprober.h"

OfficeProber::OfficeProber()
{
}

int64_t OfficeProber::getSOfficePID()
{
    std::map<std::string, int64_t> mapNamePID;

    PROCESSENTRY32 aEntry;
    aEntry.dwSize = sizeof(aEntry);

    HANDLE hProcessSnap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
    if (hProcessSnap == INVALID_HANDLE_VALUE)
    {
        printf("Create Toolhelp32Snapshot Error\n");
        return 0;
    }

    BOOL bResult = Process32First(hProcessSnap, &aEntry);

    while (bResult)
    {
        std::string sExeName = aEntry.szExeFile;
        int64_t ullPid = aEntry.th32ProcessID;
        mapNamePID.insert({sExeName, ullPid});
        bResult = Process32Next(hProcessSnap, &aEntry);
    }

    for (const auto& prNamePID : mapNamePID)
        if (prNamePID.first == "soffice.bin")
            return prNamePID.second;

    return 0;
}
