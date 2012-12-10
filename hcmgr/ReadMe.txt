lab3 - Project Report
Amanda Priscilla Araujo da Silva
Joao Felipe Nicolaci Pimentel

:File Structure
Body.h: contains the declaration of the Body class
Body.cpp: contains the definitions of the Body methods
BoundEntry.h: contains the declaration of the BoundEntry class
BoundEntry.cpp: contains the definitions of the BoundEntry methods
const.h: contains the declarations of the constants used in the program
ConstantEntry.h: contains the declaration of the ConstantEntry class
ConstantEntry.cpp: contains the definitions of the ConstantEntry methods
FunctionEntry.h: contains the declaration of the FunctionEntry class
FunctionEntry.cpp: contains the definitions of the FunctionEntry methods
FunctionSymbol.h: contains the declaration of the FunctionSymbol class
FunctionSymbol.cpp: contains the definitions of the FunctionSymbol methods
hcevaluate.h: contains the declarations of functions to evaluate the Predicate
hcevaluate.cpp: contains the definition of these functions
hcmgr.cpp: contains the definition of function main
hcprocess.h: contains the declaration of the function that process the input file 
hcprocess.cpp: contains the definition of this function
hcrandomize.h: contains the declarations of functions to randomize a variable
hcrandomize.cpp: contains the definition of these functions
hcset.h: contains the declarations of functions to set a variable
hcset.cpp: contains the definition of these functions
Head.h: contains the declaration of the Head class
Head.cpp: contains the definitions of the Head methods
HornClause.h: contains the declaration of the HornClause class
HornClause.cpp: contains the definitions of the HornClause methods
Name.h: contains the declaration of the Name class
Name.cpp: contains the definitions of the Name methods
operations_utils.h contains auxiliar functions for operations
Parser.h: contains the declaration of the Parser class
Parser.cpp: contains the definitions of the Parser methods
Predicate.h: contains the declaration of the Predicate class
Predicate.cpp: contains the definitions of the Predicate methods
PredicateEntry.h: contains the declaration of the PredicateEntry class
PredicateEntry.cpp: contains the definitions of the PredicateEntry methods
PredicatesContainer.h: contains the declaration of the PredicatesContainer class
PredicatesContainer.cpp: contains the definitions of the PredicatesContainer methods
string_utils.h: contains the declarations of functions that are used to check if a string follows defined criteria.
string_utils.cpp: contains the definitions of this functions.
SubstitutionList.h: contains the declaration of the SubstitutionList class
SubstitutionList.cpp: contains the definitions of the SubstitutionList methods
Symbol.h: contains the declaration of the Symbol class
SymbolEntry.h: contains the declaration of the SymbolEntry class
SymbolEntry.cpp: contains the definitions of the SymbolEntry methods
SymbolTable.h: contains the declaration of the SymbolTable class
SymbolTable.cpp: contains the definitions of the SymbolTable methods
SymbolTableEntry.h: contains the declaration of the SymbolTableEntry class
SymbolTableEntry.cpp: contains the definitions of the SymbolTableEntry methods
SymbolValueEntry.h: contains the declaration of the SymbolTableEntry class
SymbolValueEntry.cpp: contains the definitions of the SymbolTableEntry methods
TermSymbol.h: contains the declaration of the TermSymbol class
TermSymbol.cpp: contains the definitions of the TermSymbol methods
UnboundEntry.h: contains the declaration of the UnboundEntry class
UnboundEntry.cpp: contains the definitions of the UnboundEntry methods
UnboundSymbol.h: contains the declaration of the UnboundSymbol class
UnboundSymbol.cpp: contains the definitions of the UnboundSymbol methods


:Predicate Evaluation
All the resolutions are performed lazily (only when necessary to perform the evaluate command)

When the evaluate command is called, the predicate is parsed as a Goal (A HornClause with just the body)
Then, there is a try to unify each HornClause of the Deductive Database with the Goal. 
If a unification works, it can eliminate the body of the goal, evaluating the given predicate as True, or create a new HornClause of Subgoals.
If it is true, the evaluation function ends and answer the unification steps in reverse way.
If it is a subgoal, it is passed recursively to the evaluate function, trying to evaluate with all the HornClauses in the deductive database.

If all the unifications fails, the evaluation ends. 

This works similar to the depth-first strategy used by prolog, described in the book.
So, there are possibilities to the horn clauses enter in a infinite loop. 
To avoid that, we defined a max recursion count variable that stops the recursion. This doesn't garantee that the stopped execution was an infinite loop, 
but we decided that it is better to stop the evaluation than get a stack overflow. 

