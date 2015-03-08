#pragma  once
#include "stdafx.h"

class Aro{

	public:

	float x,y,z;
	Ogre::SceneManager* _sceneManager;
	Ogre::SceneNode* nodoAro;
	Ogre::AnimationState* animState;

	Aro::Aro( Ogre::String nombre , Ogre::SceneManager* sm , float x , float y , float z);

};
