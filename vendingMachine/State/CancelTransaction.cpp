#include "CancelTransaction.h"

CancelTransaction::CancelTransaction (VendingMachine *vendingMachine) : vendingMachine(vendingMachine){};

        void CancelTransaction::selectProduct()  {
            (vendingMachine) -> displayMessage("Cancelling previous transaction ... please wait");
            return;
        }

        void CancelTransaction::collectCash ()  {
            (vendingMachine) -> displayMessage("Cancelling previous transaction ... please wait");
            return;
        }


        void CancelTransaction::dispenseItem ()  {
            (vendingMachine) -> displayMessage("Cancelling previous transaction ... please wait");
            return;
        }

        void CancelTransaction::cancelTransaction()  {
            (vendingMachine) -> displayMessage("Cancelled previous transaction , ready for the next.");
            (vendingMachine) -> setState(new SelectProduct(vendingMachine));

            return;
        }
