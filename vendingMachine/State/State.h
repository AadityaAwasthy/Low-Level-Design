#ifndef STATE_H
#define STATE_H


class State {
    public:
        virtual void selectProduct() = 0;
        virtual void collectCash() = 0;
        virtual void dispenseItem() = 0;
        virtual void cancelTransaction() = 0;
};

#endif
