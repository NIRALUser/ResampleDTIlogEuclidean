#include "itkTestMainExtended.h"

#ifdef WIN32
#define MODULE_IMPORT// __declspec(dllimport) // "dllimport" -> Dll = Dynamic library on windows -> if ResampleDTIlogEuclidean is static, just set MODULE_IMPORT to nothing: Fails to link (linkage error) if dllimport because library is static and tries to link as dynamic
#else
#define MODULE_IMPORT
#endif

extern "C" MODULE_IMPORT int ModuleEntryPoint(int, char * []);

void RegisterTests()
{
  StringToTestFunctionMap["ModuleEntryPoint"] = ModuleEntryPoint;
}
