
#include "WinSock2.h" 
#include <Windows.h>
#include "mainDlg.h"

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
    mainDlg dlg;
    return DialogBox(hInstance, MAKEINTRESOURCE(IDD_DIALOG1), NULL, (DLGPROC)mainDlg::DlgProc);
}
