# simul_efun

Simulated efunctions (simul_efuns)

There is a mechanism to allow the mudlib to simulate efunctions. All
simulated efuns must be defined in a special file (the name and location
of which are to be specified in config.example).

When compiling an object and a function call (not a call_other) is found that
has not been defined in the object and is not an efun, then the driver
will search for that function in the list of simulated efuns. If the
function is found in that list, then the driver sets up a call_other to
that function (as defined in the simulated efun file). Note, the result
of the call_other does not have to be typecasted, since the type will be
automatically set by the compiler.

Simulated efuns have many uses. One is that it is now possible to make major
changes (and even removals) to the behavior of efuns without modifying
the driver (by making a simul_efun having the same name as an efun). Suppose
you wish to modify the behavior of the move_object() efun. You could do
so by defining a simulated efun having the same name. The simulated efun
could perform various restrictive checks and then call efun::move_object().
The efun:: prefix is necessary so that the driver will know you wish to call
the move_object efun and not recursively call the simulate_efun within which
the call to move_object is contained. [Note that valid_override() in master.c
can be used to conrol which simul_efuns may be overridden via the efun::
prefix]. Simulated efuns are also useful for adding functions that many
different objects may need to call but which aren't appropriate for
inclusion in an inherited file.

Any function in the simulated efun file that is declared protected, will
not be callable by functions outside the simulated efun file.
