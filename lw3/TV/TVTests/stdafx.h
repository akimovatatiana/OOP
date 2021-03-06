// stdafx.h : include file for standard system include files,
// or project specific include files that are used frequently, but
// are changed infrequently
//

#pragma once

#include "targetver.h"

#include <stdio.h>
#include <tchar.h>

#include <boost/algorithm/string/replace.hpp>

#define BOOST_TEST_INCLUDED
#pragma warning (disable: 4702)
#include <boost/test/unit_test.hpp>

#include <iostream>
#include <sstream>
#include <functional>
#include <map>
#include <regex>
#include <algorithm>
#include <boost/algorithm/string.hpp>

static const int FIRST_CHANNEL = 1;
static const int LAST_CHANNEL = 99;

const std::string TURNED_OFF = "TV is turned off";
const std::string TURNED_ON = "TV is turned on";

// TODO: reference additional headers your program requires here
