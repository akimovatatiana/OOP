#include "RemoteControl.h"
#include "Header.h"
#include "TVSet.h"

using namespace std;
using namespace std::placeholders;

CRemoteControl::CRemoteControl(CTVSet& tv, std::istream& input, std::ostream& output)
	: m_tv(tv)
	, m_input(input)
	, m_output(output)
	, m_actionMap({ 
		  { "TurnOn", std::bind(&CRemoteControl::TurnOn, this, _1) },
		  { "TurnOff", std::bind(&CRemoteControl::TurnOff, this, _1) },
		  { "SelectChannel", std::bind(&CRemoteControl::SelectChannel, this, _1) },
		  { "SelectChannel", std::bind(&CRemoteControl::SelectChannel, this, _1) },
		  { "SelectPreviousChannel", std::bind(&CRemoteControl::SelectPreviousChannel, this, _1) },
		  { "SetChannelName", std::bind(&CRemoteControl::SetChannelName, this, _1)},
		  { "DeleteChannelName", std::bind(&CRemoteControl::DeleteChannelName, this, _1)},
		  { "Info", bind(&CRemoteControl::Info, this, _1) } })
{
}

bool CRemoteControl::HandleCommand()
{
	string commandLine;
	getline(m_input, commandLine);
	istringstream strm(commandLine);

	string action;
	strm >> action;

	auto it = m_actionMap.find(action);
	if (it != m_actionMap.end())
	{
		it->second(strm);
		return true;
	}

	return false;
}

bool CRemoteControl::TurnOn(std::istream&)
{
	m_tv.TurnOn();
	m_output << TURNED_ON << endl;

	return true;
}

bool CRemoteControl::TurnOff(std::istream&)
{
	m_tv.TurnOff();
	m_output << TURNED_OFF << endl;

	return true;
}

bool CRemoteControl::SelectChannel(std::istream& args)
{
	string stringChannel;
	string channelName;
	getline(args, stringChannel);
	channelName = regex_replace(stringChannel, std::regex("^[ ]*(.*?)[ ]*$"), "$1");
	int channel = atoi(channelName.c_str());
	bool isNumber = (channelName.length() == to_string(channel).length());

	if (!isNumber)
	{
		if (m_tv.SelectChannel(channelName))
		{
			m_output << "Channel selected" << endl;
			return true;
		}
		else
		{
			m_output << "There is not channel called '" << channelName << "'" << endl;
			return false;
		}
	}
	if (m_tv.SelectChannel(channel))
	{
		m_output << "Channel selected" << endl;
		return true;
	}
	else
	{
		if (!IsChannelInRange(channel))
		{
			return false;
		}
	}
	m_output << "Can't select channel because " << TURNED_OFF << endl;
	return false;
}

bool CRemoteControl::SelectPreviousChannel(std::istream&)
{
	if (m_tv.IsTurnedOn())
	{
		m_tv.SelectPreviousChannel();
		m_output << "Previous channel selected" << endl;
		return true;
	}
	m_output << "Can't select previous channel because " << TURNED_OFF << endl;
	return false;
}

bool CRemoteControl::SetChannelName(std::istream& args)
{
	int channel;
	args >> channel;
	string channelName;
	getline(args, channelName);
	boost::algorithm::trim(channelName);
	channelName = RemoveExtraSpaces(channelName);
	if (channelName.empty())
	{
		m_output << "Channel name must not be an empty string" << endl;
		return false;
	}
	if (!IsChannelInRange(channel))
	{
		return false;
	}
	if (m_tv.SetChannelName(channel, channelName))
	{
		m_output << "Channel " << channel << " is set to '" << channelName << "' name" << endl;
		return true;
	}
	m_output << "Can't set channel name because " << TURNED_OFF << endl;
	return false;
}

bool CRemoteControl::DeleteChannelName(std::istream& args)
{
	string channelName;
	getline(args, channelName);
	boost::algorithm::trim(channelName);
	if (m_tv.IsTurnedOn())
	{
		if (channelName.empty())
		{
			m_output << "Channel name must not be an empty string" << endl;
			return false;
		}
		else if (!m_tv.DeleteChannelName(channelName))
		{
			m_output << "Failed to delete channel '" << channelName << "'" << endl;
			return false;
		}
		else
		{
			m_output << "Channel '" << channelName << "' is deleted" << endl;
			return true;
		}
	}
	else
	{
		m_output << "Can't delete channel because " << TURNED_OFF << endl;
		return false;
	}

}

bool CRemoteControl::Info(std::istream&)
{
	string isTurnedOn = (m_tv.IsTurnedOn())
		? (TURNED_ON + "\n")
		: TURNED_OFF + "\n";
	m_output << isTurnedOn;

	string channelNumber = to_string(m_tv.GetChannel());

	Channels channels = m_tv.GetChannelsList();

	if (m_tv.IsTurnedOn())
	{
		if (m_tv.GetChannelName(m_tv.GetChannel()).empty())
		{
			m_output << "Channel is: " + channelNumber << endl;
		}
		else
		{
			m_output << "Channel is: " + channelNumber << " - "
				<< m_tv.GetChannelName(stoi(channelNumber)) << endl;
		}
		for (const auto& pair : channels)
		{
			m_output << pair.first << " - " << pair.second << endl;
		}
	}
	return true;
}

bool CRemoteControl::IsChannelInRange(int channel)
{
	if ((channel < FIRST_CHANNEL) || (channel > LAST_CHANNEL))
	{
		m_output << "Invalid channel number. Channel number must be in range [1, 99]" << endl;
		return false;
	}
	return true;
}

std::string CRemoteControl::RemoveExtraSpaces(const std::string& str)
{
	string output;
	unique_copy(str.begin(), str.end(), back_insert_iterator<string>(output),
		[](char a, char b) { return isspace(a) && isspace(b); });
	return output;
}
