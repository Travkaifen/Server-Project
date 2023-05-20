// Server.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//
#pragma comment(lib, "ws2_32.lib") //необходимо подключить для любого приложения,
#include <WinSock2.h> //которое работает с сокетами в Windows
#include <iostream>

#pragma warning(disable: 4996)
SOCKET Connections[100];
int Count = 0;

void ClientHandler(int Index) {
    char Messagge[128];
    while (true) {
        recv(Connections[Index], Messagge, sizeof(Messagge), NULL);
        for (int i = 0; i < Count; i++) {
            if (i == Index) continue;
            send(Connections[i], Messagge, sizeof(Messagge), NULL);
        }
    }
}
int main(int argc, char* argv[])
{
    //WSAStartup
    WSAData wsaData;
    WORD DLLVersion = MAKEWORD(2, 1);
    if (WSAStartup(DLLVersion, &wsaData) != 0) // вызов функции необходим для инциализации библиотеки ws2_32.dll
    {
        std::cout << "Error" << std::endl;
        exit(1);
    }
    SOCKADDR_IN addr; //объявлении структуры и ниже инциализация полей
    int sizeofaddr = sizeof(addr);
    addr.sin_addr.s_addr = inet_addr("127.0.0.1"); //IP адрес
    addr.sin_port = htons(1111); //номер порта
    addr.sin_family = AF_INET;

    SOCKET slisten = socket(AF_INET, SOCK_STREAM, NULL); //Создаем сокет
    bind(slisten, (SOCKADDR*)&addr, sizeof(addr)); //Связывает адрес с сокетом
    listen(slisten, SOMAXCONN); //Пытаемся начать слушать сокет
    for (int i = 0; i < 100; i++) {
        SOCKET newConnection; //Ждем клиента
        newConnection = accept(slisten, (SOCKADDR*)&addr, &sizeofaddr); //разрешает входящее соединение, если сокет находиться в режиме прослушивания

        if (newConnection == 0)
        {
            std::cout << "Error #2\n";
        }
        else
        {
            std::cout << "Client Connected!\n";
            char Messagge[128] = "Hello";
            send(newConnection, Messagge, sizeof(Messagge), NULL);
            Connections[Count] = newConnection;
            Count++;
            CreateThread(NULL, NULL, (LPTHREAD_START_ROUTINE)ClientHandler, (LPVOID)(i), NULL, NULL);
        }
    }
    system("pause");
    return 0;
}

// Запуск программы: CTRL+F5 или меню "Отладка" > "Запуск без отладки"
// Отладка программы: F5 или меню "Отладка" > "Запустить отладку"

// Советы по началу работы 
//   1. В окне обозревателя решений можно добавлять файлы и управлять ими.
//   2. В окне Team Explorer можно подключиться к системе управления версиями.
//   3. В окне "Выходные данные" можно просматривать выходные данные сборки и другие сообщения.
//   4. В окне "Список ошибок" можно просматривать ошибки.
//   5. Последовательно выберите пункты меню "Проект" > "Добавить новый элемент", чтобы создать файлы кода, или "Проект" > "Добавить существующий элемент", чтобы добавить в проект существующие файлы кода.
//   6. Чтобы снова открыть этот проект позже, выберите пункты меню "Файл" > "Открыть" > "Проект" и выберите SLN-файл.
