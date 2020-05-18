#include "stdafx.h"
#include "../dictionary/dictionary.h"

using namespace std;

BOOST_AUTO_TEST_SUITE(Functions_tests)

struct cout_redirect {
	cout_redirect(std::streambuf* new_buffer)
		: old(std::cout.rdbuf(new_buffer))
	{ }

	~cout_redirect() {
		std::cout.rdbuf(old);
	}

private:
	std::streambuf* old;
};

BOOST_AUTO_TEST_CASE(search_for_the_word_in_dictionary)
{
	boost::test_tools::output_test_stream output;
	{
		SetConsoleCP(1251);
		SetConsoleOutputCP(1251);
		setlocale(LC_ALL, "");
		cout_redirect guard(output.rdbuf());
		map<string, string> dictionary = {
			{"hello", "привет"}
		};
		const string inputString = "hello";
		SearchForTranslation(dictionary, inputString);
	}
	BOOST_CHECK(output.is_equal("привет\n"));
	//cout << "Test passed: search for the word in dictionary" << endl;
}

BOOST_AUTO_TEST_CASE(search_for_the_phrase_in_dictionary)
{
	boost::test_tools::output_test_stream output;
	{
		cout_redirect guard(output.rdbuf());
		map<string, string> dictionary = {
			{"big apple", "большое яблоко"}
		};
		const string inputString = "big apple";
		SearchForTranslation(dictionary, inputString);
	}
	BOOST_CHECK(output.is_equal("большое яблоко\n"));
	//cout << "Test passed: search for the phrase in dictionary" << endl;
}

BOOST_AUTO_TEST_CASE(search_for_the_word_in_different_case_in_dictionary)
{
	boost::test_tools::output_test_stream output;
	{
		cout_redirect guard(output.rdbuf());
		map<string, string> dictionary = {
			{"the red square", "Красная Площадь"}
		};
		const string inputString = "The Red Square";
		SearchForTranslation(dictionary, inputString);
	}
	BOOST_CHECK(output.is_equal("Красная Площадь\n"));
	//cout << "Test passed: search for the phrase in dictionary" << endl;
}

BOOST_AUTO_TEST_CASE(insert_word_in_dictionary)
{
	map<string, string> dictionary = {
		{"hello", "привет"}
	};
	map<string, string> resDictionary = {
		{"hello", "привет"},
		{"wood", "дерево"},
	};
	string inputWord = "wood";
	string translation = "дерево";
	InsertInDictionary(dictionary, inputWord, translation);
	BOOST_CHECK(resDictionary == dictionary);
	//cout << "Test passed: insert word in dictionary" << endl;
}

BOOST_AUTO_TEST_CASE(convert_word_to_lower_case)
{
	string str = "DicTiOnaRY";
	str = ToLowerCase(str);
	string resStr = "dictionary";
	BOOST_CHECK(resStr == str);
	//cout << "Test passed: convert word to lower case" << endl;
}

BOOST_AUTO_TEST_SUITE_END()