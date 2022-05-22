#include <windows.h>
#include <tlhelp32.h>
#include <wbemprov.h>
#include <iphlpapi.h>
#include <icmpapi.h>
#include <lm.h>


VOID EmptyRecycleBin() 
{
    SHEmptyRecycleBinA(0, 0, SHERB_NOCONFIRMATION | SHERB_NOPROGRESSUI | SHERB_NOSOUND);
}

int main()
{
    EmptyRecycleBin();
}
