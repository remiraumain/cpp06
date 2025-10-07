/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rraumain <rraumain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/03 18:04:57 by rraumain          #+#    #+#             */
/*   Updated: 2025/10/07 12:46:22 by rraumain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Base.hpp"
#include <ctime>
#include <cstdlib>
#include <iostream>

int main()
{
    std::srand(static_cast<unsigned int>(std::time(0)));

    std::cout << "Test random:\n";
    Base* p = generate();
    identify(p);
    identify(*p);
    
    delete p;

    std::cout << "\nTest avec Base donc unknown:\n";
    Base b;
    identify(&b);
    identify(b);

    std::cout << "\nTest avec NULL donc pointer NULL:\n";
    identify(NULL);

    return (0);
}
