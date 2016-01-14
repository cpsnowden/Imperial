/********************************************
*
*
*
********************************************/

%subList(L1, L2) to mean every element in list L1 is also in list L2.
subList(L1,L2):-
\+memberOfOne(L1,L2,_).

%memberOfOne(L1,L2) a member of L1 is not a member of L2
memberOfOne(L1,L2,X):-
    member(X,L1),
   \+member(X,L2).

%difference(L1, L2, ?L) to mean L consists of all the elements in L1 that are not
%in L2.
difference(L1, L2, L):-
    findall(X,memberOfOne(L1,L2,X),L).

%sift(L, N, ?Result) to mean Result is list L but with all occurrences of
%elements greater than N removed.
sift(L, N, Result):-
    findall(X,(member(X,L), X =< N), Result).

%common(L1, L2, I) to mean I is the list of the common elements of lists L1 and
%L2
common(L1, L2, I):-
    setof(X, memberOfBoth(L1, L2, X), I).

common(L1, L2, []):-
    \+memberOfBoth(L1, L2, _).

memberOfBoth(L1,L2,X):-
    member(X,L1),
    member(X,L2).

%delete(L, Result) Result is list L with every other element deleted.
delete([],[]).

delete([H1],[H1]).

delete([H1, _|T],[H1|A]):-
    delete(T,A).

%process(L1, L2, Consistent, Inconsistent) where L1 is a given list of items of
%the form (Name, Number), and L2 is a given list of items of the form (Name,
%Number, MoreInfo). Then the output Consistent should be those items (Name,
%Number, MoreInfo) in L2 that agree on (Name, Number) with list L1, and
%Inconsistent should be whatever is left over from list L2.

process(L1,L2,C,I):-
    process(L1,L2,[],[],C,I).

process(_,[],C,I,C,I). %better

process(L1,[(X,Y,Z)|T],C1,I2,C,I):-
    S = (X,Y),
    member(S,L1),
    process(L1,T,[(X,Y,Z)|C1],I2,C,I).

process(L1,[(X,Y,Z)|T],C1,I2,C,I):-
    S = (X,Y),
\+member(S,L1),
process(L1,T,C1,[(X,Y,Z)|I2],C,I).

/*

process(L1, L2, C, I):-
    sort(L1, SL1),
    sort(L2, SL2),
    processSorted(SL1, SL2, C, I).
		
processSorted([],L,[],L).

processSorted([(F1,F2)|T1], [(F1,F2,F3)|T2], [(F1,F2,F3)|T], Inconsistent):-
    processSorted(T1,T2,T,Inconsistent).

processSorted([(F1,F2)|T1], [(G1,G2,G3)|T2], Consistent , [(G1,G2,G3)|T]):-
    F1 \= G1,
    processSorted([(F1,F2)|T1],T2,Consistent,T).

processSorted([(F1,F2)|T1], [(F1,G2,G3)|T2], Consistent , [(F1,G2,G3)|T]):-
    F2 \= G2,
    processSorted(T1,T2,Consistent,T).
*/
%split(L, N, L1, L2) Split a list L into two parts L1 and L2 such that the
%length of the first part is N
split(L, N, L1, L2):-
    append(L1, L2, L),
    length(L1, N).

%drop(L, N, Result) Drop every N'th element from a list L.

drop(L, N, Result):- drop(L, N, Result, 1).

drop([],_,[],_).

drop([_|T], N, Result, N):-
    drop(T, N, Result, 1).
    
drop([H|T], N, [H|Result], Q):-
    Q \= N,
    M is Q + 1,
    drop(T, N, Result, M).

%enrolment(L, Student, Degree) Given a list L of enrolments, and a student’s
%name, Student, the program finds the degree of the student

enrolment([(_,N)|T], Student, Degree):-
    \+member(Student, N),
    enrolment(T, Student, Degree).

enrolment([(Degree,N)|_], Student, Degree):-
    member(Student, N).

%student_list(L, Meng, MSc) Separate a list L of students into the Meng students
%and the MSc students

student_list([],[],[]).

student_list([(meng,N)|T], Meng2, MSc):-
    append(N,Meng, Meng2),
    student_list(T, Meng, MSc).

student_list([(msc,N)|T], Meng, MSc2):-
    append(N,MSc, MSc2),
    student_list(T, Meng, MSc).
