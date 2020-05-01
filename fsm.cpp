/*********************************************************************
sinbrive april 2020
File Decription: Finite State Machine general framework
Application of  wikipedia coin-operated turnstile 
*********************************************************************/
#include <iostream>
#include "fsm.h"

using namespace std;

//states
enum {
    LOCKED = 0,
    UNLOCKED,
};

//events
enum {
    COIN = 0,
    PUSH,
};

void unlock();
void lock();
void nop();

void lock() {
    // do something
    printf("locking...\n");
    printf("\n");
}

void unlock() {
    // do something
    printf("unlocking\n");
    printf("\n");
}

void nop() {
    printf("nop\n\n");
}

//testing
int processEvent() {
    return rand() % 2;
}

int main() {
    fsm turnstile(LOCKED);
    turnstile.addTransition(LOCKED, COIN, unlock, UNLOCKED);
    turnstile.addTransition(UNLOCKED, PUSH, lock, LOCKED);

    int event = -1;

    while (1) {
        event = processEvent();
        printf("event %d is received...\n", event);
        if (event >= 0) turnstile.eventHandler(event); // event<0 no event
        printf("fsm current state %d\n", turnstile.getcurState());

        unsigned int retTime = time(0) + 2;
        while (time(0) < retTime);
    }
    return 0;
}
