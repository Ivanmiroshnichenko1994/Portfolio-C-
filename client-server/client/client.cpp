#include <iostream>
#include <signal.h>
#include "TCPClient.h"


using namespace std;

TCPClient tcp;              //Наш основной класс

// обработчик выхода из программы
void sig_exit(int s)
{
    tcp.exit();
    exit(0);
}


int main(int args, char *argv[])
{
    setlocale(LC_ALL, "Russian")

    // Установка обработчика выхода из программы
    signal(SIGINT, sig_exit);
    tcp.setup("127.0.0.1",11999);
    while(1)
    {
        // Инициализация генератора случайных чисел
        srand(time(NULL));

        // Отправляем строку на сервер
        tcp.Send(to_string(rand()%25000));
        
        //Получаем ответ сервера
        string rec = tcp.receive();
        if( rec != "" )
        {
            // Выводим ответ сервера
            cout << "Сообщение сервера: " << rec <<endl;
        }
        sleep(1);               // Пропускаем секунду
    }
    return 0;
}