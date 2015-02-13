#include "Torreta.h"

Torreta::Torreta(Ogre::String _nombre, Ogre::SceneManager* sm, Ogre::Real _x, Ogre::Real _z, Ogre::Real _r){

	mSceneMgr = sm;
	nombre = _nombre;
	x = _x;
	z = _z;
	rotacion = _r;

	nodoTorreta = mSceneMgr->createSceneNode(nombre);
	Ogre::SceneNode* nodoSuperior = mSceneMgr->createSceneNode(nombre+"superior");
	Ogre::SceneNode* nodoArma = mSceneMgr->createSceneNode(nombre+"arma");

	Ogre::Entity* entTorreta = mSceneMgr->createEntity("usb_cilindro02.mesh");
	Ogre::Entity* entSuperior = mSceneMgr->createEntity("uv_sphere.mesh");
	Ogre::Entity* entArma = mSceneMgr->createEntity("usb_cilindro.mesh");

	entTorreta->setMaterialName("Torreta_text");
	entSuperior->setMaterialName("Torreta_text1");
	entArma->setMaterialName("Torreta_text2");
	
	nodoSuperior->attachObject(entSuperior);	
	nodoSuperior->setScale(0.05,0.05,0.05);
	nodoSuperior->translate(0.0,10.0,0.0);

	nodoArma->attachObject(entArma);
	nodoArma->setScale(0.3,0.3,0.3);
	nodoArma->translate(6.0,10.0,0.0);
	nodoArma->rotate(Ogre::Vector3(0.0,0.0,1.0),Ogre::Radian(Ogre::Degree(90.0)));

	nodoTorreta->attachObject(entTorreta);	
	nodoTorreta->addChild(nodoSuperior);
	nodoTorreta->addChild(nodoArma);
	nodoTorreta->rotate(Ogre::Vector3(0.0,1.0,0.0),Ogre::Radian(Ogre::Degree(rotacion)));
	nodoTorreta->setPosition(x,-60,z); 
	nodoTorreta->setScale(50.0f,50.0f,50.0f);


	
	Ogre::SceneNode* nodoLaser = mSceneMgr->createSceneNode("Laser_"+nombre);
	//mSceneMgr->getRootSceneNode()->addChild(nodoLaser);
	nodoArma->addChild(nodoLaser);
	Ogre::Entity* laser = mSceneMgr->createEntity("entLaser_"+nombre,"usb_laser.mesh");
	laser->setMaterialName("Laser_text");
	nodoLaser->attachObject(laser);	
	//nodoLaser->setPosition(0.0,0.0,-2000.0);
	nodoLaser->rotate(Ogre::Vector3(1.0,0.0,0.0),Ogre::Radian(Ogre::Degree(90.0)));
	nodoLaser->setScale(40.0f,40.0f,40.0f);

	Ogre::Animation* animation = mSceneMgr->createAnimation("LaserAnim"+nombre,1.0);
	animation->setInterpolationMode(Animation::IM_SPLINE);
	NodeAnimationTrack* track = animation->createNodeTrack(0,nodoLaser);

	TransformKeyFrame* key;

	key = track->createNodeKeyFrame(0.0f);
	key->setTranslate(Ogre::Vector3(0.0,0.0,0.0));
	key->setScale(Ogre::Vector3(0.5,0.5,0.5));
	key->setRotation(Ogre::Quaternion(Ogre::Radian(Ogre::Degree(180.0)),Ogre::Vector3(0.0,0.0,1.0)));

	key = track->createNodeKeyFrame(1.0f);
	key->setTranslate(Ogre::Vector3(0.0,-500,0.0));
	key->setScale(Ogre::Vector3(0.5,0.5,0.5));
	key->setRotation(Ogre::Quaternion(Ogre::Radian(Ogre::Degree(180.0)),Ogre::Vector3(0.0,0.0,1.0)));

	animState = mSceneMgr->createAnimationState("LaserAnim"+nombre);
	animState->setEnabled(true);
	animState->setLoop(true);
}