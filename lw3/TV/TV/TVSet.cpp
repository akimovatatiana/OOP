#include "TVSet.h"
#include "Header.h"

using namespace std;

CTVSet::CTVSet()
	:m_isTurnedOn(false)
	, m_currentChannel(1)
	, m_previousChannel(1)
{
}

CTVSet::~CTVSet()
{
}

bool CTVSet::IsTurnedOn()const
{
	return m_isTurnedOn;
}

bool CTVSet::TurnOn()
{
	m_isTurnedOn = true;
	return m_isTurnedOn;
}

bool CTVSet::TurnOff()
{
	m_isTurnedOn = false;
	return true;
}

int CTVSet::GetChannel() const
{
	if (m_isTurnedOn)
	{
		return m_currentChannel;
	}
	return 0;
}

bool CTVSet::SelectChannel(int channel)
{
	if ((channel >= FIRST_CHANNEL && channel <= LAST_CHANNEL) && IsTurnedOn())
	{
		m_previousChannel = m_currentChannel;
		m_currentChannel = channel;
		return true;
	}
	return false;
}

bool CTVSet::SelectPreviousChannel()
{
	if (m_isTurnedOn)
	{
		swap(m_previousChannel, m_currentChannel);
		return true;
	}
	return false;
}

bool CTVSet::SetChannelName(int channel, const std::string& channelName)
{
	string newChannelName = RemoveExtraSpaces(channelName);
	if (m_isTurnedOn && !newChannelName.empty() && (channel >= FIRST_CHANNEL && channel <= LAST_CHANNEL))
	{
		int prevChannelNumber = FindChannelByName(newChannelName);
		if (prevChannelNumber != 0)
		{
			DeleteChannelByNumber(prevChannelNumber);
		}
		DeleteChannelByNumber(channel);
		if (m_channels.find(channel) != m_channels.end())
		{
			m_channels.at(channel) = newChannelName;
		}
		else
		{
			m_channels.emplace(channel, newChannelName);
			return true;
		}
	}
	return false;
}

int CTVSet::FindChannelByName(const std::string& channelName)
{
	for (const auto& pair : m_channels)
	{
		if (pair.second == channelName)
		{
			return pair.first;
		}
	}
	return 0;
}

bool CTVSet::SelectChannel(const std::string& channelName)
{
	int channel = FindChannelByName(channelName);
	if (m_isTurnedOn && (channel != 0))
	{
		m_previousChannel = m_currentChannel;
		m_currentChannel = channel;
		return true;
	}
	return false;
}

bool CTVSet::DeleteChannelName(const std::string& channelName)
{
	if (m_isTurnedOn)
	{
		int channel = FindChannelByName(channelName);
		if (channel != 0)
		{
			DeleteChannelByNumber(channel);
			return true;
		}
		return false;
	}
	else
	{
		return false;
	}
}

int CTVSet::GetChannelByName(const std::string& channelName)
{
	if (m_isTurnedOn)
	{
		int channel = FindChannelByName(channelName);
		if (channel == 0)
		{
			return 0;
		}
		return channel;
	}
	else
	{
		return 0;
	}
}

string CTVSet::GetChannelName(int channel)const
{
	if (!m_isTurnedOn)
	{
		return "";
	}
	for (const auto& pair : m_channels)
	{
		if (pair.first == channel)
		{
			return pair.second;
		}
	}
	return "";
}

void CTVSet::DeleteChannelByNumber(int channel)
{
	m_channels.erase(channel);
}

Channels CTVSet::GetChannelsList()const
{
	return m_channels;
}

std::string CTVSet::RemoveExtraSpaces(const std::string& str)
{
	string output;
	unique_copy(str.begin(), str.end(), back_insert_iterator<string>(output),
		[](char a, char b) { return isspace(a) && isspace(b); });
	boost::algorithm::trim(output);
	return output;
}
