
///////////////////////////////////////////////////////////////////////////
//   This file contains examples of policies for Mobile Dragon 
//   particle system.
//   There are policies for Smoke, Sparks, Twister, Explosion types of
//   particle systems.
///////////////////////////////////////////////////////////////////////////


#include "mdragon.h"

using namespace mdragon;



///////////////////////////POLICIES STRUCTURE//////////////////////////////
// 
// Every policy should have following structure:
// 
// 	struct <PolicyName>
// 	{
// 		void operator () (CommonParticle *p, Fixed &frame_time)
// 		{
// 			// Place policy code here.
// 		}
// 	};
// 
// Policy should provide implementation of () operator that have two parameters:
// @param p - pointer to the particle.
// @param frame_time - frame time particle system (time between two successive updates).
// 
// For example policy for particle size initialization by length = height = width = 1:
// 
// 	struct InitSize
// 	{
// 		void operator () (CommonParticle *p, Fixed &frame_time)
// 		{
// 			p->size = Vector3fx(1,1,1);
// 		}
// 	};
//
///////////////////////////////////////////////////////////////////////////


////////////////////////////////NULL POLICY////////////////////////////////

/**
 * Null policy. 
 * Cork for unnecessary policy.
 */
struct NullPolicy
{
	inline void operator () (CommonParticle *p, Fixed &frame_time) {}
};

//////////////////////////////SMOKE POLICIES///////////////////////////////

/**
 * Life initialization policy for smoke.
 */
struct InitLife_Smoke
{
	Randomize RND;

	inline void operator () (CommonParticle *p, Fixed &frame_time)
	{
		p->life_time = 2500 + Int(RND.Next()%300);
	}
};


/**
 * Size initialization policy for smoke.
 */
struct InitSize_Smoke
{
	Randomize RND;

	inline void operator () (CommonParticle *p, Fixed &frame_time)
	{
		p->size = Vector3fx(0.4, 0.4, 0);
	}
};


/**
 * Velocity initialization policy for smoke.
 */
struct InitVelocity_Smoke
{
	inline void operator () (CommonParticle *p, Fixed &frame_time)
	{
		p->velocity = Vector3fx(0,2,0);
	}
}; 

/**
 * Life update policy for smoke.
 */
struct UpdateLife_Smoke
{
	inline void operator () (CommonParticle *p, Fixed &frame_time)
	{
		p->life_time -= 500 * frame_time;
	}
};

/**
 * Position noise update policy for smoke.
 */
struct UpdatePosition_Noise_Smoke
{
	Randomize RND;

	inline void operator () (CommonParticle *p, Fixed &frame_time)
	{
		Vector3fx g(5-Int(RND.Next()%11),5-Int(RND.Next()%11),5-Int(RND.Next()%11));

		g += p->velocity;
		g *= frame_time;
		p->position += g;
	}
};

/**
 * Size linear update policy for smoke.
 */
struct UpdateSize_Smoke
{
	inline void operator () (CommonParticle *p, Fixed &frame_time)
	{
		Fixed s = p->velocity.y * frame_time / 2;
		p->size.x += s;
		p->size.y += s;
	}
};


//////////////////////////////SPARKS POLISIES//////////////////////////////

/**
* Life initialization policy for sparks.
*/
struct InitLife_Sparks
{
	Randomize RND;

	inline void operator () (CommonParticle *p, Fixed &frame_time)
	{
		p->life_time = Int(RND.Next()%300);
	}
};


/**
* Size initialization policy for sparks.
*/
struct InitSize_Sparks
{
	Randomize RND;

	inline void operator () (CommonParticle *p, Fixed &frame_time)
	{
		p->size = ( Fixed(Int(1+(RND.Next()%3)))/10) * Vector3fx(1,1,1);
	}
};


/**
* Velocity initialization policy for sparks.
*/
struct InitVelocity_Sparks
{
	inline void operator () (CommonParticle *p, Fixed &frame_time)
	{
		p->velocity = Vector3fx(0,2,0);
	}
}; 


/**
* Velocity initialization policy for sparks.
*/
struct InitVelocity_Noise_Sparks
{
	Randomize RND;

	inline void operator () (CommonParticle *p, Fixed &frame_time)
	{
		p->velocity = Vector3fx(-3 + Int(RND.Next()%7), 10, -3 + Int(RND.Next()%7));
	}
};


/**
* Size update policy for sparks.
*/
struct UpdateSize_Sparks
{
	inline void operator () (CommonParticle *p, Fixed &frame_time)
	{
		Fixed s = Fixed(0.4) * frame_time;

		p->size.x -= s;
		if (p->size.x < F_ZERO)
		{
			p->size.x = F_ZERO;
		}


		p->size.y -= s;

		if (p->size.y < F_ZERO)
		{
			p->size.y = F_ZERO;
		}

	}
};


/**
* Life update policy for sparks.
*/
struct UpdateLife_Sparks
{
	inline void operator () (CommonParticle *p, Fixed &frame_time)
	{
		p->life_time -= 500 * frame_time;
	}
};


/**
* Position linear update policy for sparks.
*/
struct UpdatePosition_Linear_Sparks
{
	inline void operator () (CommonParticle *p, Fixed &frame_time)
	{
		Vector3fx g = p->velocity;
		g *= frame_time;
		p->position += g;
	}
};


/**
* Position noise update policy for sparks.
*/
struct UpdatePosition_Noise_Sparks
{
	Randomize RND;

