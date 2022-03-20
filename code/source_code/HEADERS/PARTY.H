/*
	Copyright 1998-2003 Interplay Entertainment Corp.  All rights reserved.
*/

#ifndef PARTY_H
#define PARTY_H

/***************************************************************
    The following contain all of the Party information and
    commands for Fallout 2
***************************************************************/

variable How_Many_Party_Members_Are_Injured;
variable How_Many_Party_Members_Armed;

#define FOLLOW_DISTANCE_CLOSE               (3)
#define FOLLOW_DISTANCE_MEDIUM              (6)
#define FOLLOW_DISTANCE_FAR                 (9)

#define obj_in_party(x)                     (party_member_obj(obj_pid(x)) != 0)
// Pointers to the Party Members
// Fallout 2: Alternate 2163
#define MaxStone_Ptr                        party_member_obj(PID_MAXSTONE)
#define Laura_Ptr                           party_member_obj(PID_LAURA)

// Is this person in my party
// Fallout 2: Alternate 2163
#define MaxStone_In_Party                   (MaxStone_Ptr != 0)
#define Laura_In_Party                      (Laura_Ptr != 0)

// Party Size Information
#define party_size                          (party_member_count(DONT_LIST_HIDDEN_MEMBERS) - global_var(GVAR_PLAYER_GOT_CAR))
#define true_party_size                     (party_size - 1)
#define party_max_formula                   (floor(dude_charisma/2) + (has_trait(TRAIT_PERK,dude_obj,PERK_magnetic_personality_perk)))
#define dude_at_max_party_size              ((true_party_size >= (party_max_formula)) or (true_party_size >= 5))
#define party_size_humans                   (MaxStone_Ptr+Laura_Ptr)
#define party_size_male                     (MaxStone_Ptr)
#define party_size_female                   (Laura_Ptr)
#define party_size_strange                  ()
#define party_size_biped                    (party_size_male + party_size_female)

// Health of Party Members
#define Is_Injured(Who)                     (get_critter_stat(Who, STAT_current_hp) < get_critter_stat(Who, STAT_max_hit_points))
#define Injured_How_Much(Who)               (get_critter_stat(Who, STAT_max_hit_points) - get_critter_stat(Who, STAT_current_hp))
#define Is_Crippled(Who)                    (critter_state(Who) BWAND (DAM_CRIP_LEG_LEFT BWOR DAM_CRIP_LEG_RIGHT BWOR DAM_CRIP_ARM_LEFT BWOR DAM_CRIP_ARM_RIGHT))
#define Is_Blind(Who)                       (critter_state(Who) BWAND DAM_BLIND)
//#define Is_Armed(Who)                       (((obj_item_subtype(critter_inven_obj(Who,INVEN_TYPE_RIGHT_HAND))) == item_type_weapon)       \
//                                            or ((obj_item_subtype(critter_inven_obj(Who,INVEN_TYPE_LEFT_HAND))) == item_type_weapon))
#define Is_Armed(Who)                       (((obj_item_subtype(critter_inven_obj(Who,INVEN_TYPE_RIGHT_HAND))) == item_type_weapon))


#define If_Party_Has_Injured                How_Many_Party_Members_Are_Injured := 0;			\
                                            if (MaxStone_In_Party) then                         \
                                                if (Is_Injured(MaxStone_Ptr)) then              \
                                                    How_Many_Party_Members_Are_Injured+=1;      \
                                            if (Laura_In_Party) then                            \
                                                if (Is_Injured(Laura_Ptr)) then                 \
                                                    How_Many_Party_Members_Are_Injured+=1;      \
                                            if (How_Many_Party_Members_Are_Injured > 0)


#define If_Party_Is_Armed                   How_Many_Party_Members_Armed := 0;                  \
                                            if (dude_is_armed) then                             \
                                               How_Many_Party_Members_Armed+=1;                 \
                                            if (MaxStone_In_Party) then                         \
                                                if (Is_Armed(MaxStone_Ptr)) then                \
                                                    How_Many_Party_Members_Armed+=1;            \
                                            if (Laura_In_Party) then                            \
                                                if (Is_Armed(Laura_Ptr)) then                   \
                                                    How_Many_Party_Members_Armed+=1;            \
                                            if (How_Many_Party_Members_Armed > 0)


