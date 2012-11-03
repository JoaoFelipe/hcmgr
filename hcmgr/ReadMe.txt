
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