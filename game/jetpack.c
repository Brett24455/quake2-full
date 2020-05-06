// MUCE:  JetPack addition!

#include "g_local.h"

/*
=================
ApplyThrust

MUCE:
To add thrusting velocity to player
=================
*/

//Brett: Again, credit to MUCE for his jetpack tutorial,
//it was absolutely essential to the rest of my mod and 
//helped me to get a feel for modding in Quake 2
void ApplyThrust(edict_t *ent)
{

	vec3_t forward, right;
	vec3_t pack_pos, jet_vector;

	//MUCE:  add thrust to character

	if (hasjetpack){
		if (ent->velocity[2] < -500) //ent->velocity[0] will cause the player to move in a specific direction
			ent->velocity[2] += ((ent->velocity[2]) / (-5));
		else if (ent->velocity[2] < 0)
			ent->velocity[2] += 50;
		else
			ent->velocity[2] += ((150 - ent->velocity[2]) / 8); //Changed 1000 to 150 so the jetpack doesnt shoot you up like crazy

		//MUCE:  add sparks

		AngleVectors(ent->client->v_angle, forward, right, NULL);
		VectorScale(forward, -7, pack_pos);
		VectorAdd(pack_pos, ent->s.origin, pack_pos);
		pack_pos[2] += (ent->viewheight);

		VectorScale(forward, -50, jet_vector);

		gi.WriteByte(svc_temp_entity);
		gi.WriteByte(TE_BLOOD); //Changed jetpack to spurt blood instead of missle fire
		gi.WritePosition(pack_pos);
		gi.WriteDir(jet_vector);
		gi.multicast(pack_pos, MULTICAST_PVS);

		//MUCE: add sound 

		if (ent->client->next_thrust_sound < level.time)
		{
			gi.sound(ent, CHAN_BODY, gi.soundindex("weapons/rockfly.wav"), 1, ATTN_NORM, 0);
			ent->client->next_thrust_sound = level.time + 1.0;
		}
	}

	else{
		gi.cprintf(ent, PRINT_HIGH, "Do not have Jetpack\n");
	}
}