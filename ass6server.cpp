
#include <iostream>
#include <string>
#include <algorithm>
#include <cctype>
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

    bind(s, (sockaddr*)&server_addr, sizeof(server_addr));

    cout << "Server started" << endl;

    char buffer[1024] = {};
    sockaddr_in client_addr{};
    int client_len = sizeof(client_addr);

    int bytes = recvfrom(
        s, buffer, sizeof(buffer) - 1, 0,
        (sockaddr*)&client_addr, &client_len
    );

    if (bytes > 0) {
        string str1(buffer, bytes);

        cout << "Received: " << str1 << endl;

        int choice;
        cout << "Enter choice (1-Lowercase, 2-Reverse): ";
        cin >> choice;

        string result;

        if (choice == 1) {
            result = str1;

            transform(result.begin(), result.end(),
                      result.begin(),
                      [](unsigned char c) {
                          return static_cast<char>(tolower(c));
                      });
        }
        else {
            result = str1;
            reverse(result.begin(), result.end());
        }

        sendto(
            s, result.c_str(), static_cast<int>(result.size()), 0,
            (sockaddr*)&client_addr, client_len
        );
    }

    closesocket(s);
    WSACleanup();

    return 0;
}