:Trials
$ hcmgr.exe bla
Invalid Argument format
Usage information:
hcmgr.exe [process <filename>]
    <filename> is the file with input horn clauses

$ hcmgr.exe process non-existent
HCMGR Interpreter
Processing file non-existent
Unable to open file non-existent
Type 'help'
> exit
-> It was the correct behavior. The file doesn't exist

$ hcmgr.exe process empty.txt
HCMGR Interpreter
Processing file empty.txt
Unable to open file empty.txt
Type 'help'
>
-> It was the correct behavior. The file is empty

$ hcmgr.exe process invalid.txt
HCMGR Interpreter
Processing file invalid.txt
No valid horn clauses were found in the file.
Type 'help'
>
-> It was the correct behavior. The file doesn't have any valid horn clauses

$ hcmgr.exe process mix.txt
HCMGR Interpreter
Processing file mix.txt
Type 'help'
> db
((valid))
>
-> It was the correct behavior. The invalid horn clases were ignored.


All the follwoing tests will be executed with the interpreter opened by

$ hcmgr.exe process ancestor.txt
HCMGR Interpreter
Processing file ancestor.txt
Type 'help'
>
-> The file was successfully processed... No error messages

Showing the processed horn clauses
> db
((ancestor X Y) ((parent X Z) (ancestor Z Y)))
((ancestor X X))
((parent a b))
>

Printing the Symbol Table
> print
Predicate: ancestor X Y
Predicate: parent X Z
Predicate: ancestor Z Y
Predicate: ancestor X X
Bound: a = 0
Bound: b = 0
Predicate: parent a b
>

Setting bound value
> set a 10
> print
Predicate: ancestor X Y
Predicate: parent X Z
Predicate: ancestor Z Y
Predicate: ancestor X X
Bound: a = 10
Bound: b = 0
Predicate: parent a b
>

Randomizing bound value without max
> randomize b
> print
Predicate: ancestor X Y
Predicate: parent X Z
Predicate: ancestor Z Y
Predicate: ancestor X X
Bound: a = 10
Bound: b = 9405
Predicate: parent a b
>

Randomizing bound value with max
> randomize b 10
> print
Predicate: ancestor X Y
Predicate: parent X Z
Predicate: ancestor Z Y
Predicate: ancestor X X
Bound: a = 10
Bound: b = 6
Predicate: parent a b
>

Evaluating predicate
> evaluate (ancestor a b)
(Goal ((parent 10 6))) unified with ((parent a b)): True
(Goal ((parent 10 Z) (ancestor Z 6))) unified with ((ancestor X X)): (Goal ((parent 10 6)))
(Goal ((ancestor a b))) unified with ((ancestor X Y) ((parent X Z) (ancestor Z Y))): (Goal ((parent 10 Z) (ancestor Z 6)))
>

Processing new file
> process loop.txt
Erasing deductive database
Processing file loop.txt
> db
((a [* a b]) ((b [- a b])))
((b 0) ((c [/ a b])))
((c 1) ((a [+ a 2])))
((a 5))
> print
Bound: a = 0
Bound: b = 0
Predicate: a [* a b]
Predicate: b [- a b]
Constant: 0 = 0
Predicate: b 0
Predicate: c [/ a b]
Constant: 1 = 1
Predicate: c 1
Constant: 2 = 2
Predicate: a [+ a 2]
Constant: 5 = 5
Predicate: a 5
>

Evaluating (a 0), fails because of division by zero in the second horn clause
> evaluate (a 0)
No result.
>

Setting a and b = 3
> set a 3
> set b 3
> print
Bound: a = 3
Bound: b = 3
Predicate: a [* a b]
Predicate: b [- a b]
Constant: 0 = 0
Predicate: b 0
Predicate: c [/ a b]
Constant: 1 = 1
Predicate: c 1
Constant: 2 = 2
Predicate: a [+ a 2]
Constant: 6 = 6
Predicate: a 6
>

Evaluating (a 9)
> evaluate (a 9)
(Goal ((a 5))) unified with ((a 5)): True
(Goal ((c 1))) unified with ((c 1) ((a [+ a 2]))): (Goal ((a 5)))
(Goal ((b 0))) unified with ((b 0) ((c [/ a b]))): (Goal ((c 1)))
(Goal ((a 9))) unified with ((a [* a b]) ((b [- a b]))): (Goal ((b 0)))
>


Setting a and b = 2 and evaluating (a 4)
> set a 2
> set b 2
> evaluate (a 4)
The program reached the max number of recursions. Maybe it is not a infinite loop, but we decided to stop.
>
-> We have the MAX_LOOPS = 500; in the const.h . When the evaluation reaches more than MAX_LOOPS recursion calls, it is stopped


Exitting the interpreter
> exit
