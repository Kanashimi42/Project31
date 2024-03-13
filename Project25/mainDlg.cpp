#include "mainDlg.h"
#include <tchar.h>
#include "Socket.h"

#include <thread>
mainDlg* mainDlg::ptr = NULL;
WSADATA WSAData;
int wmId;
int port = 24242; char receiveMessage[MAXSTRLEN];
char sendMessage[MAXSTRLEN];
HWND hList1;
ServerSocket server;
mainDlg::mainDlg(void)
{
	ptr = this;
}

mainDlg::~mainDlg(void)
{
}

BOOL mainDlg::DlgProc(HWND hwnd, UINT mes, WPARAM wp, LPARAM lp)
{
	switch (mes)
	{
	case WM_INITDIALOG:
		ptr->Cls_OnInitDialog(hwnd, (HWND)wp, lp);
	case WM_COMMAND:
	{
		wmId = LOWORD(wp);
		switch (wmId)
		{
		case IDC_BUTTON1:
		{

			hList1 = GetDlgItem(hwnd, IDC_LIST1);
			DWORD dwStyle = GetWindowLong(hList1, GWL_STYLE);
			dwStyle &= ~LBS_SORT; // Remove LBS_SORT style
			SetWindowLong(hList1, GWL_STYLE, dwStyle);


			/*SendMessage(hList1, LB_ADDSTRING, 0, LPARAM(_T("Starting server\\ \n")));
			UpdateWindow(hList1);
			Sleep(500);
			SendMessage(hList1, LB_RESETCONTENT, 0, 0);

			SendMessage(hList1, LB_ADDSTRING, 0, LPARAM(_T("Starting server\| \n")));
			UpdateWindow(hList1);
			Sleep(500);
			SendMessage(hList1, LB_RESETCONTENT, 0, 0);

			SendMessage(hList1, LB_ADDSTRING, 0, LPARAM(_T("Starting server\/ \n")));
			UpdateWindow(hList1);
			Sleep(500);
			SendMessage(hList1, LB_RESETCONTENT, 0, 0);

			SendMessage(hList1, LB_ADDSTRING, 0, LPARAM(_T("Starting server\-- \n")));
			UpdateWindow(hList1);
			Sleep(500);
			SendMessage(hList1, LB_RESETCONTENT, 0, 0);

			SendMessage(hList1, LB_ADDSTRING, 0, LPARAM(_T("Welcome! \n")));
			UpdateWindow(hList1);
			SendMessage(hList1, LB_ADDSTRING, 0, LPARAM(_T("10⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢀⡀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀\n")));
			Sleep(500);
			UpdateWindow(hList1);
			SendMessage(hList1, LB_ADDSTRING, 0, LPARAM(_T("11⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢀⣾⣿⠿⣷⣦⣀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀\n")));

			Sleep(100);
			UpdateWindow(hList1);
			SendMessage(hList1, LB_ADDSTRING, 0, LPARAM(_T("12⠀⠀⠀⠀⠀⠀⠀⠀⢀⣤⣶⣤⣤⣴⣿⠟⠁⠀⠈⠛⠿⣿⣿⣶⣶⣄⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀\n")));
			Sleep(100);
			UpdateWindow(hList1);
			SendMessage(hList1, LB_ADDSTRING, 0, LPARAM(_T("13⠀⢀⣴⣶⣇⠀⢀⣴⣿⠟⠉⠉⠙⠛⠁⠀⠀⠀⠀⠀⠀⠀⠈⠉⠻⣿⣆⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀\n")));
			Sleep(100);
			UpdateWindow(hList1);
			SendMessage(hList1, LB_ADDSTRING, 0, LPARAM(_T("14⢀⣿⡟⠙⢿⣿⣿⠟⠁⠀⠀⠀⠀⠀⠀⠀⣀⡀⠀⠀⠀⠀⠀⠀⠀⠘⣿⣷⣄⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀\n")));
			Sleep(100);
			UpdateWindow(hList1);
			SendMessage(hList1, LB_ADDSTRING, 0, LPARAM(_T("15⠸⣿⡇⠀⠀⠀⠀⠀⢀⡴⠶⢦⣄⣀⣤⠾⠛⠛⣧⡀⠀⠀⠀⠀⠀⠀⠈⠛⢿⣿⣄⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀\n")));
			Sleep(100);
			UpdateWindow(hList1);
			SendMessage(hList1, LB_ADDSTRING, 0, LPARAM(_T("16⢠⣿⣇⠀⠀⠀⠀⣴⠋⠀⠀⠀⠈⠉⠁⠀⠀⠀⠈⠻⣦⣤⡤⠶⠻⢿⣦⠀⠀⢻⣿⣆⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀\n")));
			Sleep(100);
			UpdateWindow(hList1);
			SendMessage(hList1, LB_ADDSTRING, 0, LPARAM(_T("17⢸⣿⠉⢳⣶⢶⡿⠇⠀⠀⠀⠀⠀⠀⠀⠀⠀⣀⡀⠀⠀⠀⠀⠀⠀⠀⣿⠁⠀⠀⣿⣿⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀\n")));
			Sleep(100);
			UpdateWindow(hList1);
			SendMessage(hList1, LB_ADDSTRING, 0, LPARAM(_T("18⠘⣿⣄⡾⠁⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠈⠙⠄⠀⠀⠀⠀⢠⡼⠋⠀⠀⠀⣿⣿⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀\n")));
			Sleep(100);
			UpdateWindow(hList1);
			SendMessage(hList1, LB_ADDSTRING, 0, LPARAM(_T("20⠀⢹⡿⠁⠀⢀⣾⡇⠀⠀⠀⠀⠀⠀⠀⠀⣀⣀⡀⠀⠀⠀⠀⠀⠠⣝⢦⡀⠀⠀⣿⣿⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀\n")));
			Sleep(100);
			UpdateWindow(hList1);
			SendMessage(hList1, LB_ADDSTRING, 0, LPARAM(_T("21⢀⣿⠇⠀⠀⠘⣿⠇⠀⠀⢀⠎⠀⠀⠀⠘⠛⠛⠿⠆⠀⠀⠀⠀⠠⣝⢧⡳⡄⣸⣿⡟⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀\n")));
			Sleep(100);
			UpdateWindow(hList1);
			SendMessage(hList1, LB_ADDSTRING, 0, LPARAM(_T("22⢸⣿⠀⠀⠀⠀⠀⠀⢠⡾⠃⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢢⣜⢷⣽⣷⣿⣿⠃⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀\n")));
			Sleep(100);
			UpdateWindow(hList1);
			SendMessage(hList1, LB_ADDSTRING, 0, LPARAM(_T("23⢸⡏⠀⠀⠀⠀⠀⠀⢿⣇⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠙⠆⣹⣿⣿⠃⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀\n")));
			Sleep(100);
			UpdateWindow(hList1);
			SendMessage(hList1, LB_ADDSTRING, 0, LPARAM(_T("24⢸⣇⠀⠀⠀⠀⠀⠀⠈⠛⠂⠀⠀⠀⠀⢠⣄⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠘⣿⣷⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀\n")));
			Sleep(100);
			UpdateWindow(hList1);
			SendMessage(hList1, LB_ADDSTRING, 0, LPARAM(_T("25⢸⣿⠀⠀⣾⣤⣀⣀⣀⢀⣀⣀⣀⡤⠔⠚⢿⣷⠀⠀⠀⠀⠀⠀⠀⠀⠀⢀⣿⣿⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀\n")));
			Sleep(100);
			UpdateWindow(hList1);
			SendMessage(hList1, LB_ADDSTRING, 0, LPARAM(_T("26⠀⣿⣇⠀⠻⠳⢤⣈⣉⠉⠉⠀⣀⣀⣤⠖⠋⠟⠀⠀⠀⠀⠀⠀⢀⣀⣠⣾⣿⠃⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀\n")));
			Sleep(100);
			UpdateWindow(hList1);
			SendMessage(hList1, LB_ADDSTRING, 0, LPARAM(_T("27⠀⠘⣿⣆⠀⠀⠀⠈⠙⣛⣛⠛⠛⠉⠀⠀⠀⠀⠀⠀⠀⠀⢀⣴⣿⠿⠛⠋⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀\n")));
			Sleep(100);
			UpdateWindow(hList1);
			SendMessage(hList1, LB_ADDSTRING, 0, LPARAM(_T("28⠀⠀⠘⢿⣧⡀⠀⠀⠈⠛⠛⠃⠀⠀⠀⠀⠀⠀⠀⠀⢀⣴⣿⡿⠃⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀\n")));
			Sleep(100);
			UpdateWindow(hList1);
			SendMessage(hList1, LB_ADDSTRING, 0, LPARAM(_T("29⠀⠀⠀⠈⠻⣿⣦⣄⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⣀⣴⣿⡿⠋⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀\n")));
			Sleep(100);
			UpdateWindow(hList1);
			SendMessage(hList1, LB_ADDSTRING, 0, LPARAM(_T("30⠀⠀⠀⠀⠀⠈⠙⠿⣿⣶⣦⣤⣤⣤⣤⣶⣶⣿⠿⠛⠁⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀\n")));
			Sleep(100);
			UpdateWindow(hList1);
			SendMessage(hList1, LB_ADDSTRING, 0, LPARAM(_T("31⠀⠀⠀⠀⠀⠀⠀⠀⠀⠈⠉⠉⠉⠉⠉⠉⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀\n")));
			UpdateWindow(hList1); */

			std::thread hostingThread(&ServerSocket::StartHosting, &server, port);
			hostingThread.detach();
			//std::thread processThread(&mainDlg::ProcessClientRequests, ptr, hList1); // Create thread
	
			//processThread.detach(); // Detach the thread
			break;
		}
		}
		break;
	}
	case WM_CLOSE:
		EndDialog(hwnd, 0);
		break;
	default:
		return FALSE;
	}
	return TRUE;
}

