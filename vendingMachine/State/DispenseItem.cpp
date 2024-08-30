#include "DispenseItem.h"

DispenseItem::DispenseItem (VendingMachine *vendingMachine) : vendingMachine(vendingMachine){};

void DispenseItem::selectProduct()  {
    (vendingMachine) -> displayMessage("Dispensing item, hit cancel to cancel");
    return;
}

void DispenseItem::collectCash ()  {
    (vendingMachine) -> displayMessage("Dispensing item, hit cancel to cancel");
    return;
}

void DispenseItem::dispenseItem ()  {
    string productId = (vendingMachine) -> getSelectedProduct();
    unsigned int quantity = (vendingMachine) -> getProductQuantity(productId);

    quantity--;
    (vendingMachine) -> setProductQuantity(productId, quantity);
    (vendingMachine) -> setState(new SelectProduct(vendingMachine));

    return;
}

void DispenseItem::cancelTransaction()  {
    (vendingMachine) -> setState(new CancelTransaction(vendingMachine));
    (vendingMachine) -> cancelTransaction();
    return;
}
