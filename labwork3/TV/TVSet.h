#ifndef TVSET_H
#define TVSET_H

#include <iostream>
#include <map>
#include <string>

using namespace std;

class CTVSet
{
private:
    bool m_isOn;
    int m_currentChannel;
    int m_previousChannel;  
    map<int, string> m_channelNames;
    void ShowError(ostream& out, const string& message);

public:
    CTVSet();

    void TurnOn();
    void TurnOff();
    void SelectChannel(int channel);
    void SelectChannelByName(const string& name);
    void SelectPreviousChannel();
    void SetChannelName(int channel, const string& name);
    string GetChannelName(int channel);
    int GetChannelByName(const string& name);
    void DeleteChannelName(const string& name);
    void Info();
};

#endif
