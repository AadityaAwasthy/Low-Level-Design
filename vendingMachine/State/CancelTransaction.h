#ifndef CANCELTRANSACTION_H
#define CANCELTRANSACTION_H
#include "../Headers.h"
#include "../VendingMachine/VendingMachine.h"
#include "SelectProduct.h"


class CancelTransaction : public State {
    private:
        VendingMachine * vendingMachine;

    public:
        CancelTransaction (VendingMachine *vendingMachine);
        void selectProduct() override; 
        void collectCash () override;
        void dispenseItem () override;
        void cancelTransaction() override;
};

#endif
