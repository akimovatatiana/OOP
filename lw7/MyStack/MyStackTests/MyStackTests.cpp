// MyStackTests.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "../MyStack/MyStack.h"

const int SIZE = 10;

struct StackFixture
{
	CMyStack<std::string> stringStack;
	CMyStack<int> intStack;
};

void InitStackWithIntegers(CMyStack<int>& stack)
{
	size_t size = SIZE;
	for (size_t i = 0; i < size; i++)
	{
		stack.Push(i);
	}
}

void InitStackWithStrings(CMyStack<std::string>& stack)
{
	size_t size = SIZE;
	for (size_t i = 0; i < size; i++)
	{
		stack.Push(std::to_string(i));
	}
}

BOOST_FIXTURE_TEST_SUITE(Stack_tests_, StackFixture)
BOOST_AUTO_TEST_SUITE(Integer_and_string_stacks_)

BOOST_AUTO_TEST_CASE(are_empty_by_default)
{
	BOOST_CHECK(stringStack.IsStackEmpty());
	BOOST_CHECK(intStack.IsStackEmpty());
}

BOOST_AUTO_TEST_CASE(have_zero_size)
{
	BOOST_CHECK(stringStack.GetSize() == 0);
	BOOST_CHECK(intStack.GetSize() == 0);
}

BOOST_AUTO_TEST_CASE(can_push_elements)
{
	int intElement = 5; 
	intStack.Push(intElement);
	BOOST_CHECK(!intStack.IsStackEmpty());
	BOOST_CHECK(intStack.GetSize() == 1);
	BOOST_CHECK(intStack.GetTopElement() == intElement);

	std::string stringElement = "String";
	stringStack.Push(stringElement);
	BOOST_CHECK(!stringStack.IsStackEmpty());
	BOOST_CHECK(stringStack.GetSize() == 1);
	BOOST_CHECK(stringStack.GetTopElement() == stringElement);
}

BOOST_AUTO_TEST_CASE(can_pop_elements)
{
	int intElement = 5;
	intStack.Push(intElement);
	BOOST_CHECK(!intStack.IsStackEmpty());
	intStack.Pop();
	BOOST_CHECK(intStack.IsStackEmpty());

	std::string stringElement = "String";
	stringStack.Push(stringElement);
	BOOST_CHECK(!stringStack.IsStackEmpty());
	stringStack.Pop();
	BOOST_CHECK(stringStack.IsStackEmpty());
}
BOOST_AUTO_TEST_CASE(can_be_cleared)
{
	InitStackWithIntegers(intStack);
	BOOST_CHECK(!intStack.IsStackEmpty());
	intStack.Clear();
	BOOST_CHECK(intStack.IsStackEmpty());

	InitStackWithStrings(stringStack);
	BOOST_CHECK(!stringStack.IsStackEmpty());
	stringStack.Clear();
	BOOST_CHECK(stringStack.IsStackEmpty());
}
BOOST_AUTO_TEST_CASE(can_be_created_by_copy_constructor)
{
	InitStackWithIntegers(intStack);
	CMyStack<int> newIntStack(intStack);
	BOOST_CHECK(!newIntStack.IsStackEmpty());
	BOOST_CHECK(newIntStack.GetTopElement() == intStack.GetTopElement());
	BOOST_CHECK(newIntStack.GetSize() == intStack.GetSize());

	InitStackWithStrings(stringStack);
	CMyStack<std::string> newStringStack(stringStack);
	BOOST_CHECK(!newStringStack.IsStackEmpty());
	BOOST_CHECK(newStringStack.GetTopElement() == stringStack.GetTopElement());
	BOOST_CHECK(newStringStack.GetSize() == stringStack.GetSize());	
}
BOOST_AUTO_TEST_CASE(can_use_copy_assignment_operator)
{
	InitStackWithIntegers(intStack);
	CMyStack<int> newIntStack;
	newIntStack.Push(5);
	BOOST_CHECK(intStack.GetSize() != newIntStack.GetSize());

	newIntStack = intStack;

	BOOST_CHECK(newIntStack.GetSize() == intStack.GetSize());
	BOOST_CHECK(newIntStack.GetTopElement() == intStack.GetTopElement());

	InitStackWithStrings(stringStack);
	CMyStack<std::string> newStringStack;
	newStringStack.Push("String");
	BOOST_CHECK(stringStack.GetSize() != newStringStack.GetSize());

	newStringStack = stringStack;

	BOOST_CHECK(newStringStack.GetSize() == stringStack.GetSize());
	BOOST_CHECK(newStringStack.GetTopElement() == stringStack.GetTopElement());
}
BOOST_AUTO_TEST_CASE(can_be_self_assigned)
{
	InitStackWithIntegers(intStack);
	intStack = intStack;
	BOOST_CHECK(intStack.GetTopElement() == 9);
	BOOST_CHECK(intStack.GetSize() == SIZE);

	InitStackWithStrings(stringStack);
	stringStack = stringStack;
	BOOST_CHECK(stringStack.GetTopElement() == "9");
	BOOST_CHECK(stringStack.GetSize() == SIZE);
}

