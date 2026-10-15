
#include <iostream>
#include <string>
#include <winsock2.h>
#include <ws2tcpip.h>
using namespace std;

#pragma comment(lib, "ws2_32.lib")

int main() {
    WSADATA wsa;
    WSAStartup(MAKEWORD(2, 2), &wsa);

    SOCKET s = socket(AF_INET, SOCK_DGRAM, 0);

    sockaddr_in server_addr{};
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(5003);
    server_addr.sin_addr.s_addr = htonl(INADDR_LOOPBACK);

    string str1;

    cout << "Enter string: ";
    getline(cin, str1);

    sendto(
        s, str1.c_str(), static_cast<int>(str1.size()), 0,
        (sockaddr*)&server_addr, sizeof(server_addr)
    );

    char buffer[1024] = {};
    sockaddr_in from_addr{};
    int from_len = sizeof(from_addr);

    int bytes = recvfrom(
        s, buffer, sizeof(buffer) - 1, 0,
        (sockaddr*)&from_addr, &from_len
    );

    if (bytes > 0) {
        cout << "Result: " << string(buffer, bytes) << endl;
    }

    closesocket(s);
    WSACleanup();

    return 0;
}
