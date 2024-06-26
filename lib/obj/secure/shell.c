/* Do not remove the headers from this file! see /USAGE for more info. */

#include <commands.h>
#include <driver/origin.h>
#include <mudlib.h>
#include <security.h>

inherit M_ACCESS;
inherit M_INPUT;
inherit M_HISTORY;
inherit M_ALIAS;
inherit M_SHELLFUNCS;
inherit M_SAVE;
inherit M_SCROLLBACK;

private
nosave object owner;

varargs void execute_command();
string query_shellname();
string query_save_path(string userid);

protected
function arg_to_words_func = ( : explode($1, " ") :);

// ### goofy fucking hack cuz the shell doesn't save for shit. only M_SAVE,
// ### even though in the alias code it professes to "not require it to be
// ### bound to M_SAVE" ... this is bunk...
private
string save_info;

void setup_for_save()
{
   /*
   ** This object has no variables to save, but many of the moduless do,
   ** so we must dispatch to them.
   */
   alias::setup_for_save();
   shellfuncs::setup_for_save();
}

void save_me()
{
   string name;
   if (!owner) /* probably the blueprint */
      return;
   name = owner->query_userid();

   if (strlen(name) > 5 && name[0..4] == "guest")
      return;

   setup_for_save();
   save_info = save_to_string();
   unguarded(1, ( : save_object, query_save_path(owner->query_userid()) :));
}
protected
void restore_me(string userid)
{
   unguarded(1, ( : restore_object, query_save_path(userid) :));
   if (save_info)
   {
      load_from_string(save_info, 0);
      save_info = 0;
   }
}

void remove()
{
   if (origin() != ORIGIN_LOCAL && owner && previous_object() != owner)
      error("illegal attempt to remove shell object\n");

   save_me();
   destruct();
}

protected
void shell_input(mixed input)
{
   if (input == -1)
   {
      remove();
      return;
   }

   /* we can safely remove leading and trailing whitespace */
   input = trim(input);
   if (input == "")
      return;

   /*
   ** ### WORK IN PROGRESS HERE
   **
   ** Defined from the BASH shell
   **
   ** Evaluation order:
   ** - history expansion
   ** - store in history
   ** - alias expansion
   ** - shell-defined expansion
   **   - TENTATIVELY: wish does: left-to-right: brace, tilde, parameter,
   **     variable, command, arithmetic, then word splitting, then
   **     pathname expansion
   ** - execution
   **
   ** If the command uses parsed arguments (argv syntax), then the only
   ** expansion that can change the number of arguments are: brace
   ** expansion, word splitting, and pathname expansion.  An exception
   ** is the expansion of $@.
   */

   // Skip commands beginning with HISTORY_CHAR, default '#'
   if (input[0] == COMMENT_CHAR)
   {
      return;
   }
   // is this history manipulation?
   else if (input[0] == HISTORY_CHAR)
   {
      input = history_command(input);
      if (!input)
         return;
   }

   add_history_item(input);

   if (input[0] == '\\')
      input = input[1..];
   else
      input = expand_alias(input);

   if (input != "")
      execute_command(input);
}

private
void cmd_exit()
{
   if (modal_stack_size() == 1)
   {
      // ### I think we could just issue the quit command rather than force it
      this_user()->force_me("quit");
      return;
   }
   printf("Exiting %s\n", query_shellname());
   modal_pop();
   remove();
}

void create()
{
   if (!clonep())
      return;

   owner = previous_object();
   if (owner != this_user())
   {
      destruct();
      error("illegal shell object creation\n");
   }

   if (owner)
      restore_me(owner->query_userid());

   alias::create();
   history::create();
}

protected
void add_admincmds()
{
   // Best way to call this since defined in /trans/obj/wish
   string *paths = this_object()->query_path();

   if (sizeof(paths) && adminp() && member_array(TRANS_ADMINCMD_DIR, paths) == -1)
   {
      paths += ({TRANS_ADMINCMD_DIR});
      this_object()->set_variable("path", paths);
      write("*** Added " + TRANS_ADMINCMD_DIR + " to your path as admin.\n");
   }
}

/*
** This function is used internally to prepare a shell for operation.
** Subclasses will typically override to set up bindings and variables
** with shell_bind_if_undefined() or set_if_undefined(), respectively.
*/
protected
void prepare_shell()
{
   shell_bind_if_undefined("alias", ( : cmd_alias:));
   shell_bind_if_undefined("unalias", ( : cmd_remove_alias($1, 1) :));
   shell_bind_if_undefined("history", ( : cmd_history:));
   shell_bind_if_undefined("scrollback", ( : cmd_scrollback:));
   //    shell_bind_if_undefined("exit",	(: cmd_exit :));
   add_admincmds();
}

protected
mixed what_prompt()
{
   return "> ";
}

void start_shell()
{
   if (owner != this_user() || previous_object() != owner)
      error("illegal attempt to take over shell\n");

   modal_push(( : shell_input:), what_prompt());

   prepare_shell();
}

nomask object query_owner()
{
   return owner;
}
