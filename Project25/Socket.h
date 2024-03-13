
#pragma once
#include "header.h"
using namespace std;

const int MAXSTRLEN = 1000;

class Socket
{
protected:
	WSADATA wsaData;//��������� ��� �������� ���������� � ������������� �������
	SOCKET _socket; //���������� ���������� ������
	SOCKET acceptSocket;//���������� ������, ������� ������ � �������� 
	sockaddr_in addr; //��������� ����� � ����
public:
	Socket();
	~Socket();
	bool SendData(char*); //����� ��� �������� ������ � ����
	bool ReceiveData(char*, int);//����� ��� ��������� ������
	void CloseConnection(); //����� ��� �������� ����������
	void SendDataMessage();//����� ��� �������� ��������� ������������
};

class ServerSocket : public Socket
{
public:
	void Listen(); //����� ��� ��������� "����������" ������
	void Bind(int port); //����� ��� �������� ������ � �����
	void StartHosting(int port); //���������� ����� ���� ���������� �������
};

class ClientSocket : public Socket
{
public:
	//����� ��� ����������� � �������
	void ConnectToServer(const char* ip, int port);
};











