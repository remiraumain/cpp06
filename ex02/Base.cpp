/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Base.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rraumain <rraumain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/07 12:15:44 by rraumain          #+#    #+#             */
/*   Updated: 2025/10/07 12:46:17 by rraumain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Base.hpp"
#include <iostream>
#include "A.hpp"
#include "B.hpp"
#include "C.hpp"
#include <cstdlib>

Base::~Base()
{
	std::cout << "Base destructed\n";
}

Base	*generate()
{
    int	choice = std::rand() % 3;
    if (choice == 0) 
		return (new A);
    if (choice == 1) 
		return (new B);
    return (new C);
}

void	identify(Base* p)
{
    if (!p) 
		std::cout << "Pointer is NULL\n";
    else if (dynamic_cast<A*>(p))
		std::cout << "A\n";
    else if (dynamic_cast<B*>(p))
		std::cout << "B\n";
    else if (dynamic_cast<C*>(p))
		std::cout << "C\n";
	else
    	std::cout << "Unknown\n";
}

void	identify(Base& p)
{
    try 
	{
		(void)dynamic_cast<A&>(p);
		std::cout << "A\n";
		return;
	} catch (...) {}

    try
	{
		(void)dynamic_cast<B&>(p);
		std::cout << "B\n";
		return;
	} catch (...) {}

    try {
		(void)dynamic_cast<C&>(p);
		std::cout << "C\n";
		return;
	} catch (...) {}
	
    std::cout << "Unknown\n";
}
