#include "stdafx.h"
#include "Camera.h"

#include "App.h"
#include "Actor.h"

Camera* Camera::sm_pInstance = nullptr;

Camera::Camera()
{
	m_vCameraCenter = Root::GetInstance()->getHalfRes();
	assert( sm_pInstance == nullptr && "Tried having two cameras at a time" );
	sm_pInstance = this;
	m_eFollowMode = STATIONARY;
}

Camera::~Camera()
{
	sm_pInstance = nullptr;
}

Camera* Camera::getInstance()
{
	return sm_pInstance;
}

void Camera::update( const float fDelta )
{
	static const float fMaxSpeed = 100.f;
	Vector2f vToTarget;
	if( m_eFollowMode == FOLLOW_ACTOR )
	{
		if( m_pFollowTarget != nullptr )
		{
			const Vector2f& vTargetPosition = m_pFollowTarget->GetPosition();
			vToTarget = vTargetPosition - m_vCameraCenter;
		}
	}
	else if( m_eFollowMode == FOLLOW_POSITION )
	{
		vToTarget = m_vSetFollowPosition - m_vCameraCenter;
	}
	if( ( fMaxSpeed * fMaxSpeed ) < vToTarget.Length2() )
		{
			vToTarget = vToTarget.Normalize() * fMaxSpeed;
		}
	m_vCameraCenter += vToTarget * fDelta;
}

void Camera::follow( Actor* pFollowTarget )
{
	m_eFollowMode = FOLLOW_ACTOR;
	m_pFollowTarget = pFollowTarget;
}

void Camera::followPositionFeed( const Vector2f& vTrackedPosition )
{
	m_eFollowMode = FOLLOW_POSITION;
	m_vSetFollowPosition = vTrackedPosition;
}
const Vector2f Camera::getCameraOffset()
{
	return m_vCameraCenter - Root::GetInstance()->getHalfRes();
}