#define BOOST_TEST_MAIN
#include <iostream>
#include <boost/test/unit_test.hpp>
#include "../TV/TVSet.h"

struct TVSetFixture
{
	CTVSet tv;
};
// Телевизор 
BOOST_FIXTURE_TEST_SUITE(TVSet, TVSetFixture)
// изначально выключен
BOOST_AUTO_TEST_CASE(is_turned_off_by_default)
{
	BOOST_CHECK(!tv.IsTurnedOn());
}
// не может переключать канал в выключенном состоянии
BOOST_AUTO_TEST_CASE(cant_select_channel_when_turned_off)
{
	BOOST_CHECK(!tv.SelectChannel(87));
	BOOST_CHECK_EQUAL(tv.GetChannel(), 0);
}

// может быть включен
BOOST_AUTO_TEST_CASE(can_be_turned_on)
{
	tv.TurnOn();
	BOOST_CHECK(tv.IsTurnedOn());
}
// изначально отображает 0 канал
BOOST_AUTO_TEST_CASE(displays_channel_0_by_default)
{
	BOOST_CHECK_EQUAL(tv.GetChannel(), 0);
}

struct TurnedOnTv : TVSetFixture
{
	TurnedOnTv()
	{
		tv.TurnOn();
	}
};
// после включения
BOOST_FIXTURE_TEST_SUITE(when_turned_on, TurnedOnTv)
// отображает канал 1
BOOST_AUTO_TEST_CASE(displays_channel_one)
{
	BOOST_CHECK_EQUAL(tv.GetChannel(), 1);
}
// можно выключить
BOOST_AUTO_TEST_CASE(can_be_turned_off)
{
	tv.TurnOff();
	BOOST_CHECK(!tv.IsTurnedOn());
}
// позволяет выбрать канал от 1 до 99
BOOST_AUTO_TEST_CASE(can_select_channel_from_1_to_99)
{
	BOOST_CHECK(tv.SelectChannel(1));
	BOOST_CHECK_EQUAL(tv.GetChannel(), 1);

	BOOST_CHECK(tv.SelectChannel(99));
	BOOST_CHECK_EQUAL(tv.GetChannel(), 99);

	// Выбираем канал между 1 и 99
	BOOST_CHECK(tv.SelectChannel(42));
	BOOST_CHECK_EQUAL(tv.GetChannel(), 42);

	// При попытке выбрать канал за пределами [1; 99] 
	// телевизор не должен менять свой канал
	BOOST_CHECK(!tv.SelectChannel(0));
	BOOST_CHECK_EQUAL(tv.GetChannel(), 42);

	BOOST_CHECK(!tv.SelectChannel(100));
	BOOST_CHECK_EQUAL(tv.GetChannel(), 42);
}
BOOST_AUTO_TEST_CASE(can_select_previous_channel)
{
	BOOST_CHECK(tv.SelectChannel(10));
	BOOST_CHECK(tv.SelectChannel(12));
	BOOST_CHECK(tv.SelectPreviousChannel());
	BOOST_CHECK_EQUAL(tv.GetChannel(), 10);
}

BOOST_AUTO_TEST_CASE(cant_set_channel_name_with_empty_string)
{
	BOOST_CHECK(!tv.SetChannelName(1, ""));
}
BOOST_AUTO_TEST_CASE(cant_set_channel_name_with_string_of_spaces)
{
	BOOST_CHECK(!tv.SetChannelName(8, "   "));
}
BOOST_AUTO_TEST_CASE(can_set_channel_name_with_one_word)
{
	BOOST_CHECK(tv.SetChannelName(1, "STS"));
	BOOST_CHECK_EQUAL(tv.GetChannelName(1), "STS");
}
BOOST_AUTO_TEST_CASE(can_set_channel_name_with_extra_spaces)
{
	BOOST_CHECK(tv.SetChannelName(2, "   MTV    HD    "));
	BOOST_CHECK_EQUAL(tv.GetChannelName(2), "MTV HD");
}
BOOST_AUTO_TEST_CASE(can_redifine_channel_name_with_new_number)
{
	BOOST_CHECK(tv.SetChannelName(2, "MTV HD"));
	BOOST_CHECK(tv.SetChannelName(3, "MTV HD"));
	BOOST_CHECK_EQUAL(tv.GetChannelName(3), "MTV HD");
	BOOST_CHECK(tv.GetChannelName(2).empty());
}
BOOST_AUTO_TEST_CASE(can_delete_channel_name)
{
	BOOST_CHECK(tv.SetChannelName(6, "TNT"));
	BOOST_CHECK(tv.SelectChannel("TNT"));
	BOOST_CHECK(tv.DeleteChannelName("TNT"));
	BOOST_CHECK_EQUAL(tv.GetChannel(), 6);
}
BOOST_AUTO_TEST_CASE(cant_delete_channel_name_with_unknown_name)
{
	BOOST_CHECK(!tv.DeleteChannelName("TNT"));
}
BOOST_AUTO_TEST_SUITE_END()


