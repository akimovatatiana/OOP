#include "../TV/RemoteControl.h"
#include "../TV/TVSet.h"
#include <sstream>
#include <boost/optional.hpp>
#include <boost/test/unit_test.hpp>

using namespace std;
using boost::optional;
using boost::none;

// Зависимости RemoteControl-а вынесены в родительскую структуру,
// чтобы гарантировать их создание до конструирования самого remote-контрола
struct RemoteControlDependencies
{
	CTVSet tv;
	stringstream input;
	stringstream output;
};

struct RemoteControlFixture : RemoteControlDependencies
{
	CRemoteControl remoteControl;

	RemoteControlFixture()
		: remoteControl(tv, input, output)
	{
	}

	// Вспомогательная функция для проверки работы команды command
	// Она принимает ожидаемый номер канала expectedChannel и expectedOutput
	void VerifyCommandHandling(const string& command, const optional<int>& expectedChannel, const string& expectedOutput)
	{
		// Предварительно очищаем содержимое выходного потока
		output = stringstream();
		input = stringstream();
		BOOST_CHECK(input << command);
		BOOST_CHECK(remoteControl.HandleCommand());
		BOOST_CHECK_EQUAL(tv.IsTurnedOn(), expectedChannel.is_initialized());
		BOOST_CHECK_EQUAL(tv.GetChannel(), expectedChannel.get_value_or(0));
		BOOST_CHECK(input.eof());
		BOOST_CHECK_EQUAL(output.str(), expectedOutput);
	}
};

BOOST_FIXTURE_TEST_SUITE(Remote_Control, RemoteControlFixture)
BOOST_AUTO_TEST_SUITE(Turn_commands_test)
	BOOST_AUTO_TEST_CASE(can_handle_TurnOn_command)
	{
		VerifyCommandHandling("TurnOn", 1, "TV is turned on\n");
	}

	BOOST_AUTO_TEST_CASE(can_turn_off_tv_which_is_on)
	{
		tv.TurnOn();
		VerifyCommandHandling("TurnOff", none, "TV is turned off\n");
	}
BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE(Info_command_test)
	BOOST_AUTO_TEST_CASE(can_print_tv_info)
	{
		// Ожидаемое поведение команды Info, вызванной у выключенного телевизора
		VerifyCommandHandling("Info", none, "TV is turned off\n");

		// Проверяем поведение команды Info у включенного телевизора
		tv.TurnOn();
		tv.SelectChannel(42);
		VerifyCommandHandling("Info", 42, "TV is turned on\nChannel is: 42\n");
	}
	BOOST_AUTO_TEST_CASE(can_print_tv_info_with_channel_list)
	{
		tv.TurnOn();
		tv.SelectChannel(42);
		tv.SetChannelName(10, "ORT");
		tv.SetChannelName(11, "MTV HD");
		VerifyCommandHandling("Info", 42, "TV is turned on\nChannel is: 42\n10 - ORT\n11 - MTV HD\n");
	}
BOOST_AUTO_TEST_SUITE_END()

