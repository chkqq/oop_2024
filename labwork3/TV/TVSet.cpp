#include "TVSet.h"

using namespace std;

void CTVSet::ShowError(ostream& out, const string& message)
{
    out << message << "\n";
}

CTVSet::CTVSet() : m_isOn(false), m_currentChannel(0), m_previousChannel(0) {}

void CTVSet::TurnOn()
{
    if (!m_isOn)
    {
        m_isOn = true;
        if (m_previousChannel != 0)
        {
            m_currentChannel = m_previousChannel;
        }
        else
        {
            m_currentChannel = 1;
        }
        cout << "TV was turned on.\n";
    }
    else
    {
        ShowError(cout, "Error: TV is already turned on.");
    }
}

void CTVSet::TurnOff()
{
    if (m_isOn)
    {
        m_isOn = false;
        m_previousChannel = m_currentChannel;
        m_currentChannel = 0;
        cout << "TV was turned off.\n";
    }
    else
    {
        ShowError(cout, "Error: TV is already turned off.");
    }
}

void CTVSet::SelectChannel(int channel)
{
    if (!m_isOn)
    {
        ShowError(cout, "Error: TV must be turned on.");
        return;
    }
    if (!(channel >= 1 && channel <= 99))
    {
        ShowError(cout, "Error: Enter a valid channel number (1 to 99).");
        return;
    }
    m_previousChannel = m_currentChannel;
    m_currentChannel = channel;
}

void CTVSet::SelectChannelByName(const string& name)
{
    for (const auto& pair : m_channelNames)
    {
        if (pair.second == name)
        {
            m_currentChannel = pair.first;
            return;
        }
    }
    ShowError(cout, "Error: Channel does not exist.");
}


void CTVSet::SelectPreviousChannel()
{
    if (m_isOn)
    {
        m_currentChannel = m_previousChannel;
    }
}

void CTVSet::SetChannelName(int channel, const string& name)
{
    if (!m_isOn)
    {
        ShowError(cout, "Error: TV must be turned on.");
        return;
    }
    if (!(channel >= 1 && channel <= 99))
    {
        ShowError(cout, "Error: Enter a valid channel number (1 to 99).");
        return;
    }
    if (name.empty())
    {
        ShowError(cout, "Error: Channel name cannot be empty.");
        return;
    }
    for (auto& pair : m_channelNames)
    {
        if (pair.second == name && pair.first != channel)
        {
            pair.second = "";
            break;
        }
    }
    m_channelNames[channel] = name;
    cout << "Channel name successfully changed.\n";
}

string CTVSet::GetChannelName(int channel)
{
    if (m_channelNames.find(channel) != m_channelNames.end())
    {
        return m_channelNames[channel];
    }
    else
    {
        ShowError(cout, "Error: Channel does not exist.");
    }
    return "";
}

int CTVSet::GetChannelByName(const string& name)
{
    for (const auto& pair : m_channelNames)
    {
        if (pair.second == name)
        {
            return pair.first;
        }
    }
    ShowError(cout, "Error: Channel does not exist.");
    return 0;
}

void CTVSet::DeleteChannelName(const string& name)
{
    for (auto i = m_channelNames.begin(); i != m_channelNames.end(); ++i)
    {
        if (i->second == name)
        {
            m_channelNames.erase(i);
            cout << "Channel name successfully delete.\n";
            return;
        }
    }
    ShowError(cout, "Error: Channel does not exist.");
}

void CTVSet::Info()
{
    cout << "TV is " << (m_isOn ? "ON" : "OFF") << "\n";
    cout << "Current channel: " << m_currentChannel << "\n";
    cout << "Current channel name: ";
    if (m_channelNames.find(m_currentChannel) != m_channelNames.end())
    {
        cout << m_channelNames[m_currentChannel] << "\n";
    }
    else
    {
        ShowError(cout, "Error: Failed to retrieve current channel name.");
    }
    cout << "All channel names:\n";
    for (const auto& pair : m_channelNames)
    {
        cout << pair.first << " - " << pair.second << "\n";
    }
}
