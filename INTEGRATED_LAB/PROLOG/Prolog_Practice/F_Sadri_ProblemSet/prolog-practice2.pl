subList([X],L):-
    member(X,L).

subList([X|T],L):-
    member(X,L),
    subList(T,L).

difference(L1,L2,L):-
    difference(L1,L2,[],L).

difference([],_,L,L).

difference([H|T],L2,X,L):-
\+member(H,L2),
difference(T,L2,[H|X],L).

difference([H|T],L2,X,L):-
    member(H,L2),
    difference(T,L2,X,L).

sift(L1,N,L):-
    sift(L1,N,[],L).

sift([],_,L,L).

sift([H|T],N,X,L):-
    H=<N,!,
    sift(T,N,[H|X],L).

sift([H|T],N,X,L):-
\+(H=<N),!,
sift(T,N,X,L).

common(L1,L2,L):-
    common(L1,L2,[],L).
common([],_,L,L2):-
    setof(X,member(X,L),L2).

common([],_,L,L2):-
\+setof(X,member(X,L),L2),
L2=[].

common([H|T],L2,X,L):-
    member(H,L2),
    common(T,L2,[H|X],L).

common([H|T],L2,X,L):-
\+member(H,L2),\
common(T,L2,X,L).

delete([],[]).

delete([X,_|T],[X|R]):-
    delete(T,R).

process(L1,L2,C,I):-
    process(L1,L2,[],[],C,I).

process(_,[],C,I,C,I).

process(L1,[(X,Y,Z)|T],C1,I2,C,I):-
    S = (X,Y),
    member(S,L1),
    process(L1,T,[(X,Y,Z)|C1],I2,C,I).

process(L1,[(X,Y,Z)|T],C1,I2,C,I):-
    S = (X,Y),
\+member(S,L1),
process(L1,T,C1,[(X,Y,Z)|I2],C,I).

split(L,0,[],L).

split([H|T],N,[H|Z],L):-
    N>0,
    N2 is N-1,
    split(T,N2,Z,L).

drop(List, N, List):-
    length(List,Length),
    Length<N.

drop([X,Y,Z|T], N, [X,Y|T2]):-
    length([X,Y,Z|T] ,Length),
    Length>=N,
    drop(T, N, T2).

enrolment([(X,Y)|_], Student, X):-
    member(Student,Y).

enrolment([(_,Y)|T], Student, Z):-
\+member(Student,Y),
enrolment(T, Student, Z).

student_list([],[],[]).

student_list([(X,Y)|T], Meng,Msc2):-
    X = msc,
    append(Y,Msc,Msc2),
    student_list(T, Meng,Msc).

student_list([(X,Y)|T], Meng2,Msc):-
    X = meng,
    append(Y,Meng,Meng2),
    student_list(T, Meng,Msc).