// Taken out because Goris should never       if (Goris_In_Party) then                            \
// appear armed.                                  if (Is_Armed(Goris_Ptr)) then                   \
//                                                    How_Many_Party_Members_Armed+=1;            \


#define Party_Childkiller_Mask              (bit_2 BWOR bit_4)

#define attempt_place_party_member(the_obj, the_tile, the_elev)            \
         if (the_obj != 0) then begin                                      \
            if (obj_is_visible_flag(the_obj)) then begin                   \
               critter_attempt_placement(the_obj, the_tile, the_elev);     \
            end                                                            \
         end
#define attempt_place_party(the_tile, the_elev)                                     \
         attempt_place_party_member(MaxStone_Ptr, the_tile, the_elev)               \
         attempt_place_party_member(Laura_Ptr, the_tile, the_elev)

//#define Party_Childkiller                   (global_var(GVAR_PARTY_CHILDKILLER) BWAND Party_Childkiller_Mask)

#define Childkiller_MaxStone                ((global_var(GVAR_PARTY_CHILDKILLER) BWAND bit_2) and (MaxStone_Ptr != 0))
#define Childkiller_Laura                   ((global_var(GVAR_PARTY_CHILDKILLER) BWAND bit_4) and (Laura_Ptr != 0))


#define Party_Childkiller                   (Childkiller_MaxStone or Childkiller_Laura)

//#define inc_party_childkiller(who)          if () then

variable PartyHealingItem;

#define obj_heal(who)                        if (obj_is_carrying_obj_pid(who,PID_SUPER_STIMPAK)) then begin                     \
                                                gfade_out(600);                                                                 \
                                                gfade_in(600);                                                                  \
                                                PartyHealingItem:=obj_carrying_pid_obj(who,PID_SUPER_STIMPAK);                  \
                                                use_obj_on_obj(PartyHealingItem,who);                                           \
                                                debug_msg(obj_name(who)+" used super stimpak.");                                \
                                             end                                                                                \
                                             else if (obj_is_carrying_obj_pid(who,PID_STIMPAK)) then begin                      \
                                                gfade_out(600);                                                                 \
                                                gfade_in(600);                                                                  \
                                                use_obj_on_obj(obj_carrying_pid_obj(who,PID_STIMPAK),who);                      \
                                                debug_msg(obj_name(who)+" used stimpak.");                                      \
                                             end                                                                                \
                                             else if (obj_is_carrying_obj_pid(who,PID_HEALING_POWDER)) then begin               \
                                                gfade_out(600);                                                                 \
                                                gfade_in(600);                                                                  \
                                                use_obj_on_obj(obj_carrying_pid_obj(who,PID_HEALING_POWDER),who);               \
                                                debug_msg(obj_name(who)+" used healing powder.");                               \
                                             end                                                                                \
                                             else if (obj_is_carrying_obj_pid(who,PID_DOCTORS_BAG)) then begin                  \
                                                gfade_out(600);                                                                 \
                                                gfade_in(600);                                                                  \
                                                use_obj_on_obj(obj_carrying_pid_obj(who,PID_DOCTORS_BAG),who);                  \
                                                debug_msg(obj_name(who)+" used doctor's bag kit.");                             \
                                             end                                                                                \
                                             else if (obj_is_carrying_obj_pid(who,PID_FIRST_AID_KIT)) then begin                \
                                                gfade_out(600);                                                                 \
                                                gfade_in(600);                                                                  \
                                                use_obj_on_obj(obj_carrying_pid_obj(who,PID_FIRST_AID_KIT),who);                \
                                                debug_msg(obj_name(who)+" used First Aid kit.");                                \
                                             end                                                                                \
                                             else if (has_skill(who,SKILL_DOCTOR) > has_skill(who,SKILL_FIRST_AID)) then begin  \
                                                gfade_out(600);                                                                 \
                                                gfade_in(600);                                                                  \
                                                game_time_advance(ONE_GAME_HOUR);                                               \
                                                if (is_success(roll_vs_skill(who,SKILL_DOCTOR,0))) then begin                   \
                                                    critter_heal(who,random(10,25));                                            \
                                                    debug_msg(obj_name(who)+" healed some using doctor skill.");                \
                                                end                                                                             \
                                             end                                                                                \
                                             else begin                                                                         \
                                                gfade_out(600);                                                                 \
                                                gfade_in(600);                                                                  \
                                                game_time_advance(15*ONE_GAME_MINUTE);                                          \
                                                if (is_success(roll_vs_skill(who,SKILL_FIRST_AID,0))) then begin                \
                                                    critter_heal(who,random(5,15));                                             \
                                                    debug_msg(obj_name(who)+" healed some using first aid skill.");             \
                                                end                                                                             \
                                             end                                                                                \



