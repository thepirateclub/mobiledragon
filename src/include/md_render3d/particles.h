/** \file
 *	Particle system. <br>
 *
 *	Copyright 2005-2006 Herocraft Hitech Co. Ltd.<br>
 *	Version 1.0 beta.
 */

#ifndef __PARTICLES_H__
#define __PARTICLES_H__

namespace mdragon
{


/// Single particle structure.
struct CommonParticle
{
	Vector3fx		position;
	Vector3fx		velocity;
	Fixed			life_time;
	Color			color;
	Vector3fx		size;
	Vector3fx		gravity;
};


/// Basic particle manager class.
class BasicParticleManager
{
public:

	/// Default constructor.
	BasicParticleManager();

	/// Destructor.
	~BasicParticleManager();

	/// Initializes particle system. 
	/**
	 * Every time you'll call this function, it'll reallocate memory for particles storage.
	 * Call this function before you will work with particle system.
	 * @param total_particles_count_ - total particles count.
	 */
	void Init(Int total_particles_count_);

	/// Returns current particles count.
	/**
	 * @return Returns current particles count.
	 */
	inline Int GetCurrentParticlesCount()
	{
		return curr_count;
	}

	/// Returns total particles count.
	/**
	 * @return Returns total particles count.
	 */
	inline Int GetTotalParticlesCount()
	{
		return total_count;
	}

	/// Sets time period of particles emission.
	/**
	 * @param emit_period_ - emission period.
	 */
	inline void SetEmissionPeriod( Fixed emission_period_)
	{
		emission_period = emission_period_;
	}

	/// Returns emission period of particle system.
	/**
	 * @return Returns emission period of particle system.
	 */
	inline Fixed GetEmissionPeriod()
	{
		return emission_period;
	}

	/// Sets position of emitter.
	/**
	 * @param emitter_pos_ - position of emitter.
	 */
	inline void SetEmitterPos(const Vector3fx & emitter_pos_)
	{
		emitter_pos = emitter_pos_;
	}

	/// Returns emitter position.
	/**
	 * @return Returns position of emitter.
	 */
	inline Vector3fx GetEmitterPos()
	{
		return emitter_pos;
	}

	/// Sets count of particles for emitting.
	/**
	 * @param emit_count_ - count of particles.
	 */
	inline void SetEmitCount(Int emit_count_)
	{
		emit_count = emit_count_;
	}

	/// Returns count of particles for emitting.
	/**
	 * @return Returns count of particles for emitting.
	 */
	inline Int GetEmitCount()
	{
		return emit_count;
	}

	/// Sets emitter parameters.
	/**
	 * @param emit_count_ - count of particles for emitting.
	 * @param emission_period_ - emission period.
	 * @param emitter_pos_ - position of emitter.
	 */
	inline void Set(Int emit_count_, Fixed emission_period_, const Vector3fx & emitter_pos_ )
	{
		SetEmitCount(emit_count_);
		SetEmissionPeriod(emission_period_);
		SetEmitterPos(emitter_pos_);
	}

	/// Set particle system alive flag.
	/**
	 * @param is_alive_ - alive flag value.
	 */
	inline void SetAlive(Bool is_alive_)
	{
		is_alive = is_alive_;
	}

	/// Returns alive flag value. 
	/**
	 * @return Returns True if particle system is alive, else - False.
	 */
	inline Bool IsAlive()
	{
		return is_alive;
	}

	/// Particles array.
	CommonParticle * pArr;

protected:

	/// Total particles count.
	Int total_count;

	/// Current particles count.
	Int curr_count;

	/// Emission period.
	Fixed emission_period;

	/// Emitter position.
	Vector3fx emitter_pos; 

	/// Emit count.
	Int emit_count;

	/// Current period.
	Fixed curr_period;

