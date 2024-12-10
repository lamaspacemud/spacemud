inherit SPELL;

void setup()
{
   set_name("conjure ale");
   set_category("conjuration");
}

void cast_spell(object ob, object reagent, int success)
{
   object ale;
   this_body()->simple_action("A streak of ale appears at the wave of $p hand.");
   ale = new ("domains/std/ale");
   ale->move(environment(this_body()));
}
