#pragma once

#include "Mysock.h"

class Tcpsock: public Mysock
{
	bool m_NotListen = true;
public:
    Tcpsock(const char* ip, const int port): Mysock(ip, port) {}

	Tcpsock(int sockfd): Mysock(sockfd) {}

    Tcpsock(const Tcpsock& sock): Mysock(sock.m_sock) {}

    bool Write(const char* buf, int size);

    char* Read(int& len);

	bool Listen(int len = 128);

	int Accept();
};
