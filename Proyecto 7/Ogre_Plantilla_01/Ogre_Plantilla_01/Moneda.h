#pragma  once
#include "stdafx.h"

class Moneda{

	public:

	float x,y,z;
	Ogre::SceneManager* mSceneMgr;
	Ogre::SceneNode* nodoMoneda;
	Ogre::AnimationState* animState;
	Ogre::Entity* entMoneda;
	Ogre::Real scale;
	bool visible;
	Moneda::Moneda( Ogre::String nombre , Ogre::SceneManager* sm , float x , float y , float z);

	Ogre::Vector3 Moneda::getCenter();
	Ogre::Real Moneda::getRadius();
	Ogre::AxisAlignedBox Moneda::getBox();
};
