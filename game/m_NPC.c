/*
Copyright (C) 1997-2001 Id Software, Inc.

This program is free software; you can redistribute it and/or
modify it under the terms of the GNU General Public License
as published by the Free Software Foundation; either version 2
of the License, or (at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.

See the GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program; if not, write to the Free Software
Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.

*/
/*
==============================================================================

INFANTRY

==============================================================================
*/

#include "g_local.h"
#include "m_infantry.h"


static int	sound_pain1;
static int	sound_pain2;
static int	sound_die1;
static int	sound_die2;

static int	sound_gunshot;
static int	sound_weapon_cock;
static int	sound_punch_swing;
static int	sound_punch_hit;
static int	sound_sight;
static int	sound_search;
static int	sound_idle;


mframe_t NPC_frames_stand[] =
{
	ai_stand, 0, NULL,
	ai_stand, 0, NULL,
	ai_stand, 0, NULL,
	ai_stand, 0, NULL,
	ai_stand, 0, NULL,
	ai_stand, 0, NULL,
	ai_stand, 0, NULL,
	ai_stand, 0, NULL,
	ai_stand, 0, NULL,
	ai_stand, 0, NULL,
	ai_stand, 0, NULL,
	ai_stand, 0, NULL,
	ai_stand, 0, NULL,
	ai_stand, 0, NULL,
	ai_stand, 0, NULL,
	ai_stand, 0, NULL,
	ai_stand, 0, NULL,
	ai_stand, 0, NULL,
	ai_stand, 0, NULL,
	ai_stand, 0, NULL,
	ai_stand, 0, NULL,
	ai_stand, 0, NULL
};
mmove_t NPC_move_stand = { FRAME_stand50, FRAME_stand71, NPC_frames_stand, NULL };

void NPC_stand(edict_t *self)
{
	self->monsterinfo.currentmove = &NPC_move_stand;
}


mframe_t NPC_frames_fidget[] =
{
	ai_stand, 1, NULL,
	ai_stand, 0, NULL,
	ai_stand, 1, NULL,
	ai_stand, 3, NULL,
	ai_stand, 6, NULL,
	ai_stand, 3, NULL,
	ai_stand, 0, NULL,
	ai_stand, 0, NULL,
	ai_stand, 0, NULL,
	ai_stand, 0, NULL,
	ai_stand, 1, NULL,
	ai_stand, 0, NULL,
	ai_stand, 0, NULL,
	ai_stand, 0, NULL,
	ai_stand, 0, NULL,
	ai_stand, 1, NULL,
	ai_stand, 0, NULL,
	ai_stand, -1, NULL,
	ai_stand, 0, NULL,
	ai_stand, 0, NULL,
	ai_stand, 1, NULL,
	ai_stand, 0, NULL,
	ai_stand, -2, NULL,
	ai_stand, 1, NULL,
	ai_stand, 1, NULL,
	ai_stand, 1, NULL,
	ai_stand, -1, NULL,
	ai_stand, 0, NULL,
	ai_stand, 0, NULL,
	ai_stand, -1, NULL,
	ai_stand, 0, NULL,
	ai_stand, 0, NULL,
	ai_stand, 0, NULL,
	ai_stand, 0, NULL,
	ai_stand, 0, NULL,
	ai_stand, -1, NULL,
	ai_stand, 0, NULL,
	ai_stand, 0, NULL,
	ai_stand, 1, NULL,
	ai_stand, 0, NULL,
	ai_stand, 0, NULL,
	ai_stand, -1, NULL,
	ai_stand, -1, NULL,
	ai_stand, 0, NULL,
	ai_stand, -3, NULL,
	ai_stand, -2, NULL,
	ai_stand, -3, NULL,
	ai_stand, -3, NULL,
	ai_stand, -2, NULL
};
mmove_t NPC_move_fidget = { FRAME_stand01, FRAME_stand49, NPC_frames_fidget, NPC_stand };

