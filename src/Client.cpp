#include <boost/asio.hpp>
#include <iostream>
#include "Read-Write.h"

using namespace std;

int main()
{
    io_service io_service;
    ip::tcp::socket client_socket(io_service);

    client_socket.connect(tcp::endpoint(address::from_string("127.0.0.1"),9999));

    cout << "Enter your name: ";
    string u_name, reply, response;

    getline(cin, u_name);

    sendData(client_socket, u_name);


    while(true){

        response = getData(client_socket);
        response.pop_back(); // Remove last character "\n"

        if (response == "exit") {
            cout << "Connection terminated" << endl;
            break;
        }
        cout << "Server: " << response << endl;
        cout << u_name << ": ";
        getline(cin, reply);
        sendData(client_socket, reply);

        if (reply == "exit")
            break;
    }
    return 0;
}