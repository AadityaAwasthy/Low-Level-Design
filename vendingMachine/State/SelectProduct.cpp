#include "SelectProduct.h"  // Include the header file for SelectProduct
#include "CollectCash.h"

SelectProduct::SelectProduct(VendingMachine* vendingMachine) : vendingMachine(vendingMachine) {}

void SelectProduct::selectProduct() {
    std::string productId = vendingMachine->getSelectedProduct();
    unsigned int collectedCash = vendingMachine->getCollectedCash();

    if (!vendingMachine->isProductRegistered(productId) || vendingMachine->getProductQuantity(productId) == 0) {
        vendingMachine->displayMessage("This product is not available.");
        return;
    }

    // Transition to CollectCash state
    vendingMachine->setState(new CollectCash(vendingMachine));
    vendingMachine->collectCash();
}

void SelectProduct::collectCash() {
    vendingMachine->displayMessage("Please select item first.");
}

void SelectProduct::dispenseItem() {
    vendingMachine->displayMessage("Please select item first.");
}

void SelectProduct::cancelTransaction() {
    vendingMachine->displayMessage("Please select item first.");
    vendingMachine->cancelTransaction();
}

