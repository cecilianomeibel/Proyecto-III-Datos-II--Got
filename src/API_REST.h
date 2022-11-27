#include <iostream>
#include "DataBaseConnection.h"

using namespace std;

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
int GotInit(string name){
    string command = "DROP TABLE IF EXISTS " + name;
    string command2 = "CREATE TABLE " + name + "(def CHAR(100))";
    DataBaseConn(command);
    DataBaseConn(command2);
    return 0;
}

int GotAdd(string path, string name){
    string command = "LOAD DATA LOCAL INFILE '" + path + "' INTO TABLE " + name;
    DataBaseConn(command);
    return 0;
}