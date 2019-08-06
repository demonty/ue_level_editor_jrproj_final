#ifndef APPSTATS_H
#define APPSTATS_H

#include <d3dx9.h>

class AppStats
{
public:
	AppStats();
	~AppStats();

	void onLostDevice();
	void onResetDevice();
	void update(float dt);
	void display();
	float getFPS(){return theFPS;}

private:
	AppStats(const AppStats& as);
	AppStats& operator=(const AppStats& as);

	
	ID3DXFont* theFont;
	float theFPS;
	float theMSPerFrame;
};

#endif //appstats.h