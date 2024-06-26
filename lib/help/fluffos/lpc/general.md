# general

Types can be used in four places:

    Declaring type of global variables.
    Declaring type of functions.
    Declaring type of arguments to functions.
    Declaring type of local variables in functions.

Normally, the type information is completely ignored, and can be
regarded purely as documentation. The exception is that certain
optimizations can use it, so the compiler is allowed to treat 'x + 0'
as the same as 'x' if 'x' has been declared to be a int variable, but
will not use this trick if 'x' is declared to be a string variable,
since the results would then be different. Also, when the basic type
of a function is declared, then a more strict type checking will be
enforced inside of that function. #pragma strict_types forces
functions to have return values, and hence strict type checking inside
functions is unavoidable. That means that the type of all arguments
must be defined, and the variables can only be used to store values of
the declared type. The function call_other() is defined to return an
unknown type, as the compiler has no way of knowing the return type.
If CAST_CALL_OTHERS is defined, this value must be casted, otherwise
it is assumed to be of type 'mixed'. Casting a type is done by
putting the type name inside a pair of '(' and ')'. Casting has no
effect, except for pacifying the compiler.

An example when querying the short description of an object:

    (string)call_other(ob, "short");

...or...

    (string)ob->short();

When a function is compiled with strict type testing, it can only call other
functions that are already defined. If they are not yet defined, prototypes
must be used to allow the current function to call them.

An example of a prototype:

    string func(int arg);

Note the ';' instead of a body to the function. All arguments can be given
by names, but do not have to have the same names as in the real definition.
All types must of course be the same. The name of the argument can also
be omitted:

    string func(int);

There are two kinds of types. Basic types, and special types. There can be
at most one basic type, but any number of special types assigned to a
variable/function.

The strict type checking is only used by the compiler, not at runtime. So,
it is actually possible to store a number in a string variable even when
strict type checking is enabled.

Why use strict type checking? It is really recommended, because the compiler
will find many errors at compile time, which will save a lot of hard work. It
is in general much harder to trace an error occuring at run time.

The basic types can be divided into groups. Those that are referenced
by value, and those that are referenced by address. The types int,
string, and float are referenced by value. The types mapping,
function, object, and pointers `('<type> \*')` are referenced by address.
If a value of this type is assigned to a variable or passed as
argument, they will all point to the same actual data. That means
that if the value of an element in an array is changed, then it can
modify all other variables pointing to the same array. Changing the
size of the array will always allocate a new one though. The
comparison operator, ==, will compare the actual value for the group
of value-referenced types above. But for arrays, mappings, etc, it
will simply check if it is the same array, mapping, etc. That has the
very important implication that the expression `({ 1 }) == ({ 1 })` will
evaluate to false because the array construction operator-pair,
`({ ... })` always generates a new array.


## Basic types

### int

    An integer number (32 bit).

### float

    A floating point number (32 bit).

### string

    An unlimited string of characters (no '\0' allowed tho).

### object

    A pointer to an object.

### mapping

    A form of associative array; see separate documentation.

### function

    A special type that points to a function of some sort; see
    separate documentation.

### Arrays

    Arrays are declared using a '*' following a basic type. For example,
    declaring an array of numbers: int *arr;. Use the type mixed if you want an
    array of arrays, or a mixed combination of types.

### void

    This type is only usable for functions. It means that the function will not
    return any value. The compiler will complain (when type checking is enabled)
    if a return value is used.

### mixed

    This type is special, in that it is valid to use in any context. Thus, if
    everything was declared mixed, then the compiler would never complain. This
    is of course not the idea. It is really only supposed to be used when a
    variable really is going to contain different types of values. This should
    be avoided if possible. It is not good coding practice to allow a function,
    for example, to return different types.

## Special types

    There are some special types, which can be given before the basic type. These
    special types can also be combined. When using special type T before an
    inherit statement, all symbols defined by inheritance will also get the
    special type T. The only special case is public--defined symbols, which can
    not be redefined as private in a private inheritance statement.

### varargs

    A function of this type can be called with a variable number of arguments.
    Otherwise, the number of arguments is checked, and can generate an error.

### private

    Can be given for both functions and variables. Functions that are private in
    object A can not be called through call_other() in another object. They're
    also not accessable to any object that inherits A.

### static

    This special type behaves different for variables and functions. It is
    similar to private for functions, in that they cannot be called from other
    objects with call_other(). static variables will be neither saved nor
    restored when using save_object() or restore_object().

### public

    A function defined as public will always be accessible from other objects,
    even if private inheritance is used.

### nomask

    All symbols defined as nomask cannot be redefined by inheritance. They can
    still be used and accessed as usual. nomask also blocks functions from
    being shadowed with shadow().
