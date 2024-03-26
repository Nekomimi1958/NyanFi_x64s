//----------------------------------------------------------------------//
// ShExe																//
//																		//
//----------------------------------------------------------------------//
#include <tchar.h>
#include <windows.h>
//---------------------------------------------------------------------------
int WINAPI _tWinMain(HINSTANCE, HINSTANCE, LPTSTR lpCmdLine, int)
{
	if (lstrlen(lpCmdLine)==0) return 0;

	return (ShellExecute(NULL, _T("open"), lpCmdLine, NULL, NULL, SW_SHOWNORMAL) <= (HINSTANCE)32)? 1 : 0;
}
//---------------------------------------------------------------------------
