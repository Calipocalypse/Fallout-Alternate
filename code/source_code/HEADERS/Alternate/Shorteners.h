/* They are common used lines but shortened */

//timed_event_p_proc
#define ate                                  add_timer_event
#define ates(time,fixed_param)               add_timer_event(self_obj,time,fixed_param);

//text floaters
#define floaterdude(mstrnum)                 float_msg(dude_obj,mstr(mstrnum),FLOAT_MSG_BLUE);

//critter TRAITS
#define critter_team(Team)	                 critter_add_trait(self_obj,TRAIT_OBJECT,OBJECT_TEAM_NUM,Team);
#define critter_team_next(Team, Critter)     critter_add_trait(Critter,TRAIT_OBJECT,OBJECT_TEAM_NUM,Team);
#define critter_ai(Ai)                       critter_add_trait(self_obj,TRAIT_OBJECT,OBJECT_AI_PACKET,Ai);

//critter flags
#define set_self_visible                     set_obj_visibility(self_obj,false);
#define set_self_invisible                   set_obj_visibility(self_obj,true);

//items weapons giving inventory
#define add_new_obj_to_dude(object_pid)		 add_obj_to_inven(dude_obj,create_object(object_pid,0,0));

/* For Template */
#define SET_HOME_TILE if local_var(LVAR_Home_Tile) == 0 then set_local_var(LVAR_Home_Tile, self_tile);
#define HOME_TILE     local_var(LVAR_Home_Tile)

//wearing purple
#define dude_is_purple                       (obj_pid(critter_inven_obj(dude_obj,INVEN_TYPE_WORN))==PID_PURPLE_ROBE)

//stop critter

#define critter_stop(x) reg_anim_begin(); \
      reg_anim_clear(x); \
      reg_anim_animate(x, ANIM_stand, -1); \
      reg_anim_end();
	  
#define dude_has_item(x) obj_is_carrying_obj_pid(dude_obj,x)