//Hiding party members, by Chris Holland
//GVAR_PARTY_MEMBERS_HIDDEN

/*

#define set_p_hidden_flag_obj(x, the_ptr, the_bit)                   \
         if (x == the_ptr) then begin                                \
            set_gvar_bit_on(GVAR_PARTY_MEMBERS_HIDDEN, the_bit);     \
         end
#define set_p_hidden_flag(x)                                                                    \
         set_p_hidden_flag_obj(x, Vic_Ptr, hidden_vic_bit)                                      \
         else set_p_hidden_flag_obj(x, Myron_Ptr, hidden_myron_bit)                             \
         else set_p_hidden_flag_obj(x, Marcus_Ptr, hidden_marcus_bit)                           \
         else set_p_hidden_flag_obj(x, MacRae_Ptr, hidden_macrae_bit)                           \
         else set_p_hidden_flag_obj(x, Sulik_Ptr, hidden_sulik_bit)                             \
         else set_p_hidden_flag_obj(x, Lenny_Ptr, hidden_lenny_bit)                             \
         else set_p_hidden_flag_obj(x, Cyberdog_Ptr, hidden_cyberdog_bit)                       \
         else set_p_hidden_flag_obj(x, Doc_Ptr, hidden_doc_bit)                                 \
         else set_p_hidden_flag_obj(x, Goris_Ptr, hidden_goris_bit)                             \
         else set_p_hidden_flag_obj(x, Davin_Ptr, hidden_davin_bit)                             \
         else set_p_hidden_flag_obj(x, Miria_Ptr, hidden_miria_bit)                             \
         else set_p_hidden_flag_obj(x, Robobrain_Ptr, hidden_robobrain_bit)                     \
         else set_p_hidden_flag_obj(x, Dogmeat_Ptr, hidden_dogmeat_bit)                         \
         else set_p_hidden_flag_obj(x, Pariah_Dog_Ptr, hidden_pariah_dog_bit)                   \
         else set_p_hidden_flag_obj(x, K9_Ptr, hidden_k9_bit)                                   \
         else set_p_hidden_flag_obj(x, Robobrain_Human_Ptr, hidden_robobrain_human_bit)         \
         else set_p_hidden_flag_obj(x, Robobrain_Abnormal_Ptr, hidden_robobrain_abnormal_bit)   \
         else set_p_hidden_flag_obj(x, Robobrain_Chimp_Ptr, hidden_robobrain_chimp_bit)

#define unset_p_hidden_flag_obj(x, the_ptr, the_bit)                    \
         if (x == the_ptr) then begin                                   \
            set_gvar_bit_off(GVAR_PARTY_MEMBERS_HIDDEN, the_bit);       \
         end
#define unset_p_hidden_flag(x)                                                                     \
         unset_p_hidden_flag_obj(x, Vic_Ptr, hidden_vic_bit)                                       \
         else unset_p_hidden_flag_obj(x, Myron_Ptr, hidden_myron_bit)                              \
         else unset_p_hidden_flag_obj(x, Marcus_Ptr, hidden_marcus_bit)                            \
         else unset_p_hidden_flag_obj(x, MacRae_Ptr, hidden_macrae_bit)                            \
         else unset_p_hidden_flag_obj(x, Sulik_Ptr, hidden_sulik_bit)                              \
         else unset_p_hidden_flag_obj(x, Lenny_Ptr, hidden_lenny_bit)                              \
         else unset_p_hidden_flag_obj(x, Cyberdog_Ptr, hidden_cyberdog_bit)                        \
         else unset_p_hidden_flag_obj(x, Doc_Ptr, hidden_doc_bit)                                  \
         else unset_p_hidden_flag_obj(x, Goris_Ptr, hidden_goris_bit)                              \
         else unset_p_hidden_flag_obj(x, Davin_Ptr, hidden_davin_bit)                              \
         else unset_p_hidden_flag_obj(x, Miria_Ptr, hidden_miria_bit)                              \
         else unset_p_hidden_flag_obj(x, Robobrain_Ptr, hidden_robobrain_bit)                      \
         else unset_p_hidden_flag_obj(x, Dogmeat_Ptr, hidden_dogmeat_bit)                          \
         else unset_p_hidden_flag_obj(x, Pariah_Dog_Ptr, hidden_pariah_dog_bit)                    \
         else unset_p_hidden_flag_obj(x, K9_Ptr, hidden_k9_bit)                                    \
         else unset_p_hidden_flag_obj(x, Robobrain_Human_Ptr, hidden_robobrain_human_bit)          \
         else unset_p_hidden_flag_obj(x, Robobrain_Abnormal_Ptr, hidden_robobrain_abnormal_bit)    \
         else unset_p_hidden_flag_obj(x, Robobrain_Chimp_Ptr, hidden_robobrain_chimp_bit)

variable tmp_hidden;

#define party_member_hide(x)                                                                 \
   if (x) then begin                                                                         \
      if (obj_is_visible_flag(x)) then begin                                                 \
         set_p_hidden_flag(x)                                                                \
         set_obj_visibility(x, 1);                                                           \
      end else begin                                                                         \
         debug_msg("PARTY.H:::: no party member hidden because they already are invisible"); \
      end                                                                                    \
   end

#define party_member_unhide(x)                                                            \
   if (x) then begin                                                                      \
      if (obj_is_visible_flag(x) == 0) then begin                                         \
         get_p_hidden_flag(x, tmp_hidden)                                                 \
         if (tmp_hidden) then begin                                                       \
            unset_p_hidden_flag(x)                                                        \
            set_obj_visibility(x, 0);                                                     \
         end else begin                                                                   \
            debug_msg("PARTY.H:::: party member wasn't hidden by my macro");              \
         end                                                                              \
      end else begin                                                                      \
         unset_p_hidden_flag(x)                                                           \
         debug_msg("PARTY.H:::: party member wasn't hidden.. clearing my state");         \
      end                                                                                 \
   end

*/
#define get_p_hidden_flag_obj(x, the_ptr, the_bit, the_var)             \
         if (x == the_ptr) then begin                                   \
            the_var := gvar_bit(GVAR_PARTY_MEMBERS_HIDDEN, the_bit);    \
         end
