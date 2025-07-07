#include <iostrem>
#include "TCPServer.h"

TCPServer tcp;
void *loop(void *m)
{
    pthread_detach(pthread_self());
    while(1)
    {
        srand(time(NULL));
        char ch = 'a' + rand() % 26;
        string s(1, ch);
        string str = tcp.getMessage();
        if (str!= "") 
        {
            cout << "Сообщение: " << str << endl;
            tcp.Send("[Сообщение клиента: "+str+"]" + s);
            tcp.clean();
        }
        usleep(1000);
    }
    tcp.detach();
}
int main()
{
    setlocate(LC_ALL, "Russian");
    pthread_t msg;
    tcp.setup(11999);
    if (pthread_create(&msg, NULL, loop, (void *)0) == 0) 
    {
        tcp.receive();
    }
    return 0;
}