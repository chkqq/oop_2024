#include <iostream>
#include <string>
#include <regex>
#include <Windows.h>

using namespace std;

enum class Protocol
{
    HTTP,
    HTTPS,
    FTP
};

void SetLocale()
{
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
}

int GetDefaultPort(Protocol protocol) 
{
    switch (protocol) 
    {
    case Protocol::HTTP:
        return 80;
    case Protocol::HTTPS:
        return 443;
    case Protocol::FTP:
        return 21;
    default:
        return -1; 
    }
}


bool ParseURL(const string& url, Protocol& protocol, int& port, string& host, string& document)
{
    regex url_regex("^([a-zA-Z]+)://([^:/]+)(?::([0-9]+))?(/.*)?$");
    smatch url_match;

    if (regex_match(url, url_match, url_regex)) 
    {
        string protocol_str = url_match[1].str();
        string host_str = url_match[2].str();
        string port_str = url_match[3].str();
        string document_str = url_match[4].str();

        if (protocol_str == "http") 
        {
            protocol = Protocol::HTTP;
        }
        else if (protocol_str == "https") 
        {
            protocol = Protocol::HTTPS;
        }
        else if (protocol_str == "ftp") 
        {
            protocol = Protocol::FTP;
        }
        else {
            return false;
        }

        if (!port_str.empty()) 
        {
            port = stoi(port_str);
        }
        else 
        {
            port = GetDefaultPort(protocol);
        }

        host = host_str;
        document = document_str.empty() ? "/" : document_str;

        return true;
    }

    return false;
}

void PrintURLInfo(const std::string& url, Protocol protocol, int port, const std::string& host, const std::string& document) 
{
    cout << "Исходный URL" << endl;
    cout << url << endl;
    cout << "HOST: " << host << endl;
    cout << "PORT: " << port << endl;
    cout << "DOC: " << document << endl;
}

int main(int argc, char* argv[]) 
{
    SetLocale();

    if (argc < 2) {
        cerr << "Usage: " << argv[0] << " <URL>" << endl;
        return 1;
    }

    for (int i = 1; i < argc; ++i) 
    {
        string url = argv[i];
        Protocol protocol;
        int port;
        string host, document;

        if (ParseURL(url, protocol, port, host, document))
        {
            PrintURLInfo(url, protocol, port, host, document);
        }
        else 
        {
            cerr << "Invalid URL: " << url << endl;
        }
    }

    return 0;
}