#define get_p_hidden_flag(x, hidden)                                                                     \
          get_p_hidden_flag_obj(x, MaxStone_Ptr, hidden_maxstone_bit, hidden)                            \
          else get_p_hidden_flag_obj(x, Laura_Ptr, hidden_laura_bit, hidden)

#define party_member_hidden(x, result)                                           \
   if (x) then begin                                                             \
      if (obj_is_visible_flag(x) == 0) then begin                                \
         get_p_hidden_flag(x, result)                                            \
         if (result) then begin                                                  \
            result := 1;                                                         \
         end else begin                                                          \
            result := 0;                                                         \
            debug_msg("PARTY.H:::: party member hidden but not my my macro.. "); \
         end                                                                     \
      end                                                                        \
   end

#define hidden_maxstone_bit                  bit_1
#define hidden_laura_bit                     bit_2
#define all_hidden_bit                       bit_3

#define party_bit_hidden(x)                  (gvar_bit(GVAR_PARTY_MEMBERS_HIDDEN, x))

#define all_party_hidden                     party_bit_hidden(all_hidden_bit)
#define set_party_bit_hidden(x, member)      set_gvar_bit_on(GVAR_PARTY_MEMBERS_HIDDEN, x); set_obj_visibility(member, 1)
#define party_member_hide(the_obj, the_bit)                                                        \
         if (the_obj) then begin                                                                   \
            if (obj_is_visible_flag(the_obj)) then begin                                           \
               set_party_bit_hidden(the_bit, the_obj);                                             \
            end else begin                                                                         \
               debug_msg("PARTY.H:::: no party member hidden because they already are invisible"); \
            end                                                                                    \
         end
#define party_member_hide_all                                                       \
         set_gvar_bit_on(GVAR_PARTY_MEMBERS_HIDDEN, all_hidden_bit);                \
         party_member_hide(MaxStone_Ptr, hidden_maxstone_bit)                       \
         party_member_hide(Laura_Ptr, hidden_laura_bit)