//SelectChannel
struct tv_has_channel_list_ : RemoteControlFixture
{
	tv_has_channel_list_()
	{
		tv.TurnOn();
		tv.SetChannelName(2, "STS");
		tv.SetChannelName(5, "Ren TV");
	}
};
BOOST_AUTO_TEST_SUITE(SelectChannel_command_test)
	BOOST_FIXTURE_TEST_SUITE(SelectChannel_by_channel_name, tv_has_channel_list_)
		BOOST_AUTO_TEST_CASE(can_select_channel_by_name)
		{
			VerifyCommandHandling("SelectChannel STS", 2, "Channel selected\n");
			VerifyCommandHandling("SelectChannel Ren TV", 5, "Channel selected\n");
		}
		BOOST_AUTO_TEST_CASE(cant_select_channel_by_unknown_name)
		{
			VerifyCommandHandling("SelectChannel TNT", 1, "There is not channel called 'TNT'\n");
		}
	BOOST_AUTO_TEST_SUITE_END()
	BOOST_AUTO_TEST_SUITE(SelectChannel_by_channel_number)
		BOOST_AUTO_TEST_CASE(can_select_a_valid_channel_when_tv_which_is_on)
		{
			tv.TurnOn();
			VerifyCommandHandling("SelectChannel 42", 42, "Channel selected\n");
		}
		BOOST_AUTO_TEST_CASE(cant_select_an_invalid_channel_when_tv_is_on)
		{
			tv.TurnOn();
			tv.SelectChannel(42);
			VerifyCommandHandling("SelectChannel 100", 42, "Invalid channel number. Channel number must be in range [1, 99]\n");
			VerifyCommandHandling("SelectChannel 0", 42, "Invalid channel number. Channel number must be in range [1, 99]\n");
		}
	BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE(SelectPreviousChannel_command_test)
	BOOST_AUTO_TEST_CASE(cant_select_previous_channel_when_tv_which_is_off)
	{
		tv.TurnOff();
		VerifyCommandHandling("SelectPreviousChannel", none, "Can't select previous channel because TV is turned off\n");
	}
	BOOST_AUTO_TEST_CASE(can_select_previous_channel_when_tv_which_is_on)
	{
		tv.TurnOn();
		tv.SelectChannel(42);
		VerifyCommandHandling("SelectPreviousChannel", 1, "Previous channel selected\n");
	}
BOOST_AUTO_TEST_SUITE_END()


BOOST_AUTO_TEST_SUITE(SetChannelName_command_test)
	BOOST_AUTO_TEST_CASE(cant_set_channel_name_when_tv_turned_off)
	{
		VerifyCommandHandling("SetChannelName 10 STS", none, "Can't set channel name because TV is turned off\n");
	}
	BOOST_AUTO_TEST_CASE(cant_set_channel_name_to_out_of_range_channel_number)
	{
		tv.TurnOn();
		VerifyCommandHandling("SetChannelName 100 STS", 1, "Invalid channel number. Channel number must be in range [1, 99]\n");
		VerifyCommandHandling("SetChannelName 0 STS", 1, "Invalid channel number. Channel number must be in range [1, 99]\n");
	}
	BOOST_AUTO_TEST_CASE(can_set_channel_name_with_extra_spaces_when_tv_turned_on)
	{
		tv.TurnOn();
		VerifyCommandHandling("SetChannelName 10      STS   Love", 1, "Channel 10 is set to 'STS Love' name\n");
	}
	BOOST_AUTO_TEST_CASE(can_set_channel_name_when_name_is_number_when_tv_turned_on)
	{
		tv.TurnOn();
		VerifyCommandHandling("SetChannelName 10 22", 1, "Channel 10 is set to '22' name\n");
	}
	BOOST_AUTO_TEST_CASE(can_set_channel_name_when_tv_turned_on)
	{
		tv.TurnOn();
		VerifyCommandHandling("SetChannelName 10 STS", 1, "Channel 10 is set to 'STS' name\n");
		BOOST_CHECK_EQUAL(tv.GetChannelName(10), "STS");
	}
BOOST_AUTO_TEST_SUITE_END()

BOOST_FIXTURE_TEST_SUITE(DeleteChannelName_command_test, tv_has_channel_list_)
	BOOST_AUTO_TEST_CASE(cant_delete_channel_name_when_tv_turned_off)
	{
		tv.TurnOff();
		VerifyCommandHandling("DeleteChannelName STS", none, "Can't delete channel because TV is turned off\n");
	}
	BOOST_AUTO_TEST_CASE(cant_delete_channel_name_with_unknown_name)
	{
		VerifyCommandHandling("DeleteChannelName MTV", 1, "Failed to delete channel 'MTV'\n");
	}
	BOOST_AUTO_TEST_CASE(can_delete_channel_name_with_one_word_name)
	{
		VerifyCommandHandling("DeleteChannelName STS", 1, "Channel 'STS' is deleted\n");
	}
	BOOST_AUTO_TEST_CASE(can_delete_channel_name_with_few_words_name)
	{
		VerifyCommandHandling("DeleteChannelName Ren TV", 1, "Channel 'Ren TV' is deleted\n");
	}
BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE_END()
