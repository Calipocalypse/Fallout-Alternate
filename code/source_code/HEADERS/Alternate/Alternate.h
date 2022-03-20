#include "Debug.h"
#include "Globals.h"
#include "Shorteners.h"
#include "Critters.h"
#include "Cities.h"

/* Locations */
#include "Vault13.h"
#include "Shed.h"

#define TIMED_ADD_PARTY              (1234)

#define rotate_obj(who, side) reg_anim_clear(who); anim(who, ANIMATE_ROTATION, side); reg_anim_clear(who);
#define RIGHTTOP  (0)
#define RIGHT     (1)
#define RIGHTDOWN (2)
#define LEFT      (3)
#define LEFTDOWN  (4)
#define LEFTTOP   (5)