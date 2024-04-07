#ifndef MYEPOLL_H
#define MYEPOLL_H

#include <vector>
#include <sys/epoll.h>
#include <functional>

class Myepoll
{
    epoll_event m_node;
    int m_epfd;
    std::vector<epoll_event> m_ready;
    int m_size;

public:
    Myepoll(int size = 10);

    void AddNode(int fd);

    void DelNode(int fd);

    std::vector<epoll_event>* Wait(int& num);
};

#endif // MYEPOLL_H