void NPC_fidget(edict_t *self)
{
	self->monsterinfo.currentmove = &NPC_move_fidget;
	gi.sound(self, CHAN_VOICE, sound_idle, 1, ATTN_IDLE, 0);
}

mframe_t NPC_frames_walk[] =
{
	ai_walk, 5, NULL,
	ai_walk, 4, NULL,
	ai_walk, 4, NULL,
	ai_walk, 5, NULL,
	ai_walk, 4, NULL,
	ai_walk, 5, NULL,
	ai_walk, 6, NULL,
	ai_walk, 4, NULL,
	ai_walk, 4, NULL,
	ai_walk, 4, NULL,
	ai_walk, 4, NULL,
	ai_walk, 5, NULL
};
mmove_t NPC_move_walk = { FRAME_walk03, FRAME_walk14, NPC_frames_walk, NULL };

void NPC_walk(edict_t *self)
{
	self->monsterinfo.currentmove = &NPC_move_walk;
}

mframe_t NPC_frames_run[] =
{
	ai_run, 10, NULL,
	ai_run, 20, NULL,
	ai_run, 5, NULL,
	ai_run, 7, NULL,
	ai_run, 30, NULL,
	ai_run, 35, NULL,
	ai_run, 2, NULL,
	ai_run, 6, NULL
};
mmove_t NPC_move_run = { FRAME_run01, FRAME_run08, NPC_frames_run, NULL };

void NPC_run(edict_t *self)
{
	if (self->monsterinfo.aiflags & AI_STAND_GROUND)
		self->monsterinfo.currentmove = &NPC_move_stand;
	else
		self->monsterinfo.currentmove = &NPC_move_run;
}


mframe_t NPC_frames_pain1[] =
{
	ai_move, -3, NULL,
	ai_move, -2, NULL,
	ai_move, -1, NULL,
	ai_move, -2, NULL,
	ai_move, -1, NULL,
	ai_move, 1, NULL,
	ai_move, -1, NULL,
	ai_move, 1, NULL,
	ai_move, 6, NULL,
	ai_move, 2, NULL
};
mmove_t NPC_move_pain1 = { FRAME_pain101, FRAME_pain110, NPC_frames_pain1, NPC_run };

mframe_t NPC_frames_pain2[] =
{
	ai_move, -3, NULL,
	ai_move, -3, NULL,
	ai_move, 0, NULL,
	ai_move, -1, NULL,
	ai_move, -2, NULL,
	ai_move, 0, NULL,
	ai_move, 0, NULL,
	ai_move, 2, NULL,
	ai_move, 5, NULL,
	ai_move, 2, NULL
};
mmove_t NPC_move_pain2 = { FRAME_pain201, FRAME_pain210, NPC_frames_pain2, NPC_run };

void NPC_pain(edict_t *self)
{
	int		n;

	if (self->health < (self->max_health / 2))
		self->s.skinnum = 1;

	if (level.time < self->pain_debounce_time)
		return;

	self->pain_debounce_time = level.time + 3;

	if (skill->value == 3)
		return;		// no pain anims in nightmare

	n = rand() % 2;
	if (n == 0)
	{
		self->monsterinfo.currentmove = &NPC_move_pain1;
		gi.sound(self, CHAN_VOICE, sound_pain1, 1, ATTN_NORM, 0);
	}
	else
	{
		self->monsterinfo.currentmove = &NPC_move_pain2;
		gi.sound(self, CHAN_VOICE, sound_pain2, 1, ATTN_NORM, 0);
	}
}
void sprinkle(edict_t *self)
{
	vec3_t	start;
	vec3_t	forward, right;

	AngleVectors(self->s.angles, forward, right, NULL);
	G_ProjectSource(self->s.origin, monster_flash_offset[MZ2_SOLDIER_BLASTER_1], forward, right, start);

	if (level.time > self->delay)
	{
		fire_water(self, start, forward, 500, EF_BLASTER);
	}
	self->think = sprinkle;
	self->nextthink = level.time + 1;
	
}

