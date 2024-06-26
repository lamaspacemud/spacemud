# notify_fail

### NAME

    int notify_fail( string | function str );

### DESCRIPTION

    Store  'str' as the error message to be returned instead of the default
    message 'What?'.  The message will be displayed if a 0 is returned from
    an action setup via add_action().  This is the preferred way to display
    error messages since it allows other objects a chance to respond to the
    same  verb  (command).  Do not use write() to display the error message
    since this will require you to return a 1 (unless you want to  see  the
    result of the write() in addition to the 'What?' message).  However, if
    you do return a 1, then no other objects will get a chance  to  respond
    to the user command.

    If  a  function  is  passed instead of a string, the function is called
    instead of printing a message.  If the function returns a string,  that
    string is used as the failure message.  Also, this_player() is set cor‐
    rectly, so write() can be used.

    If "notify_fail()" is called more than once, only the  last  call  will
    have an effect.

    The  idea  behind  this function is to allow better error messages than
    'What?'.

### RETURN VALUE

    notify_fail() always returns 0.

