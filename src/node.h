#ifndef NODE_H
#define NODE_H

struct Node {
    char code ;
    struct Node** child ;
    char child_count ;
} ;

#endif
