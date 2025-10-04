/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rraumain <rraumain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/03 18:04:57 by rraumain          #+#    #+#             */
/*   Updated: 2025/10/04 21:44:34 by rraumain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ScalarConverter.hpp"
#include <iostream>

int main(int argc, char** argv) 
{
    if (argc != 2) 
	{
        std::cout << "Usage: ./scalar_converter <literal>\n";
        return (1);
    }
	
    ScalarConverter::convert(argv[1]);
	
    return (0);
}
