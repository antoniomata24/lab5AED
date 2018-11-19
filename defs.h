/*
 *  File name: defs.h
 *
 *  Author: 2013 Fall Semester AED Team
 *
 *  Release date: 2013/10/04
 *                2018/11/12, AED Team
 *
 *  Description: Header file for an abstract type.
 *
 *  Data type list:
 *    Item
 *
 *  Function list:
 *    None
 *
 *  Dependencies:
 *    None
 *
 *  Version: 1.0
 *
 *  Change log: N/A
 *
 */


/* Prevent multiple inclusions                                      */
#ifndef defsHeader
#define defsHeader

/*
 *  Data type: Item
 *
 *  Description: Pointer to void.
 */
typedef void * Item;
typedef struct node link;
typedef struct _graph Graph;
struct node {int v; int weight; link *next;};
struct _graph{int V; int E; link **adj;};
typedef struct _edge{
  int v;
  int w;
} Edge;

Graph *GRAPHinit(int );
void GRAPHinsertE(Graph *, Edge *, int);
link *NEW(int , link *, int);

/* End of: Protect multiple inclusions                              */
#endif
