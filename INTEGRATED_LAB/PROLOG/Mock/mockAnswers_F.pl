:-use_module(library(lists)).


% child_mother(C, M) means C is a child of mother M.
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

child_mother(amy, mary).
child_mother(arthur, mary).
child_mother(angel, jane).
child_mother(anton, rita).
child_mother(alan, rita).
child_mother(axel, susan).
child_mother(ann, tina).    


% age(C, A) means C is of age A.
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

age(amy, 6).
age(arthur, 15).
age(angel, 16).
age(anton, 4).
age(alan, 8).
age(axel, 16).
age(ann, 4).

% employed(X) means X is employed.
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

employed(susan).
employed(rita).

ecb(M):-
    child_mother(C,M),
    age(C,A),
    A =< 14.

ecb(M):- 
    child_mother(C,M),
    \+employed(M),
    age(C,A),
    A>14,
    A=<16.

mother_of_youngest(M):-
    setof(MM,a_mother_of_youngest(MM),[M|_]).

a_mother_of_youngest(M):-
    child_mother(C,M),
    min_age(C).

min_age(C):-
    age(C,A),
\+lower_age(A).

lower_age(A,M):-
    child_mother(C,M),
    age(C,A2),
    A2 < A.

mothers_of_young(LM):-
    setof(M,lower_age(11, M), LM).

merge(L1,L2,L):-
    merge(L1,L2,L,[]).

merge([H1|T1],[H2|T2],L,A):-
    H1 =< H2,
    append(A,[H1],A2),
    merge(T1,[H2|T2],L,A2).

merge([H1|T1],[H2|T2],L,A):-
    H1 > H2,
    append(A,[H2],A2),
    merge([H1|T1],T2,L,A2).

merge([],L2,L,A):-
    append(A,L2,L).

merge(L1,[],L,A):-
    append(A,L1,L).

merge2([],L,L).
merge2(L,[],L).
merge2([X|Xs],[Y|Ys],[X|T]):-
	   X=<Y,
	   merge(Xs,[Y|Ys],T).

merge2([X|Xs],[Y|Ys],[Y|T]):-
	   X>Y,
	   merge([X|Xs],Ys,T).


findElement2(N,L,E):-
    N > 0,
    length(L,LN),
    LN >= N,
    M is N -1,
    append(L1, L2, L),
    length(L1, M),
    L2 = [E|Rest].
		
findElement(N,L,E):-
    length(L,Len),
    N =< Len,
    N >= 1,
    findElement(N,L,E,1).

findElement(N,[H|T],E,Count):-
    N \= Count,
    Count2 is Count + 1,
    findElement(N,T,E,Count2).

findElement(N,[H|_],H,Count):-
    Count = N.
