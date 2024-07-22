inherit OBJ;
inherit M_GETTABLE;

string capability;
int level;

mixed *payload;

void mudlib_setup(mixed *p)
{
   set_id("space shuttle pass", "pass", "shuttle pass");
   payload = p;
}

mixed *payload()
{
   return payload;
}

string short()
{
   return "space shuttle pass";
}

string long()
{
   return "A pass that can be inserted into a docking terminal to summon a space shuttle.";
}

int is_docking_pass()
{
   return 1;
}

string query_module_name()
{
   return "shuttle pass";
}

// Can be put into things.
mixed direct_put_obj_wrd_obj(object ob1, string wrd, object ob2)
{
   return 1;
}
