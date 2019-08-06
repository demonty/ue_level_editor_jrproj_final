#include "dxCamera.h"
#include "dxInput.h"
#include "dxUtil.h"

Camera* theCamera = 0;

Camera::Camera()
{
	free = false;
	D3DXMatrixIdentity(&theView);
	D3DXMatrixIdentity(&theProjection);
	D3DXMatrixIdentity(&theViewProjection);

	theWorldPos   = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	theWorldRight = D3DXVECTOR3(1.0f, 0.0f, 0.0f);
	theWorldUp    = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	theWorldLook  = D3DXVECTOR3(0.0f, 0.0f, 1.0f);

	theSpeed = 100.0f;
}

Camera::~Camera()
{}

const D3DXMATRIX& Camera::view() const
{
	return theView;
}

const D3DXMATRIX& Camera::proj() const
{
	return theProjection;
}

const D3DXMATRIX& Camera::viewProj() const
{
	return theViewProjection;
}

const D3DXVECTOR3& Camera::right() const
{
	return theWorldRight;
}

const D3DXVECTOR3& Camera::up() const
{
	return theWorldUp;
}

const D3DXVECTOR3& Camera::look() const
{
	return theWorldLook;
}

void Camera::flipLook()
{
	theWorldLook *= -1.0f;
	theWorldRight *= -1.0f;
}

D3DXVECTOR3& Camera::pos()
{
	return theWorldPos;
}

void Camera::lookAt(D3DXVECTOR3& pos, D3DXVECTOR3& target, D3DXVECTOR3& up)
{
	D3DXVECTOR3 L = target - pos;
	D3DXVec3Normalize(&L, &L);
	D3DXVECTOR3 R;
	D3DXVec3Cross(&R, &up, &L);
	D3DXVec3Normalize(&R, &R);
	D3DXVECTOR3 U;
	D3DXVec3Cross(&U, &L, &R);
	D3DXVec3Normalize(&U, &U);

	theWorldPos = pos;
	theWorldRight = R;
	theWorldUp = U;
	theWorldLook = L;

	buildView();
	buildFPlanes();
	theViewProjection = theView * theProjection;
}

void Camera::setLens(float fov, float aspect, float nearZ, float farZ)
{
	D3DXMatrixPerspectiveFovLH(&theProjection, fov, aspect, nearZ, farZ);
	theViewProjection = theView * theProjection;
}

void Camera::setSpeed(float s)
{
	theSpeed = s;
}

void Camera::setFree(bool f)
{
	free = f;
}

void Camera::setCamera(int c)
{
	switch(c)
	{
	case 0:
		free = true;
		theWorldPos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		theWorldRight = D3DXVECTOR3(1.0f, 0.0f, 0.0f);
		theWorldUp = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		theWorldLook = D3DXVECTOR3(0.0f, 0.0f, 1.0f);
		break;
	case 1:
		free = false;
		theWorldPos		= D3DXVECTOR3( 0.0f,  200.0f, -150.0f);
		theWorldUp		= D3DXVECTOR3(0.0f, 0.0f, 1.0f);
		theWorldLook	= D3DXVECTOR3(0.0f, -0.845142f, 0.534541f);
		theWorldRight	= D3DXVECTOR3(1.0f, 0.0f, 0.0f);
		break;
	case 2:
		theWorldPos =	D3DXVECTOR3(0.0f, 100.0f, 0.0f);
		theWorldRight = D3DXVECTOR3(1.0f, 0.0f, 0.0f);
		theWorldUp =	D3DXVECTOR3(0.0f, 0.0f, -1.0f);
		theWorldLook =	D3DXVECTOR3(0.0f, -1.0f, 0.0f);
		break;
	case 3:
		theWorldPos =	D3DXVECTOR3(0.0f, 20.0f, -100.0f);
		theWorldRight = D3DXVECTOR3(1.0f, 0.0f, 0.0f);
		theWorldUp =	D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		theWorldLook =	D3DXVECTOR3(0.0f, 0.0f, 1.0f);
		break;
	case 4:
		theWorldPos =	D3DXVECTOR3(-100.0f, 20.0f, 0.0f);
		theWorldRight = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
		theWorldUp =	D3DXVECTOR3(0.0f, -1.0f, 0.0f);
		theWorldLook =	D3DXVECTOR3(1.0f, 0.0f, 0.0f);
		break;
	default:
		free = false;
		break;
	};
}

