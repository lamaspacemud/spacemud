# author_file

### NAME

    author_file - determine the author for a given object

### SYNOPSIS

    string author_file (string file);

### DESCRIPTION

    This  function  must  exist  in the master object.  It is called by the
    author statistic functions in the driver to  determine  what  author  a
    given  object should be associated with.  This is totally arbitrary and
    up to the mudlib designers wishes.  It should be noted that the  author
    that  the  object  is  assigned to will receive "credit" for all of the
    objects behavior (errors, heart_beats, worth, etc).

    At startup the driver  will  ask  for  the  master  author  by  calling
    author_file(__MASTER_FILE__).

### SEE ALSO

    author_stats(3), domain_stats(3), domain_file(4)