BOOL mainDlg::Cls_OnInitDialog(HWND hwnd, HWND hwndFocus, LPARAM lParam)
{
	        string ipAddress; // Адрес сервера

	SendMessage(hList1, LB_ADDSTRING, 0, LPARAM(_T("Connecting\n")));

	cout << "Enter an IP address: " << endl;
	// Запрашиваем IP сервера
	cin >> ipAddress;
	if (ipAddress == "localhost")
	{
	  ipAddress = "";
	  char hostname[1024];
	  memset(hostname, 0, sizeof(hostname));
	  struct hostent* hostEntry;
	  if (WSAStartup(MAKEWORD(2, 2), &WSAData) != 0)
	  {
	    MessageBox(NULL, TEXT("WSAStartup failed!"), TEXT("Error"), MB_OK);
	    return FALSE;
	  }
	  gethostname(hostname, 1024);
	  hostEntry = gethostbyname(hostname);
	  char* localIP = inet_ntoa(*((struct in_addr*)hostEntry->h_addr_list[0]));
	  WSACleanup();
	  ipAddress = string(localIP);
	  cout << ipAddress << endl;
	}
	ClientSocket client;
	// Подключаемся к серверу
	client.ConnectToServer(ipAddress.c_str(), port);
	while (true)
	{
	  // Отправляем сообщение
	  client.SendDataMessage();
	  cout << "\tWaiting" << endl;
	  // Получаем ответ
	  client.ReceiveData(receiveMessage, MAXSTRLEN);
	  cout << "Received: " << receiveMessage << endl;
	  if (strcmp(receiveMessage, "end") == 0 || strcmp(sendMessage, "end") == 0)
	    break;
	}
	// Закрываем соединение
	client.CloseConnection();

	return 0;
}

void mainDlg::Cls_OnClose(HWND hwnd)
{
}

void mainDlg::Cls_OnCommand(HWND hwnd, int id, HWND hwndCtl, UINT codeNotify)
{
}

void mainDlg::ProcessClientRequests(HWND hList1) {
	const int MAXSTRLEN = 256; // Adjust the maximum string length as needed
	char receiveMessage[MAXSTRLEN];
	char sendMessage[MAXSTRLEN];

	while (true) {
		SendMessage(hList1, LB_ADDSTRING, 0, LPARAM(_T("Waiting... \n")));

		// Receive data from the client
		server.ReceiveData(receiveMessage, MAXSTRLEN);
		SendMessage(hList1, LB_ADDSTRING, 0, LPARAM(_T("Received... \n")));

		// Send data to the client
		server.SendDataMessage();

		// If the message is "end", break the loop
		if (strcmp(receiveMessage, "end") == 0 || strcmp(sendMessage, "end") == 0)
			break;
	}
}
