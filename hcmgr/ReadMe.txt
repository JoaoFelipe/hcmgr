lab2 - Project Report
Amanda Priscilla Araujo da Silva
Joao Felipe Nicolaci Pimentel


hcmgr
hcprocess



string_utils
operation_utils


SubstitutionList

Parser

:File Structure
hcmgr.cpp: contains the definition of function main
hcprocess.h: contains the declaration of the function that process the input file 
hcprocess.cpp: contains the definition of this function.
string_utils.h: contains the declarations of functions that are used to check if a string follows defined criteria.
string_utils.cpp: contains the definitions of this functions.
const.h: contains the declarations of the constants used in the program
Parser.h: contains the declaration of the Parser class
Parser.cpp: contains the definitions of the Parser methods
HornClause.h: contains the declaration of the HornClause class
HornClause.cpp: contains the definitions of the HornClause methods
Head.h: contains the declaration of the Head class
Head.cpp: contains the definitions of the Head methods
Body.h: contains the declaration of the Body class
Body.cpp: contains the definitions of the Body methods
Predicate.h: contains the declaration of the Predicate class
Predicate.cpp: contains the definitions of the Predicate methods
Name.h: contains the declaration of the Name class
Name.cpp: contains the definitions of the Name methods
Symbol.h: contains the declaration of the Symbol class
Symbol.cpp: contains the definitions of the Symbol methods
SymbolTable.h: contains the declaration of the SymbolTable class
SymbolTable.cpp: contains the definitions of the SymbolTable methods
SymbolTableEntry.h: contains the declaration of the SymbolTableEntry class
SymbolTableEntry.cpp: contains the definitions of the SymbolTableEntry methods
SymbolEntry.h: contains the declaration of the SymbolEntry class
SymbolEntry.cpp: contains the definitions of the SymbolEntry methods
ConstantEntry.h: contains the declaration of the ConstantEntry class
ConstantEntry.cpp: contains the definitions of the ConstantEntry methods
BoundEntry.h: contains the declaration of the BoundEntry class
BoundEntry.cpp: contains the definitions of the BoundEntry methods
PredicateEntry.h: contains the declaration of the PredicateEntry class
PredicateEntry.cpp: contains the definitions of the PredicateEntry methods
SubstitutionList.h: contains the declaration of the SubstitutionList class
SubstitutionList.cpp: contains the definitions of the SubstitutionList methods


:Abstract representation of HornClauses
One well-formed horn clause is abstractly represented by the class HornClause.
The class HornClause has a field of type Head and a field of type pointer to Body. When the pointer == 0, it means that the Horn Clause doesn't have a body.
The class Head has a field of type Predicate
The class Body has a vector of Predicates
The class Predicate has a Name and a vector of Symbols
Both the class Name and the class Symbol has a string _value

This abstractaction is readed from the text file by the Parser in the hcprocess file and a fill_symbol_table method is called for each HornClause. 
This method calls the method with same name of Head and Body that calls the method of same name of Predicate
In the Predicate, this method adds the symbols to the SymbolTable and then, adds the Predicate itself.


:Structure of Symbol Table
We have a class SymbolTable that has a vector of SymbolTableEntry
The SymbolTableEntry can be a SymbolEntry or a PredicateEntry
The SymbolEntry can be a BoundEntry that has a string field _label or a ConstantEntry that has an unsigned int field _value
The PredicateEntry has a string field _name and a vector of pointers of SymbolTableEntry to indicate the symbols

This structure allows us to easily identify the type os the entry in the table by virtual methods is_constant, is_variable, is_predicate and allows us to store different types of fields:
-string for variables
-unsigned int for constants
-string and list of pointers to SymbolTableEntry for predicate


:Unification
To check if two predicates matches, we have the method matches in the predicates that receives another predicate and receives a class SubstitutionList that stores the substitutions of symbols 
and finds recursively the substitution of a symbol (eg.: if we have the symbol X, and the substitutions Y/X 2/Y, the find method will return a pointer to the SymbolTableEntry 2)

For checking in the matches method, we first check if both predicates have the same name and the same amount of symbols.
Then, we iterates through the symbols:
  first we try to find any substitutions for the current symbols in both predicates
  if no substitutions are found, the original symbol are used.
  Then we check if both substituted (or original) symbols are equals.
  If they are, it iterates to the next symbol.
  If not, we check:
	Are both constants? If yes, the matching fails.
	Are both variables? If yes, adds a substitution in the SubstitutionList for first variable (from current predicate) to the second variable (from predicate that is being matched)
	Otherwise: adds a substitution in the SubstitutionList for the variable to the constant
If nothing fails, the predicates match

:Trials
$ hcmgr.exe bla
Invalid Argument format
Usage information:
hcmgr.exe process <filename>
    <filename> is the file with input horn clauses
