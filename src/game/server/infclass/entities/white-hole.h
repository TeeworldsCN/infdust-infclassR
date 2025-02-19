/* (c) Magnus Auvinen. See licence.txt in the root of the distribution for more information. */
/* If you are missing that file, acquire a complete release at teeworlds.com.                */
#ifndef GAME_SERVER_ENTITIES_WHITE_HOLE_H
#define GAME_SERVER_ENTITIES_WHITE_HOLE_H

#include "infcentity.h"

class CWhiteHole : public CInfCEntity
{
private:
	void StartVisualEffect();
	void MoveParticles();
	void MoveCharacters();

public:
	CWhiteHole(CGameContext *pGameContext, vec2 CenterPos, int Owner);
	virtual ~CWhiteHole();
	
	virtual void Snap(int SnappingClient);
	virtual void TickPaused();
	virtual void Tick();

	int LifeSpan() const { return m_LifeSpan; }
	
private:
	// physics
	float m_PlayerPullStrength; // will be set with a config var
	const float m_RadiusGrowthRate = 6.0f; // how fast the hole growths when it is created
	const float m_PlayerDrag = 0.9f;
	// visual
	const float m_ParticleStartSpeed = 1.1f; 
	const float m_ParticleAcceleration = 1.01f;
	int m_ParticleStopTickTime; // when X time is left stop creating particles - close animation

	int m_NumParticles; // will be set with a config var
	int *m_IDs;
	vec2 *m_ParticlePos;
	vec2 *m_ParticleVec;

	bool isDieing;
	
public:
	int m_StartTick;
	int m_LifeSpan;
	int m_Radius; // changes overtime - grows when created - shrinks when dieing
};

#endif


