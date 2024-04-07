#pragma once

#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include <unistd.h>

class Mysock
{
protected:
	int m_sock = -1;

public:
	Mysock() = default;

	Mysock(int sock): m_sock(sock) {}

	Mysock(const char* ip, const int port);

	~Mysock();

	int Open(const char* ip = "", const int port = 0);

    void Close();

    int GetSock();
};
