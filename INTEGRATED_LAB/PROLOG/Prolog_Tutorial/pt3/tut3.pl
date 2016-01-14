/*mysort(L,SL) SL is list L sorted and all duplicates removed.*/
mysort(L1,L2):-
    setof(X,member(X,L1),L2).

/*rev(L, RevL) RevL is list L with the order of its elements reversed*/
rev([],[]).

rev([H|T],L):-
    rev(T,R),
    append(R,[H],L).

/*followedBy(X,Y,L) X is followed by Y on list L*/
followedBy(H,Y,[H,Y|_]).

followedBy(X,Y,[_|T]):-
   followedBy(X,Y,T).

/*nextTo(X,Y,L) X and Y are next to one another on list L*/
nextTo(H,Y,[H,Y|_]).
nextTo(H,Y,[Y,H|_]).

nextTo(X,Y,[_|T]):-
    nextTo(X,Y,T).

/*sumList(L,S) S is the sum of all integers on list L.*/
sumList([],0).

sumList([H|T],S):-
    sumList(T,SS),
    S is SS + H.

/*last(E,L) that finds the last element E of a list L.*/
last(H,[H|[]]).

last(E,[_|T]):-
    last(E,T).

/*edge(X,Y) stating that there is an edge from node X to node Y.*/

edge(a,b).
edge(b,c).
edge(c,d).
edge(a,e).
edge(e,f).
edge(f,d).
edge(f,c).

/*path(X,Y) that determines if there is path from node X to node Y.*/

path(Y,Y).

path(X,Y):-
    edge(X,Z),
    path(Z,Y).


/*path/3 such that path(X,Y,P) succeeds when P is a path from
 node X to node Y.*/

path(Y,Y,[Y]).

path(X,Y,[X,Y]):-
    edge(X,Y).

path(X,Y,[X,Z|T]):-
    edge(X,Z),
    path(Z,Y,[Z|T]).

/*max(E,L) that determines the maximum element E of a list L.*/

max(T,[T]).

max(E,[H|T]):-
    T\=[],
    max(F,T),
    (F>H -> E=F; E=H).

/*max_of_all(E, Ls) to find the maximum element E of a list of lists Ls*/

max_of_all(E,L):-
    setof(X,max_it(X,L),L2),
    last(E,L2).

max_it(X,[H|T]):-
    max(X,H);max_it(X,T).

max_of_all2(E,[T]):-
    T\=[],
    max(E,T).

max_of_all2(E,[H|T]):-
    T\=[],
    max(G,H),
    max_of_all2(F,T),
    (F>G -> E=F; E=G).

max_of_all3(E,[T]):-
    T\=[],
    max(E,T).

max_of_all3(E,[H|T]):-
    T\=[],
    max(G,H),
    max_of_all3(F,T),
    F>G -> E=F; E=G.
    
/*This will fail as it is trying to solve This

max_of_all3(E,[H|T]):-
    (T\=[],
    max(G,H),
    max_of_all3(F,T),
    F>G) -> (E=F); (E=G).

if use this query: max_of_all3(X,[[1,2,3],[1,2,1]]). then F is not > G so will fail as an F cannot be found */


