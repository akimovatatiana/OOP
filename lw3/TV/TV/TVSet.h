#pragma once
#include "Header.h"

using Channels = std::map<int, std::string>;
class CTVSet
{
public:
	CTVSet();

	~CTVSet();

	bool IsTurnedOn()const;
	bool TurnOn();
	bool TurnOff();
	bool SelectChannel(int channel);
	int GetChannel()const;
	bool SelectPreviousChannel();
	bool SetChannelName(int channel, const std::string& channelName);
	bool SelectChannel(const std::string& channelName);
	bool DeleteChannelName(const std::string& channelName);

	int GetChannelByName(const std::string& channelName);
	std::string GetChannelName(int channel)const;
	Channels GetChannelsList()const;

private:
	bool m_isTurnedOn;
	int m_currentChannel;
	int m_previousChannel;
	Channels m_channels;

	int FindChannelByName(const std::string& channelName);
	void DeleteChannelByNumber(int channel);
	std::string RemoveExtraSpaces(const std::string& str);
};


