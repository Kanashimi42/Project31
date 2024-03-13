#include "WinSock2.h" 
#include "Socket.h"
#include <thread>
#include <windows.h> // Include Windows.h for MessageBox
Socket::Socket()
{
    // если инициализация сокетов прошла неуспешно, выводим сообщение об ошибке
    if (WSAStartup(MAKEWORD(2, 2), &wsaData) != NO_ERROR)
    {
        MessageBox(NULL, L"Ошибка инициализации сокетов", L"Ошибка", MB_OK | MB_ICONERROR);
        WSACleanup();
        exit(10);
    }

    // создаем потоковый сокет, протокол TCP
    _socket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

    // при неуспешном создании сокета выводим сообщение об ошибке
    if (_socket == INVALID_SOCKET)
    {
        MessageBox(NULL, L"Ошибка создания сокета.", L"Ошибка", MB_OK | MB_ICONERROR);
        WSACleanup();
        exit(11);
    }
}

Socket::~Socket()
{
    WSACleanup(); // очищаем ресурсы
}

bool Socket::SendData(char* buffer)
{
    /*Отправляем сообщение на указанный сокет*/
    send(_socket, buffer, strlen(buffer), 0);
    return true;
}

bool Socket::ReceiveData(char* buffer, int size)
{
    // Получаем сообщение и сохраняем его в буфере
    // Метод является блокирующим!
    int i = recv(_socket, buffer, size, 0);

    if (i == -1)
    {
        // Ошибка при получении данных
        return false;
    }
    else if (i == 0)
    {
        // Соединение закрыто другой стороной
        MessageBox(NULL, L"Соединение закрыто удаленным хостом.", L"Ошибка", MB_OK | MB_ICONERROR);
        return false;
    }

    buffer[i] = '\0'; // Добавляем завершающий символ строки
    return true;
}

void Socket::CloseConnection()
{
    // Закрываем сокет
    closesocket(_socket);
}

void Socket::SendDataMessage()
{
    // Строка для сообщения пользователя
    char message[MAXSTRLEN];
    // Без этого метода из потока будет считан последний
    // ввод пользователя, выполняем сброс.
    cin.ignore();
    cout << "Введите сообщение: ";
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
    MessageBox(NULL, L"Ожидание подключения клиента...", L"Информация", MB_OK | MB_ICONINFORMATION);

    // При ошибке активации сокета в режиме прослушивания
    // выводим ошибку
    if (listen(_socket, 1) == SOCKET_ERROR)
    {
        MessageBox(NULL, L"Ошибка прослушивания\n", L"Ошибка", MB_OK | MB_ICONERROR);
        WSACleanup();
        exit(15);
    }
    /*
    Метод является блокирующим. Ожидаем подключение клиента.
    Как только клиент подключился, функция accept возвращает
    новый сокет, через который происходит обмен данными.
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
    // Указываем семейство адресов IPv4
    addr.sin_family = AF_INET;
    /* Преобразуем адрес "0.0.0.0"в правильную
    структуру хранения адресов, результат сохраняем в поле sin_addr */
    inet_pton(AF_INET, "0.0.0.0", &addr.sin_addr);
    // Указываем порт. 
    // Функция htons выполняет преобразование числа в
    // сетевой порядок байт
    addr.sin_port = htons(port);

    // При неудачном биндинге к порту, выводим сообщение про ошибку
    if (bind(_socket, (SOCKADDR*)&addr, sizeof(addr)) == SOCKET_ERROR)
    {
        MessageBox(NULL, L"Не удалось привязаться к порту\n", L"Ошибка", MB_OK | MB_ICONERROR);
        WSACleanup();
        exit(14);
    }
}

void ClientSocket::ConnectToServer(const char* ipAddress, int port)
{
    addr.sin_family = AF_INET;
    inet_pton(AF_INET, ipAddress, &addr.sin_addr);
    addr.sin_port = htons(port);
    // при неудачном подключении к серверу выводим сообщение про ошибку
    if (connect(_socket, (SOCKADDR*)&addr, sizeof(addr)) == SOCKET_ERROR)
    {
        MessageBox(NULL, L"Не удалось подключиться к серверу\n", L"Ошибка", MB_OK | MB_ICONERROR);
        WSACleanup();
        exit(13);
    }
}
