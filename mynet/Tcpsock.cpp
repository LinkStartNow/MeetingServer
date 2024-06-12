#include "Tcpsock.h"
#include <iostream>
#include <string.h>

using namespace std;


bool Tcpsock::Write(const char* buf, int size)
{
    char* sz = (char*)&size;
    int num = 0;
    int max = sizeof(size);
    while (num < max) {
        int t;
        if ((t = send(m_sock, sz + num, max - num, 0)) == -1) {
            perror("send size failed");
            return false;
        }
        num += t;
    }

    num = 0;
    max = size;

    while (num < max) {
        int t;
        if ((t = send(m_sock, buf + num, max - num, 0)) == -1) {
            perror("send size failed");
            return false;
        }
        num += t;
    }
	
//	if (send(m_sock, buf, size, 0) == -1) {
//		perror("send buf failed");
//		return false;
//	}

	return true;
}

char* Tcpsock::Read(int& len)
{
//	int t;
    int num = 0;
    int max = sizeof(int);
    char sz[max];

    while (num < max) {
        int t;
        if ((t = recv(m_sock, sz + num, max - num, 0)) == -1) {
            perror("send size failed");
            return nullptr;
        }
        if (!t) {
            cout << "发送端已经退出，结束通信" << endl;
            return nullptr;
        }
        num += t;
    }

//    if ((t = recv(m_sock, (char*)&num, sizeof(int), 0)) == -1) {
//		perror("read size failed");
//        return nullptr;
//	}

//    if (!t) {
//		cout << "发送端已经退出，结束通信" << endl;
//        return nullptr;
//	}

    num = *(int*)(sz);
    len = num;

    cout << "size:" << num << endl;

    char* buf = new char[num];
    max = num;
    num = 0;

    while (num < max) {
        int t;
        if ((t = recv(m_sock, buf + num, max - num, 0)) == -1) {
            perror("send size failed");
            return nullptr;
        }
        num += t;
    }
	
//	if (recv(m_sock, buf, num, 0) == -1) {
//		perror("read buf failed");
//        return nullptr;
//	}
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
