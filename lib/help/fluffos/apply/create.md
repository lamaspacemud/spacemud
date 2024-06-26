# create

### NAME

    create - object initialization

### SYNOPSIS

    void create( void | ... );

### DESCRIPTION

    Every  object  should have a create function defined within it.  Within
    that function, all initial object initialization should be done.   cre‐
    ate()  is called on *all* objects.  *NOTE* - This behavior is different
    than the stock 3.1.2 LPmud driver.  In 3.1.2, if an object  is  created
    first by being inherited, then create() wasn't called on it.  In MudOS,
    this behavior has changed so that it is *always* called when an  object
    is  created.   As a result, you may see some odd behavior if you have a
    create in a parent object that does a write, you will see  two  writes,
    as  if  create() had been called twice on the same object.  In reality,
    create *is* being called twice, but on  two  *different*  objects:  the
    parent, and the child that is calling parent::create() manually.

    The arguments passed to the function will be the same as those passed to
    new() or clone_object() in addition to the filename, if the object was
    loaded using either of those efuns. For example, clone_object(file, 3, "hi")
    will cause create(3, "hi") to be called in the object after it is created.

### SEE ALSO

    reset(4), __INIT(4)

### AUTHOR

    Wayfarer@Portals
