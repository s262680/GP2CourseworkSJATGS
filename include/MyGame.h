#ifndef _MyGame_H
#define _MyGame_H

#include "GameApplication.h"

class MyGame:public GameApplication
{
public:
	MyGame();
	~MyGame();

	void render();
	void update();
	void initScene();
	void destroyScene();

	void onKeyDown(SDL_Keycode keyCode);
private:
	//matrices
	mat4 m_ViewMatrix;
	mat4 m_ProjMatrix;

	shared_ptr<GameObject> m_TestGO;

	vector<shared_ptr<GameObject> > GOList;//KS
	
	shared_ptr<Light> m_Light;
	vec4 m_AmbientLightColour;

	vec3 m_CameraPosition;
};
#endif