void NPC_sight(edict_t *self)
{
	gi.sound(self, CHAN_BODY, sound_sight, 1, ATTN_NORM, 0);
}

void NPC_dead(edict_t *self)
{
	VectorSet(self->mins, -16, -16, -24);
	VectorSet(self->maxs, 16, 16, -8);
	self->movetype = MOVETYPE_TOSS;
	self->svflags |= SVF_DEADMONSTER;
	gi.linkentity(self);

	M_FlyCheck(self);
}

mframe_t NPC_frames_death1[] =
{
	ai_move, -4, NULL,
	ai_move, 0, NULL,
	ai_move, 0, NULL,
	ai_move, -1, NULL,
	ai_move, -4, NULL,
	ai_move, 0, NULL,
	ai_move, 0, NULL,
	ai_move, 0, NULL,
	ai_move, -1, NULL,
	ai_move, 3, NULL,
	ai_move, 1, NULL,
	ai_move, 1, NULL,
	ai_move, -2, NULL,
	ai_move, 2, NULL,
	ai_move, 2, NULL,
	ai_move, 9, NULL,
	ai_move, 9, NULL,
	ai_move, 5, NULL,
	ai_move, -3, NULL,
	ai_move, -3, NULL
};
mmove_t NPC_move_death1 = { FRAME_death101, FRAME_death120, NPC_frames_death1, NPC_dead };

mframe_t NPC_frames_death3[] =
{
	ai_move, 0, NULL,
	ai_move, 0, NULL,
	ai_move, 0, NULL,
	ai_move, -6, NULL,
	ai_move, -11, NULL,
	ai_move, -3, NULL,
	ai_move, -11, NULL,
	ai_move, 0, NULL,
	ai_move, 0, NULL
};
mmove_t NPC_move_death3 = { FRAME_death301, FRAME_death309, NPC_frames_death3, NPC_dead };


void NPC_die(edict_t *self, int damage)
{
	int		n;

	// check for gib
	if (self->health <= self->gib_health)
	{
		gi.sound(self, CHAN_VOICE, gi.soundindex("misc/udeath.wav"), 1, ATTN_NORM, 0);
		for (n = 0; n < 2; n++)
			ThrowGib(self, "models/objects/gibs/bone/tris.md2", damage, GIB_ORGANIC);
		for (n = 0; n < 4; n++)
			ThrowGib(self, "models/objects/gibs/sm_meat/tris.md2", damage, GIB_ORGANIC);
		ThrowHead(self, "models/objects/gibs/head2/tris.md2", damage, GIB_ORGANIC);
		self->deadflag = DEAD_DEAD;
		return;
	}

	if (self->deadflag == DEAD_DEAD)
		return;

	// regular death
	self->deadflag = DEAD_DEAD;
	self->takedamage = DAMAGE_YES;

	n = rand() % 3;
	if (n == 0)
	{
		self->monsterinfo.currentmove = &NPC_move_death1;
		gi.sound(self, CHAN_VOICE, sound_die2, 1, ATTN_NORM, 0);
	}
	else
	{
		self->monsterinfo.currentmove = &NPC_move_death3;
		gi.sound(self, CHAN_VOICE, sound_die2, 1, ATTN_NORM, 0);
	}
}

/*QUAKED monster_infantry (1 .5 0) (-16 -16 -24) (16 16 32) Ambush Trigger_Spawn Sight
*/
void Buy(edict_t *ent)
{
	gi.centerprintf(ent, "1.Apple-3\n 2.Banana-6\n 3.Cherry-9\n 4.Durian-12\n 5.ElderBerry-15\nCash: %i", ent->client->ps.stats[CASH]);
}

