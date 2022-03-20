/* Vault 13 Shorteners */

#define DAYS_TRANSITION_PILLS       (75)

#define sirius_pills_in_inventory   obj_carrying_pid_obj(dude_obj,PID_HEART_PILLS)

#define jasper_has_been_betrayed    global_var(GVAR_VAULT13MUT_JASPER) == JASPER_IS_BETRAYED
#define jasper_is_dead              global_var(GVAR_VAULT13MUT_JASPER) == JASPER_IS_DEAD

#define transition_cutscene_played  (global_var(GVAR_VAULT13MUT_TRANSITION_CUTSCENE) >= 1)

#define edward_had_sex              (global_var(GVAR_VAULT13MUT_EDWARD_HAD_SEX) == 1)