//========= Copyright � 1996-2005, Valve Corporation, All rights reserved. ============//
//
// Purpose: 
//
// $NoKeywords: $
//
//=============================================================================//
#ifndef C_FIRE_SMOKE_H
#define C_FIRE_SMOKE_H

#include "particles_simple.h"
#include "tempent.h"
#include "glow_overlay.h"
#include "view.h"
#include "particle_litsmokeemitter.h"

class CFireOverlay;

class C_FireSprite : public C_Sprite
{
	DECLARE_CLASS( C_FireSprite, C_Sprite );

public:
	Vector	m_vecMoveDir;
};



#define	NUM_CHILD_FLAMES	4

#define	SMOKE_RISE_RATE		92.0f
#define	SMOKE_LIFETIME		2.0f
#define	EMBER_LIFETIME		2.0f

#define	FLAME_CHILD_SPREAD	64.0f
#define	FLAME_SOURCE_HEIGHT	128.0f

//==================================================
// C_FireSmoke
//==================================================

//NOTENOTE: Mirrored in dlls/fire_smoke.h
#define	bitsFIRESMOKE_NONE				0x00000000
#define	bitsFIRESMOKE_ACTIVE			0x00000001
#define	bitsFIRESMOKE_SMOKE				0x00000002
#define	bitsFIRESMOKE_SMOKE_COLLISION	0x00000004
#define	bitsFIRESMOKE_GLOW				0x00000008

#define	OVERLAY_MAX_VISIBLE_RANGE	512.0f

class C_FireSmoke : public C_BaseEntity
{
public:
	DECLARE_CLIENTCLASS();
	DECLARE_CLASS( C_FireSmoke, C_BaseEntity );

	C_FireSmoke();
	~C_FireSmoke();

	void	Start( void );
	void	Simulate( void );

	void	StartClientOnly( void );
	void	RemoveClientOnly( void );

protected:
	void	Update( void );
	void	UpdateAnimation( void );
	void	UpdateScale( void );
	void	UpdateFlames( void );
	void	AddFlames( void );
	void	SpawnSmoke( void );
	void	FindClipPlane( void );
	
//C_BaseEntity
public:

	virtual void	OnDataChanged( DataUpdateType_t updateType );
	virtual bool	ShouldDraw();

	float GetScale( void ) const { return m_flScaleRegister;	}
	
//From the server
public:
	float	m_flStartScale;
	float	m_flScale;
	float	m_flScaleTime;
	int		m_nFlags;
	int		m_nFlameModelIndex;

//Client-side only
public:
	float	m_flScaleRegister;
	float	m_flScaleStart;
	float	m_flScaleEnd;
	float	m_flScaleTimeStart;
	float	m_flScaleTimeEnd;
	float	m_flChildFlameSpread;

	VPlane	m_planeClip;
	float	m_flClipPerc;
	bool	m_bClipTested;

	bool	m_bFadingOut;

protected:

	void	UpdateEffects( void );

	//CSmartPtr<CEmberEffect> m_pEmberEmitter;
	CSmartPtr<CLitSmokeEmitter> m_pSmokeEmitter;

	C_FireSprite		m_entFlames[NUM_CHILD_FLAMES];
	float				m_entFlameScales[NUM_CHILD_FLAMES];

	TimedEvent			m_tParticleSpawn;

	CFireOverlay		*m_pFireOverlay;

private:
	C_FireSmoke( const C_FireSmoke & );
};

//Fire overlay
class CFireOverlay : public CGlowOverlay
{
public:
	
	//Constructor
	CFireOverlay( C_FireSmoke *owner )
	{
		m_pOwner	= owner;
		m_flScale	= 0.0f;
		m_nGUID		= random->RandomInt( -999999, 999999 );
	}

	//-----------------------------------------------------------------------------
	// Purpose: Generate a flicker value
	// Output : scalar value
	//-----------------------------------------------------------------------------
	float GetFlickerScale( void )
	{
		float	result = 0.0f;

		float	time = Helper_GetTime() + m_nGUID;

		result = sin( time * 1000.0f );
		result += 0.5f * sin( time * 2000.0f );
		result -= 0.5f * cos( time * 8000.0f );
		
		return result;
	}

	//-----------------------------------------------------------------------------
	// Purpose: Update the overlay
	//-----------------------------------------------------------------------------
	virtual bool Update( void )
	{
		if ( m_pOwner == NULL )
			return false;

		float scale	 = m_pOwner->GetScale();
		float dscale = scale - m_flScale;

		m_vPos[2] += dscale * FLAME_SOURCE_HEIGHT;
		m_flScale = scale;

		scale *= 0.75f;

		float flickerScale = GetFlickerScale();

		float newScale = scale + ( scale * flickerScale * 0.1f );

		m_Sprites[0].m_flHorzSize = ( newScale * 0.2f ) + ( m_Sprites[0].m_flHorzSize * 0.8f );
		m_Sprites[0].m_flVertSize = m_Sprites[0].m_flHorzSize * 1.5f;
		
		float	cameraDistance = ( CurrentViewOrigin() - (m_pOwner->GetAbsOrigin())).Length();

		C_BasePlayer *local = C_BasePlayer::GetLocalPlayer();
		if ( local )
		{
			cameraDistance *= local->GetFOVDistanceAdjustFactor();
		}

		if ( cameraDistance > OVERLAY_MAX_VISIBLE_RANGE )
			cameraDistance = OVERLAY_MAX_VISIBLE_RANGE;

		float alpha = 1.0f - ( cameraDistance / OVERLAY_MAX_VISIBLE_RANGE );

		Vector	newColor = m_vBaseColors[0] + ( m_vBaseColors[0] * flickerScale * 0.5f );
		m_Sprites[0].m_vColor = ( newColor * 0.1f ) + ( m_Sprites[0].m_vColor * 0.9f ) * alpha;

		return true;
	}

public:

	C_FireSmoke	*m_pOwner;
	Vector		m_vBaseColors[MAX_SUN_LAYERS];
	float		m_flScale;
	int			m_nGUID;
};

//
// Entity flame, client-side implementation
//

#define	NUM_FLAMELETS	5

class C_EntityFlame : public C_BaseEntity
{
public:
	DECLARE_CLIENTCLASS();
	DECLARE_CLASS( C_EntityFlame, C_BaseEntity );

	C_EntityFlame( void );
	~C_EntityFlame( void );

	void OnDataChanged( DataUpdateType_t updateType );
	RenderGroup_t GetRenderGroup();
	void Simulate( void );

	EHANDLE			m_hEntAttached;				// The entity that we are burning (attached to).
	bool			m_bUseHitboxes;
	virtual void	ClientThink( void );

	C_FireSmoke *m_pFireSmoke[NUM_HITBOX_FIRES];

protected:

	void AttachToHitBoxes( void );
	void UpdateHitBoxFlames( void );
	void DeleteHitBoxFlames( void );

	float			m_flSize;
	CSmartPtr<CEmberEffect> m_pEmitter;
	TimedEvent		m_ParticleSpawn;
	bool			m_bAttachedToHitboxes;

	const model_t	*m_pCachedModel;				// Holds the model pointer to detect when it changes

	Vector			m_vecLastPosition;

	PMaterialHandle	m_MaterialHandle[NUM_FLAMELETS];

	// For attaching to the hitboxes of an animating model.
	Vector m_vecFireOrigin[NUM_HITBOX_FIRES];
	int m_nHitbox[NUM_HITBOX_FIRES];
};

#endif //C_FIRE_SMOKE_H