#pragma  once
#include "stdafx.h"

class Banderin{

	public:

	float x,y,z;
	Ogre::SceneManager* _sceneManager;
	Ogre::SceneNode* nodoBanderin;
	Ogre::AnimationState* animState;

	Banderin::Banderin( Ogre::String nombre , Ogre::SceneManager* sm , float x , float y , float z);

};
