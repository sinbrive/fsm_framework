/*********************************************************************
sinbrive april 2020
forked from :Li Junshi
File Decription: Finite State Machine general framework
*********************************************************************/
#include <iostream>

#include <vector>

using namespace std;

class transition {
    public:
        int state;
        int event;
        void( * eventActFun)();
        int nextState;
};

class fsm {
    private:
        int _g_max_num;
        vector < transition > caseTable;
        int curState; //FSM
        transition * FsmTable; //table d'état

    public:
        fsm(int istate) {
        curState = istate;
        }

    int getCurState() {
        return curState;
    }

    /*state update*/
    void ToNewState(int istate) {
        curState = istate;
    }

    /*event handler */
    void eventHandler(int event) {
        void( * eventAction)() = NULL;
        int currentState = curState;

        for (int j = 0; j < caseTable.size(); j++) {
            /*scan de la table*/
            if (event == caseTable[j].event && currentState == caseTable[j].state) {
                eventAction = caseTable[j].eventActFun;
                if (eventAction) eventAction(); // if  very important 
                ToNewState(caseTable[j].nextState);
                break;
            }
        }
    }

    void addTransition(int state, int event, void( * eventActFun)(), int nextState) {
        transition v;
        v.state = state;
        v.event = event;
        v.eventActFun = eventActFun;
        v.nextState = nextState;
        caseTable.push_back(v);
    }
    int getcurState() {
        return curState;
    }
};

//les états
enum {
    LOCKED = 0,
    UNLOCKED,
};

//les évenments
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