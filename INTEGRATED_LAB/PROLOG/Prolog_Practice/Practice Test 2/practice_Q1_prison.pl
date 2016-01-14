%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%                                                         %
%         276 Introduction to Prolog                      %
%                                                         %
%         Practice Lexis Test                             %
%                                                         %
%         Question 1 (prison)                             %
%                                                         %
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%


%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%                                                         %
%         Question 1 (prison)                             %
%                                                         %
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%


% compile the Prison Database

:- ensure_loaded(prisonDB_lexis).

forall(C1,C2) :- \+ (C1, \+ C2).

cell(N) :-
   cells(Cells),
   in_range(1,Cells,N).

in_range(Min, Max, Max):-
    Min =< Max.

in_range(Min, Max, N):-
    Min =< Max,
    NMax is Max - 1,
    in_range(Min, NMax, N).

empty(Cell):-
    cell(Cell),
    \+prisoner(_,_,Cell,_,_,_).

forall(C1,C2) :- \+ (C1, \+ C2).

occupant(Cell, FN):-
    prisoner(_,FN,Cell,_,_,_).

all_female_cell(Cell):-
    cell(Cell),
    \+empty(Cell),
    forall(occupant(Cell,FN) ,female_name(FN)).

female_prisoners(N):-
    setof((FN,SN),(A^B^C^D^prisoner(SN,FN,A,B,C,D),
	      female_name(FN)
	  ),
	  PList),
    length(PList,N).

male_prisoners(N):-
    setof((FN,SN),A^B^C^D^(
	      prisoner(SN,FN,A,B,C,D),
	      \+female_name(FN)
	  ),
	  PList),
    length(PList,N).

prisoners(N):-
    setof((FN,SN),A^B^C^D^(
	      prisoner(SN,FN,A,B,C,D)
	  ),
	  PList),
    length(PList,N).

cell_occupancy(Cell, N):-
    setof((FN,SN),B^C^D^prisoner(SN,FN,Cell,B,C,D),PList),
    length(PList,N).

cell_occupancy(Cell, 0):-
    cell(Cell),
    \+occupant(Cell, _).

fullest_cell(Cell, N):-
    cell_occupancy(Cell,N),
\+ (cell(Cell2), Cell \= Cell2, cell_occupancy(Cell2,N2), N2 > N).

worst_psychopath(S,F,Crime,T):-
    psychopath(S,F),
    prisoner(S,F,_,Crime,T,_),
\+ (psychopath(S2,F2),
    S\=S2,
    F\=F2,
    prisoner(S2,F2,_,_,T2,_),
    T2 > T).

ciminals(Crime, N):-
    setof((FN,SN),A^C^D^(
	      prisoner(SN,FN,A,Crime,C,D)
	  ),
	  PList),
    length(PList,N). 


/*  Remove the following comments if you wish to skip part(a) */

/*  

% load the library(between) module

:- use_module(library(between)).

in_range(Min, Max, N) :- between(Min, Max, N).

*/

%% ------ Add your code to this file here.
 
