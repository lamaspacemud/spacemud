# mappings

Mappings usage 1992 September 28

Documentation on MudOS's mapping datatype - written by Truilkan@TMI:

MudOS 0.9 provides a datatype calling the 'mapping'. Mappings are
the equivalent of associative arrays found in other languages (e.g. Perl).
An associative array is similar to a regular array except that associative
arrays can be indexed by any type of data (string, object, int, array, etc)
rather than just integers. In addition, associative arrays are sparse arrays
which means you can have a mapping which has a value for its 1,000,000th
element without having values for any other elements. Two particularly
effective uses for mappings are: 1) databases, and 2) a substitute for the
aggregate type 'struct' (as used in the C language) by representing each
field of the C struct as a key in the mapping.

A mapping is declared like this:

    mapping x;

A mapping can be initialized in one of two ways:

    x = ([key0 : value0, key1 : value1, ...]);

note: `x = ([]);` can be used to create an empty mapping

Note that a mapping _must_ be initialized before you may assign any elements
to it. This restriction exists because of the way the gamedriver
initializes all variables (regardless of type) to zero (0). If you do not
initialize the mapping, then you'll see an "Indexing on illegal type" error
when you try to assign an element to the mapping.

New (key, value) pairs may be added to the map in the following way:

    x[key] = value;

The above statement causes the driver to search the mapping named 'x' for the
specified key. If the mapping contains that key, then the associated value
(in the mapping) is replaced with the value on the right hand side of the
assignment. If the mapping does not already contain that key, then
additional space is automatically allocated (dynamically) and the
(key, value) pair is inserted into the mapping.

An element of a mapping may be referenced as follows:

    write(x[key] + "\n");

An element of a mapping may be deleted as follows:

    map_delete(x, key);

this deletion will cause the following expression to evaluate to true (1):

    undefinedp(x[key])

so that you could write code such as this:

```c
if (undefinedp(value = x["MudOS"])) {
    write("'MudOS' is not used as a key in the mapping 'x'\n");
} else {
    write("the value for the key 'MudOS' is " + value + "\n");
}
```

A list of the keys (indices) may be obtained using the keys() efun, for
example:

```c
mixed *idx;
map x;

x = ([ "x" : 3, "y" : 4]);
idx = keys(x);  /* idx == ({"x", "y"}) or ({"y", "x"}) */
```

Note that keys() will return the list of indices in an apparently random
order (the order is a side effect of the implementation used to store
the mapping -- in this case, an extensible hash table).

A list of the values in a mapping may be obtained using the values()
efun, for example:

    idx = values(x);

causes idx to be equal to ({3, 4}) or ({4, 3}). Note that values() will
return the values in the same order as keys() returns the corresponding
keys.

---
The (key, value) pairs in a mapping may be iterated over using the each()
efun. each() returns a null vector when the end of the mapping is reached.
each() returns the (key, value) pairs in the same order as keys() and values()
do. For example:

```c
mixed *pair;

while ((pair = each(x)) != ({})) {
    write("key   = " + pair[0] + "\n");
    write("value = " + pair[1] + "\n");
}
```

`Warning: each is not a efun in fluffos, you can simul it.`

---

Mappings can be two-dimensional (or n-dimensional for that matter) in the same
sense that LPC arrays can be.

    mapping x, y;

    x = ([]);
    y = ([]);

    y["a"] = "c";
    x["b"] = y;

And then :

    x["b"]["a"]  == "c"

Mappings can also be composed using the '*' operator (composed in the
mathematical sense of the word):

    mapping r1, r2, a;

    r1 = ([]);
    r2 = ([]);

    r1["driver"] = "mudlib";
    r2["mudlib"] = "castle";

so:

    a = r1 * r2

defines a to be a map with:

    a["driver"] == "castle";

You may also add two mappings. The sum of two mappings is defined
as the union of the two mappings.

    a = r1 + r2

defines a to be a map with `a["driver"] == "mudlib"` and `a["mudlib"] == "castle"`

The += operator is also supported. Thus you could use:

    a += ([key : value]);

as a substitute for:

    a[key] = value;

However, the latter form (a[key] = value) is much more efficient since
the former (in the present implementation) involves the creation of a new
mapping while the latter does not.

The subtraction operator is not defined for mappings (use map_delete()).

The sizeof() efun may be used to determine how many (key, value) pairs
are in the mapping. For example,

    write("The mapping 'x' contains " + sizeof(x) + " elements.\n");

the implementation:

MudOS's mappings are implemented using an extensible hash table. The
size of the hash table is always a power of 2. When a certain percentage
of the hash table buckets become full, the size of the hash table is
doubled in order to maintain the efficiency of accesses to the hash
table.

credits:

MudOS's mappings were originally implemented by Whiplash@TMI. Parts of
the implementation were later rewritten by Truilkan@TMI (to use an
extensible hash table rather than a binary tree).

Parts of the data structure used to implement mappings are based on
the hash.c module from the Perl programming language by Larry Wall.
The Perl package is covered under the GNU Copyleft general public license.