-> It was the correct behavior. This is the invalid format for the argument line

$ hcmgr.exe process non_existent.txt
Unable to open file non_existent.txt
-> It was the correct behavior. The file doesn't exist

$ hcmgr.exe process empty.txt
No valid horn clauses were found in the file.
-> It was the correct behavior. The file is empty

$ hcmgr.exe process invalid.txt
No valid horn clauses were found in the file.
-> It was the correct behavior. The file doesn't have any valid horn clauses

$ hcmgr.exe process mix.txt
mix
horn clause
-> It was the correct behavior. The invalid horn clases were ignored. And there is no predicates with the same name for unification

$ hcmgr.exe process greater.txt
greater x y
greater x z
greater z y
greater z 3

(greater x y) matches (greater x z)
  z/y
  Unification (greater x z/y) matches (greater x z)

(greater x y) matches (greater z y)
  z/x
  Unification (greater z/x y) matches (greater z y)

(greater x y) matches (greater z 3)
  z/x
  3/y
  Unification (greater z/x 3/y) matches (greater z 3)

(greater x z) matches (greater x y)
  y/z
  Unification (greater x y/z) matches (greater x y)

(greater x z) matches (greater z y)
  z/x
  y/z
  Unification (greater y/x y/z) matches (greater y/z y)

(greater x z) matches (greater z 3)
  z/x
  3/z
  Unification (greater 3/x 3/z) matches (greater 3/z 3)

(greater z y) matches (greater x y)
  x/z
  Unification (greater x/z y) matches (greater x y)

(greater z y) matches (greater x z)
  x/z
  x/y
  Unification (greater x/z x/y) matches (greater x x/z)

(greater z y) matches (greater z 3)
  3/y
  Unification (greater z 3/y) matches (greater z 3)

(greater z 3) matches (greater x y)
  x/z
  3/y
  Unification (greater x/z 3) matches (greater x 3/y)

(greater z 3) matches (greater x z)
  x/z
  3/x
  Unification (greater 3/z 3) matches (greater 3/x 3/z)

(greater z 3) matches (greater z y)
  3/y
  Unification (greater z 3) matches (greater z 3/y)
-> It was the correct behavior. All the predicates matches with each other after the unification.

$ hcmgr.exe process equals.txt
equals 2 2
equals x 3

(equals 2 2) doesn't match (equals x 3)

(equals x 3) doesn't match (equals 2 2)
-> It was the correct behavior. The predicates doesn't match.

$ hcmgr.exe process 2hc.txt
equals x 2
equals 2 x
less x y z w
less y z w x

(equals x 2) matches (equals 2 x)
  2/x
  Unification (equals 2/x 2) matches (equals 2 2/x)

(equals 2 x) matches (equals x 2)
  2/x
  Unification (equals 2 2/x) matches (equals 2/x 2)

(less x y z w) matches (less y z w x)
  y/x
  z/y
  w/z
  Unification (less w/x w/y w/z w) matches (less w/y w/z w w/x)

(less y z w x) matches (less x y z w)
  x/y
  x/z
  x/w
  Unification (less x/y x/z x/w x) matches (less x x/y x/z x/w)
-> It was the correct behavior. All the predicates matches with the other that have the same name

$ hcmgr.exe process less.txt
less x 2
less 2 x
less y 3

(less x 2) matches (less 2 x)
  2/x
  Unification (less 2/x 2) matches (less 2 2/x)

(less x 2) doesn't match (less y 3)

(less 2 x) matches (less x 2)
  2/x
  Unification (less 2 2/x) matches (less 2/x 2)

(less 2 x) matches (less y 3)
  2/y
  3/x
  Unification (less 2 3/x) matches (less 2/y 3)

(less y 3) doesn't match (less x 2)

(less y 3) matches (less 2 x)
  2/y
  3/x
-> It was the correct behavior. There are matches and mismatches


:Extra Credit
To check if there is no repetition of Predicates, we used the same idea of checking if there is no repetition of Variables and Constants
Before adding any SymbolTableEntry to the SymbolTable, it iterates through all the SymbolTableEntry, trying to find one that has the same values returned by the virtual methods type() and text()
The type() returns "Predicate", "Constant" or "Variable" depending on the type of the SymbolTableEntry. And the text() returns the _label, the _value or the _name followed by the text() of the SymbolTableEntry pointed by the Predicate
If there is already one finded element, the adding fails and for the case of the Predicate, it shows a message:

$ hcmgr.exe process extra.txt
The predicate (copy) was found in the symbol table. Skipping...

The predicate (new 1 2) was found in the symbol table. Skipping...

The predicate (new 1 2) was found in the symbol table. Skipping...

copy
new 1 2
new 1 2 3

(new 1 2) doesn't match (new 1 2 3)

(new 1 2 3) doesn't match (new 1 2)