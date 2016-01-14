:- use_module(library(lists )).


remove_item(_,[],[]).

remove_item(E, [H|T1], [H|T2]):-
    H \= E,
    remove_item(E, T1, T2).

remove_item(E, [E|T1], T2):-
    remove_item(E, T1, T2).

drop_items(L, N, NewL):-
    length(L, LL),
    LL > N,
    append(B,NewL,L),
    length(B,N).

drop_items(L, N, []):-
    length(L, LL),
    LL =< N.

drop_more_items(L, N, NewL):-
    append(Begin, End, L),
    length(Begin, N),
    remove_items(L, Begin, NewL).

remove_items(NewL,[],NewL).

remove_items(L, [H|T], RemL):-
    remove_item(H, L, NewL),
    remove_items(NewL, T, RemL).

count(L, Result):-
    setof((X,N),(member(X,L),countX(X,L,N)),Result).

countX(_,[],0).

countX(X,[X|T],N):-
    countX(X,T,M),
    N is M + 1.

countX(X,[H|T],N):-
    X \= H,
    countX(X,T,N).
