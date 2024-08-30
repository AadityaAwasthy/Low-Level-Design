#ifndef VENDINGMACHINE_H
#define VENDINGMACHINE_H
#include "../Headers.h"
#include "../State/State.h"
#include "../Product/Product.h"


class VendingMachine {
    private:
        unsigned int collectedCash;
        string selectedProduct;
        map<string, Product *> products;
        map<string, unsigned int> productQuantity;
        State * currentState;


    public:
        VendingMachine();

        // Methods to handle products
        void addProduct(string productId, unsigned int quantity);
        void registerProduct(Product * newProduct);
        bool isProductRegistered(string productId);
        void setProductQuantity(string productId, int quantity);
        int getProductQuantity (string productId);
        void displayMessage(string message);
        void setSelectedProduct(string productId);
        string getSelectedProduct();
        unsigned int getCollectedCash();
        void setCollectedCash(unsigned int collectedCash);
        void setState(State *newState);
        Product *getProduct(string productId);
        void buyProduct(string productId, unsigned int collectedCash);

        void selectProduct ();
        void collectCash();
        void dispenseItem();
        void cancelTransaction();
};

#endif
