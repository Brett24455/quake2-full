#include "g_local.h"

/*
=================
RegenField
=================
*/

void RegenField(edict_t *ent)
{

	vec3_t forward, right;
	vec3_t pack_pos, jet_vector;

	gi.cprintf(ent, PRINT_HIGH, "Regen Locked\n");
	if (ent->health != 100){
		if (ent->health == 99)
			ent->health += 1;
		else if (ent->health == 98)
			ent->health += 2;
		else
			ent->health += 3;
	}

	//add sparks

	AngleVectors(ent->client->v_angle, forward, right, NULL);
	VectorScale(forward, -7, pack_pos);
	VectorAdd(pack_pos, ent->s.origin, pack_pos);
	pack_pos[2] += (ent->viewheight);

	VectorScale(forward, -50, jet_vector);

	gi.WriteByte(svc_temp_entity);
	gi.WriteByte(TE_SPARKS);
	gi.WritePosition(pack_pos);
	gi.WriteDir(jet_vector);
	gi.multicast(pack_pos, MULTICAST_PVS);

	//add sound 

	if (ent->client->next_thrust_sound < level.time)
	{
		gi.sound(ent, CHAN_BODY, gi.soundindex("weapons/rockfly.wav"), 1, ATTN_NORM, 0);
		ent->client->next_thrust_sound = level.time + 1.0;
	}
}