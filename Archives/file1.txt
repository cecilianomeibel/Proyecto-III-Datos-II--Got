#include <iostream>
#include <boost/asio.hpp>

using namespace boost::asio;
using namespace boost::asio::ip;
using namespace std;

// Driver program for receiving data from buffer
string getData(tcp::socket& socket){
    boost::asio::streambuf buf;
    read_until(socket, buf, "%");
    string data = buffer_cast<const char*>(buf.data());
    return data;
}

// Driver program to send data
void sendData(tcp::socket& socket, const string& message)
{
    write(socket,buffer(message + "%"));
}