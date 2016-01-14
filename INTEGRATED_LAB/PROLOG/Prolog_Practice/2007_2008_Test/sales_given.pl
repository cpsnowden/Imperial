sellsFor('Peter Jones',swan123,28).
sellsFor('Peter Jones',electrolux214,27).

sellsFor('Peter Jones',hoover02,60).
sellsFor('Peter Jones',electrolux09,70).

sellsFor('Harrods', electrolux214, 31).
sellsFor('Harrods', swan123, 30).

sellsFor('Harrods', hoover02, 65).
sellsFor('Harrods', electrolux09, 80).

inStock('Peter Jones',electrolux214).
inStock('Peter Jones',hoover02).
inStock('Peter Jones',electrolux09).

inStock('Harrods',swan123).
inStock('Harrods',electrolux09).

locatedIn('Peter Jones',london).
locatedIn('Harrods',london).
	

typeOfItem(swan123,electricKettle).
typeOfItem(electrolux214,electricKettle).
typeOfItem(hoover02, vacuum_cleaner).     
typeOfItem(electrolux09, vacuum_cleaner).        

equivalentItems(electrolux214,swan123).
equivalentItems(electrolux09,hoover02).



forall(C1,C2) :- \+ (C1,\+C2).


sellsOneForLessThan(T,MP,S,I,P):-
    sellsFor(S,I,P),
    typeOfItem(I,T),
    P < MP.

equivalent(I1,I2):- equivalentItems(I1, I2).
equivalent(I1,I2):- equivalentItems(I2, I1).

sellsEquivalentItemIn(I,C,EI, S):-
    locatedIn(S, C),
    inStock(S, I),
    EI = I.

sellsEquivalentItemIn(I,C,EI, S):-
    locatedIn(S, C),
    equivalent(I,EI), 
    inStock(S, EI),
    sellsFor(S, I, PI),
    sellsFor(S, EI, PEI),
    PEI =< PI.

neverUnderSold(S,C):-
    locatedIn(S,C),
    locatedIn(S2,C),
    S \= S2,
    forall((sellsFor(S,X,PS), sellsFor(S2,X,PS2)), PS2 >= PS).

listOfSuppliersFor(I,C,L):-
    setof((P,S),(locatedIn(S,C),sellsFor(S,I,P),inStock(S,I)),L).
    
