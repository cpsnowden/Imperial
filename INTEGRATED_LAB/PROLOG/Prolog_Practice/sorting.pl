%insert sort


age(a,m,some).
age(b,m,thing).
age(c,f,else).
age(d,f,why).


iSort(L2,SL):-
    findall(E, age(E,_,_),L2),
    iSort(L2,[],SL).

iSort([],A,A).
iSort([H1|T1],A,L2):-insert2(H1,A,NA), iSort(T1,NA,L2).

insert(E,[],[E]).
insert(E,[X|T],[E,X|T]):- E =< X.
insert(E,[X|T],[X|NT]):-  E > X, insert(E,T,NT).

insert2(E,[],[E]).
insert2(E,[X|T],[E,X|T]):- age(E,_,EA), age(X,_,XA), EA @=< XA.
insert2(E,[X|T],[X|NT]):- age(E,_,EA), age(X,_,XA), EA @> XA, insert2(E,T,NT).


%pivot sort
qSort([],[]).
qSort([H|T],L):-
    pivot(H,T,L1,L2),
    qSort(L1,SL1),
    qSort(L2,SL2),
    append(SL1, [H|SL2], L).

pivot(H,[X|T],[X|NT],L2):- X =< H, pivot(H,T,NT,L2).
pivot(H,[X|T],L1,[X|NT]):- X > H, pivot(H,T,L1,NT).
pivot(H,[],[],[]).



%append
append2([],L2,L2).

append2([H|T],L2,[H|L3]):-
    append2(T,L2,L3).

