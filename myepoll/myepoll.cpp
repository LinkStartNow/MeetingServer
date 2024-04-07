#include "myepoll.h"
#include <iostream>

using namespace std;

Myepoll::Myepoll(int size): m_ready(size), m_size(size)
{
    // 初始化节点
    m_node.events = EPOLLIN;

    // 创建树
    m_epfd = epoll_create(size);
}

void Myepoll::AddNode(int fd)
{
    m_node.data.fd = fd;

    epoll_ctl(m_epfd, EPOLL_CTL_ADD, fd, &m_node);
}

void Myepoll::DelNode(int fd)
{
    m_node.data.fd = fd;
    epoll_ctl(m_epfd, EPOLL_CTL_DEL, fd, &m_node);
}

std::vector<epoll_event> *Myepoll::Wait(int& num)
{

    num = epoll_wait(m_epfd, m_ready.data(), m_size, -1);
    if (num <= 0) return nullptr;
    return &m_ready;
}
