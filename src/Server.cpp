#include <boost/asio.hpp>
#include <iostream>
#include "Read-Write.h"
#include "API_REST.h"

using namespace std;


int main(int argc, char* argv[])
{
    string name;
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

    /*
     * main loop of the server
     */
    while (true) {
        response = getData(server_socket);
        response.pop_back(); // Remove last character "%"

        /*
         * Function that verify if the client wants to exit
         */

        if (response == "exit") {
            cout << u_name << " left!" << endl;
            break;

        /*
         * Function "got help"
         */
        }else if (response == "got help"){
            cout << u_name << ": " << response << endl;
            sendData(server_socket, GotHELP());

        /*
         * Function "got init <name>"
         */
        }else if(response.find("init") == 4) {
            cout << u_name << ": " << response << endl;
            //eliminate the string "got init" to obtain the name of the repository
            if (!response.empty()) {
                name = response.substr(9, response.size() - 1);
            }
            if(GotInit(name) == 0){
                sendData(server_socket, "Se ha iniciado correctamente el repositorio: " + name);
            }else{
                sendData(server_socket, "Hubo un error al crear el repositorio, intente de nuevo");
            }

        }else if(response.find("add") == 4){
            cout << u_name << ": " << response << endl;
            std::string path;
            //eliminate the string "got add" to obtain the name of the repository
            if (!response.empty()) {
                path = response.substr(8, response.size() - 1);
            }
            if(GotAdd(path, name) == 0){
                sendData(server_socket, "Se ha subido correctamente el archivo: " + path + " en el repositorio: " + name);
            }else{
                sendData(server_socket, "Hubo un error al subirse el archivo, intente de nuevo");
            }
        }
        /*
         * in case that the client enter an invalid command, return a message
         */
        else{
            cout << u_name << ": " << response << endl;
            sendData(server_socket, "Por favor, ingrese un comando válido, para más información digite el comando: got help");
        }

    }
    return 0;
}