struct TurnedOffTv : TurnedOnTv
{
	TurnedOffTv()
	{
		tv.SetChannelName(12, "ORT");
		tv.TurnOff();
	}
};

BOOST_FIXTURE_TEST_SUITE(when_turned_off, TurnedOffTv)

BOOST_AUTO_TEST_CASE(is_at_channel_0_when_turned_off)
{
	BOOST_CHECK_EQUAL(tv.GetChannel(), 0);
}
BOOST_AUTO_TEST_CASE(cant_select_previous_channel_when_turned_off)
{
	BOOST_CHECK(!tv.SelectPreviousChannel());
}
BOOST_AUTO_TEST_CASE(cant_select_channel_when_turned_off)
{
	BOOST_CHECK(!tv.SelectChannel(10));
}
BOOST_AUTO_TEST_CASE(cant_delete_channel_name_when_turned_off)
{
	BOOST_CHECK(!tv.DeleteChannelName("ORT"));
}
BOOST_AUTO_TEST_CASE(cant_get_channel_name_when_turned_off)
{
	BOOST_CHECK_EQUAL(tv.GetChannelName(12), "");
}
BOOST_AUTO_TEST_CASE(cant_get_channel_by_name_when_turned_off)
{
	BOOST_CHECK_EQUAL(tv.GetChannelByName("ORT"), 0);
}
BOOST_AUTO_TEST_SUITE_END()

struct after_subsequent_turning_on_ : TurnedOnTv
{
	after_subsequent_turning_on_()
	{
		tv.SelectChannel(33);
		tv.TurnOff();
		tv.TurnOn();
	}
};

// после повторного включения
BOOST_FIXTURE_TEST_SUITE(after_subsequent_turning_on, after_subsequent_turning_on_)
// восстанавливает последний выбранный канал
BOOST_AUTO_TEST_CASE(restores_last_selected_channel)
{
	BOOST_CHECK_EQUAL(tv.GetChannel(), 33);
}

BOOST_AUTO_TEST_CASE(remember_previous_channel)
{
	BOOST_CHECK(tv.SelectPreviousChannel());
	BOOST_CHECK_EQUAL(tv.GetChannel(), 1);
}
BOOST_AUTO_TEST_SUITE_END()

struct after_subsequent_turning_on_and_setting_name_ : TurnedOnTv
{
	after_subsequent_turning_on_and_setting_name_()
	{
		tv.SetChannelName(33, "ORT");
		tv.TurnOff();
		tv.TurnOn();
	}
};
BOOST_FIXTURE_TEST_SUITE(after_subsequent_turning_on_and_setting_name, after_subsequent_turning_on_and_setting_name_)
BOOST_AUTO_TEST_CASE(can_get_channel_name)
{
	BOOST_CHECK_EQUAL(tv.GetChannelName(33), "ORT");
}
BOOST_AUTO_TEST_CASE(can_get_channel_by_name)
{
	BOOST_CHECK_EQUAL(tv.GetChannelByName("ORT"), 33);
}
BOOST_AUTO_TEST_CASE(can_delete_channel_name)
{
	BOOST_CHECK(tv.SelectChannel("ORT"));
	BOOST_CHECK(tv.DeleteChannelName("ORT"));
	BOOST_CHECK_EQUAL(tv.GetChannel(), 33);
}


BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()