﻿#include <iostream>
#include <string>
#include <sstream>
#include "TVSet.h"

using namespace std;

void displayMenu()
{
    cout << "=== TV Control Menu ===\n"
        << "1. turn_on\n"
        << "2. turn_off\n"
        << "3. select_channel <channel_number>\n"
        << "4. select_channel_by_name <channel_name>\n"
        << "5. select_previous_channel\n"
        << "6. set_channel_name <channel_number> <channel_name>\n"
        << "7. get_channel_name <channel_number>\n"
        << "8. get_channel_by_name <channel_name>\n"
        << "9. delete_channel_name <channel_name>\n"
        << "10. TV_info\n"
        << "11. exit\n"
        << "=======================\n";
}

void printError(const string& error) {
    cout << error << endl;
}

void printMissingParameterError(const string& parameter) {
    printError("Missing parameter. Enter " + parameter + ".");
}

void printInvalidParameterError(const string& parameter) {
    printError("Invalid " + parameter + ".");
}

void processCommand(CTVSet& tv, const string& command)
{
    istringstream iss(command);
    string cmd, param1, param2;
    iss >> cmd >> param1 >> param2;

    if (cmd.empty()) {
        printError("Invalid command. Type 'help' for the list of commands.");
        return;
    }

    if (cmd == "turn_on" || cmd == "1") {
        tv.TurnOn();
    }
    else if (cmd == "turn_off" || cmd == "2") {
        tv.TurnOff();
    }
    else if (cmd == "select_channel" || cmd == "3") {
        if (param1.empty()) {
            printMissingParameterError("channel number");
            return;
        }
        int channel;
        if (!(istringstream(param1) >> channel)) {
            printInvalidParameterError("channel number");
            return;
        }
        tv.SelectChannel(channel);
    }
    else if (cmd == "select_channel_by_name" || cmd == "4") {
        if (param1.empty()) {
            printMissingParameterError("channel name");
            return;
        }
        tv.SelectChannelByName(param1);
    }
    else if (cmd == "select_previous" || cmd == "5") {
        tv.SelectPreviousChannel();
    }
    else if (cmd == "set_channel_name" || cmd == "6") {
        if (param1.empty() || param2.empty()) {
            printMissingParameterError("channel number and name.");
            return;
        }
        int channel;
        if (!(istringstream(param1) >> channel)) {
            printInvalidParameterError("channel number");
            return;
        }
        tv.SetChannelName(channel, param2);
    }
    else if (cmd == "get_channel_name" || cmd == "7") {
        if (param1.empty()) {
            printMissingParameterError("channel number");
            return;
        }
        int channel;
        if (!(istringstream(param1) >> channel)) {
            printInvalidParameterError("channel number");
            return;
        }
        cout << "Channel name: " << tv.GetChannelName(channel);
    }
    else if (cmd == "get_channel_by_name" || cmd == "8") {
        if (param1.empty()) {
            printMissingParameterError("channel name");
            return;
        }
        cout << "Channel number: " << tv.GetChannelByName(param1);
    }
    else if (cmd == "delete_channel_name" || cmd == "9") {
        if (param1.empty()) {
            printMissingParameterError("channel name");
            return;
        }
        tv.DeleteChannelName(param1);
    }
    else if (cmd == "TV_info" || cmd == "10") {
        tv.Info();
    }
    else if (cmd == "exit" || cmd == "11") {
        cout << "Exiting...\n";
        exit(0);
    }
    else {
        printError("Invalid command. Type 'help' for the list of commands.");
    }
}


void TVRun()
{
    CTVSet tv;
    cout << "Welcome to TV Control!\n";
    string command;
    while (true)
    {
        cout << "> ";
        getline(cin, command);

        if (command == "help") {
            displayMenu();
        }
        else {
            processCommand(tv, command);
        }
    }
}
