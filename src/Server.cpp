#include <boost/asio.hpp>
#include <iostream>
#include "Read-Write.h"
#include "API_REST.h"

using namespace std;

int main(int argc, char* argv[])
{
    vector<string> files;
    string RepoName;
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
            sendData(server_socket, GotInit(response));
        /*
         * Function "got add [-A] <filepath> <repository name>"
         */
        }else if(response.find("add") == 4){
            cout << u_name << ": " << response << endl;
            files = GotAdd(response);
            for (int i=0; i<files.size(); i++){
                cout<<"Elemento "<<to_string(i)<< ":"<< files[i] <<"\n";
            }
            RepoName = files[0];
            files.erase(files.begin());
            sendData(server_socket, "Se han subido los archivos correctamente, su estado es 'pendiente de commit'");
        /*
         * Function "got commit <message>"
         */
        }else if(response.find("commit") == 4){
            cout << u_name << ": " << response << endl;
            sendData(server_socket, GotCommit(RepoName, files));

        }else{
            cout << u_name << ": " << response << endl;
            sendData(server_socket, "Por favor, ingrese un comando válido, para más información digite el comando 'got help'");
        }

    }
    return 0;
}