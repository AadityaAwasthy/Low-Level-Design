#ifndef DISPENSEITEM_H
#define DISPENSEITEM_H
#include "../Headers.h"
#include "../VendingMachine/VendingMachine.h"
#include "CancelTransaction.h"

class DispenseItem : public State {
    private:
        VendingMachine * vendingMachine;

    public:
        DispenseItem (VendingMachine *vendingMachine);
        void selectProduct() override;
        void collectCash () override;
        void dispenseItem () override;
        void cancelTransaction() override;
};

#endif
