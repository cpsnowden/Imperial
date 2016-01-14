/*How to modify progam to avoid nonsense strings*/

/*exclude(X):-
	X = [a, grass, eats, a ,cow];
	X = [a, song, chews, the, grass].

sentence(L,[]) :-
	exclude(L),
	!,
	false.
*/
sentence --> sNounPhrase, sVerbPhrase.
sentence --> pNounPhrase, pVerbPhrase.

nounPhrase --> sNounPhrase.
nounPhrase --> pNounPhrase.

sNounPhrase --> article, sNoun.
sNounPhrase --> sArticle, sNoun.
sNounPhrase --> article, sVNoun.
sNounPhrase --> sVArticle, sVNoun.
pNounPhrase --> article, pNoun.

sVerbPhrase --> sVerb.
pVerbPhrase --> pVerb.
sVerbPhrase --> sVerb, nounPhrase.
pVerbPhrase --> pVerb, nounPhrase.

article --> [the].
sArticle --> [a].
sVArticle --> [an].
sNoun --> [boy].
pNoun --> [boys].
sVNoun --> [apple].
pNoun --> [apples].
sNoun --> [song].
pNoun --> [songs].
sVerb --> [eats].
pVerb --> [eat].
sVerb --> [sings].
pVerb --> [sing].
sNoun --> [grass].
sNoun --> [cow].