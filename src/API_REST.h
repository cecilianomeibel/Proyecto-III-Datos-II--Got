#include <iostream>
#include "DataBaseConnection.h"

using namespace std;

vector<string> divideInput(string input){
    std::vector<std::string> result;
    std::istringstream isstream(input);
    std::string word;

    while(std::getline(isstream, word, ' ')){
        result.push_back(word);
    }
    return result;
}

/*
 * function that holds the logic of "got help" command
 */
string GotHELP(){

    string message;
    message = "Los comandos válidos son: \n"
              "got init <name>:\n"
              "Instancia un nuevo repositorio en el servidor y lo identifica con el nombre indicado por <name>\n"
              "\n"
              "got add [-A] [name]:\n"
              "Permite agregar todos los archivos que no estén registrados o que tengan nuevos cambios al\n"
              "repositorio. El usuario puede usar el flag -A para agregar todos los archivos relevantes\n"
              "\n"
              "got commit <mensaje>:\n"
              "Envía los archivos agregados y pendientes de commit al server.\n"
              "\n"
              "got status <file>:\n"
              "Este comando nos va a mostrar cuales archivos han sido cambiados, agregados o eliminados\n"
              "de acuerdo al commit anterior.\n"
              "\n"
              "got rollback <file> <commit>:\n"
              "Permite regresar un archivo en el tiempo a un commit específico\n"
              "\n"
              "got reset <file>:\n"
              "Deshace cambios locales para un archivo y lo regresa al último commit.\n"
              "\n"
              "got sync <file>:\n"
              "Recupera los cambios para un archivo en el server y lo sincroniza con el archivo en el cliente"
            ;
    return message;
}

/*
 * function that holds the logic of "got init <name>" command
 */
string GotInit(string input){
    string RepoName;
    // divide de client's request into separated words
    if (!input.empty()) {
        vector<string> result = divideInput(input);
        RepoName = result[2]; //obtain the repository name
    }
    string command = "DROP TABLE IF EXISTS " + RepoName;
    string command2 = "CREATE TABLE " + RepoName + "(def CHAR(100))";
    if ((DataBaseConn(command) & DataBaseConn(command2)) == 0){
        string message = "Se ha iniciado correctamente el repositorio: " + RepoName;
        return message;
    }else{
        string message = "Hubo un error al crear el repositorio, intente de nuevo";
        return message;
    }
}

string GotAdd(string input){
    string path, name;

    if (!input.empty()) {
        std::vector<std::string> result = divideInput(input);
        path = result[2];
        name = result[3];
    }
    string command = "LOAD DATA LOCAL INFILE '" + path + "' INTO TABLE " + name;
    if (DataBaseConn(command) == 0){
        string message = "Se ha añadido correctamente el archivo: " + path + " al repositorio: " + name;
        return message;
    }else{
        string message = "Hubo un error al añadir el archivo, intente de nuevo o pida ayuda con el comando 'got help'";
        return message;
    }

}