#pragma once
#include <boost/noncopyable.hpp>
#include "TVSet.h"

using Channels = std::map<int, std::string>;
class CRemoteControl
{
public:
	CRemoteControl(CTVSet& tv, std::istream& input, std::ostream& output);
	bool HandleCommand();

private:
	bool TurnOn(std::istream& args);
	bool TurnOff(std::istream& args);
	bool SelectChannel(std::istream& args);
	bool SelectPreviousChannel(std::istream& args);
	bool SetChannelName(std::istream& args);
	bool DeleteChannelName(std::istream& args);
	bool Info(std::istream&);

private:
	using ActionMap = std::map<std::string, std::function<void(std::istream& args)>>;
	CTVSet& m_tv;
	std::istream& m_input;
	std::ostream& m_output;

	const ActionMap m_actionMap;
	bool IsChannelInRange(int channel);
	std::string RemoveExtraSpaces(const std::string& str);
};