void Camera::update(float dt)
{
	if(!free)
	{
		D3DXVECTOR3 dir(0.0f, 0.0f, 0.0f);
		if(theGlobalInput->keyDown(DIK_W))
		{
			dir += theWorldUp;
		}
		if(theGlobalInput->keyDown(DIK_S))
		{
			dir -= theWorldUp;
		}
		if(theGlobalInput->keyDown(DIK_D))
		{
			dir += theWorldRight;
		}
		if(theGlobalInput->keyDown(DIK_A))
		{
			dir -= theWorldRight;
		}
		if(theGlobalInput->keyDown(DIK_Q))
		{
			dir += theWorldLook;
		}
		if(theGlobalInput->keyDown(DIK_E))
		{
			dir -= theWorldLook;
		}
		if(theGlobalInput->keyDown(DIK_SPACE))
		{
			free = false;
		}

		D3DXVec3Normalize(&dir, &dir);
		theWorldPos += dir*theSpeed*dt;

	}
	else
	{
		D3DXVECTOR3 dir(0.0f, 0.0f, 0.0f);
		if(theGlobalInput->keyDown(DIK_W))
		{
			dir.z += 1;
		}
		if(theGlobalInput->keyDown(DIK_S))
		{
			dir.z -= 1;
		}
		if(theGlobalInput->keyDown(DIK_D))
		{
			dir.x += 1;
		}
		if(theGlobalInput->keyDown(DIK_A))
		{
			dir.x -= 1;
		}
		if(theGlobalInput->keyDown(DIK_E))
		{
			dir.y -= 1;
		}
		if(theGlobalInput->keyDown(DIK_Q))
		{
			dir.y += 1;
		}

		D3DXVec3Normalize(&dir, &dir);
		theWorldPos += dir*theSpeed*dt;
	}

	if(theGlobalInput->mouseButtonDown(1))
	{
		float pitch = theGlobalInput->mouse_y() / 150.0f;
		float yAngle = theGlobalInput->mouse_x() / 150.0f;

		D3DXMATRIX R;
		D3DXMatrixRotationAxis(&R, &theWorldRight, pitch);
		D3DXVec3TransformCoord(&theWorldLook, &theWorldLook, &R);
		D3DXVec3TransformCoord(&theWorldUp, &theWorldUp, &R);

		D3DXMatrixRotationY(&R, yAngle);
		D3DXVec3TransformCoord(&theWorldRight, &theWorldRight, &R);
		D3DXVec3TransformCoord(&theWorldUp, &theWorldUp, &R);
		D3DXVec3TransformCoord(&theWorldLook, &theWorldLook, &R);
	}
	//}

	buildView();
	buildFPlanes();
	theViewProjection = theView * theProjection;
}

void Camera::buildView()
{
	D3DXVec3Normalize(&theWorldLook, &theWorldLook);

	D3DXVec3Cross(&theWorldUp, &theWorldLook, &theWorldRight);
	D3DXVec3Normalize(&theWorldUp, &theWorldUp);
	D3DXVec3Cross(&theWorldRight, &theWorldUp, &theWorldLook);
	D3DXVec3Normalize(&theWorldRight, &theWorldRight);

	float x = -D3DXVec3Dot(&theWorldPos, &theWorldRight);
	float y = -D3DXVec3Dot(&theWorldPos, &theWorldUp);
	float z = -D3DXVec3Dot(&theWorldPos, &theWorldLook);

	theView(0,0) = theWorldRight.x;
	theView(1,0) = theWorldRight.y;
	theView(2,0) = theWorldRight.z;
	theView(3,0) = x;
	theView(0,1) = theWorldUp.x;
	theView(1,1) = theWorldUp.y;
	theView(2,1) = theWorldUp.z;
	theView(3,1) = y;
	theView(0,2) = theWorldLook.x;
	theView(1,2) = theWorldLook.y;
	theView(2,2) = theWorldLook.z;
	theView(3,2) = z;
	theView(0,3) = 0.0f;
	theView(1,3) = 0.0f;
	theView(2,3) = 0.0f;
	theView(3,3) = 1.0f;
}

void Camera::buildFPlanes()
{
	D3DXMATRIX VP = theView * theProjection;

	D3DXVECTOR4 col0(VP(0,0), VP(1,0), VP(2,0), VP(3,0));
	D3DXVECTOR4 col1(VP(0,1), VP(1,1), VP(2,1), VP(3,1));
	D3DXVECTOR4 col2(VP(0,2), VP(1,2), VP(2,2), VP(3,2));
	D3DXVECTOR4 col3(VP(0,3), VP(1,3), VP(2,3), VP(3,3));

	theFPlanes[0] = (D3DXPLANE)(col2);		  //near
	theFPlanes[1] = (D3DXPLANE)(col3 - col2); //far
	theFPlanes[2] = (D3DXPLANE)(col3 + col0); //left
	theFPlanes[3] = (D3DXPLANE)(col3 - col0); //right
	theFPlanes[4] = (D3DXPLANE)(col3 - col1); //top
	theFPlanes[5] = (D3DXPLANE)(col3 + col1); //bottom

	for(int i = 0; i < 6; i++)
	{
		D3DXPlaneNormalize(&theFPlanes[i], &theFPlanes[i]);
	}
}

bool Camera::isVisible(AABB &box)
{
	//from book
	D3DXVECTOR3 P, Q;

	for(int i = 0; i < 3; i++)
	{
		for(int j = 0; j < 3; j++) //for each xyz axis
		{
			if(theFPlanes[i][j] >= 0.0f) //set as same direction as plane normal
			{
				P[j] = box.minPt[j];
				Q[j] = box.maxPt[j];
			}
			else
			{
				P[j] = box.maxPt[j];
				Q[j] = box.minPt[j];
			}
		}

		if(D3DXPlaneDotCoord(&theFPlanes[i], &Q) < 0.0f)
		{ //box is behind the plane
			return false;
		}
	}

	return true;
}

//void dxCamera::MoveUp()
//{
//}