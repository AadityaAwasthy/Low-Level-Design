#ifndef PRODUCT_H
#define PRODUCT_H
#include "../Headers.h"

class Product {
    private:
        string productId;
        string productName;
        unsigned int price;

    public:
        Product(string productName, unsigned int price);
        string getProductName();
        string getProductId ();
        unsigned int getPrice ();
};

#endif
