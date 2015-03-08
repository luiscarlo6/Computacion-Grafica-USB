#pragma  once
#include "stdafx.h"

class Obstaculo{

	public:

	float x,y,z;
	Ogre::SceneManager* _sceneManager;
	Ogre::SceneNode* nodoObstaculo;
	Ogre::AnimationState* animState;

	Obstaculo::Obstaculo( Ogre::String nombre, int tipo , Ogre::SceneManager* sm , float x , float y , float z);

};
