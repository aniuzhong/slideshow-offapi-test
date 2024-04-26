#include <windows.h>
#include <TlHelp32.h>

#include <map>
#include <string>
#include "officeprober.h"

OfficeProber::OfficeProber()
{
}

int64_t OfficeProber::getSOfficeBinPid()
{
    return getProcessPid("soffice.bin");
}

void OfficeProber::killSOfficeBin()
{
    int64_t ullPID = getSOfficeBinPid();
    if (ullPID == 0)
        return;

    HANDLE hProcess = NULL;
    hProcess = OpenProcess(PROCESS_TERMINATE, FALSE, ullPID);
    if (hProcess == NULL)
    {
        printf("Failed Open Process: %lu\n", GetLastError());
        return;
    }
    if(TerminateProcess(hProcess,0) == 0)
    {
        printf("Failed to TerminateProcess: %lu", GetLastError());
        return;
    }
}

int64_t OfficeProber::getProcessPid(const std::string& sProcessName)
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

    for (const auto& pairNamePID : mapNamePID)
        if (pairNamePID.first == sProcessName)
            return pairNamePID.second;

    return 0;
}

