#include "g_local.h"

/*
=================
ApplyThrusterThrust

Sorry for the shit naming convention, works really similarly to the jetpack
=================
*/

void ApplyThrusterThrust(edict_t *ent)
{

	vec3_t forward, right;
	vec3_t pack_pos, jet_vector;


	if (hasthrusterpack){
		ent->velocity[0] = 1250;

		AngleVectors(ent->client->v_angle, forward, right, NULL);
		VectorScale(forward, -7, pack_pos);
		VectorAdd(pack_pos, ent->s.origin, pack_pos);
		pack_pos[2] += (ent->viewheight);

		VectorScale(forward, -50, jet_vector);

		gi.WriteByte(svc_temp_entity);
		gi.WriteByte(TE_BULLET_SPARKS);
		gi.WritePosition(pack_pos);
		gi.WriteDir(jet_vector);
		gi.multicast(pack_pos, MULTICAST_PVS);

		if (ent->client->next_thrust_sound < level.time)
		{
			gi.sound(ent, CHAN_BODY, gi.soundindex("weapons/bfg__x1b.wav"), 1, ATTN_NORM, 0);
			ent->client->next_thrust_sound = level.time + 1.0;
		}
	}

	else{
		gi.cprintf(ent, PRINT_HIGH, "Do not have Thruster Pack\n");
	}
}