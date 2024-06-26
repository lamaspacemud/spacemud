/* Do not remove the headers from this file! see /USAGE for more info. */

inherit INDOOR_ROOM;

void setup()
{
   set_area("wiz_area");
   set_brief("Grand Hall");
   set_long("The Grand Hall, the meeting place for Lima Wizards, is a large "
            "room with polished wooden floorboards, and rough hewn beams "
            "overhead. A narrow flight of stairs lead upwards, their top "
            "splashed by flickering blue light, while an equally narrow "
            "flight leads downwards into the gloom. Two rocky passages leave "
            "the room. The northwest one is warm and sulfurous, while the "
            "air wafting from the south passage smells as though something "
            "had recently died there. For some bizarre reason, there is an "
            "elevator door off to the west.\n"
            "A low doorway in the east wall allows access to the example "
            "room, a glowing portal in the north wall leads to the mortal "
            "start area, and to the northeast is the quiet room, the door of "
            "which is currently $oak_door.  $lamp");
   set_state_description("oak_door_off", "closed");
   set_state_description("oak_door_on", "open");
   set_state_description("lamp_on", "The lamp beside the elevator is lit.");
   set_exits((["east":"Example_Room1", "south":"Monster_Room", "northwest":"Lava_Room", ]));
   set_objects(([STAIRS:({"Attic", "Shop"}),
        "../object/large_oak_door":({"northeast", "Quiet_Room"}),
                "../object/portal":({"/domains/std/room/beach/Sandy_Beach"}),
              "/std/elevator_door":({"west", "/domains/std/room/elevator"}),
       "/std/elevator_call_button":({"1/lima", "/domains/std/room/elevator"}), "../monster/greeter":1,
                   "../object/map":1, ]));
   set_default_error("Walking through walls is painful. Try a more pleasant "
                     "direction.\n");
   set_exit_msg("east", ({"$N $vwomble east.", "$N $vfritter away."}));
   set_enter_msg("east", ({"$N $venter from the zoo.", "$N $vdecide to pop in for a visit."}));
   set_listen("This is an example sound.  Only you are getting this msg, so "
              "I guess you're hearing voices");
   set_smell("Smells a bit dusty here");
}

void arrived()
{
   if (query_state("lamp"))
      tell_from_inside(this_object(), "The lamp on the button beside the elevator goes out.\n");
   clear_room_state("lamp");
}

mixed query_hint(int level)
{
   if (level > 10)
      return "You're a big wizard, you know all about this room.";
   return ({"This is a room with many different features and examples for state descriptions, objects, listen, smell "
            "and exits.",
            "Read the source by using 'more here' or 'cd here' to go to the directory of this file.",
            "Use 'talk to greeter' for some basic information about the LIMA Mudlib."});
}

// These functions are for testing STATE_D and EVENT_D and schedules.
// Use:
// @EVENT_D->register_event("00 12 *","/domains/std/room/Wizroom","ding")
// to schedule the event to run. Cancel it with
// @EVENT_D->unregister_event("/domains/std/room/Wizroom","ding")

int is_stateful(string d)
{
   return d == "ding" ? 1 : 0;
}

int state_update(string d)
{
   tell_from_outside(this_object(), "A grandfather clock somewhere goes, \"Ding! Dong!\".");
   return 0;
}
