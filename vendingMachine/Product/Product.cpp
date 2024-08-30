#include "../Headers.h"
#include "../ProductCodeGenerator/ProductCodeGenerator.h"

class Product {
    private:
        string productId;
        string productName;
        unsigned int price;

    public:
        Product(string productName, unsigned int price) {
            this -> productName = productName;
            this -> price = price;
            this -> productId = ProductCodeGenerator::generate(5);
        }

        string getProductName() {
            return this -> productName;
        }

        string getProductId () {
            return this -> productId;
        }

        unsigned int getPrice () {
            return this -> price;
        }
};
