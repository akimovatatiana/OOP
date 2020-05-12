// RationalTests.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "../Rational/Rational.h"

BOOST_AUTO_TEST_CASE(Test_Greates_Common_Denominator)
{
	BOOST_CHECK_EQUAL(GCD(2, 3), 1u);
	BOOST_CHECK_EQUAL(GCD(3, 2), 1u);
	BOOST_CHECK_EQUAL(GCD(12, 8), 4u);
	BOOST_CHECK_EQUAL(GCD(8, 12), 4u);
	BOOST_CHECK_EQUAL(GCD(0, 2), 2u);
	BOOST_CHECK_EQUAL(GCD(2, 0), 2u);
	BOOST_CHECK_EQUAL(GCD(0, 0), 1u);
}

void VerifyRational(const CRational & rational, int expectedNumerator, int expectedDenominator)
{
	BOOST_CHECK_EQUAL(rational.GetNumerator(), expectedNumerator);
	BOOST_CHECK_EQUAL(rational.GetDenominator(), expectedDenominator);
}

BOOST_AUTO_TEST_SUITE(Rational_number)
	BOOST_AUTO_TEST_CASE(is_0_by_default)
	{
		VerifyRational(CRational(), 0, 1);
	}
	BOOST_AUTO_TEST_CASE(can_be_constructed_from_integer)
	{
		VerifyRational(CRational(10), 10, 1);
		VerifyRational(CRational(-10), -10, 1);
		VerifyRational(CRational(0), 0, 1);
	}
	BOOST_AUTO_TEST_CASE(can_be_constructed_with_numerator_and_denominator)
	{
		VerifyRational(CRational(5, 2), 5, 2);
		VerifyRational(CRational(-5, 2), -5, 2);
		VerifyRational(CRational(5, -2), -5, 2);
		VerifyRational(CRational(-5, -2), 5, 2);
	}
	BOOST_AUTO_TEST_CASE(is_normalized_after_construction)
	{
		VerifyRational(CRational(6, 8), 3, 4);
		VerifyRational(CRational(6, -8), -3, 4);
		VerifyRational(CRational(-6, 8), -3, 4);
		VerifyRational(CRational(-6, -8), 3, 4);
		VerifyRational(CRational(-10, 20), -1, 2);
	}
	BOOST_AUTO_TEST_CASE(cant_have_zero_denominator)
	{
		BOOST_REQUIRE_THROW(CRational(1, 0), std::invalid_argument);
	}

	BOOST_AUTO_TEST_CASE(can_be_converted_to_double)
	{
		BOOST_CHECK_CLOSE(CRational().ToDouble(), 0, DBL_EPSILON);
		BOOST_CHECK_CLOSE(CRational(1).ToDouble(), 1, DBL_EPSILON);
		BOOST_CHECK_CLOSE(CRational(-1).ToDouble(), -1, DBL_EPSILON);
		BOOST_CHECK_CLOSE(CRational(3, 5).ToDouble(), 0.6, DBL_EPSILON);
		BOOST_CHECK_CLOSE(CRational(-3, 5).ToDouble(), -0.6, DBL_EPSILON);
		BOOST_CHECK_CLOSE(CRational(3, -5).ToDouble(), -0.6, DBL_EPSILON);
		BOOST_CHECK_CLOSE(CRational(-3, -5).ToDouble(), 0.6, DBL_EPSILON);
	}

	BOOST_AUTO_TEST_SUITE(can_use_unary_operators)
	BOOST_AUTO_TEST_CASE(unary_plus_returns_same_number)
	{
		VerifyRational(+CRational(), 0, 1);
		VerifyRational(+CRational(1), 1, 1);
		VerifyRational(+CRational(3, 5), 3, 5);
		VerifyRational(+CRational(-3, 5), -3, 5);
		VerifyRational(+CRational(-3, -5), 3, 5);
	}
	BOOST_AUTO_TEST_CASE(unary_minus_returns_opposite_number)
	{
		VerifyRational(-CRational(), 0, 1);
		VerifyRational(-CRational(1), -1, 1);
		VerifyRational(-CRational(3, 5), -3, 5);
		VerifyRational(-CRational(-3, 5), 3, 5);
		VerifyRational(-CRational(-3, -5), -3, 5);
	}
	BOOST_AUTO_TEST_SUITE_END()

	BOOST_AUTO_TEST_SUITE(can_be_converted_to_mixed_fraction)
	BOOST_AUTO_TEST_CASE(with_positive_rational)
	{
		BOOST_CHECK_EQUAL(CRational(9, 4).ToCompoundFraction().first, 2);
		BOOST_CHECK_EQUAL(CRational(9, 4).ToCompoundFraction().second, CRational(1, 4));
	}
	BOOST_AUTO_TEST_CASE(with_negative_rational)
	{
		BOOST_CHECK_EQUAL(CRational(-9, 4).ToCompoundFraction().first, -2);
		BOOST_CHECK_EQUAL(CRational(-9, 4).ToCompoundFraction().second, CRational(-1, 4));
	}
	BOOST_AUTO_TEST_CASE(with_rational_without_integer_part)
	{
		BOOST_CHECK_EQUAL(CRational(1, 2).ToCompoundFraction().first, 0);
		BOOST_CHECK_EQUAL(CRational(1, 2).ToCompoundFraction().second, CRational(1, 2));
	}
	BOOST_AUTO_TEST_SUITE_END()

	BOOST_AUTO_TEST_SUITE(binary_plus_returns_sum_of_two_numbers)
	BOOST_AUTO_TEST_CASE(with_two_positive_rational)
	{
		CRational number1(1, 2);
		CRational number2(1, 6);
		CRational result = number1 + number2;
		VerifyRational(result, 2, 3);
	}
	BOOST_AUTO_TEST_CASE(with_two_negative_rational)
	{
		CRational number1(-1, 2);
		CRational number2(-1, 6);
		CRational result = number1 + number2;
		VerifyRational(result, -2, 3);
	}
	BOOST_AUTO_TEST_CASE(with_two_positive_integer)
	{
		int number1 = 1;
		int number2 = 2;
		CRational result = number1 + number2;
		VerifyRational(result, 3, 1);
	}
	BOOST_AUTO_TEST_CASE(with_two_negative_integer)
	{
		int number1 = -1;
		int number2 = -2;
		CRational result = number1 + number2;
		VerifyRational(result, -3, 1);
	}
	BOOST_AUTO_TEST_CASE(with_rational_and_integer)
	{
		CRational number1(1, 2);
		int number2 = 1;
		CRational result = number1 + number2;
		VerifyRational(result, 3, 2);
	}
	BOOST_AUTO_TEST_CASE(with_integer_and_rational)
	{
		int number1 = 1;
		CRational number2(1, 2);
		CRational result = number1 + number2;
		VerifyRational(result, 3, 2);
	}

	BOOST_AUTO_TEST_SUITE_END()

	BOOST_AUTO_TEST_SUITE(binary_minus_returns_difference_of_two_numbers)
	BOOST_AUTO_TEST_CASE(with_two_positive_rationals)
	{
		CRational number1(1, 2);
		CRational number2(1, 6);
		CRational result = number1 - number2;
		VerifyRational(result, 1, 3);
	}
	BOOST_AUTO_TEST_CASE(with_two_negative_rationals)
	{
		CRational number1(-1, 2);
		CRational number2(-1, 6);
		CRational result = number1 - number2;
		VerifyRational(result, -1, 3);
	}
	BOOST_AUTO_TEST_CASE(with_rational_and_integer)
	{
		CRational number1(1, 2);
		int number2 = 1;
		CRational result = number1 - number2;
		VerifyRational(result, -1, 2);
	}
	BOOST_AUTO_TEST_CASE(with_integer_and_rational)
	{
		int number1 = 1;
		CRational number2(1, 2);
		CRational result = number1 - number2;
		VerifyRational(result, 1, 2);
	}
	BOOST_AUTO_TEST_SUITE_END()

	BOOST_AUTO_TEST_SUITE(can_be_increased_by_additional)
	BOOST_AUTO_TEST_CASE(with_second_rational)
	{
		CRational number1(1, 2);
		CRational number2(1, 6);
		number1 += number2;
		VerifyRational(number1, 2, 3);
	}
	BOOST_AUTO_TEST_CASE(with_second_integers)
	{
		CRational number1(1, 2);
		int number2 = 1;
		number1 += number2;
		VerifyRational(number1, 3, 2);
	}
	BOOST_AUTO_TEST_SUITE_END()

	BOOST_AUTO_TEST_SUITE(can_be_decreased_by_subtraction)
	BOOST_AUTO_TEST_CASE(with_second_rational)
	{
		CRational number1(1, 2);
		CRational number2(1, 6);
		number1 -= number2;
		VerifyRational(number1, 1, 3);
	}
	BOOST_AUTO_TEST_CASE(with_second_integer)
	{
		CRational number1(1, 2);
		int number2 = 1;
		number1 -= number2;
		VerifyRational(number1, -1, 2);
	}
	BOOST_AUTO_TEST_SUITE_END()

	BOOST_AUTO_TEST_SUITE(multiplication_operator_returns_composition_of_two_numbers)
	BOOST_AUTO_TEST_CASE(with_two_positive_rationals)
	{
		CRational number1(1, 2);
		CRational number2(2, 3);
		CRational result = number1 * number2;
		VerifyRational(result, 1, 3);
	}
	BOOST_AUTO_TEST_CASE(with_two_negative_rationals)
	{
		CRational number1(-1, 2);
		CRational number2(-1, 6);
		CRational result = number1 * number2;
		VerifyRational(result, 1, 12);
	}
	BOOST_AUTO_TEST_CASE(with_rational_and_integer)
	{
		CRational number1(1, 2);
		int number2 = -3;
		CRational result = number1 * number2;
		VerifyRational(result, -3, 2);
	}
	BOOST_AUTO_TEST_CASE(with_integer_and_rational)
	{
		int number1 = 3;
		CRational number2(3, 2);
		CRational result = number1 * number2;
		VerifyRational(result, 9, 2);
	}
	BOOST_AUTO_TEST_SUITE_END()

	BOOST_AUTO_TEST_SUITE(division_operator_returns_quotient_of_two_numbers)
	BOOST_AUTO_TEST_CASE(with_two_positive_rationals)
	{
		CRational number1(1, 2);
		CRational number2(2, 3);
		CRational result = number1 / number2;
		VerifyRational(result, 3, 4);
	}
	BOOST_AUTO_TEST_CASE(with_two_negative_rationals)
	{
		CRational number1(-1, 2);
		CRational number2(-1, 6);
		CRational result = number1 / number2;
		VerifyRational(result, 3, 1);
	}
	BOOST_AUTO_TEST_CASE(with_rational_and_integer)
	{
		CRational number1(1, 2);
		int number2 = 5;
		CRational result = number1 / number2;
		VerifyRational(result, 1, 10);
	}
	BOOST_AUTO_TEST_CASE(with_integer_and_rational)
	{
		int number1 = 7;
		CRational number2(3, 2);
		CRational result = number1 * number2;
		VerifyRational(result, 21, 2);
	}
	BOOST_AUTO_TEST_SUITE_END()

	BOOST_AUTO_TEST_SUITE(can_be_increased_by_multiplication)
	BOOST_AUTO_TEST_CASE(with_second_rational)
	{
		CRational number1(1, 2);
		CRational number2(2, 3);
		number1 *= number2;
		VerifyRational(number1, 1, 3);
	}
	BOOST_AUTO_TEST_CASE(with_second_integer)
	{
		CRational number1(1, 2);
		int number2 = 3;
		number1 *= number2;
		VerifyRational(number1, 3, 2);
	}
	BOOST_AUTO_TEST_SUITE_END()

	BOOST_AUTO_TEST_SUITE(can_be_decreased_by_division)
	BOOST_AUTO_TEST_CASE(with_second_rational)
	{
		CRational number1(1, 2);
		CRational number2(2, 3);
		number1 /= number2;
		VerifyRational(number1, 3, 4);
	}
	BOOST_AUTO_TEST_CASE(with_second_integer)
	{
		CRational number1(1, 2);
		int number2 = 3;
		number1 /= number2;
		VerifyRational(number1, 1, 6);
	}
	BOOST_AUTO_TEST_SUITE_END()

	BOOST_AUTO_TEST_SUITE(can_be_compared_on_equality)
	BOOST_AUTO_TEST_CASE(with_two_rationals)
	{
		BOOST_CHECK(CRational(1, 2) == CRational(1, 2)); 
		BOOST_CHECK(!(CRational(1, 3) == CRational(1, 2)));
		BOOST_CHECK(!(CRational() == CRational(1)));
		BOOST_CHECK(CRational() == CRational(0, 1));
	}
	BOOST_AUTO_TEST_CASE(with_rational_and_integer)
	{
		BOOST_CHECK(CRational(3, 1) == 3);
		BOOST_CHECK(!(CRational(1, 3) == 3));
		BOOST_CHECK(!(CRational() == 1));
		BOOST_CHECK(CRational() == 0);
	}
	BOOST_AUTO_TEST_CASE(with_integer_and_rational)
	{
		BOOST_CHECK(3 == CRational(3, 1));
		BOOST_CHECK(!(3 == CRational(1, 3)));
		BOOST_CHECK(!(1 == CRational()));
		BOOST_CHECK(0 == CRational());
	}
	BOOST_AUTO_TEST_SUITE_END()

	BOOST_AUTO_TEST_SUITE(can_be_compared_on_inequality)
	BOOST_AUTO_TEST_CASE(with_two_rationals)
	{
		BOOST_CHECK(!(CRational(1, 2) != CRational(1, 2)));
		BOOST_CHECK(CRational(1, 3) != CRational(1, 2));
		BOOST_CHECK(CRational() != CRational(1));
		BOOST_CHECK(!(CRational() != CRational(0, 1)));
	}
	BOOST_AUTO_TEST_CASE(with_rational_and_integer)
	{
		BOOST_CHECK(!(CRational(3, 1) != 3));
		BOOST_CHECK(CRational(1, 3) != 3);
		BOOST_CHECK(CRational() != 1);
		BOOST_CHECK(!(CRational() != 0));
	}
	BOOST_AUTO_TEST_CASE(with_integer_and_rational)
	{
		BOOST_CHECK(!(3 != CRational(3, 1)));
		BOOST_CHECK(3 != CRational(1, 3));
		BOOST_CHECK(1 != CRational());
		BOOST_CHECK(!(0 != CRational()));
	}
	BOOST_AUTO_TEST_SUITE_END()

	BOOST_AUTO_TEST_SUITE(can_be_greater)
	BOOST_AUTO_TEST_CASE(with_two_rationals)
	{
		BOOST_CHECK(CRational(1, 2) > CRational(1, 3));
		BOOST_CHECK(!(CRational(1, 3) > CRational(1, 2)));
	}
	BOOST_AUTO_TEST_CASE(with_rational_and_integer)
	{
		BOOST_CHECK(CRational(3, 1) > 2);
		BOOST_CHECK(!(CRational(1, 2) > 3));
	}
	BOOST_AUTO_TEST_CASE(with_integer_and_rational)
	{
		BOOST_CHECK(3 > CRational(2, 1));
		BOOST_CHECK(!(3 > CRational(4, 1)));
	}
	BOOST_AUTO_TEST_SUITE_END()

	BOOST_AUTO_TEST_SUITE(can_be_less)
	BOOST_AUTO_TEST_CASE(with_two_rationals)
	{
		BOOST_CHECK(!(CRational(1, 2) < CRational(1, 3)));
		BOOST_CHECK(CRational(1, 3) < CRational(1, 2));
	}
	BOOST_AUTO_TEST_CASE(with_rational_and_integer)
	{
		BOOST_CHECK(!(CRational(3, 1) < 2));
		BOOST_CHECK(CRational(1, 2) < 3);
	}
	BOOST_AUTO_TEST_CASE(with_integer_and_rational)
	{
		BOOST_CHECK(!(3 < CRational(2, 1)));
		BOOST_CHECK(3 < CRational(4, 1));
	}
	BOOST_AUTO_TEST_SUITE_END()

	BOOST_AUTO_TEST_SUITE(can_be_greater_or_equal)
	BOOST_AUTO_TEST_CASE(with_two_rationals)
	{
		BOOST_CHECK(CRational(2, 1) >= CRational(2, 1));
		BOOST_CHECK(CRational(1, 2) >= CRational(1, 2));
		BOOST_CHECK(CRational(1, 2) >= CRational(1, 3));
		BOOST_CHECK(!(CRational(1, 3) >= CRational(1, 2)));
	}
	BOOST_AUTO_TEST_CASE(with_rational_and_integer)
	{
		BOOST_CHECK(CRational(3, 1) >= 2);
		BOOST_CHECK(CRational(3, 1) >= 3);
		BOOST_CHECK(!(CRational(1, 2) >= 3));
	}
	BOOST_AUTO_TEST_CASE(with_integer_and_rational)
	{
		BOOST_CHECK(3 >= CRational(2, 1));
		BOOST_CHECK(2 >= CRational(2, 1));
		BOOST_CHECK(!(3 >= CRational(4, 1)));
	}
	BOOST_AUTO_TEST_SUITE_END()

	BOOST_AUTO_TEST_SUITE(can_be_less_or_equal)
	BOOST_AUTO_TEST_CASE(with_two_rationals)
	{
		BOOST_CHECK(!(CRational(1, 2) <= CRational(1, 3)));
		BOOST_CHECK(CRational(1, 3) <= CRational(1, 2));
		BOOST_CHECK(CRational(1, 3) <= CRational(1, 3));
	}
	BOOST_AUTO_TEST_CASE(with_rational_and_integer)
	{
		BOOST_CHECK(!(CRational(3, 1) <= 2));
		BOOST_CHECK(CRational(1, 2) <= 3);
		BOOST_CHECK(CRational(3, 1) <= 3);
	}
	BOOST_AUTO_TEST_CASE(with_integer_and_rational)
	{
		BOOST_CHECK(!(3 <= CRational(2, 1)));
		BOOST_CHECK(3 <= CRational(4, 1));
		BOOST_CHECK(4 <= CRational(4, 1));
	}
	BOOST_AUTO_TEST_SUITE_END()

	BOOST_AUTO_TEST_SUITE(can_be_output_to_ostream)
	BOOST_AUTO_TEST_CASE(with_rational)
	{
		CRational rational(4, 19);
		std::stringstream stream;
		stream << rational;
		BOOST_CHECK_EQUAL(stream.str(), "4/19");
	}
	BOOST_AUTO_TEST_CASE(with_negative_rational)
	{
		CRational rational(-4, 19);
		std::stringstream stream;
		stream << rational;
		BOOST_CHECK_EQUAL(stream.str(), "-4/19");
	}
	BOOST_AUTO_TEST_SUITE_END()

	BOOST_AUTO_TEST_SUITE(can_be_input_from_istream)
	BOOST_AUTO_TEST_CASE(with_positive_rational)
	{
		CRational rational;
		std::istringstream stream("7/15");
		stream >> rational;
		VerifyRational(rational, 7, 15);
	}
	BOOST_AUTO_TEST_CASE(with_negative_rational)
	{
		CRational rational;
		std::istringstream stream("-7/15");
		stream >> rational;
		VerifyRational(rational, -7, 15);
	}
	BOOST_AUTO_TEST_CASE(with_rational_with_negative_denominator)
	{
		CRational rational;
		std::istringstream stream("-7/-15");
		stream >> rational;
		VerifyRational(rational, 7, 15);
	}
	BOOST_AUTO_TEST_CASE(with_string_fails)
	{
		CRational rational;
		std::istringstream stream("string");
		stream >> rational;
		BOOST_CHECK(stream.fail());
	}
	BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE_END()
