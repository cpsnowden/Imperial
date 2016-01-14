natural_no(0).
natural_no(X) :-
	natural_no(Y),
	X is Y+1.