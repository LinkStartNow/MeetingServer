#include "Tcpsock.h"
#include <iostream>
#include <string.h>

using namespace std;


bool Tcpsock::Write(const char* buf, int size)
{
	if (send(m_sock, (char*)&size, sizeof(int), 0) == -1) {
		perror("send size failed");
		return false;
	}
	
	if (send(m_sock, buf, size, 0) == -1) {
		perror("send buf failed");
		return false;
	}

	return true;
}

char* Tcpsock::Read()
{
	int t;
    int num;
    if ((t = recv(m_sock, (char*)&num, sizeof(int), 0)) == -1) {
		perror("read size failed");
        return nullptr;
	}

    if (!t) {
		cout << "发送端已经退出，结束通信" << endl;
        return nullptr;
	}

    cout << "num:" << num << endl;

    char* buf = new char[num];
	
	if (recv(m_sock, buf, num, 0) == -1) {
		perror("read buf failed");
        return nullptr;
	}
    return buf;
}

bool Tcpsock::Listen(int len)
{
	if (listen(m_sock, len) == -1) {
		perror("listen failed");
		return false;
	}
	cout << "listen success" << endl;
	m_NotListen = false;
	return true;
}

int Tcpsock::Accept()
{
    cout << __func__ << endl;
	if (m_NotListen) Listen();
    sockaddr_in addr;
    socklen_t len = 1;
	int sock = accept(m_sock, (sockaddr*)&addr, &len);
	
	if (sock == -1) {
		perror("accept failed");
		return -1;
	}

	char cip[16];
	inet_ntop(AF_INET, &addr.sin_addr.s_addr, cip, 16);
	cout << "accept ip:" << cip << endl;

	return sock;
}
