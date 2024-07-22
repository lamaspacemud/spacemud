/* Do not remove the headers from this file! see /USAGE for more info. */

inherit LIVING;
inherit M_CONVERSATION;
inherit M_STATEFUL;

#define MAX_MISSIONS 3
#define RENEW_MISSIONS_MINUTES 120

private
mapping missions = ([]);

void generate_key(string key)
{
   object pass = new ("/domains/common/item/shuttle_pass", missions[key]);
   pass->move(this_body());
   this_object()->targetted_action("$N $vhand $o to $t.", pass, this_body());
   map_delete(missions, key);
}

void generate_missions()
{
   string *problems =
       ({"<bld>Power Core Failure:<res> The ship's primary power source has malfunctioned, leading to a complete "
         "systems shutdown.",
         "<bld>Communication Array Damage:<res> The ship's antennas or communication systems have been damaged, "
         "rendering them unable to send or receive signals.",
         "<bld>Navigational System Malfunction:<res> A critical error in the navigational systems has left the ship "
         "adrift and unable to correct its course or send distress signals.",
         "<bld>Hull Breach:<res> A breach in the hull has caused an emergency lockdown, sealing off sections of the "
         "ship and disabling communication.",
         "<bld>Computer Virus:<res> A malicious software attack has crippled the ship's onboard computers, preventing "
         "any form of communication.",
         "<bld>Engine Overload:<res> The ship's engines have experienced a catastrophic failure, resulting in an "
         "emergency shutdown of all systems.",
         "<bld>Life Support System Failure:<res> The life support systems have failed, putting the crew in immediate "
         "danger and prioritizing internal emergency protocols over external communication.",
         "<bld>Hostile Boarding:<res> The ship has been boarded by hostile forces, who have disabled communication to "
         "avoid detection.",
         "<bld>Asteroid Collision:<res> An unexpected collision with an asteroid or space debris has caused "
         "significant damage, disrupting all communication channels.",
         "<bld>Electromagnetic Interference:<res> A nearby cosmic anomaly or enemy device is emitting strong "
         "electromagnetic waves, blocking all outgoing and incoming signals."});
   missions = ([]);
   for (int i = 0; i < MAX_MISSIONS; i++)
   {
      string ship_type = SHIP_D->random_large_ship();
      int size = random(6) + 3;
      string problem = choice(problems);
      missions["mission" + i] = ({ship_type, size, problem});
   }
}

void setup_chats()
{
   mapping responses = (["hello":"Sorry, I do not have time to chat. Did you have a question?@@help"]);
   mapping options =
       (["hello":"Hello, Chief Voss.", "help":"Can I assist the landing operations of Omega Station in some way?"]);
   string *confirmations =
       ({"My team and I will handle the", "We'll attempt to help the", "I decided on the", "I've picked the",
         "We are going for the", "Let's do the", "The", "Umm.. the", "The team has decided that we go for the"});
   string mission_txt = "I have the following \"dark ships\" right now - check back later for other missions:\n\n";
   string mission_list = "";

   foreach (string key in keys(missions))
   {
      mission_list += key + ",";
   }
   mission_list = mission_list[0.. < 1];

   foreach (string key, mixed mish in missions)
   {
      mission_txt +=
          "       <148>" + capitalize(mish[0]) + " category " + mish[1] + "<res>:\n       " + mish[2] + "\n\n";
      options[key] = choice(confirmations) + " <148>" + mish[0] + " category " + mish[1] + "<res>!";
      responses[key] = ({"Okay, the " + mish[0] + " it is then.@@@@nothanks," + mission_list, ( : generate_key, key:)});
   }

   responses["help"] =
       ({mission_txt + "...",
         "Let me know if you want to help with one of these and I'll give you a terminal key to summon a "
         "shuttle.",
         "Higher category of ship means more people needed to handle the situation.",
         "So what will it be?@@nothanks," + mission_list});
   options["nothanks"] = "Nevermind, not right now then. My team is not quite ready.";
   responses["nothanks"] = "Stop wasting my time.@@@@" + mission_list;
   set_responses(responses);
   set_options(options);
}

void begin_conversation()
{
   // Generate missions just in time
   if (!sizeof(keys(missions)))
      generate_missions();
   setup_chats();
   set_start(({"hello"}));

   ::begin_conversation();
}

void setup()
{
   set_gender(2);
   set_name("Aria Voss");
   add_id("aria", "voss", "aria voss", "chief");
   set_proper_name("Aris Voss");
   set_in_room_desc("Chief landing controller Aria Voss");
   set_long("Behind the main counter stands the chief landing controller, Aria Voss, a seasoned veteran with sharp "
            "eyes and an air of authority. She wears a crisp uniform adorned with insignias of her rank and years of "
            "service. Her short-cropped hair is streaked with silver, hinting at her vast experience, and her focused "
            "expression reveals a mind always at work, juggling multiple tasks at once. A headset is permanently "
            "affixed to her ear, connecting her to various ship channels and station personnel.");

   // Refresh the missions every RENEW_MISSIONS_MINUTES
   set_call_interval(RENEW_MISSIONS_MINUTES);
}

int state_update()
{
   if (arrayp(missions))
      exit_conversations();
   missions = 0;
   return 1;
}

string query_hint(int level)
{
   return "Aria Voss provides missions in space around Omega Terminal.";
}
