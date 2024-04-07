#include "Mysock.h"
#include <iostream>

using namespace std;

Mysock::Mysock(const char* ip, const int port)
{
	Open(ip, port);
}

Mysock::~Mysock()
{
}

int Mysock::Open(const char* ip, const int port)
{
	m_sock = socket(AF_INET, SOCK_STREAM, 0);

	if (m_sock == -1) {
		perror("sock failed");
        exit(-1);
	}
	else cout << "sock success" << endl;

	if (port) {
		sockaddr_in addr;
		addr.sin_family = AF_INET;
		addr.sin_port = htons(port);
        addr.sin_addr.s_addr = INADDR_ANY;

		if (bind(m_sock, (sockaddr*)&addr, sizeof(addr)) == -1) {
			perror("bind failed");
            exit(-1);
		}
		else cout << "bind success" << endl;
	}


    return m_sock;
}

void Mysock::Close()
{
    if (m_sock != -1) {
        close(m_sock);
        m_sock = -1;
    }
}

int Mysock::GetSock()
{
    return m_sock;
}
