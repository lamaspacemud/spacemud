# functionp

### NAME

    functionp()  -  determine whether or not a given variable is a function
    pointer, and if so what kind

### SYNOPSIS

    int functionp( mixed arg );

### DESCRIPTION

    Return nonzero if 'arg' is a function pointer and zero  (0)  otherwise.
    Function  pointers are variables of type 'function' as indicated in the
    documentation for the type 'function', for example:

    f = (: obj, func :);

    The return value indicates the type of function pointer using the  val‐
    ues given in the driver include file "include/function.h".

    function pointer type       value
    ---------------------       -----
    call_other                  FP_CALL_OTHER
    lfun                        FP_LOCAL
    efun                        FP_EFUN
    simul_efun                  FP_SIMUL
    functional                  FP_FUNCTIONAL

    In addition, the following values will be added in some cases:
    FP_HAS_ARGUMENTS            arguments provided
    FP_OWNER_DESTED             creator has been dested
    FP_NOT_BINDABLE             not rebindable)

    The last set of values are bit values and can be tested with bit opera‐
    tions. The value FP_MASK is provided for ignoring the bit values and
    testing the basic type of the function pointer.

    Examples:

    To test if a function variable is an efun pointer:

    if ((functionp(f) & FP_MASK) == FP_EFUN) ...

    to test if it has args:

    if (functionp(f) & FP_HAS_ARGUMENTS) ...

### SEE ALSO

    mapp(3),  stringp(3),  pointerp(3),  objectp(3),  intp(3),  bufferp(3),
    floatp(3), nullp(3), undefinedp(3), errorp(3), bind(3), lpc/types/func‐
    tion

