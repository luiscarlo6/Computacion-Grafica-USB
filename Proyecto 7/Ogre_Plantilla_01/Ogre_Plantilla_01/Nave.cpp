#include "stdafx.h"

Nave::Nave(Ogre::SceneManager* sm, Ogre::Camera* cam){
	camera = cam;
	mSceneMgr = sm;
	lastMove = 0;
	speed = 50.0;
	x = 0.0;
	y = 0.0;
	z = 0.0;
	nodoNave = mSceneMgr->createSceneNode("Nave");
	nodoEntNave = nodoNave->createChildSceneNode("NaveEnt");
	nodoCamara = nodoNave->createChildSceneNode("NaveCam");

	mSceneMgr->getRootSceneNode()->addChild(nodoNave);
	Ogre::Entity* entNave = mSceneMgr->createEntity("RZR-002.mesh");
	entNave->setMaterialName("RZR-002");
	nodoEntNave->attachObject(entNave);		
	nodoNave->setPosition(0.0,0.0,0.0); 
	nodoNave->setScale(20.0f,20.0f,20.0f);
	nodoCamara->setPosition((Ogre::Vector3(0.0f,500.0f,-3000.0f)));


	Ogre::ParticleSystem* partSystem = mSceneMgr->createParticleSystem("Smoke","Examples/Smoke");
	nodoEntNave->attachObject(partSystem);

	Ogre::ParticleSystem* partSystem2 = mSceneMgr->createParticleSystem("Smoke2","Examples/Smoke2");
	//nodoEntNave->attachObject(partSystem2);

	Ogre::Vector3 escala(2.0f,2.0f,2.0f);
	Ogre::Light* light = mSceneMgr->createLight("luz");
	light->setType(Ogre::Light::LT_POINT);
	light->setDiffuseColour(Ogre::ColourValue(1.0f,1.0f,1.0f));
	light->setDirection(Ogre::Vector3(0.0,-1.0,0.0));
	light->setDirection(Ogre::Vector3(0.0,0.0,0.0));
	nodoEntNave->attachObject(light);
	nodoNave->attachObject(camera);


	Ogre::Animation* animDer = mSceneMgr->createAnimation("NaveAnimDer",1.0);
	animDer->setInterpolationMode(Ogre::Animation::IM_SPLINE);
	Ogre::NodeAnimationTrack* trackDer = animDer->createNodeTrack(0,nodoEntNave);

	Ogre::TransformKeyFrame* keyD;

	keyD = trackDer->createNodeKeyFrame(0.0f);
	//key->setTranslate(Ogre::Vector3(0.0,0.0,0.0));
	//key->setScale(Ogre::Vector3(0.5,0.5,0.5));
	keyD->setRotation(Ogre::Quaternion(Ogre::Radian(Ogre::Degree(0.0)),Ogre::Vector3(0.0,0.0,1.0)));

	keyD = trackDer->createNodeKeyFrame(1.0f);
	//key->setTranslate(Ogre::Vector3(0.0,-500,0.0));
	//key->setScale(Ogre::Vector3(0.5,0.5,0.5));
	keyD->setRotation(Ogre::Quaternion(Ogre::Radian(Ogre::Degree(45.0)),Ogre::Vector3(0.0,0.0,1.0)));

	animStateDer = mSceneMgr->createAnimationState("NaveAnimDer");
	animStateDer->setEnabled(false);
	animStateDer->setLoop(false);


	Ogre::Animation* animIzq = mSceneMgr->createAnimation("NaveAnimIzq",1.0);
	animIzq->setInterpolationMode(Ogre::Animation::IM_SPLINE);
	Ogre::NodeAnimationTrack* trackIzq = animIzq->createNodeTrack(0,nodoEntNave);

	Ogre::TransformKeyFrame* keyI;

	keyI = trackIzq->createNodeKeyFrame(0.0f);
	//key->setTranslate(Ogre::Vector3(0.0,0.0,0.0));
	//key->setScale(Ogre::Vector3(0.5,0.5,0.5));
	keyI->setRotation(Ogre::Quaternion(Ogre::Radian(Ogre::Degree(0.0)),Ogre::Vector3(0.0,0.0,1.0)));

	keyI = trackIzq->createNodeKeyFrame(1.0f);
	//key->setTranslate(Ogre::Vector3(0.0,-500,0.0));
	//key->setScale(Ogre::Vector3(0.5,0.5,0.5));
	keyI->setRotation(Ogre::Quaternion(Ogre::Radian(Ogre::Degree(-45.0)),Ogre::Vector3(0.0,0.0,1.0)));

	animStateIzq = mSceneMgr->createAnimationState("NaveAnimIzq");
	animStateIzq->setEnabled(false);
	animStateIzq->setLoop(false);

}


void Nave::moverDerecha(){
	nodoNave->translate(-speed,0.0,0.0);
	if ( lastMove != 1 ){

		lastMove++;
		animStateDer->setEnabled(true);
		animStateDer->setTimePosition(0.0);
		animStateIzq->setEnabled(false);
		//nodoEntNave->rotate(Ogre::Vector3(0.0,0.0,1.0),Ogre::Radian(Ogre::Degree(10.0)));
	}
	
	x-=speed;
}


void Nave::moverIzquierda(){
	nodoNave->translate(speed,0.0,0.0);
	if ( lastMove != -1 ){

		lastMove--;
		animStateIzq->setEnabled(true);
		animStateIzq->setTimePosition(0.0);
		animStateDer->setEnabled(false);
		//nodoEntNave->rotate(Ogre::Vector3(0.0,0.0,1.0),Ogre::Radian(Ogre::Degree(-10.0)));
	}
	x=speed;
	
}


void Nave::moverAdelante(){
	z+=speed;
	nodoNave->translate(0.0,0.0,speed);
}


void Nave::moverAtras(){
	z-=speed;
	nodoNave->translate(0.0,0.0,-speed);
}

void Nave::moverArriba(){
	y+=speed;
	nodoNave->translate(0.0,speed,0.0);
}

void Nave::moverAbajo(){
	y-=speed;
	nodoNave->translate(0.0,-speed,0.0);
}


void Nave::reset(){
	nodoEntNave->resetOrientation();
	animStateDer->setTimePosition(0.0);
	//animStateDer->setEnabled(false);
	animStateIzq->setTimePosition(0.0);
	//animStateIzq->setEnabled(false);
}