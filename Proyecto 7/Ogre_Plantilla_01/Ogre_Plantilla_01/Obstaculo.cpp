#include "stdafx.h"

Obstaculo::Obstaculo(Ogre::String nombre, Ogre::SceneManager* sm , float _x , float _y , float _z){

	x = _x;
	y = _y;
	z = _z;
	mSceneMgr = sm;
	visible = true;
	
	nodoObstaculo = mSceneMgr->createSceneNode("Obstaculo"+nombre);
	Ogre::SceneNode* nodoMedio = mSceneMgr->createSceneNode("Obstaculo"+nombre+"medio");
	nodoSuperior = mSceneMgr->createSceneNode("Obstaculo"+nombre+"superior");
	
	entObstaculo = mSceneMgr->createEntity("poly17.mesh");
	Ogre::Entity* entMedio = mSceneMgr->createEntity("poly15.mesh");
	Ogre::Entity* entSuperior= mSceneMgr->createEntity("uv_sphere.mesh");
	entObstaculo->setMaterialName("obstaculo");
	entMedio->setMaterialName("cadena");
	entSuperior->setMaterialName("mina");
	
	nodoMedio->attachObject(entMedio);
	nodoMedio->setScale(1.0,2.0,1.0);
	nodoMedio->translate(0.0,120.0,0.0);

	nodoSuperior->attachObject(entSuperior);
	nodoSuperior->setScale(2.0,0.3,2.0);
	nodoSuperior->translate(0.0,250.0,0.0);

	nodoObstaculo->attachObject(entObstaculo);
	nodoObstaculo->addChild(nodoMedio);
	nodoObstaculo->addChild(nodoSuperior);
	
	nodoObstaculo->setPosition(x,y,z);
	nodoObstaculo->setScale(1.0,10.0,1.0);

	mSceneMgr->getRootSceneNode()->addChild(nodoObstaculo);


	
	Ogre::Real duration=4.0;
	Ogre::Real step=duration/4.0;
	Ogre::Real x_trans = x/4;
	Ogre::Animation* animation = mSceneMgr->createAnimation("AnimObs_"+nombre,duration);
	animation->setInterpolationMode(Ogre::Animation::IM_SPLINE);
	animation->setRotationInterpolationMode(Ogre::Animation::RIM_SPHERICAL);
	Ogre::NodeAnimationTrack* track = animation->createNodeTrack(0,nodoObstaculo);

	Ogre::TransformKeyFrame* key;
 
	key = track->createNodeKeyFrame(0.0f);
	key->setTranslate(Ogre::Vector3(x,y,z));
	key->setScale(Ogre::Vector3(1.0,10.0,1.0));
	//key->setRotation(Ogre::Quaternion(Ogre::Radian(Ogre::Degree(90.0)),Ogre::Vector3(1.0,0.0,0.0)));
	key->setRotation(Ogre::Quaternion(Ogre::Radian(Ogre::Degree(0.0)),Ogre::Vector3(0.0,1.0,0.0)));
	

	key = track->createNodeKeyFrame(step);
	key->setTranslate(Ogre::Vector3(x+x_trans,y,z));
	key->setScale(Ogre::Vector3(1.0,10.0,1.0));
	//key->setRotation(Ogre::Quaternion(Ogre::Radian(Ogre::Degree(90.0)),Ogre::Vector3(1.0,0.0,0.0)));
	key->setRotation(Ogre::Quaternion(Ogre::Radian(Ogre::Degree(90.0)),Ogre::Vector3(0.0,1.0,0.0)));
	
 
	key = track->createNodeKeyFrame(2.0*step);
	key->setTranslate(Ogre::Vector3(x+2*x_trans,y,z));
	key->setScale(Ogre::Vector3(1.0,10.0,1.0));
	//key->setRotation(Ogre::Quaternion(Ogre::Radian(Ogre::Degree(90.0)),Ogre::Vector3(1.0,0.0,0.0)));
	key->setRotation(Ogre::Quaternion(Ogre::Radian(Ogre::Degree(180.0)),Ogre::Vector3(0.0,1.0,0.0)));
	

	key = track->createNodeKeyFrame(3.0*step);
	key->setTranslate(Ogre::Vector3(x-x_trans,y,z));
	key->setScale(Ogre::Vector3(1.0,10.0,1.0));
	//key->setRotation(Ogre::Quaternion(Ogre::Radian(Ogre::Degree(90.0)),Ogre::Vector3(1.0,0.0,0.0)));
	key->setRotation(Ogre::Quaternion(Ogre::Radian(Ogre::Degree(270.0)),Ogre::Vector3(0.0,1.0,0.0)));
	

	key = track->createNodeKeyFrame(4.0*step);
	key->setTranslate(Ogre::Vector3(x,y,z));
	key->setScale(Ogre::Vector3(1.0,10.0,1.0));
	//key->setRotation(Ogre::Quaternion(Ogre::Radian(Ogre::Degree(90.0)),Ogre::Vector3(1.0,0.0,0.0)));
	key->setRotation(Ogre::Quaternion(Ogre::Radian(Ogre::Degree(360.0)),Ogre::Vector3(0.0,1.0,0.0)));

	animState = mSceneMgr->createAnimationState("AnimObs_"+nombre);
	animState->setEnabled(true);
	animState->setLoop(true);



	nodoObstaculo->_updateBounds();



}


Ogre::Vector3 Obstaculo::getCenter(){
	return nodoSuperior->getPosition();
}

Ogre::AxisAlignedBox Obstaculo::getBox(){

	return nodoSuperior->_getWorldAABB();
}
