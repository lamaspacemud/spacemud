/* Do not remove the headers from this file! see /USAGE for more info. */

/*
** dismount.c
*/

//: COMMAND
// USAGE
//
//  |  ``dismount``
//  |  ``dismount <something>``
//
// Dismount something you're sitting on, a high chair or a horse.
//
// .. TAGS: RST

inherit VERB_OB;

void do_dismount_obj(object ob)
{
   ob->do_verb_rule("dismount", "OBJ", ob);
}

void do_dismount()
{
   environment(this_body())->do_verb_rule("dismount");
}

void create()
{
   add_rules(({"", "OBJ"}));
}
