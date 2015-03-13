#pragma  once
#include "stdafx.h"

class Obstaculo{

	public:

	float x,y,z;
	Ogre::SceneManager * mSceneMgr;
	Ogre::SceneNode* nodoObstaculo;
	Ogre::SceneNode* nodoSuperior;
	Ogre::AnimationState* animState;
	Ogre::Entity* entObstaculo;
	Obstaculo::Obstaculo( Ogre::String nombre, Ogre::SceneManager* sm , float x , float y , float z);
	bool visible;
	Ogre::Vector3 Obstaculo::getCenter();

	Ogre::Real Obstaculo::getRadius();

	Ogre::AxisAlignedBox Obstaculo::getBox();
};
