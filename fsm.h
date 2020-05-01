#include <vector>

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
        std::vector <transition> caseTable;
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
