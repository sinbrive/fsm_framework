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
        std::vector <transition> fsmTable;
        int curState; 

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

        for (int j = 0; j < fsmTable.size(); j++) {
            if (event == fsmTable[j].event && currentState == fsmTable[j].state) {
                eventAction = fsmTable[j].eventActFun;
                if (eventAction) eventAction();  
                ToNewState(fsmTable[j].nextState);
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
        fsmTable.push_back(v);
    }
		
    int getcurState() {
        return curState;
    }
};
