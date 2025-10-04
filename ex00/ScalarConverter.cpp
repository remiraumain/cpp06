/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ScalarConverter.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rraumain <rraumain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/02 18:09:06 by rraumain          #+#    #+#             */
/*   Updated: 2025/10/04 21:44:37 by rraumain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ScalarConverter.hpp"
#include <iostream>
#include <iomanip>
#include <cerrno>
#include <cmath>
#include <limits>
#include <cstdlib>

ScalarConverter::ScalarConverter()
{
	std::cout << "ScalarConverter constructed\n";
}

ScalarConverter::ScalarConverter(const ScalarConverter &copy)
{
	(void)copy;
	std::cout << "ScalarConverter copy-constructed\n";
}

ScalarConverter	&ScalarConverter::operator=(const ScalarConverter &copy)
{
	(void)copy;
	std::cout << "ScalarConverter copy-assigned\n";
	return (*this);
}

ScalarConverter::~ScalarConverter()
{
	std::cout << "ScalarConverter destructed\n";
}

bool	isDigit(const char c)
{
	return (std::isdigit(static_cast<unsigned char>(c)));
}

bool	isPseudoFloat(const std::string &s)
{
	return (s == "nanf" || s == "+inff" || s == "-inff");
}

bool	isPseudoDouble(const std::string &s)
{
	return (s == "nan" || s == "+inf" || s == "-inf");
}

bool	isCharLiteral(const std::string &s) 
{
	return (s.size() == 1 && !isDigit(s[0]));
}

bool	isIntLiteral(const std::string &s)
{
	if (s.empty()) 
		return (false);
	
	size_t	i = 0;
	if (s[i] == '+' || s[i] == '-') 
	{
		i++;
		if (i == s.size()) 
			return (false);
	}
	while (i < s.size())
	{
		if (!isDigit(s[i]))
			return (false);
		i++;
	}
	return (true);
}

bool	isCorrectDotDigitAndSign(const std::string &s)
{
	bool		hasDot = false;
	bool		hasDigit = false;
	bool		hasDigitAfterDot = false;
	size_t 		i = 0;
	
	if (s[i] == '+' || s[i] == '-')
	{ 
		i++; 
		if (i == s.size())
			return (false);
	}
	
	while (i < s.size())
	{
		if (s[i] == '.')
		{
			if (hasDot)
				return (false);
			hasDot = true;
		}
		else if (isDigit(s[i]))
		{
			hasDigit = true;
			if (hasDot)
				hasDigitAfterDot = true;
		}
		else
			return (false);
		i++;
	}

	return (hasDot && hasDigit && hasDigitAfterDot);
}

bool	isFloatLiteral(const std::string &s)
{
	if (isPseudoFloat(s))
		return (true);

	if (s.size() < 2) 
		return (false);

	if (s[s.size()-1] != 'f') 
		return (false);
	
	std::string	number = s.substr(0, s.size()-1);
	return (isCorrectDotDigitAndSign(number));
}

bool	isDoubleLiteral(const std::string &s)
{
	if (isPseudoDouble(s))
		return (true);

	if (s.empty())
		return (false);
	
	return (isCorrectDotDigitAndSign(s));
}

bool	parseAsDouble(const std::string &s, double &out)
{
	char	*end = 0;
	errno = 0;

	out = std::strtod(s.c_str(), &end);

	if (errno == ERANGE) 
		return (false);
	if (end == s.c_str())
		return (false);
	if (*end != '\0')
		return (false);
	return (true);
}

bool	parseAsLong(const std::string &s, long &out)
{
	char	*end = 0;
	errno = 0;

	out = std::strtol(s.c_str(), &end, 10);
	
	if (errno == ERANGE) 
		return (false);
	if (end == s.c_str())
		return (false);
	if (*end != '\0')
		return (false);
	return (true);
}

bool	isDisplayableChar(int n)
{
	return (n >= 32 && n <= 126);
}

bool	isIntegralDouble(double n)
{
	if (n != n)
		return (false);

	if (n == std::numeric_limits<double>::infinity() ||
		n == -std::numeric_limits<double>::infinity()) 
		return (false);
	
	return (n == std::floor(n));
}

void	printChar(double number, bool isPseudo)
{
    std::cout << "char: ";
    if (isPseudo || number != number 
		|| number < std::numeric_limits<char>::min()
		|| number > std::numeric_limits<char>::max())
    { 
		std::cout << "impossible\n"; 
		return; 
	}
	
    int ascii = static_cast<int>(number);
    if (!isDisplayableChar(ascii)) 
	{ 
		std::cout << "Non displayable\n";
		return;
	}
	
    std::cout << "'" << static_cast<char>(ascii) << "'\n";
}

void	printInt(double number, bool isPseudo)
{
    std::cout << "int: ";
    if (isPseudo || number != number
		|| number < std::numeric_limits<int>::min()
		|| number > std::numeric_limits<int>::max())
    { 
		std::cout << "impossible\n";
		return;
	}
	
    std::cout << static_cast<int>(number) << "\n";
}

void	printFloat(double number, bool isPseudo)
{
    std::cout << "float: ";
    if (isPseudo)
	{
		if (number != number)
			std::cout << "nanf\n";
		else
			std::cout << (number > 0 ? "+inff" : "-inff") << "\n";
        return;
    }
    
	if ( number != number
		|| std::fabs(number) > static_cast<double>(std::numeric_limits<float>::max()))
	{
		std::cout << "impossible\n"; 
		return;
	}

    float res = static_cast<float>(number);
    std::cout	<< std::fixed
				<< std::setprecision(isIntegralDouble(number) ? 1 : 6)
				<< res << "f\n";
}

void	printDouble(double number, bool isPseudo)
{
    std::cout << "double: ";
    if (isPseudo) 
	{
		if (number != number)
			std::cout << "nan\n";
		else
		    std::cout << (number > 0 ? "+inf" : "-inf") << "\n";
        return;
    }
	
	if (number != number
		|| std::fabs(number) > std::numeric_limits<double>::max())
	{
		std::cout << "impossible\n";
		return;
	}
    std::cout	<< std::fixed 
				<< std::setprecision(isIntegralDouble(number) ? 1 : 6) 
				<< number << "\n";
}

void	ScalarConverter::convert(const std::string &literal)
{
    if (isCharLiteral(literal))
	{
        unsigned char	c = static_cast<unsigned char>(literal[0]);
        double			ascii = static_cast<double>(c);
        printChar(ascii, false);
        printInt(ascii, false);
        printFloat(ascii, false);
        printDouble(ascii, false);
        return;
    }

    if (isPseudoFloat(literal)) 
	{
        double	ascii;
		if (literal[0] == '-')
			ascii = -std::numeric_limits<double>::infinity();
		else if (literal[0] == '+')
			ascii = std::numeric_limits<double>::infinity();
		else
			ascii = std::numeric_limits<double>::quiet_NaN();
        printChar(ascii, true);
        printInt(ascii, true);
        printFloat(ascii, true);
        printDouble(ascii, true);
        return;
    }

    if (isPseudoDouble(literal))
	{
		double ascii;
		if (literal[0] == '-')
			ascii = -std::numeric_limits<double>::infinity();
		else if (literal == "nan")
			ascii = std::numeric_limits<double>::quiet_NaN();
		else
			ascii = std::numeric_limits<double>::infinity();
        printChar(ascii, true);
        printInt(ascii, true);
        printFloat(ascii, true);
        printDouble(ascii, true);
        return;
    }

    if (isIntLiteral(literal))
	{
        long resL;
        if (!parseAsLong(literal, resL)
			|| resL < std::numeric_limits<int>::min()
			|| resL > std::numeric_limits<int>::max())
        {
            double resD;
            if (!parseAsDouble(literal, resD)) {
                std::cout	<< "char: impossible\n"
							<< "int: impossible\n"
							<< "float: impossible\n"
							<< "double: impossible\n";
                return;
            }
            printChar(resD, false);
            printInt(resD, false);
            printFloat(resD, false);
            printDouble(resD, false);
            return;
        }
        double ascii = static_cast<double>(static_cast<int>(resL));
        printChar(ascii, false);
        printInt(ascii, false);
        printFloat(ascii, false);
        printDouble(ascii, false);
        return;
    }

    if (isFloatLiteral(literal))
	{
        std::string number = literal.substr(0, literal.size() - 1);
        double res;
        if (!parseAsDouble(number, res))
		{
            std::cout	<< "char: impossible\n"
						<< "int: impossible\n"
						<< "float: impossible\n"
						<< "double: impossible\n";
			return;
        }
        printChar(res, false);
        printInt(res, false);
        printFloat(res, false);
        printDouble(res, false);
        return;
    }

    if (isDoubleLiteral(literal)) {
        double res;
        if (!parseAsDouble(literal, res)) {
            std::cout	<< "char: impossible\n"
						<< "int: impossible\n"
						<< "float: impossible\n"
						<< "double: impossible\n";
			return;
        }
        printChar(res, false);
        printInt(res, false);
        printFloat(res, false);
        printDouble(res, false);
        return;
    }

	std::cout	<< "char: impossible\n"
				<< "int: impossible\n"
				<< "float: impossible\n"
				<< "double: impossible\n";
}