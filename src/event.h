#ifndef EVENT_H
#define EVENT_H

typedef enum { 
    None, 
    Quit,
    Solve,
} Action;

Action handleEvents();

#endif // EVENT_H

