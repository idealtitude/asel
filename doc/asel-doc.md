# ASEL Documentaiton

**Language basics**

## Comments

Single line comment:

```
; This is a comment
```

Multi lines comment:

```
;; This comment spans on
multiple lines, it's close when it
reaches another double semi colon
;;
```

## Variables

### Types

```
; integer
int x = 10

; float/long
float y = 0.123456789

; boolean
bool z = true

; string
str a = "Shalom Shamayim!"

; arrays
int[] b = {10, 20, 30, 40}
str[] c = {"Abc", "Def", "Ghj"}

; associative arrays
; an array where keys are strings, and values integers
str[int] d = {"item1": 10, "item2": 20, "item30": 30}

; constants
const int = 100

; pointers
int i = 200
int* pi = i ; as it is a pointer it automatically receives the addess of i
*pi = 300 ; change the value of i, here the # operator is deferencing pi

; references
; unless explictly said, variable, objects are passed by value
; so the use of an operator to mark a variable as a reference is mandatory
float f1 = 0.25;
; f2 is a reference to f1
float& f2 = f1;
```

## Basic statements and loops

### Conditional branchements

```
int i = 10
str s = ""
if (i < 10):
    s = "Less"
elif (i > 10):
    s = "More"
else:
    s = "Equal"

```

## Function

```
; a function that return an integer
; and takes 2 integers arguments
int add(int x, int y):
    int z = x + y
    return z
```

