/*********************************************************************
sinbrive april 2020
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

class _FSM_t {
    private:
        int curState; //FSM
    transition * FsmTable; //table d'état

    public:

        int getCurState() {
            return curState;
        }

    void setCurState(int state) {
        curState = state;
    }

    // setFsmTable(transition *t){
    // 	FsmTable=t;
    // }
};

class fsm {

    private:
        int _g_max_num;
    _FSM_t pFsm;
    vector < transition > caseTable;

    public:
        fsm(int istate) {
            //	_g_max_num = sizeof(turnstileTable) / sizeof(transition);
            pFsm.setCurState(istate);
            //pFsm.setFsmTable(&caseTable[0]);
        }
    /*state update*/
    void _FSM_ToNewState(int state) {
        pFsm.setCurState(state);
    }

    /*event handler */
    void _FSM_EventHandle(int event) {
        void( * eventAction)() = NULL;
        int currentState = pFsm.getCurState();

        for (int j = 0; j < caseTable.size(); j++) {
            /*scan de la table*/
            if (event == caseTable[j].event && currentState == caseTable[j].state) {
                eventAction = caseTable[j].eventActFun;
                if (eventAction) eventAction(); // if  very important 
                _FSM_ToNewState(caseTable[j].nextState);
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
        return pFsm.getCurState();
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
int _g_max_num; //le nombre d'états

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

    int event = COIN;

    while (1) {
        printf("event %d is coming...\n", event);
        if (event >= 0) turnstile._FSM_EventHandle(event); // event<0 no event
        printf("fsm current state %d\n", turnstile.getcurState());
        event = processEvent();

        unsigned int retTime = time(0) + 2;
        while (time(0) < retTime);
    }
    return 0;
}