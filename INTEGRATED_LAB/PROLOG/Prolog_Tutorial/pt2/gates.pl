xorgate(g1).
xorgate(g2).
andgate(g3).
andgate(g4).
orgate(g5).

and_result(X,Y,Z):-
	X=1,
	Y=1,
	Z=1,
	!.

and_result(_,_,0).

or_result(X,Y,Z):-
	(X\=0;Y\=0),
	Z=1.

or_result(0,0,0).

output(G,X):-
	andgate(G),
	input1(G,I1),
	input2(G,I2),
	and_result(I1,I2,X).

output(G,X):-
	orgate(G),
	input1(G,I1),
	input2(G,I2),
	or_result(I1,I2,X).

output(G,X):-
	xorgate(G),
	input1(G,I1),
	input2(G,I2),
	xor_result(I1,I2,X).

xor_result(X,X,0).
xor_result(X,Y,1):- X\=Y.

input1(g1,1).
input1(g2,X):-output(g1,X).
input1(g3,1).
input1(g4,1).
input1(g5,X):-output(g3,X).

input2(g1,0).
input2(g2,1).
input2(g3,X):-output(g1,X).
input2(g4,0).
input2(g5,X):-output(g4,X).