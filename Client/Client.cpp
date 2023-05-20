// Client.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#pragma comment(lib, "ws2_32.lib") //необходимо подключить для любого приложения,
#include <WinSock2.h> //которое работает с сокетами в Windows
#include <iostream>

#pragma warning(disable: 4996)

SOCKET Connection;

void ClientHandler(int Index) {
    char Messagge[128];
    while (true) {
        recv(Connection, Messagge, sizeof(Messagge), NULL);
        std::cout << Messagge << std::endl;
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

    Connection = socket(AF_INET, SOCK_STREAM, NULL);
    if (connect(Connection, (SOCKADDR*)&addr, sizeof(addr)) != 0) {
        std::cout << "error\n";
        return 1;
    }
    std::cout << "Connected\n";
    CreateThread(NULL, NULL, (LPTHREAD_START_ROUTINE)ClientHandler, NULL, NULL, NULL);
    char Messagge1[128];
    while (true) {
        std::cin.getline(Messagge1, sizeof(Messagge1));
        send(Connection, Messagge1, sizeof(Messagge1), NULL);
        Sleep(10);
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
