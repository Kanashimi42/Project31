#include "WinSock2.h" 
#include "Socket.h"
#include <thread>
#include <windows.h> // Include Windows.h for MessageBox
Socket::Socket()
{
    // ���� ������������� ������� ������ ���������, ������� ��������� �� ������
    if (WSAStartup(MAKEWORD(2, 2), &wsaData) != NO_ERROR)
    {
        MessageBox(NULL, L"������ ������������� �������", L"������", MB_OK | MB_ICONERROR);
        WSACleanup();
        exit(10);
    }

    // ������� ��������� �����, �������� TCP
    _socket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

    // ��� ���������� �������� ������ ������� ��������� �� ������
    if (_socket == INVALID_SOCKET)
    {
        MessageBox(NULL, L"������ �������� ������.", L"������", MB_OK | MB_ICONERROR);
        WSACleanup();
        exit(11);
    }
}

Socket::~Socket()
{
    WSACleanup(); // ������� �������
}

bool Socket::SendData(char* buffer)
{
    /*���������� ��������� �� ��������� �����*/
    send(_socket, buffer, strlen(buffer), 0);
    return true;
}

bool Socket::ReceiveData(char* buffer, int size)
{
    // �������� ��������� � ��������� ��� � ������
    // ����� �������� �����������!
    int i = recv(_socket, buffer, size, 0);

    if (i == -1)
    {
        // ������ ��� ��������� ������
        return false;
    }
    else if (i == 0)
    {
        // ���������� ������� ������ ��������
        MessageBox(NULL, L"���������� ������� ��������� ������.", L"������", MB_OK | MB_ICONERROR);
        return false;
    }

    buffer[i] = '\0'; // ��������� ����������� ������ ������
    return true;
}

void Socket::CloseConnection()
{
    // ��������� �����
    closesocket(_socket);
}

void Socket::SendDataMessage()
{
    // ������ ��� ��������� ������������
    char message[MAXSTRLEN];
    // ��� ����� ������ �� ������ ����� ������ ���������
    // ���� ������������, ��������� �����.
    cin.ignore();
    cout << "������� ���������: ";
    cin.get(message, MAXSTRLEN);
    SendData(message);
}

void ServerSocket::StartHosting(int port)
{
    Bind(port);
    std::thread listenThread(&ServerSocket::Listen, this);

    listenThread.detach();
}

void ServerSocket::Listen()
{
    MessageBox(NULL, L"�������� ����������� �������...", L"����������", MB_OK | MB_ICONINFORMATION);

    // ��� ������ ��������� ������ � ������ �������������
    // ������� ������
    if (listen(_socket, 1) == SOCKET_ERROR)
    {
        MessageBox(NULL, L"������ �������������\n", L"������", MB_OK | MB_ICONERROR);
        WSACleanup();
        exit(15);
    }
    /*
    ����� �������� �����������. ������� ����������� �������.
    ��� ������ ������ �����������, ������� accept ����������
    ����� �����, ����� ������� ���������� ����� �������.
    */
    acceptSocket = SOCKET_ERROR;
    while (acceptSocket == SOCKET_ERROR)
    {
        acceptSocket = accept(_socket, NULL, NULL);
    }
    _socket = acceptSocket;
}

void ServerSocket::Bind(int port)
{
    // ��������� ��������� ������� IPv4
    addr.sin_family = AF_INET;
    /* ����������� ����� "0.0.0.0"� ����������
    ��������� �������� �������, ��������� ��������� � ���� sin_addr */
    inet_pton(AF_INET, "0.0.0.0", &addr.sin_addr);
    // ��������� ����. 
    // ������� htons ��������� �������������� ����� �
    // ������� ������� ����
    addr.sin_port = htons(port);

    // ��� ��������� �������� � �����, ������� ��������� ��� ������
    if (bind(_socket, (SOCKADDR*)&addr, sizeof(addr)) == SOCKET_ERROR)
    {
        MessageBox(NULL, L"�� ������� ����������� � �����\n", L"������", MB_OK | MB_ICONERROR);
        WSACleanup();
        exit(14);
    }
}

void ClientSocket::ConnectToServer(const char* ipAddress, int port)
{
    addr.sin_family = AF_INET;
    inet_pton(AF_INET, ipAddress, &addr.sin_addr);
    addr.sin_port = htons(port);
    // ��� ��������� ����������� � ������� ������� ��������� ��� ������
    if (connect(_socket, (SOCKADDR*)&addr, sizeof(addr)) == SOCKET_ERROR)
    {
        MessageBox(NULL, L"�� ������� ������������ � �������\n", L"������", MB_OK | MB_ICONERROR);
        WSACleanup();
        exit(13);
    }
}