BOOST_AUTO_TEST_CASE(can_be_created_by_move_constructor)
{
	InitStackWithIntegers(intStack);
	CMyStack<int> newIntStack(std::move(intStack));
	BOOST_CHECK(intStack.IsStackEmpty());
	BOOST_CHECK(!newIntStack.IsStackEmpty());
	BOOST_CHECK(newIntStack.GetTopElement() == 9);
	BOOST_CHECK(newIntStack.GetSize() == SIZE);

	InitStackWithStrings(stringStack);
	CMyStack<std::string> newStringStack(std::move(stringStack));
	BOOST_CHECK(stringStack.IsStackEmpty());
	BOOST_CHECK(!newStringStack.IsStackEmpty());
	BOOST_CHECK(newStringStack.GetTopElement() == "9");
	BOOST_CHECK(newStringStack.GetSize() == SIZE);
}
BOOST_AUTO_TEST_CASE(can_use_move_assignment_operator)
{
	InitStackWithIntegers(intStack);
	CMyStack<int> newIntStack;
	
	newIntStack = std::move(intStack);

	BOOST_CHECK(intStack.IsStackEmpty());
	BOOST_CHECK(newIntStack.GetSize() == SIZE);
	BOOST_CHECK(newIntStack.GetTopElement() == 9);

	InitStackWithStrings(stringStack);
	CMyStack<std::string> newStringStack;
	newStringStack = std::move(stringStack);
	
	BOOST_CHECK(stringStack.IsStackEmpty());
	BOOST_CHECK(newStringStack.GetSize() == SIZE);
	BOOST_CHECK(newStringStack.GetTopElement() == "9");
}
BOOST_AUTO_TEST_CASE(can_be_self_move_assigned)
{
	InitStackWithIntegers(intStack);
	intStack = std::move(intStack);
	BOOST_CHECK(!intStack.IsStackEmpty());
	BOOST_CHECK(intStack.GetTopElement() == 9);
	BOOST_CHECK(intStack.GetSize() == SIZE);

	InitStackWithStrings(stringStack);
	stringStack = std::move(stringStack);
	BOOST_CHECK(!stringStack.IsStackEmpty());
	BOOST_CHECK(stringStack.GetTopElement() == "9");
	BOOST_CHECK(stringStack.GetSize() == SIZE);
}

BOOST_AUTO_TEST_CASE(can_be_destroyed_without_exceptions)
{
	InitStackWithIntegers(intStack);
	CMyStack<int> newIntStack;
	BOOST_CHECK_NO_THROW(newIntStack = std::move(intStack));

	InitStackWithIntegers(intStack);
	BOOST_CHECK_NO_THROW(intStack.~CMyStack());

	InitStackWithStrings(stringStack);
	CMyStack<std::string> newStringStack;
	BOOST_CHECK_NO_THROW(newStringStack = std::move(stringStack));

	InitStackWithStrings(stringStack);
	BOOST_CHECK_NO_THROW(stringStack.~CMyStack());
}
BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE(Exceptions_are_thrown_when)
BOOST_AUTO_TEST_CASE(pop_element_if_stack_is_empty)
{
	BOOST_CHECK_THROW(intStack.Pop(), std::logic_error);
	BOOST_CHECK_THROW(stringStack.Pop(), std::logic_error);
}
BOOST_AUTO_TEST_CASE(get_top_element_if_stack_is_empty)
{
	BOOST_CHECK_THROW(intStack.GetTopElement(), std::logic_error);
	BOOST_CHECK_THROW(stringStack.GetTopElement(), std::logic_error);
}
BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE_END()