#pragma  once
#include "stdafx.h"

class Moneda{

	public:

	float x,y,z;
	Ogre::SceneManager* _sceneManager;
	Ogre::SceneNode* nodoMoneda;
	Ogre::AnimationState* animState;

	Moneda::Moneda( Ogre::String nombre , Ogre::SceneManager* sm , float x , float y , float z);

};
