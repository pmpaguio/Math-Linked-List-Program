# Math-Linked-List-Program
This program reads in various computations consisting of 2 numbers of an unknown length of digits, followed by an operator defining what math operation to perform.  The results for each calculation are written to the output.txt as they’re computed. This means that output.txt should be opened only once and remain open until all results have been obtained and saved to the file. 


Function prototype / Description
---------------------------------
digit * loadNumber(ifstream & file);
Is called twice for each computation (once for each large number in the file). Returns a pointer to the first element in the linked list. Uses the new operator to create each element in the list.

char getOperator(ifstream & file);
Returns the char version of the + or - operators to indicate the desired operation.
void writeNumber(digit * num, ofstream & file);
Writes the resulting number to the file. Should be passed the head pointer of that number.

void deleteNumber(digit * num);
Is called for each number created dynamically when no longer needed. Calls the delete operator on each node in the list to protect against a memory leak.

digit * addNumbers(digit * left, digit * right);
Adds the left and right operands. Returns a pointer to the first element of the result in a newly-created linked list. Creates each element in the list using the new operator. The right operand is the second number in the input file.

digit * subNumbers(digit * left, digit * right);
Subtracts the right operand from the left and returns a pointer to the first element of the result in a newly-created linked list. Creates each element in the list using the new operator. The right operand is the second number in the input file.
