%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%                                                         %
%         276 Introduction to Prolog                      %
%                                                         %
%         Practice Lexis Test                             %
%                                                         %
%                                                         %
%         Question 2 (graphs)                             %
%                                                         %
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% Some examples for testing %
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

testgraph(g1,
          [b > f, f > c, c > b, g > h, g > g, d, b, f > k, k > f, f > c],
          graph([b,c,d,f,g,h,k],
                [e(b,f),e(c,b),e(f,c),e(f,k),e(g,g),e(g,h),e(k,f)]),
          [n(b,[f]),n(c,[b]),n(d,[]),n(f,[c,k]),n(g,[g,h]),n(h,[]),n(k,[f])]).
testgraph(g2,
          [s, s > r, t, u > r, s > u, u > s, v > u],
          graph([r,s,t,u,v],[e(s,r),e(s,u),e(u,r),e(u,s),e(v,u)]),
          [n(r,[]),n(s,[r,u]),n(t,[]),n(u,[r,s]),n(v,[u])]).
testgraph(g3,
          [p>q, m>q, q>m, m>p, p>p],
          graph([m,p,q],[e(m,p),e(m,q),e(p,p),e(p,q),e(q,m)]),
          [n(m,[p,q]),n(p,[p,q]),n(q,[m])]).


%%%%%%% End of test examples %%%%%%%%

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%                                                  %
%         Question 2 (graphs)                      %
%                                                  %
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%


%% ------ Add your code to this file here.

merge_ordered(H,[],H).
merge_ordered([],[H|T],[H|T]).

merge_ordered([L1|LR],[R1|RR],[L1|MR]):-
    L1 @=< R1,
    merge_ordered(LR,[R1|RR],MR).
    
merge_ordered([L1|LR],[R1|RR],[R1|MR]):-
    L1 @> R1,
    merge_ordered([L1|LR],RR,MR).

hf_to_graph_term(Hform,[Nodes,Edges]):-
    setof(Node,
	    B^(
		member(Node>B,Hform);
		member(B>Node,Hform);
		(member(Node,Hform), Node \= (_>_))
	    )	    
	    ,Nodes),
    setof(e(X,Y),member(X>Y,Hform) ,Edges).
	  



