/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Serializer.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rraumain <rraumain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/07 11:46:00 by rraumain          #+#    #+#             */
/*   Updated: 2025/10/07 11:58:01 by rraumain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Serializer.hpp"
#include <iostream>

Serializer::Serializer()
{
	std::cout << "Serializer constructed\n";
}

Serializer::Serializer(const Serializer &copy)
{
	(void)copy;
	std::cout << "Serializer copy-constructed\n";
}

Serializer	&Serializer::operator=(const Serializer &copy)
{
	(void)copy;
	std::cout << "Serializer copy-assigned\n";
	return (*this);
}

Serializer::~Serializer()
{
	std::cout << "Serializer destructed\n";
}

uintptr_t	Serializer::serialize(Data *ptr)
{
	return (reinterpret_cast<uintptr_t>(ptr));
}

Data*	Serializer::deserialize(uintptr_t raw)
{
	return (reinterpret_cast<Data *>(raw));
}
