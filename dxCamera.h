#ifndef DXCAMERA_H
#define DXCAMERA_H

#include <d3dx9.h>
#include "dxUtil.h"
#pragma comment(lib, "dinput8.lib")

class Camera
{
public:
	Camera();
	~Camera();

	const D3DXMATRIX& view() const;
	const D3DXMATRIX& proj() const;
	const D3DXMATRIX& viewProj() const;

	const D3DXVECTOR3& right() const;
	const D3DXVECTOR3& up() const;
	const D3DXVECTOR3& look() const;

	D3DXVECTOR3& pos();

	void lookAt(D3DXVECTOR3& pos,
				D3DXVECTOR3& target,
				D3DXVECTOR3& up);
	bool isVisible(AABB& box);
	void setLens(float fov, float aspect, float nearZ, float farZ);
	void setSpeed(float s);
	void setCamera(int c);
	void setFree(bool f);
	void update(float dt);
	void flipLook();

	void MoveUp();
	void MoveDown();
	void MoveLeft();
	void MoveRight();
	void ZoomIn();
	void ZoomOut();

protected:
	void buildView();
	void buildFPlanes();

	D3DXMATRIX theView;
	D3DXMATRIX theProjection;
	D3DXMATRIX theViewProjection;

	D3DXVECTOR3 theWorldPos;
	D3DXVECTOR3 theWorldRight;
	D3DXVECTOR3 theWorldUp;
	D3DXVECTOR3 theWorldLook;

	float theSpeed;
	bool free;

	D3DXPLANE theFPlanes[6]; //near
						 //far
						 //left
						 //right
						 //top
						 //bottom
};

#endif