#define all_party_unhidden                   (all_party_hidden == false)
#define set_party_bit_unhidden(x, member)    debug_msg("unhiding party member "+obj_name(member)); set_gvar_bit_off(GVAR_PARTY_MEMBERS_HIDDEN, x); set_obj_visibility(member, 0)
#define party_member_unhide(the_obj, the_bit)                                                   \
         if (the_obj) then begin                                                                \
            if (obj_is_visible_flag(the_obj) == 0) then begin                                   \
               if (party_bit_hidden(the_bit)) then begin                                        \
                  set_party_bit_unhidden(the_bit, the_obj);                                     \
               end else begin                                                                   \
                  debug_msg("PARTY.H:::: party member wasn't hidden by my macro");              \
               end                                                                              \
            end else begin                                                                      \
               set_party_bit_unhidden(the_bit, the_obj);                                        \
               debug_msg("PARTY.H:::: party member wasn't hidden.. clearing my state");         \
            end                                                                                 \
         end
#define party_member_unhide_all                                                        \
         set_gvar_bit_off(GVAR_PARTY_MEMBERS_HIDDEN, all_hidden_bit);                  \
         party_member_unhide(MaxStone_Ptr, hidden_maxstone_bit)                        \
         party_member_unhide(Laura, hidden_robobrain_chimp_bit)
//End hiding party members


// Default
// party member health states
#define party_healed_max                     (self_cur_hits == self_max_hits)
#define party_healed_good                    (((self_cur_hits * 100)/self_max_hits) >= 90)
#define party_healed_hurt                    (((self_cur_hits * 100)/self_max_hits) >= 70)
#define party_healed_bad                     (((self_cur_hits * 100)/self_max_hits) < 70)

// Generic Options for party members
#define def_heal_msg                         g_mstr(10001)
#define def_wait_msg                         g_mstr(10002)
#define def_unarm_msg                        g_mstr(10003)
#define def_close_msg                        g_mstr(10004)
#define def_med_msg                          g_mstr(10005)
#define def_far_msg                          g_mstr(10006)
#define def_end_msg                          g_mstr(10007)
#define def_follow_msg                       g_mstr(10008)
#define def_gear_msg                         g_mstr(10009)
#define def_ignore_follow_msg                g_mstr(10010)
#define def_ignore_gear_msg                  g_mstr(10011)
#define def_armor_msg                        g_mstr(10012)
#define def_weapon_use_msg                   g_mstr(10013)
#define def_nowait_msg                       g_mstr(10100)
#define def_stupid_msg                       g_mstr(random(300, 303))

#define DEF_PARTY_HEAL_NODE                  PartyOption_HealYourself
#define DEF_PARTY_WAIT_NODE                  PartyOption_Wait
#define DEF_UNARM_NODE                       PartyOption_PutDownTheWeapon
#define DEF_FOLLOW_CLOSE_NODE                PartyOption_FollowClose
#define DEF_FOLLOW_MEDIUM_NODE               PartyOption_FollowMedium
#define DEF_FOLLOW_FAR_NODE                  PartyOption_FollowFar
#define DEF_PARTY_FOLLOW_NODE                PartyOption_FollowOptions
#define DEF_PARTY_GEAR_NODE                  PartyOption_GearMenu
#define DEF_REMOVE_ARMOR_NODE                PartyOption_RemoveArmor
#define DEF_WEAPON_USE_NODE                  PartyOption_Tell_Good_Weapons
#define DEF_PARTY_NOWAIT_NODE                PartyOption_StopWaiting
#define DEF_PARTY_END_NODE                   Node999
#define DEF_PARTY_STUPID_NODE                Node999
#define party_member_options(heal_msg, follow_msg, gear_msg, wait_msg, nowait_msg, end_msg, stupid_msg)  \
                                             if (party_is_waiting == false) then begin                   \
                                                if (local_var(LVAR_FOLLOW_DISTANCE) == 0) then begin     \
                                                   set_follow_medium;                                    \
                                                end                                                      \
                                                if (heal_msg != 0) then begin                            \
                                                   if (self_cur_hits < self_max_hits) then begin         \
                                                      NOption(heal_msg, DEF_PARTY_HEAL_NODE, 001);       \
                                                   end                                                   \
                                                end                                                      \
                                                if (follow_msg != 0) then begin                          \
                                                   NOption(follow_msg, DEF_PARTY_FOLLOW_NODE, 001);      \
                                                end                                                      \
                                                if (gear_msg != 0) then begin                            \
                                                   NOption(gear_msg, DEF_PARTY_GEAR_NODE, 001);          \
                                                end                                                      \
                                                if (wait_msg != 0) then begin                            \
                                                   NOption(wait_msg, DEF_PARTY_WAIT_NODE, 001);          \
                                                end                                                      \
                                             end else if (nowait_msg != 0) then begin                    \
                                                NOption(nowait_msg, DEF_PARTY_NOWAIT_NODE, 001);         \
                                             end                                                         \
                                             if (end_msg != 0) then begin                                \
                                                NOption(end_msg, DEF_PARTY_END_NODE, 001);               \
                                             end                                                         \
                                             if (stupid_msg != 0) then begin                             \
                                                NOption(stupid_msg, DEF_PARTY_STUPID_NODE, -003);        \
                                             end                                                         \
                                             debug_msg("USED PARTY MEMBER OPTIONS")
