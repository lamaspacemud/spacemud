# debugmalloc

### NAME

    debugmalloc() - dumps information on malloc'd memory to a file.

### SYNOPSIS

    void debugmalloc( string filename, int mask );

### DESCRIPTION

    This efun is only available when DEBUGMALLOC and DEBUGMALLOC_EXTENSIONS
    are both defined in options.h at driver build time.  The  debugmalloc()
    efun will dump information on those chunks of memory allocated by DMAL‐
    LOC() and related macros if the mask bitwise and'd  (&)  with  the  tag
    supplied  by  the macro (i.e. (mask & tag)) is non-zero.  Read md.c and
    config.h in the driver source for more information.

### SEE ALSO

    set_malloc_mask(3)

