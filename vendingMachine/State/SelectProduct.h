#ifndef SELECTPRODUCT_H
#define SELECTPRODUCT_H
#include "../Headers.h"
#include "../VendingMachine/VendingMachine.h"

class SelectProduct : public State {
    private:
        VendingMachine *vendingMachine;

    public:
        SelectProduct (VendingMachine *vendingMachine);
        void selectProduct () override;
        void collectCash () override;
        void dispenseItem() override;
        void cancelTransaction() override;
};

#endif