	/// Alive flag.
	/**
	 * You should to set yourself this flag to True to start particles system.
	 * If all emitted particles will die this flag sets to False.
	 */
	Bool is_alive;
};




/// Particle Manager represents concrete particle system template class.
/**
 * It manages particle system.
 * This template class have to be initialized by two policies in template parameters. 
 * @param InitPolicy - initialization policy. This policy provide particles initialization.
 * @param UpdatePolicy - update policy. This policy provide particles update.
 */
template<class InitPolicy, class UpdatePolicy>
class ParticleManager : public BasicParticleManager
{
public:

	/// Default constructor.
	ParticleManager(){};

	/// Destructor.
	~ParticleManager(){};

	/// Updates particle system.
	/**
	 * @param frame_time - frame time particle system (time between two successive updates).
	 */
	void Update(Fixed &frame_time);

private:

	/// Emits particles.
	/**
	 * @param count_ - particles count.
	 * @param start_pos_ -  emission start position.
	 */
	void Emit(Int count_, Vector3fx &start_pos_);

	/// Initialization policy.
	InitPolicy pInit;

	/// Update policy.
	UpdatePolicy pUpdate;

};


template<class InitPolicy, class UpdatePolicy>
void ParticleManager<InitPolicy, UpdatePolicy>::Update(Fixed &frame_time)
{
	if (is_alive)
	{
		for (Int i = 0; i < curr_count; i++)
		{
			if (pArr[i].life_time <= 0)
			{
				pArr[i] = pArr[--curr_count];
			}

			if (curr_count == 0)
				is_alive = False;
		}

		for (i = 0; i < curr_count; i++)
			pUpdate(&pArr[i], frame_time);
		
		
		curr_period += frame_time;

		if ( curr_period > emission_period )
		{
			Emit( emit_count, emitter_pos);

			curr_period = 0;
		}
	}
	else
		curr_count = 0;

}

template<class InitPolicy, class UpdatePolicy>
void ParticleManager<InitPolicy, UpdatePolicy>::Emit(Int count_, Vector3fx &start_pos_)
{
	Int tC = curr_count;

	for (; (curr_count < tC + count_) && (curr_count < total_count); curr_count++)
	{
		pArr[curr_count].position = start_pos_;

		Fixed dummy;
		pInit(&pArr[curr_count], dummy);
	}
}


/// CompletePolicy represents template class that provides implementation of policies container to store complete policies.
/**
 * This template class have to be initialized by template parameters.
 * @param LifePolicy - life policy. 
 * @param PositionPolicy - position policy.
 * @param SizePolicy - size policy.
 * @param VelocityPolicy - velocity policy.
 * @param ColorPolicy - color policy.
 */
template<class LifePolicy, class PositionPolicy, 
		 class SizePolicy, class VelocityPolicy, class ColorPolicy>
class CompletePolicy
{
public:
	
	/// Provides container for few policies.
	inline void operator () (CommonParticle *p, Fixed &frame_time)
	{
		life_policy(p, frame_time);
		velocity_policy(p, frame_time);
		position_policy(p, frame_time);
		size_policy(p, frame_time);
		color_policy(p, frame_time);
	}

	/// Life policy.
	LifePolicy	life_policy;

	/// Position policy.
	PositionPolicy	position_policy;

	/// Size policy.
	SizePolicy size_policy;

	/// Velocity policy.
	VelocityPolicy	velocity_policy;

	/// Color policy.
	ColorPolicy	color_policy;
};


/// CompositePolicy represents template class that provides implementation of policies composer to composite two policies.
/**
 * This template class have to be initialized by template parameters.
 * @param PolicyOne - first policy. 
 * @param PolicyTwo - second policy.
 */
template<class PolicyOne, class PolicyTwo>
class CompositePolicy: public PolicyOne, public PolicyTwo
{
public:
	
	/// Provides composition of two policies.
	inline void operator () (CommonParticle *p, Fixed &frame_time)
	{
		PolicyOne::operator () (p, frame_time);
		PolicyTwo::operator () (p, frame_time);
	}
};

} //namespace mdragon

#endif	// __PARTICLES_H__
