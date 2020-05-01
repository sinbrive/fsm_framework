# fsm_framework

### how to:
1. Create your state and event names (here LOCKED, UNLOCKED, COIN ...)
2. write your transition functions (here lock(), unlock()...)
2. get your transition table and add it by using the method addTransition (here turnstile.addTransition(LOCKED, COIN, unlock, UNLOCKED))
2. write your eventManager (here processEvent()) [no event -> event=-1]

### example of main
```language:c
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
````
