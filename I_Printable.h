//
// Created by Toor on 2/16/2021.
//

#ifndef BLOCKCHAIN_I_PRINTABLE_H
#define BLOCKCHAIN_I_PRINTABLE_H

#include <iostream>

class I_Printable {

    friend std::ostream &operator<<(std::ostream &os, const I_Printable &obj);

public:
    virtual void print(std::ostream &os) const =0;

    virtual ~I_Printable() =default;

};


#endif //BLOCKCHAIN_I_PRINTABLE_H
