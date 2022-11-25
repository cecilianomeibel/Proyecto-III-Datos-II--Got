#include <boost/asio.hpp>
#include <iostream>
#include "Read-Write.h"
#include "API_REST.h"

using namespace std;


int main(int argc, char* argv[])
{
    io_service io_service;

    tcp::acceptor acceptor_server(io_service,tcp::endpoint(tcp::v4(), 9999));
    tcp::socket server_socket(io_service);  // Creating socket object
    acceptor_server.accept(server_socket); // waiting for connection

    string u_name = getData(server_socket); // Reading username
    u_name.pop_back(); // Remove last character "\n"

    string response, reply;
    reply = "Hello " + u_name + "!";
    cout << "Server: " << reply << endl;
    sendData(server_socket, reply);

    while (true) {
        response = getData(server_socket);
        response.pop_back(); // Remove last character "\n"

        if (response == "exit") {
            cout << u_name << " left!" << endl;
            break;
        }else if (response == "got help"){
            cout << u_name << ": " << response << endl;
            sendData(server_socket, GotHELP());
        }else{
            cout << u_name << ": " << response << endl;
            sendData(server_socket, "Por favor, ingrese un comando válido, para más información digite el comando: got help");
        }

    }
    return 0;
}