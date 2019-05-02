#include <iostream>
#include <fstream>
#include <string>

using namespace std;

class digit
{
    public:
    int data;
    digit *next = nullptr;
};

digit * writeNum(ifstream & file);
int digcmp(digit * left, digit *right);
char getOperator(ifstream & file);
void writeNum(digit * num, ofstream & file);
void deleteNum(digit * num);
digit * addNumbers(digit * left, digit * right);
digit * subNumbers(digit * left, digit * right);
void writeRecursive(digit * num, ofstream & file);
void setNeg(digit * num);
void printNum(digit * num);
void printRecursive(digit * num);
void subtractCarry(digit * head, digit * prev);
digit * clearLeadingZeros(digit * num);

//-----------------PROVIDED BY INSTRUCTOR-----------------
int main() {
    digit * left, * right, * result;
    int test;
    char op;
    ofstream outFile ("output.txt");
    ifstream inFile ("largeNumbers.txt");

    while (!inFile.eof()){
        left  = writeNum(inFile);
        right = writeNum(inFile);
        if (left == nullptr || right == nullptr) {
            // check after two reads if we didn't get numbers
            // in case of one extra newline at end of file
            break;
        }
        op = getOperator(inFile);

        if (op == '+'){
            result = addNumbers(left, right);
        }
        else {
            test = digcmp(left, right);
            if (test > 0) {
                result = subNumbers(left, right); // result will be positive
                result = clearLeadingZeros(result);
            } else if (test < 0) {
                result = subNumbers(right, left); // result will be negative
                result = clearLeadingZeros(result);
                setNeg(result);
            } else {
                result = new digit; // result of subtraction was zero
            }
        }
        writeNum(result, outFile);
        deleteNum(left);
        deleteNum(right);
        deleteNum(result);
        left = nullptr;
        right = nullptr;
        result = nullptr;
    }

    outFile.close();
    inFile.close();
    return 0;
}

//-----------------PROVIDED BY INSTRUCTOR-----------------
/* returns a number <0 || 0 || >0
*  <0 right number is larger
*   0  the numbers are equal
*  >0 left number is larger
*  only works if the number is stored with lowest significant at front of the list
*/
int digcmp(digit * left, digit * right){
    int result= 0;
    do // the assignment guarantees there will not be zero length numbers
    {
        if (left->data - right->data == 0){
        } // take no action
        else {
            result= left->data - right->data;
        }
        left = left->next;
        right = right->next;
    } while (left != nullptr && right != nullptr);
    if (left == nullptr && right != nullptr) {
        // right number is longer and therefore larger
        result= -1;
    }
    if (left != nullptr && right == nullptr) {
        // left number is longer and therefore larger
        result= 1;
    }
    return result;
}

//-----------------PROVIDED BY INSTRUCTOR-----------------
digit * writeNum(ifstream & file){
    if (file.eof())
    return nullptr;
    digit * head = new digit;
    digit * dig = head;

    char aChar;
    int num;

    file.get(aChar);
    while (aChar != '\n' && !file.eof()){
        num = int(aChar - '0');
        head->data = num;
        file.get(aChar);
        if (aChar != '\n'){
            dig = head;
            head = new digit;
            head->next = dig;
        }
    }
    return head;
}

//-----------------PROVIDED BY INSTRUCTOR-----------------
char getOperator(ifstream & file){
    char aChar;
    string toss;

    file.get(aChar);
    getline(file, toss);

    return aChar;
}

//-----------------PROVIDED BY INSTRUCTOR-----------------
void printRecursive(digit * num){
    if (num == nullptr)
    return;
    printRecursive(num->next);
    cout << num->data;
}

//-----------------PROVIDED BY INSTRUCTOR-----------------
void printNum(digit * num){
    printRecursive(num);
    cout << endl;

}

//-----------------PROVIDED BY INSTRUCTOR-----------------
void writeRecursive(digit * num, ofstream & file) {
    if (num == nullptr)
    return;
    file << num->data;
    writeRecursive(num->next, file);
}

//-----------------PROVIDED BY INSTRUCTOR-----------------
void writeNum(digit * num, ofstream & file){
    writeRecursive(num, file);
    file << endl;
}

//-----------------PROVIDED BY INSTRUCTOR-----------------
void deleteNum(digit * num){
    digit * n;
    while (num != nullptr)
    {
        n = num->next;
        delete num;
        num = n;
    }
}

// TODO: Implement function to add 2 numbers stored in 2 linked lists
digit * addNumbers(digit * left, digit * right){ // this function makes numbers in order.
    digit * resHead = new digit;
    digit * resDigit = resHead;
    int resDig;
    bool carryDig = false;
    while (left != nullptr || right != nullptr){
      if (left != nullptr)
        resDig = left->data;
      else
        resDig = 0;
      if (carryDig)
        resDig += 1;
      if (right != nullptr){
        resDig += right->data;
      }
      if (resDig >= 10)
      {
        carryDig = true;
        resDig -= 10;
      }
      else
        carryDig = false;
      resHead->data = resDig;
      resDigit = resHead;
      resHead = new digit;
      resHead->next = resDigit;
      if (left != nullptr)
        left = left->next;
      if (right != nullptr)
        right = right->next;
    }
    if (carryDig)
      resHead->data = 1;
    else
      resHead = resHead->next;

    return resHead;
}

//-----------------PROVIDED BY INSTRUCTOR-----------------
void subtractCarry(digit * head, digit * prev){
    if (head == nullptr){
        return;
        } // safety check only, this should never happen!
    if (head->data == 0){
        head->data = 9;
        subtractCarry(head->next, head);
    } else {
        head->data -= 1;
    }
}

// TODO: Implement function to subtract 2 numbers stored in 2 linked lists. Use provided helper functions
digit * subNumbers(digit * left, digit * right){
    digit * resHead = new digit;
    digit * resDigit = resHead;
    int leftNum, rightNum, resNum;
    bool borrow = false;
    while (left != nullptr || right != nullptr){
      if (left != nullptr)
        leftNum = left->data;
      else
        leftNum = 0;
      if(borrow)
        leftNum -= 1;
      if (right != nullptr)
        rightNum = right->data;
      else
        rightNum = 0;
      if (leftNum >= rightNum)
      {
        resNum = leftNum - rightNum;
        borrow = false;
      }
      else
      {
        resNum = 10 + leftNum - rightNum;
        borrow = true;
      }

      resHead->data = resNum;
      resDigit = resHead;
      resHead = new digit;
      resHead->next = resDigit;
      if (left != nullptr)
        left = left->next;
      if (right != nullptr)
        right = right->next;
    }
    resHead = resHead->next;

    return resHead;
}

//-----------------PROVIDED BY INSTRUCTOR-----------------
digit * clearLeadingZeros(digit * num){
    digit * next;
    while (num->data == 0) {
        next = num->next;
        delete num;
        num = next;
        }
        return num;
    }
void setNeg(digit * num){
    num->data = -num->data;
}