// this goes into node 1007
#define party_follow_options(close_msg, med_msg, far_msg, follow_ignore_msg)                                                  \
                                             if (close_msg != 0) then begin                                                   \
                                                if (local_var(LVAR_FOLLOW_DISTANCE) != FOLLOW_DISTANCE_CLOSE) then begin      \
                                                   NOption(close_msg, DEF_FOLLOW_CLOSE_NODE, 001);                            \
                                                end                                                                           \
                                             end                                                                              \
                                             if (med_msg != 0) then begin                                                     \
                                                if (local_var(LVAR_FOLLOW_DISTANCE) != FOLLOW_DISTANCE_MEDIUM) then begin     \
                                                   NOption(med_msg, DEF_FOLLOW_MEDIUM_NODE, 001);                             \
                                                end                                                                           \
                                             end                                                                              \
                                             if (far_msg != 0) then begin                                                     \
                                                if (local_var(LVAR_FOLLOW_DISTANCE) != FOLLOW_DISTANCE_FAR) then begin        \
                                                   NOption(far_msg, DEF_FOLLOW_FAR_NODE, 001);                                \
                                                end                                                                           \
                                             end                                                                              \
                                             if (follow_ignore_msg != 0) then begin                                           \
                                                NOption(follow_ignore_msg, PARTY_NODE_X, 001);                                \
                                             end                                                                              \
                                             debug_msg("USED PARTY FOLLOW OPTIONS")

// this goes into node 1008
#define party_gear_options(weapon_use_msg, unarm_msg, armor_msg, gear_ignore_msg)                     \
                                             if (weapon_use_msg != 0) then begin                      \
                                                NOption(weapon_use_msg, DEF_WEAPON_USE_NODE, 001);    \
                                             end                                                      \
                                             if (unarm_msg != 0) then begin                           \
                                                if (self_is_armed) then begin                         \
                                                   NOption(unarm_msg, DEF_UNARM_NODE, 001);           \
                                                end                                                   \
                                             end                                                      \
                                             if (armor_msg != 0) then begin                           \
                                                if (self_wearing_armor) then begin                    \
                                                   NOption(armor_msg, DEF_REMOVE_ARMOR_NODE, 001);    \
                                                end                                                   \
                                             end                                                      \
                                             if (gear_ignore_msg != 0) then begin                     \
                                                NOption(gear_ignore_msg, PARTY_NODE_X, 001);          \
                                             end                                                      \
                                             debug_msg("USED PARTY GEAR OPTIONS")

#define party_member_default_options         party_member_options(def_heal_msg, def_follow_msg, def_gear_msg, def_wait_msg, def_nowait_msg, def_end_msg, def_stupid_msg)
#define party_member_def_follow_options      party_follow_options(def_close_msg, def_med_msg, def_far_msg, def_ignore_follow_msg)
#define party_member_def_gear_options        party_gear_options(def_weapon_use_msg, def_unarm_msg, def_armor_msg, def_ignore_gear_msg)

