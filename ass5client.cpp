
#include <iostream>
#include <string>
#include <winsock2.h>
#include <ws2tcpip.h>
using namespace std;

#pragma comment(lib, "ws2_32.lib")

int main() {
    WSADATA wsa;
    WSAStartup(MAKEWORD(2, 2), &wsa);

    SOCKET client_socket = socket(AF_INET, SOCK_STREAM, 0);

    sockaddr_in server_addr{};
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(5001);
    server_addr.sin_addr.s_addr = htonl(INADDR_LOOPBACK);

    if (connect(client_socket, (sockaddr*)&server_addr,
                sizeof(server_addr)) == SOCKET_ERROR) {
        cout << "Connection failed." << endl;
        closesocket(client_socket);
        WSACleanup();
        return 1;
    }

    cout << "Select Mode:" << endl;
    cout << "1. Mathematical Operations" << endl;
    cout << "2. Chatbot Application" << endl;

    string choice;
    cout << "Enter your choice (1 or 2): ";
    getline(cin, choice);

    if (choice == "1") {
        string mode = "MATH";
        send(client_socket, mode.c_str(),
             static_cast<int>(mode.size()), 0);

        while (true) {
            cout << "\n--- Math Menu ---" << endl;
            cout << "1. Addition" << endl;
            cout << "2. Subtraction" << endl;
            cout << "3. Multiplication" << endl;
            cout << "4. Division" << endl;
            cout << "5. Power" << endl;
            cout << "6. Exit" << endl;

            string op;
            cout << "Choose operation (1-6): ";
            getline(cin, op);

            if (op == "6") {
                string exit_msg = "EXIT";
                send(client_socket, exit_msg.c_str(),
                     static_cast<int>(exit_msg.size()), 0);
                break;
            }

            if (op < "1" || op > "5") {
                cout << "Invalid choice." << endl;
                continue;
            }

            string n1, n2;

            cout << "Enter first number: ";
            getline(cin, n1);

            cout << "Enter second number: ";
            getline(cin, n2);

            string request = op + "," + n1 + "," + n2;

            send(client_socket, request.c_str(),
                 static_cast<int>(request.size()), 0);

            char buffer[1024] = {};
            int received = recv(client_socket, buffer,
                                sizeof(buffer) - 1, 0);

            if (received <= 0)
                break;

            cout << "\nResult from server: "
                 << string(buffer, received) << endl;
        }
    }
    else if (choice == "2") {
        string mode = "CHAT";
        send(client_socket, mode.c_str(),
             static_cast<int>(mode.size()), 0);

        cout << "\nChatbot started." << endl;

        while (true) {
            char buffer[1024] = {};
            int received = recv(client_socket, buffer,
                                sizeof(buffer) - 1, 0);

            if (received <= 0)
                break;

            string reply(buffer, received);

            if (reply.find("quit") != string::npos) {
                size_t pos = reply.find("\nquit");

                if (pos != string::npos)
                    reply.erase(pos);

                cout << "\nChatbot: " << reply << endl;
                break;
            }

            cout << "Chatbot: " << reply << endl;

            string msg;
            cout << "You: ";
            getline(cin, msg);

            send(client_socket, msg.c_str(),
                 static_cast<int>(msg.size()), 0);
        }
    }

    closesocket(client_socket);
    WSACleanup();

    return 0;
}
