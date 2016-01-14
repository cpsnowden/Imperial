:- use_module(library(lists)).

my_last(X,L):-
    length(L,N),
    N > 0,
    M is N - 1,
    length(F,M),
    append(F,[X],L).

last_but_one(X,L):-
    length(L,N),
    N > 1,
    M is N - 2,
    length(F,M),
    append(F,[X|_],L).

element_at(X,L,K):-
    length(L,N),
    N >= K,
    N > 0,
    K > 0,
    M is K - 1,
    length(F,M),
    append(F,[X|_],L).

my_length(L,N):- length(L,N).

my_reverse(L1,L2) :- reverse(L1,L2).

is_palindrome(L) :-
    reverse(L, L1),
    L1 = L.

my_flatten(L1,L2) :-
    