// party member follow macros
#define party_no_follow_on                   set_global_var(GVAR_PARTY_NO_FOLLOW, 1)
#define party_no_follow_off                  set_global_var(GVAR_PARTY_NO_FOLLOW, 0)
#define party_no_follow                      (global_var(GVAR_PARTY_NO_FOLLOW) != 0)

#define set_follow_close                     set_local_var(LVAR_FOLLOW_DISTANCE, FOLLOW_DISTANCE_CLOSE)
#define set_follow_medium                    set_local_var(LVAR_FOLLOW_DISTANCE, FOLLOW_DISTANCE_MEDIUM)
#define set_follow_far                       set_local_var(LVAR_FOLLOW_DISTANCE, FOLLOW_DISTANCE_FAR)
#define party_member_follow_dude             if ((party_is_waiting == false) and (party_no_follow == false)) then begin                \
                                                if (local_var(LVAR_FOLLOW_DISTANCE) == 0) then begin                                   \
                                                   set_follow_medium;                                                                  \
                                                end                                                                                    \
                                                follow_dude_point(((3*local_var(LVAR_FOLLOW_DISTANCE))/2), local_var(LVAR_FOLLOW_DISTANCE))  \
                                             end

// party member team macros
#define set_default_party_follow             set_follow_medium
#define store_party_team                     if (self_team != TEAM_PLAYER) then begin                 \
                                                set_local_var(LVAR_TEAM, self_team);                  \
                                             end
#define party_add_self                       if (local_var(LVAR_FOLLOW_DISTANCE) == 0) then begin                       \
                                                set_default_party_follow;                                               \
                                             end                                                                        \
                                             debug_msg("join party: " + self_name);                                     \
                                             set_local_var(LVAR_WAITING, 0);                                            \
                                             store_party_team                                                           \
                                             critter_add_trait(self_obj, TRAIT_OBJECT, OBJECT_TEAM_NUM, TEAM_PLAYER);   \
                                             party_add(self_obj)
#define party_remove_self                    party_remove(self_obj)

// party member abandons party macros
#define abandoned_party                      (local_var(LVAR_TEAM) == -1)
#define set_self_abandon_party               if (obj_in_party(self_obj)) then begin                                                \
                                                debug_msg("abandon party: " + self_name);                                          \
                                                party_remove_self;                                                                 \
                                             end                                                                                   \
                                             if ((self_pid == PID_MIRIA) or (self_pid == PID_DAVIN)) then begin                    \
                                                set_dude_was_married;                                                              \
                                             end                                                                                   \
                                             if (local_var(LVAR_TEAM) != -1) then begin                                            \
                                                 critter_add_trait(self_obj, TRAIT_OBJECT, OBJECT_TEAM_NUM, local_var(LVAR_TEAM)); \
                                             end                                                                                   \
                                             set_local_var(LVAR_TEAM, -1)

// party member waiting macros
#define party_is_waiting                     (local_var(LVAR_WAITING) != 0)
#define set_party_waiting                    set_local_var(LVAR_WAITING, game_time);      \
                                             party_remove_self
#define end_party_waiting                    set_local_var(LVAR_WAITING, 0);              \
                                             party_add_self


/***************************************************************************************
   This is to check to see if there are any party members within range of the door
   so it doesn't close.
****************************************************************************************/

/* How far do party members have to be from the door before it closes */
#define PARTY_CLOSE_DIST                (5)

#define CHECKMEMBERNEARDOOR(inparty, obj)                                           \
         if (inparty) then begin                                                    \
            if (tile_distance_objs(self_obj, obj) <= PARTY_CLOSE_DIST) then begin   \
               return 1;                                                            \
            end                                                                     \
         end

procedure checkPartyMembersNearDoor begin
   CHECKMEMBERNEARDOOR(MaxStone_In_Party, MaxStone_Ptr)
   CHECKMEMBERNEARDOOR(Laura_In_Party, Laura_Ptr)
   return 0;
end

#define party_member_map_enter                        if (cur_map_index == MAP_MODOC_BEDNBREAKFAST or cur_map_index == MAP_THE_SQUAT_A or cur_map_index == MAP_THE_SQUAT_B) then \
                                                         if ((self_elevation != dude_elevation) and (party_is_waiting)) then move_to(self_obj, self_tile, dude_elevation)

#endif // PARTY_H
