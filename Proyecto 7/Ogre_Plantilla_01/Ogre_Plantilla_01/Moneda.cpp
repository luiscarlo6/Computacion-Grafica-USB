#include "stdafx.h"

Moneda::Moneda( Ogre::String nombre , Ogre::SceneManager* sm , float _x , float _y , float _z){

	x = _x;
	y = _y;
	z = _z;
	mSceneMgr = sm;
	scale = 0.7;
	visible = true;
	nodoMoneda = mSceneMgr->createSceneNode("moneda_"+nombre);
	mSceneMgr->getRootSceneNode()->addChild(nodoMoneda);
	entMoneda = mSceneMgr->createEntity("poly14.mesh");
	entMoneda->setMaterialName("moneda");
	nodoMoneda->rotate(Ogre::Quaternion(Ogre::Radian(Ogre::Degree(90.0)),Ogre::Vector3(1.0,0.0,0.0)));
	nodoMoneda->attachObject(entMoneda);
	nodoMoneda->setPosition(x,y,z); 
	nodoMoneda->setScale(scale,scale,scale);
	//nodoMoneda->showBoundingBox(true);
	
	Ogre::Real duration=4.0;
	Ogre::Real step=duration/4.0;
	Ogre::Animation* animation = mSceneMgr->createAnimation("AnimMoneda_"+nombre,duration);
	animation->setInterpolationMode(Ogre::Animation::IM_SPLINE);
	animation->setRotationInterpolationMode(Ogre::Animation::RIM_SPHERICAL);
	Ogre::NodeAnimationTrack* track = animation->createNodeTrack(0,nodoMoneda);

	Ogre::TransformKeyFrame* key;
 
	key = track->createNodeKeyFrame(0.0f);
	key->setTranslate(Ogre::Vector3(x,y,z));
	key->setScale(Ogre::Vector3(scale,scale,scale));
	//key->setRotation(Ogre::Quaternion(Ogre::Radian(Ogre::Degree(90.0)),Ogre::Vector3(1.0,0.0,0.0)));
	key->setRotation(Ogre::Quaternion(Ogre::Radian(Ogre::Degree(0.0)),Ogre::Vector3(1.0,1.0,1.0)));
	

	key = track->createNodeKeyFrame(step);
	key->setTranslate(Ogre::Vector3(x,y,z));
	key->setScale(Ogre::Vector3(scale,scale,scale));
	//key->setRotation(Ogre::Quaternion(Ogre::Radian(Ogre::Degree(90.0)),Ogre::Vector3(1.0,0.0,0.0)));
	key->setRotation(Ogre::Quaternion(Ogre::Radian(Ogre::Degree(90.0)),Ogre::Vector3(1.0,1.0,1.0)));
	
 
	key = track->createNodeKeyFrame(2.0*step);
	key->setTranslate(Ogre::Vector3(x,y,z));
	key->setScale(Ogre::Vector3(scale,scale,scale));
	//key->setRotation(Ogre::Quaternion(Ogre::Radian(Ogre::Degree(90.0)),Ogre::Vector3(1.0,0.0,0.0)));
	key->setRotation(Ogre::Quaternion(Ogre::Radian(Ogre::Degree(180.0)),Ogre::Vector3(1.0,1.0,1.0)));
	

	key = track->createNodeKeyFrame(3.0*step);
	key->setTranslate(Ogre::Vector3(x,y,z));
	key->setScale(Ogre::Vector3(scale,scale,scale));
	//key->setRotation(Ogre::Quaternion(Ogre::Radian(Ogre::Degree(90.0)),Ogre::Vector3(1.0,0.0,0.0)));
	key->setRotation(Ogre::Quaternion(Ogre::Radian(Ogre::Degree(270.0)),Ogre::Vector3(1.0,1.0,1.0)));
	

	key = track->createNodeKeyFrame(4.0*step);
	key->setTranslate(Ogre::Vector3(x,y,z));
	key->setScale(Ogre::Vector3(scale,scale,scale));
	//key->setRotation(Ogre::Quaternion(Ogre::Radian(Ogre::Degree(90.0)),Ogre::Vector3(1.0,0.0,0.0)));
	key->setRotation(Ogre::Quaternion(Ogre::Radian(Ogre::Degree(360.0)),Ogre::Vector3(1.0,1.0,1.0)));
	

	animState = mSceneMgr->createAnimationState("AnimMoneda_"+nombre);
	animState->setEnabled(true);
	animState->setLoop(true);

	nodoMoneda->_updateBounds();
	
}
Ogre::Vector3 Moneda::getCenter(){
	return nodoMoneda->getPosition();
}


Ogre::Real Moneda::getRadius(){
	return entMoneda->getBoundingRadius();
}

Ogre::AxisAlignedBox Moneda::getBox(){

	return entMoneda->getWorldBoundingBox();
}