	inline void operator () (CommonParticle *p, Fixed &frame_time)
	{

		Vector3fx g(5-Int(RND.Next()%11),5-Int(RND.Next()%11),5-Int(RND.Next()%11));

		g += p->velocity;
		g *= frame_time;
		p->position += g;
	}
};


/////////////////////////////TWISTER POLICIES//////////////////////////////

/**
 * Life initialization policy for twister.
 */
struct InitLife_Twister
{
	inline void operator () (CommonParticle *p, Fixed &frame_time)
	{
		p->life_time = 3;
	}
};


/**
 * Position initialization policy for twister.
 */
struct InitPos_Twister
{
	Randomize RND;

	inline void operator () (CommonParticle *p, Fixed &frame_time)
	{
		Fixed h;
		h = Fixed(2) - (Fixed)((Int)RND.Next()%400)/100;
		p->position.y += h;
		h = Fixed(2) - (Fixed)((Int)RND.Next()%100)/100;
		p->position.x += h + p->position.y / 2;
		p->position.z = 0;
		p->gravity.x = abs(p->position.x);
	}
};

/**
 * Size initialization policy for twister.
 */
struct InitSize_Twister
{
	inline void operator () (CommonParticle *p, Fixed &frame_time)
	{
		p->size = Vector3fx(0.4,0.4,0.4);
	}
};


/**
 * Velocity initialization policy for twister.
 */
struct InitVelocity_Twister
{
	Randomize RND;

	inline void operator () (CommonParticle *p, Fixed &frame_time)
	{
		p->velocity = Vector3fx( 5 * (1 +(Fixed)((Int)RND.Next()%214)/100), 0, 0 );
	}
};


/**
 * Position update policy for twister.
 */
struct UpdatePosition_Twister
{
	inline void operator () (CommonParticle *p, Fixed &frame_time)
	{
		p->position.x = p->gravity.x * Cos(p->velocity.y);
		p->position.z = p->gravity.x * Sin(p->velocity.y);
	}
};

/**
 * Velocity update policy for twister.
 */
struct UpdateVelocity_Twister
{
	inline void operator () (CommonParticle *p, Fixed &frame_time)
	{
		p->velocity.y += (p->velocity.x * frame_time);
	}
};


/////////////////////////////EXPLOSION POLICIES////////////////////////////


/**
 * Life initialization policy for explosion.
 */
struct InitLife_Explosion
{
	Randomize RND;

	inline void operator () (CommonParticle *p, Fixed &frame_time)
	{
		p->life_time = 500 + Int(RND.Next()%300);
	}
};


/**
 * Size initialization policy for explosion.
 */
struct InitSize_Explosion
{
	inline void operator () (CommonParticle *p, Fixed &frame_time)
	{
		p->size = Vector3fx(0.4,0.4,0.0);
	}
};


/**
 * Velocity initialization policy for explosion.
 */
struct InitVelocity_Explosion
{
	Randomize RND;

	inline void operator () (CommonParticle *p, Fixed &frame_time)
	{
		p->velocity = Vector3fx((5 - Int(RND.Next()%11))*3, (3+Int(RND.Next()%7))*3, (5-Int(RND.Next()%11))*3);
	}
};


/**
 * Life update policy for explosion.
 */
struct UpdateLife_Explosion
{
	inline void operator () (CommonParticle *p, Fixed &frame_time)
	{
		p->life_time -= 500 * frame_time;
	}
};


/**
 * Position linear update policy for explosion.
 */
struct UpdatePosition_Linear_Explosion
{
	inline void operator () (CommonParticle *p, Fixed &frame_time)
	{
		Vector3fx g = p->velocity;
		g *= frame_time;
		p->position += g;
	}
};



////////////////EXAMPLE OF COMMON TYPES OF PARTICLE SYSTEMS////////////////

/**
 * Smoke particle system.
 */
typedef ParticleManager
<CompletePolicy<InitLife_Smoke, NullPolicy, InitSize_Smoke, InitVelocity_Smoke, NullPolicy>,
 CompletePolicy<UpdateLife_Smoke, UpdatePosition_Noise_Smoke, UpdateSize_Smoke, NullPolicy, NullPolicy> >
PSmoke;


/**
 * Sparks particle system.
 */
typedef ParticleManager
<CompletePolicy<InitLife_Sparks, NullPolicy, InitSize_Sparks, CompositePolicy<InitVelocity_Sparks, InitVelocity_Noise_Sparks>, NullPolicy>,
 CompletePolicy<UpdateLife_Sparks, CompositePolicy<UpdatePosition_Noise_Sparks, UpdatePosition_Linear_Sparks>, UpdateSize_Sparks, NullPolicy, NullPolicy> >
PSparks;


/**
 * Twister particle system.
 */
typedef ParticleManager
<CompletePolicy<InitLife_Twister, InitPos_Twister, InitSize_Twister, InitVelocity_Twister, NullPolicy>,
 CompletePolicy<NullPolicy, UpdatePosition_Twister, NullPolicy, UpdateVelocity_Twister, NullPolicy> >
PTwister;


/**
 * Explosion particle system.
 */
typedef ParticleManager
<CompletePolicy<InitLife_Explosion, NullPolicy, InitSize_Explosion, InitVelocity_Explosion, NullPolicy>,
 CompletePolicy<UpdateLife_Explosion, UpdatePosition_Linear_Explosion, NullPolicy, NullPolicy, NullPolicy> >
PExplosion;


