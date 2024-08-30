#ifndef COLLECTCASH_H
#define COLLECTCASH_H
#include "../Headers.h"
#include "../VendingMachine/VendingMachine.h"
#include "DispenseItem.h"
#include "CancelTransaction.h"


class CollectCash : public State {
    private:
        VendingMachine * vendingMachine;

    public:
        CollectCash (VendingMachine *vendingMachine);
        void selectProduct() override;
        void collectCash () override;
        void dispenseItem () override;
        void cancelTransaction() override;
};


#endif
