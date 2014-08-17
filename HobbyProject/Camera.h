#ifndef _CAMERA_H_
#define _CAMERA_H_

#include "Vector.h"

class Actor;

class Camera
{
public:
	Camera();
	~Camera();

	enum FollowMode
	{
		FOLLOW_ACTOR,
		FOLLOW_POSITION,
		STATIONARY,
	};

	static Camera*	getInstance();

	void			update( const float fDelta );
	void			follow( Actor* pFollowTarget );
	void			followPositionFeed( const Vector2f& vTrackedPosition );

	const Vector2f	getCameraOffset();

private:
	static Camera*	sm_pInstance;
	Vector2f		m_vCameraCenter;

	FollowMode		m_eFollowMode;

	Actor*			m_pFollowTarget;
	Vector2f		m_vSetFollowPosition;

};

#endif // _CAMERA_H_