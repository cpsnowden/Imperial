:- use_module(library(lists)).
:- set_prolog_flag( toplevel_print_options, [max_depth(100)] ).

decode([],[]).

decode([bear|T1], [double|T2]):-
    decode(T1,T2).

decode([cub|T1], [agent|T2]):-
    decode(T1,T2).

decode([H|T1], [H|T2]):-
    H \= cub,
    H \= bear,
    decode(T1,T2).

agents(Message, Decoded_Message, ListofAgents):-
    decode(Message, Decoded_Message),
    getAgents(Decoded_Message, UnSortedLoA),
    sort(UnSortedLoA,ListofAgents).

getAgents([],[]).

getAgents([Name,is,a,double,agent|T],[Name|Rest]):-
    getAgents(T,Rest),!.

getAgents([_|T],Rest):-
    getAgents(T,Rest).

count_word(_,[],0).

count_word(W,[W|T],C):-
    count_word(W,T,D),
    C is D + 1,!.

count_word(W,[_|T],C):-
    count_word(W,T,C).

count_ag_names(Message, Ag_name_counts):-
    agents(Message,Decode,LoA),
    setof((Name,Count),(member(Name,LoA),count_word(Name,Decode,Count)),Ag_name_counts).

count_ag_names(Message, []):-
    agents(Message,Decode,[]).

agentsRep(Message, ListofAgents):-
    decode(Message, Decoded_Message),
    getAgents(Decoded_Message, ListofAgents).

accusation_counts(M, AC2):-
     agentsRep(M,LoA),
     setof((Count,Name),(member(Name,LoA),count_word(Name,LoA,Count)),NAC),
     findall((Name,Count),member((Count,Name),NAC),AC),
     reverse(AC,AC2).

accusation_counts(M, []):-
     agentsRep(M,[]).
