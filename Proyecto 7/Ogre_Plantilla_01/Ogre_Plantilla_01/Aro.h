#pragma  once
#include "stdafx.h"

class Aro{

	public:

	float x,y,z;
	Ogre::SceneManager* mSceneMgr;
	Ogre::SceneNode* nodoAro;
	Ogre::AnimationState* animState;
	Ogre::Entity* entAro;
	Ogre::Real radio;
	bool visible;
	Aro::Aro( Ogre::String nombre , Ogre::SceneManager* sm , float x , float y , float z);
	Ogre::AxisAlignedBox Aro::getBox();
	bool Aro::adentro(Ogre::AxisAlignedBox box, Ogre::Vector3 center);
	bool Aro::adentro(Ogre::Vector3 point);
};
