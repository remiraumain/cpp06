/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rraumain <rraumain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/03 18:04:57 by rraumain          #+#    #+#             */
/*   Updated: 2025/10/07 12:09:13 by rraumain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Serializer.hpp"
#include <iostream>

int main() 
{
    Data before;
    Data *after;
    uintptr_t raw;

    before.something = 100;
    after = NULL;

    std::cout << "after  addr (unserialized): " << static_cast<void*>(after)  << "\n";
    std::cout << "before addr: " << static_cast<void*>(&before) << "\n";

    raw = Serializer::serialize(&before);
	after = Serializer::deserialize(raw);


    std::cout << "after  addr: " << static_cast<void*>(after)  << "\n";
    std::cout << "raw (uintptr): " << raw << "\n";
    std::cout << "after->something: " << after->something << "\n";

    std::cout << "same pointer: " << (after == &before) << "\n";
    std::cout << "same value: " << (after->something == before.something) << "\n";

    
    uintptr_t rawNull = Serializer::serialize(NULL);
    Data* backNull = Serializer::deserialize(rawNull);
    std::cout << "NULL test: " << (backNull == NULL) << "\n";

    return (0);
}
