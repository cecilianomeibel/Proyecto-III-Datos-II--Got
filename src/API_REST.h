#include <iostream>
#include "DataBaseConnection.h"
#include <vector>

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
    string command1 = "DROP TABLE IF EXISTS " + RepoName;
    string command2 = "DROP TABLE IF EXISTS " + RepoName + "Changes";
    string command3 = "CREATE TABLE " + RepoName + "(deflt CHAR(100))";
    string command4 = "CREATE TABLE " + RepoName + "Changes(deflt CHAR(100))";
    if ((DataBaseConn(command1) & DataBaseConn(command2) & DataBaseConn(command3) & DataBaseConn(command4)) == 0){
        string message = "Se ha iniciado correctamente el repositorio: " + RepoName;
        return message;
    }else{
        string message = "Hubo un error al crear el repositorio, intente de nuevo";
        return message;
    }
}

/*
 * function that holds the logic of "got add [-A] <filepath> <repository name>" command
 */
vector<string> GotAdd(string input){
    vector<string> information;
    if(input.find("-A") == 8){
        std::vector<std::string> result = divideInput(input);

        string RepoName = result[result.size()-1];
        information.push_back(RepoName);

        for(int i=0; i<3; i++){
            result.erase(result.begin());
        }
        result.erase(result.end());
        for (int i=0; i<result.size(); i++){
            information.push_back(result[i]);
        }
    }else{
        std::vector<std::string> result = divideInput(input);
        information.push_back(result[2]);
        information.push_back(result[3]);
    }

    return information;
}

string GotCommit(string RepoName, vector<string> files){
    vector<string> columns;
    string status;

    for(int i=0; i<files.size(); i++){
        string colunmName = files[i];
        for(int j=0; j<4;j++){ //this for loop only removes the ".txt" extension
            colunmName.pop_back();
        }
        columns.push_back(colunmName);
    }

    for(int i=0; i<files.size(); i++){

        string path;
        path = "/home/albert/CLionProjects/Proyecto_III/Archives/" + files[i];

        string command1 = "ALTER TABLE " + RepoName + " ADD " + columns[i]  + " CHAR(100)"; //create a new column with the name of the file
        string command2 = "LOAD DATA LOCAL INFILE '" + path + "' INTO TABLE " + RepoName + "(" + columns[i] + ")"; //store the content of the file in the column

        if ((DataBaseConn(command1) & DataBaseConn(command2)) == 0){
            status = "Se han añadido correctamente los archivos al repositorio: " + RepoName;
        }else{
            status = "Hubo un error al añadir el archivo, intente de nuevo o pida ayuda con el comando 'got help'";
        }
    }

    return status;

}