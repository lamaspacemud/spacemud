/* Do not remove the headers from this file! see /USAGE for more info. */

// Tsath, summer 2024 while the others were at the beach.

//: MODULE
// This daemon handles player misisons, and centralizes controling them.
// Missions are generally repeatable, unlike quests that can only be done
// once.
// Missions can be multiplayer experiences, unlike quests that are inherently
// single player. They typically have a mission giver, that can provide a list
// of variants that are available.

inherit M_DAEMON_DATA;
inherit CLASS_MISSION_INFO;

private
mapping missions = ([]);

int is_file(string file)
{
   if (file[ < 2..] != ".c")
      file += ".c";
   return file_length(file) != -1;
}

void unregister_mission(string name)
{
   map_delete(missions, name);
   save_me();
}

void register_mission(string name, string giver, string controller, int rec_level_min, int rec_level_max)
{
   class mission_info mi = new (class mission_info);

   if (!is_file(giver))
      error("No such file '" + giver + "'.");
   if (!is_file(controller))
      error("No such file '" + controller + "'.");
   if (rec_level_max < rec_level_min)
      error("rec_level_max < rec_level_min");

   mi.name = name;
   mi.giver = giver;
   mi.controller = controller;
   mi.rec_level_min = rec_level_min;
   mi.rec_level_max = rec_level_max;

   missions[name] = mi;
   save_me();
}

object *find_givers(string giver)
{
   // Should be cloned, match base name, and have an environment.
   return filter_array(objects(), ( : clonep($1) && base_name($1) == $(giver) && environment($1) :));
}

//: FUNCTION live_missions
// Fetch all the live missions from the mission givers.
// This array will return what is currently available and live.
class mission_info *live_missions(string domain)
{
   class mission_info *live = ({});
   foreach (string name, class mission_info mi in missions)
   {
      string *variants;
      object *givers = find_givers(mi.giver);
      if (!sizeof(givers))
         continue;
      foreach (object g in givers)
      {
         class mission_info mi_cl = clone_class(mi);
         if (domain && strsrch(base_name(environment(g)), "/domains/" + domain) != 0)
            continue;
         mi_cl.location = environment(g)->short() + " [" + g->query_location() + "]";
         variants = g->query_variants(name) || ({"Main"});
         mi_cl.variants = variants;
         mi_cl.giver_name = g->short();
         live += ({mi_cl});
      }
   }
   return live;
}

mapping missions()
{
   return missions;
}

void create()
{
   ::create();
   set_privilege("Mudlib:daemons");
}