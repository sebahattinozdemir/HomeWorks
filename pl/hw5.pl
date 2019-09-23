:-module(hw5, [catomic_number/2, ion/2 ,molecule/2 ]).
:-[catoms].

catomic_number(NAME, CATOMIC_NUMBER):-
	catom(NAME, _, _, ELECTRONS),
	sum_list(ELECTRONS, CATOMIC_NUMBER).

ion(NAME, CHARGE):-
	catom(NAME, _, _, ELECTRONS),
	last(ELECTRONS, OUTER),
	OUTER =< 4,
	CHARGE is OUTER.

ion(NAME, CHARGE):-
	catom(NAME, _, _, ELECTRONS),
	last(ELECTRONS, OUTER),
	OUTER > 4,
	CHARGE is OUTER - 8.

molecule(CATOM_LIST, TOTAL_CATOMIC_NUMBER):-
	molecule(0, 0, TOTAL_CATOMIC_NUMBER, [], CATOM_LIST).

molecule(_, 0, 0, CATOM_LIST, CATOM_LIST):-!.
molecule(MIN_CN, CHARGES_SUM, CURRENT_CATOMIC_NUMBER, CURRENT_LIST, CATOM_LIST):-
	CURRENT_CATOMIC_NUMBER >= 0,
	catomic_number(NAME, CATOMIC_NUMBER),
	CATOMIC_NUMBER >= MIN_CN,
	CATOMIC_NUMBER =< CURRENT_CATOMIC_NUMBER,
	REMAINING_NUMBER is CURRENT_CATOMIC_NUMBER - CATOMIC_NUMBER,
	ion(NAME, CHARGE),
	NEW_CHARGE is CHARGES_SUM + CHARGE,
	insert_at_last(NAME, CURRENT_LIST, NEW_LIST),
	molecule(CATOMIC_NUMBER, NEW_CHARGE, REMAINING_NUMBER, NEW_LIST, CATOM_LIST).

sum_list([], 0).
sum_list([H|T], S):-
	sum_list(T, S1),
	S is H + S1.

last([X], X).
last([_|T], L):-
	last(T, L).

add_atomic_number([], []).
add_atomic_number([H|T], [(N,H)|T2]):-
	catomic_number(H,N),
	add_atomic_number(T, T2).

insert_at_last(X, [], [X]).
insert_at_last(X, [H|T], [H|T2]):-insert_at_last(X, T, T2),!.
