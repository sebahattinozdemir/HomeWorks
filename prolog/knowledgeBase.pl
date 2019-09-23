
loves(romeo, juliet).

loves(juliet, romeo) :- loves(romeo, juliet).


male(albert).
male(bob).
male(bill).
male(carl).
male(charlie).
male(dan).
male(edward).

female(alice).
female(betsy).
female(diana).

isPerson(X):- male(X);female(X).

happy(albert).
happy(alice).
happy(bob).
happy(bill).
with_albert(alice).

runs(X):-happy(X),with_albert(X).

parent(albert, bob).
parent(albert, betsy).
parent(albert, bill).

parent(alice, bob).
parent(alice, betsy).
parent(alice, bill).

parent(bob, carl).
parent(bob, charlie).

related(X,Y):-parent(X,Y).
related(X,Y):-parent(X,Z),related(Z,Y).


grandparent(X,Y):-parent(X,Z),parent(Z,Y).

grandparent(X,Y),parent(X,Z),parent(Z,Y).

% Does Carl have an Uncle?
% Who is Carls parent? Who is Carls fathers brother?

brother(X,Y):-parent(Z,X),parent(Z,Y).

haveUncle(Z) :- parent(X,Z),brother(X,Y),male(Y).

blushes(X):-isPerson(X).


owns(albert, pet(cat, olive)).
owns(betsy, pet(cat, olive)).

customer(sally, smith, 120.55).

vertical(point(X,_),point(X,_)).
horizantal(point(_,Y),point(_,Y)).

vertical(point(4,3),point(4,5)).


warm_blooded(penguin).
warm_blooded(human).

produce_milk(penguin).
produce_milk(human).

have_feathers(penguin).
have_hair(human).


mammal(X):-
	warm_blooded(X)
	,produce_milk(X)
	,have_hair(X).


count(10).
count(X):- 
		  write(X),nl,
		  X < 10,
          Y is X+1,
          count(Y).

% Receives Low (lowest value) and High (highest value)
  % Assigns values between Low and High to Y
  % Assigns the difference to Z
  % Continue looping until Y = 10

countUp(Low,High):-
				between(Low,High,Y),
				write(Y),nl,
				Y=0.

write([[alice, bob]|albert]), nl.

List1 = [a,b,c,d].

member(X, List1).

List2 = [1,2,3].

reverse([1,3,4],X).

append(List1,List2,X).

length([1,2,3],X).

len(Res,X):- Res == [],X is 0.
len([_|Res],X):-len(Res,Y),X is Y+1.


subset ([] ,[]).
subset ( Rsub ,[ |R]) :-subset( Rsub ,R).
subset ([H| Rsub ] ,[H|R]) :-subset( Rsub ,R).