void Sell(edict_t *ent)
{
	gi.centerprintf(ent, "Sell\n 1.Apple-5\n 2.Banana-10\n 3.Cherry-15\n 4.Durian-20\n 5.ElderBerry-25\nCash: %i", ent->client->ps.stats[CASH]);
}
void Equip(edict_t *ent)
{
	gi.centerprintf(ent, "1.sprinkler-10\n 2.armor welder-20\n 3.Seed Maker-30\n", ent->client->ps.stats[CASH]);
}
void Touch_Shop(edict_t *self, edict_t *other, cplane_t *plane, csurface_t *surf)
{
	self = self;
		plane = NULL;
	surf = NULL;
	if (!other->client)
		return;
	else
	{
		other->inShop = true;
		gi.centerprintf(other, "What would you like?\n 1.Buy\n 2.Sell\n 3.Equipment");
	}
}
void SP_monster_NPC(edict_t *owner)
{
	edict_t *self;
	vec3_t forward;

	self = G_Spawn();

	if (deathmatch->value)
	{
		G_FreeEdict(self);
		return;
	}

	sound_pain1 = gi.soundindex("infantry/infpain1.wav");
	sound_pain2 = gi.soundindex("infantry/infpain2.wav");
	sound_die1 = gi.soundindex("infantry/infdeth1.wav");
	sound_die2 = gi.soundindex("infantry/infdeth2.wav");

	sound_gunshot = gi.soundindex("infantry/infatck1.wav");
	sound_weapon_cock = gi.soundindex("infantry/infatck3.wav");
	sound_punch_swing = gi.soundindex("infantry/infatck2.wav");
	sound_punch_hit = gi.soundindex("infantry/melee2.wav");

	sound_sight = gi.soundindex("infantry/infsght1.wav");
	sound_search = gi.soundindex("infantry/infsrch1.wav");
	sound_idle = gi.soundindex("infantry/infidle1.wav");

	AngleVectors(owner->client->v_angle, forward, NULL, NULL);
	VectorMA(owner->s.origin, 100, forward, self->s.origin);

	
	self->classname = "monster_NPC";
	self->movetype = MOVETYPE_STEP;
	self->solid = SOLID_BBOX;
	self->s.modelindex = gi.modelindex("models/monsters/infantry/tris.md2");
	VectorSet(self->mins, -16, -16, -24);
	VectorSet(self->maxs, 16, 16, 32);

	self->health = 1000;
	self->gib_health = -40;
	self->mass = 200;
	self->touch = Touch_Shop;
	//self->pain = NPC_pain;
	//self->die = NPC_die;

	self->monsterinfo.stand = NPC_stand;
	self->monsterinfo.walk = NULL;
	self->monsterinfo.run = NULL;
	self->monsterinfo.melee = NULL;
	self->monsterinfo.sight = NULL;
	self->monsterinfo.idle = NPC_fidget;
	
	gi.linkentity(self);

	self->monsterinfo.currentmove = &NPC_move_stand;
	self->monsterinfo.scale = MODEL_SCALE;

}
void SP_sprinkler(edict_t *ent)
{
	edict_t *self;
	vec3_t forward, up;
	int timer = 5;
	self = G_Spawn();

	if (deathmatch->value)
	{
		G_FreeEdict(self);
		return;
	}

	AngleVectors(ent->movedir, forward, NULL, up);
	VectorMA(ent->s.origin, 100, up, self->s.origin);


	self->classname = "monster_NPC_sprinkler";
	self->movetype = MOVETYPE_STEP;
	self->solid = SOLID_BBOX;
	self->s.modelindex = gi.modelindex("models/monsters/infantry/tris.md2");
	VectorSet(self->mins, -16, -16, -24);
	VectorSet(self->maxs, 16, 16, 32);

	self->health = 1000;
	self->gib_health = -40;
	self->mass = 200;
	
	//self->pain = NPC_pain;
	//self->die = NPC_die;

	self->monsterinfo.stand = NPC_stand;
	self->monsterinfo.walk = NULL;
	self->monsterinfo.run = NULL;
	self->monsterinfo.melee = NULL;
	self->monsterinfo.sight = NULL;
	self->monsterinfo.idle = NPC_fidget;
	self->nextthink = level.time + timer;
	self->think = sprinkle;
	self->delay = level.time + 10;
	gi.linkentity(self);

	self->monsterinfo.currentmove = &NPC_move_stand;
	self->monsterinfo.scale = MODEL_SCALE;

}
void armorTouch(edict_t *self, edict_t *other, cplane_t *plane, csurface_t *surf)
{
	plane = NULL;
	surf = NULL;
	self = self;
	if (other->client)
	{
		other->inArmor = true;
		gi.centerprintf(other,"Would you like to convert your monster drops? Y/N\n You have %i\n", other->client->pers.Mondrops);
	}
}
void seedTouch(edict_t *self, edict_t *other, cplane_t *plane, csurface_t *surf)
{
	plane = NULL;
	surf = NULL;
	self = self;
	if (other->client)
	{
		other->inSEMake = true;
		gi.centerprintf(other, "Which seeds do you want to make\n1.Apple\n2.Banana\n3.Cherry\n4.Durian\n5.Elder Berries");
	}
}
void SP_armor(edict_t *ent)
{
	edict_t *self;
	vec3_t forward, up;
	
	self = G_Spawn();

	if (deathmatch->value)
	{
		G_FreeEdict(self);
		return;
	}

	AngleVectors(ent->movedir, forward, NULL, up);
	VectorMA(ent->s.origin, 100, up, self->s.origin);


	self->classname = "monster_NPC_armor";
	self->movetype = MOVETYPE_STEP;
	self->solid = SOLID_BBOX;
	self->s.modelindex = gi.modelindex("models/monsters/gladiatr/tris.md2");
	VectorSet(self->mins, -16, -16, -24);
	VectorSet(self->maxs, 16, 16, 32);

	self->health = 1000;
	self->gib_health = -40;
	self->mass = 200;

	//self->pain = NPC_pain;
	//self->die = NPC_die;

	self->monsterinfo.stand = NPC_stand;
	self->monsterinfo.walk = NULL;
	self->monsterinfo.run = NULL;
	self->monsterinfo.melee = NULL;
	self->monsterinfo.sight = NULL;
	self->monsterinfo.idle = NPC_fidget;
	self->touch = armorTouch;
	
	gi.linkentity(self);

	self->monsterinfo.currentmove = &NPC_move_stand;
	self->monsterinfo.scale = MODEL_SCALE;
}
void SP_seedMaker(edict_t *ent)
{
	edict_t *self;
	vec3_t forward, up;

	self = G_Spawn();

	if (deathmatch->value)
	{
		G_FreeEdict(self);
		return;
	}

	AngleVectors(ent->movedir, forward, NULL, up);
	VectorMA(ent->s.origin, 100, up, self->s.origin);


	self->classname = "monster_NPC_seed";
	self->movetype = MOVETYPE_STEP;
	self->solid = SOLID_BBOX;
	self->s.modelindex = gi.modelindex("models/monsters/medic/tris.md2");
	VectorSet(self->mins, -16, -16, -24);
	VectorSet(self->maxs, 16, 16, 32);

	self->health = 1000;
	self->gib_health = -40;
	self->mass = 200;

	//self->pain = NPC_pain;
	//self->die = NPC_die;

	self->monsterinfo.stand = NPC_stand;
	self->monsterinfo.walk = NULL;
	self->monsterinfo.run = NULL;
	self->monsterinfo.melee = NULL;
	self->monsterinfo.sight = NULL;
	self->monsterinfo.idle = NPC_fidget;
	self->touch = seedTouch;

	gi.linkentity(self);

	self->monsterinfo.currentmove = &NPC_move_stand;
	self->monsterinfo.scale = MODEL_SCALE;
}
