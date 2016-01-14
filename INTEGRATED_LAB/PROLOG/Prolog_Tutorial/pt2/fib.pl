f(Y,1):-
	(Y=1;Y=2).


f(Y,X):-
	Y>2,
	Z is Y-1,f(Z,W),
	U is Y-2,f(U,T),
	X is W+T.