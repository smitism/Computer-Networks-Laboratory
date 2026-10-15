
#include <iostream>
#include <string>
#include <sstream>
#include <winsock2.h>
#include <ws2tcpip.h>
using namespace std;
#include <cmath>
#pragma comment(lib, "ws2_32.lib")

int main() {
    WSADATA wsa;
    WSAStartup(MAKEWORD(2, 2), &wsa);

    SOCKET server_socket = socket(AF_INET, SOCK_STREAM, 0);

    sockaddr_in server_addr{};
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(5001);
    server_addr.sin_addr.s_addr = htonl(INADDR_LOOPBACK);

    bind(server_socket, (sockaddr*)&server_addr, sizeof(server_addr));
    listen(server_socket, 1);

    cout << "Server is listening on port 5001..." << endl;

    SOCKET conn = accept(server_socket, nullptr, nullptr);
    cout << "Client connected." << endl;

    char buffer[1024] = {};
    int bytes = recv(conn, buffer, sizeof(buffer) - 1, 0);

    if (bytes <= 0) {
        closesocket(conn);
        closesocket(server_socket);
        WSACleanup();
        return 0;
    }

    string mode(buffer, bytes);

    if (mode == "MATH") {
        cout << "Client selected Mathematical Operations mode." << endl;

        while (true) {
            char data[1024] = {};
            int received = recv(conn, data, sizeof(data) - 1, 0);

            if (received <= 0)
                break;

            string request(data, received);

            if (request == "EXIT")
                break;

            stringstream ss(request);
            string op;
            double n1, n2;

            getline(ss, op, ',');
            ss >> n1;
            ss.ignore(1, ',');
            ss >> n2;

            double result = 0;
            string response;

            if (op == "1")
                result = n1 + n2;
            else if (op == "2")
                result = n1 - n2;
            else if (op == "3")
                result = n1 * n2;
            else if (op == "4") {
                if (n2 == 0) {
                    response = "Error: Division by zero";
                } else {
                    result = n1 / n2;
                }
            } else if (op == "5") {
                result = pow(n1, n2);
            }

            if (response.empty()) {
                response = to_string(result);
            }

            send(conn, response.c_str(),
                 static_cast<int>(response.size()), 0);
        }
    }
    else if (mode == "CHAT") {
        cout << "Client selected Chatbot mode." << endl;

        string questions[] = {
            "What is your name?",
            "What is your college?",
            "What is your degree?"
        };

        string answers[3];

        for (int i = 0; i < 3; i++) {
            send(conn, questions[i].c_str(),
                 static_cast<int>(questions[i].size()), 0);

            char data[1024] = {};
            int received = recv(conn, data, sizeof(data) - 1, 0);

            if (received <= 0) {
                closesocket(conn);
                closesocket(server_socket);
                WSACleanup();
                return 0;
            }

            answers[i] = string(data, received);
        }

        string final_msg =
            "Here are your combined inputs -> Name: " + answers[0] +
            ", College: " + answers[1] +
            ", Degree: " + answers[2] + "\nquit";

        send(conn, final_msg.c_str(),
             static_cast<int>(final_msg.size()), 0);
    }

    closesocket(conn);
    closesocket(server_socket);
    WSACleanup();

    return 0;
}
