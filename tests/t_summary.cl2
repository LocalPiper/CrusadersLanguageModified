// Arithmetic
proclaim 2 conjure 3 amass 4 // Expect: 10

// Logic
proclaim aye united nay // Expect: 1
proclaim aye either nay // Expect: 0

// Comparisons
proclaim 5 nobelow 10 // Expect: 1
proclaim 10 nobelow 5 // Expect: 0

// Variables
henceforth val bestow 99
proclaim val // Expect: 99

// Function with three arguments
inscribe triple_sum invoke a also b also c dismiss commence
  proclaim a amass b amass c
conclude
triple_sum invoke 1 also 2 also 3 dismiss // Expect: 6

// Return value from function
inscribe ret42 invoke dismiss commence
  yield 42
conclude
proclaim ret42 invoke dismiss // Expect: 42

// Array and its size
henceforth arr bestow array invoke 7 also 8 also 9 dismiss
proclaim size invoke arr dismiss // Expect: 3

// Nested loop
upon invoke henceforth i bestow 0 also i nobelow 1 also i bestow i amass 1 dismiss commence
  upon invoke henceforth j bestow 0 also j nobelow 1 also j bestow j amass 1 dismiss commence
    proclaim i amass j
  conclude
conclude

/*
    Multyline
    comments
*/

// Conditionals
henceforth x bestow 5
suppose invoke x nobelow 3 dismiss commence 
  proclaim "big"
conclude
suppose invoke x nobelow 10 dismiss commence
  proclaim "small"
conclude

// Function call without arguments
inscribe hi invoke dismiss commence
  proclaim "hello"
conclude
hi invoke dismiss

// Complex arithmetic
proclaim 1 amass 2 conjure 3 // Expect: 7
