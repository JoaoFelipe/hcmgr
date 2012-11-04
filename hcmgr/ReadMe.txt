lab2 - Project Report
Amanda Priscilla Araujo da Silva
Joao Felipe Nicolaci Pimentel


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
VariableEntry.h: contains the declaration of the VariableEntry class
VariableEntry.cpp: contains the definitions of the VariableEntry methods
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
The SymbolEntry can be a VariableEntry that has a string field _label or a ConstantEntry that has an unsigned int field _value
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
$ hcmgr.exe process empty.txt
->Nothing occurred. This is the expected behavior, since the file doesn't have any horn clauses

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