# preprocessor

### LPC Preprocessor Manual

> (Updated 93.07.17)

The preprocessor is a front end to the LPC compiler that provides such
handy features as:

    o   sharing definitions and code (#include)
    o   macros (#define, #undef)
    o   conditional compilation (#if, #ifdef, #ifndef, #else, #elif, #endif)
    o   debugging (#echo)
    o   compiler specific (#pragma)
    o   text formatting short cuts (@, @@)

The first three are identical to C usage, so those already familiar with
C may want to just skim the last few sections of this document.

Note:

    For those directives that begin with '#' (such as #include), the
    '#' symbol must start in the first column (of the line).

Sharing Definitions and Code

This facility is provided through the #include directive.

Syntax 1:

    #include <file.h>

Syntax 2:

    #include "file.h"

Notes:

    The '#include <file.h>' form looks for the file, 'file.h' in the
    system's standard include directories.
    (On TMI this is just '/include'.)

    The '#include "file.h"' form looks for the file, 'file.h' in the
    same directory as the file that is including it.

The #include statement is a way to textually include one file into another.
Putting a statement such as '#include "file.h"' in a file gives the same
effect as if the contents of file.h had been directly entered into the file
at the point where the #include statement occurred.  Included files are
recompiled each time the object that include's them is recompiled.  If the
included file contains variables or functions of the same name as variables
in the file doing the including, then a duplicate-name error will occur at
compile time (in the same way that the error would occur if you simply typed
in file.h rather than using #include).


#### Macros

Macro definitions are used to replace subsequent instances of a given
word with a different sequence of text.  Reasons for doing so include
hiding implementation details, reducing the number of keystrokes, and
ease in changing constants.

Syntax 1:

    #define identifier token_sequence

Syntax 2:

    #define identifier(id_list) token_sequence

Notes:

    As a matter of convention, identifiers are usually capitalized to
    emphasize their presence in the code, and defined close to the
    start of program, or in a separate header file which you #include.

    The second case allows identifiers in the id_list to be substituted
    back into the token_sequence.

Example:

```c
// Create a 40 cell array of integers and initialize each cell
// to its cell number times 2,
//   i.e. stack[0] = 0, stack[1] = 2, stack[2] = 4, etc

#define STACKSIZE 40
#define INITCELL(x) 2*x

int *stack;

create() {
    int i;

    stack = allocate(STACKSIZE);

    for (i = 0; i < STACKSIZE; i++)
    stack[i] = INITCELL(i);
}
```

Lastly, it's sometimes useful to undefine (i.e. make the compiler forget
about) a macro.  The following directive is then used:

Syntax:

    #undef identifier

Note:

    It's perfectly acceptable to undefine an identifier that hasn't been
    defined yet.


#### Conditional Compilation

These directives can add flexibility to your code.  Based on whether an
identifier is defined (or not defined), variations of the code can be
produced for different effects.  Applications include selective admin
logging and support for multiple drivers (or versions of the same driver).

Syntax:

    #ifdef <identifier>
    #ifndef <identifier>
    #if <expression>
    #elif <expression>
    #else
    #endif

Note:

    <identifier> refers to an identifier that has been (or could be) defined
    by your program, a file you have included, or a symbol predefined by
    the driver.

    <expression> is a constant expression that evaluates to a boolean
    condition.  The expression may contain any legal combination of the
    following:
    operators: ||, &&, >>, <<,
               +, -, *, /, %,
               &, |, ^, !, ~,
               ==, !=, <, >, <=, >=, ?:
    parentheses for grouping: (, )
    calls of the form: defined(identifier)

    and identifiers `#ifdef identifier` can be considered shorthand for:
    `#if defined(identifier)`

    `#ifndef identifier` can be considered shorthand for:
    `#if !defined(identifier)`

    `#elif expression` can be considered shorthand for the sequence:
    #else
    #if expression
    #endif

Example 1:

```c
// Using #if 0 allows you to comment out a block of code that
// contains comments.  One reason to do so may be to keep a copy
// of the old code around in case the new code doesn't work.
#if 0
// In this case, the constant expression evaluates
// (or is) 0, so the code here is not compiled

write(user_name + " has " + total_coins + " coins\n");
#else
// This is the alternate case (non-zero), so the code
// here _is_ compiled

printf("%s has %d coins\n", user_name, total_coins);
#endif
```

Example 2:

```c
// This example is derived from TMI's /adm/simul_efun/system.c
#ifdef __VERSION
string version() { return __VERSION__; }
#elif defined(MUDOS_VERSION)
string version() { return MUDOS_VERSION; }
#else
#if defined(VERSION)
string version() { return VERSION; }
#else
string version() { return -1; }
#endif
#endif
```

#### Debugging

The '#echo' directive allows you to print messages to the driver's stderr
(STanDard ERRor) stream.  This facility is useful for diagnostics and
debugging.

Syntax:

    #echo This is a message

Note:

    The rest of the line (or end-of-file, which ever comes first) is the
    message, and is printed verbatim.  It's not necessary to enclose text
    with quotes.


#### Compiler Specific

This facility performs implementation-dependent actions.

Syntax:

    #pragma keyword

At this time the following control keywords are recognized:

    o   strict_types
    o   save_binary
    o   save_types
    o   warnings
    o   optimize
    o   error_context

Also, #pragma no_keyword can be used to turn a pragma off.

Notes:

    'strict_types' informs the compiler that the return value from
    call_other()'d functions must be casted

    'save_binary' informs the compiler to save the binary object;
    loading will go faster after a reboot/shutdown since object has been
    precompiled

    'save_types' is currently unused

    'warnings' enables certain warnings about things in your LPC code which
    probably won't behave the way you intended

    'optimize' takes a second pass over the compiled code to improve it
    slightly

    'error_context' adds more text to error messages indicating where on
    the line the error occured

#### Text Formatting Shortcuts

This facility makes it easier to format text for help messages, room
descriptions, etc.

Syntax 1:

    @marker
    <... text block ...>
    marker

Syntax 2:

    @@marker
    <... text block ...>
    marker

Notes:

    @   - produces a string suitable for write()
    @@  - produces an array of strings, suitable for the body pager

These are used by prepending '@' (or '@@') before an end marker word.  This
is followed by your formatted text, as you would have it appear to the user.
The text block is terminated by the end marker word, without the '@'
(or '@@').  With '@', the text block is processed as if it were a single
string surrounded by quotes and '\n' (newlines) in between the lines.
With '@@', the text block is processed as it were an array of strings,
with each line being a string surrounded by quotes.

Example 1:

```c
int help() {
    write( @ENDHELP
This is the help text.
It's hopelessly inadequate.
ENDHELP
    );
    return 1;
}

Is equivalent to:

```c
int help() {
    write( "This is the help text\nIt's hopelessly inadequate.\n" );
    return 1;
}
```

Example 2:

```c
int help() {
    this_player()->more( @@ENDHELP
This is the help text.
It's hopelessly inadequate.
ENDHELP
    , 1);
    return 1;
}
```

Is equivalent to:

```c
int help() {
    this_player()->more( ({ "This is the help text.",
    "It's hopelessly inadequate." }), 1);
    return 1;
}
```
