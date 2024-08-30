#include "CollectCash.h"


CollectCash::CollectCash (VendingMachine *vendingMachine) : vendingMachine(vendingMachine) {};

void CollectCash::selectProduct()  {
    (vendingMachine) -> displayMessage("Collecting cash for previous selection, cancel to select again...");
    return;
}

void CollectCash::collectCash ()  {
    unsigned int collectCash = (vendingMachine) -> getCollectedCash();
    string productId = (vendingMachine) -> getSelectedProduct();

    unsigned int priceOfProduct = (vendingMachine -> getProduct(productId)) -> getPrice();

    if(collectCash < priceOfProduct) {
        (vendingMachine) -> displayMessage("not enough cash, cancelling transaction.");
        (vendingMachine) -> setState(new CancelTransaction(vendingMachine));
        return;
    }

    unsigned int change = collectCash - priceOfProduct;
    if(change > 0) {
        (vendingMachine) -> displayMessage("Returning change.");
    }

    (vendingMachine) -> setState(new DispenseItem(vendingMachine));
    (vendingMachine) -> dispenseItem();

    return;
}


void CollectCash::dispenseItem ()  {
    (vendingMachine) -> displayMessage("Collecting cash for previous selection, cancel to select again...");
    return;
}

void CollectCash::cancelTransaction()  {
    (vendingMachine) -> setState(new CancelTransaction(vendingMachine));
    (vendingMachine) -> cancelTransaction();
    return;
}
