#include "VendingMachine.h"

class VendingMachine {
    private:
        unsigned int collectedCash;
        string selectedProduct;
        map<string, Product *> products;
        map<string, unsigned int> productQuantity;
        State * currentState;


    public:
        VendingMachine() {
            collectedCash = 0;
            products = map<string, Product *>();
            productQuantity = map<string, unsigned int>();
        }

        // Methods to handle products
        void addProduct(string productId, unsigned int quantity) {
            if(!isProductRegistered(productId)) {
                this -> displayMessage("Please register the product first.");
                return;
            }

            productQuantity[productId] += quantity;
            return;
        }

        void registerProduct(Product * newProduct){
            if(isProductRegistered(newProduct -> getProductId())) {
                this -> displayMessage("The product is already registered");
                return;
            }

            products[newProduct -> getProductId()] = newProduct;
            productQuantity[newProduct -> getProductId()] = 0;

            return;
        }

        bool isProductRegistered(string productId) {
            return (products.find(productId) != products.end());
        }

        void setProductQuantity(string productId, int quantity) {
            (this -> productQuantity)[productId] = quantity;
        }

        int getProductQuantity (string productId) {
            return (this -> productQuantity)[productId];
        }

        void displayMessage(string message) {
            cout << "Vending Machine : " << message << endl;
            return;
        }

        void setSelectedProduct(string productId) {
            (this -> selectedProduct) = productId;
        }

        string getSelectedProduct() {
            return (this -> selectedProduct);
        }

        unsigned int getCollectedCash() {
            return (this -> collectedCash);
        }

        void setCollectedCash(unsigned int collectedCash) {
            (this -> collectedCash) = collectedCash;
        }

        void setState(State *newState) {
            this -> currentState = newState;
        }

        Product *getProduct(string productId) {
            return products[productId];
        }

        void buyProduct(string productId, unsigned int collectedCash) {
            setSelectedProduct(productId);
            setCollectedCash(collectedCash);

            (this -> currentState) -> selectProduct();
        }

        void selectProduct () {
            (this -> currentState) -> selectProduct();
            return;
        }

        void collectCash() {
            (this -> currentState) -> collectCash();
            return;
        }

        void dispenseItem() {
            (this -> currentState) -> dispenseItem();
        }

        void cancelTransaction() {
            (this -> currentState) -> cancelTransaction();
            return;
        }
};
