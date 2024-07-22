inherit SPACESHIP;

string query_owner();

string shuttle_id = "shuttle-" + random(100000);

void setup()
{
   // Feed the random ID to SHIP_D to get a "proper ship ID"
   shuttle_id = SHIP_D->ship_name(shuttle_id);
   set_id("shuttle", "ship");
   set_brief("Space shuttle " + shuttle_id + " passenger bay");
   set_long(
       "The passenger bay of the Orion X-5 space shuttle is a compact with small round windows on each side, "
       "utilitarian space designed for functionality and efficiency. Rows of padded seats, arranged in pairs on "
       "either side of a narrow aisle, provide seating for up to ten passengers. Each seat is equipped with harnesses "
       "to ensure safety during turbulent phases of the flight. The walls are smooth and unadorned, covered in a "
       "durable, easy-to-clean material, with no access panels or buttons within reach of curious hands. The "
       "bulkhead at the front is sealed off to passengers.\n"
       "An airlock is set in the wall leading outside.");
   add_item(
       "window", "windows",
       "The shuttle's windows are small and reinforced, offering limited but intriguing glimpses of the outer space "
       "beyond. The flooring is made of non-slip material, ensuring safe movement even in zero gravity conditions.");
   add_item("bulkhead",
            "At the front of the bay, a reinforced bulkhead separates the passenger area from the cockpit, with an "
            "intercom system being the only means of communication with the crew. A simple, built-in display screen at "
            "the head of the aisle provides basic flight information and emergency instructions, ensuring passengers "
            "are well-informed without unnecessary distractions.");
   set_ship_cost(50000);
   set_ship_size(5);
   set_ship_type("orion space shuttle");
   set_objects((["^common/item/airlock":1]));
}

// Override the persistance function, since this one is not persisted.
void object_arrived(object ob)
{
   TBUG(ob->short() + " arrived.");
}

// Must be in a spaceship to handle the virtualization
object virtual_create(string arg)
{
   return ::virtual_create(__FILE__, arg);
}