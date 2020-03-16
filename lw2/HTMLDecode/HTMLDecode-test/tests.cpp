#include "Header-test.h"
#include "HTMLDecode/HTMLDecode.h"

TEST_CASE("HtmlDecode should return an empty string")
{
	CHECK("" == HtmlDecode(""));
}

TEST_CASE("Decode only one entity")
{
	// Декодирвание всех сущностей по отдельности
	CHECK("\"" == HtmlDecode("&quot;"));
	CHECK("'" == HtmlDecode("&apos;"));
	CHECK("<" == HtmlDecode("&lt;"));
	CHECK(">" == HtmlDecode("&gt;"));
	CHECK("&" == HtmlDecode("&amp;"));
}
TEST_CASE("Decode all existing entities")
{
	// Декодирование всех имеющихся HTML сущностей
	CHECK("\"\'<>&" == HtmlDecode("&quot;&apos;&lt;&gt;&amp;"));
}
TEST_CASE("Decode consecutive entities")
{
	// Декодирование двух кавычек
	CHECK("\"\"" == HtmlDecode("&quot;&quot;"));
}

TEST_CASE("Decode only first entity")
{
	// Декодирование только одной сущности
	CHECK("&lt;" == HtmlDecode("&amp;lt;"));
}

TEST_CASE("Decode cases with repetiton of the letter")
{
	// Декодирование случаев с повторением буквы
	CHECK("It's the dog's toy" == HtmlDecode("It's the dog&apos;s toy"));
	CHECK("Dog&aposs toy" == HtmlDecode("Dog&aposs toy"));
}
TEST_CASE("Decode a string with entities")
{
	// Декодирование строки с сущностями
	CHECK("Cat <says> \"Meow\". M&M's" == HtmlDecode("Cat &lt;says&gt; &quot;Meow&quot;. M&amp;M&apos;s"));
}
