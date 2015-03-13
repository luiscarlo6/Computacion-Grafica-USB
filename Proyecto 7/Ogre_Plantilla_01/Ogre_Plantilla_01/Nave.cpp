#include "stdafx.h"

Nave::Nave(Ogre::SceneManager* sm, Ogre::Camera* cam){
	camera = cam;
	mSceneMgr = sm;
	lastMove = 0;
	speed = 50.0;
	x = 0.0;
	y = 0.0;
	z = 0.0;
	Ogre::Real s = 20.0f;
	nodoNave = mSceneMgr->createSceneNode("Nave");
	nodoEntNave = nodoNave->createChildSceneNode("NaveEnt");
	nodoCamara = nodoNave->createChildSceneNode("NaveCam");

	mSceneMgr->getRootSceneNode()->addChild(nodoNave);
	entNave = mSceneMgr->createEntity("Batboat.001.mesh");
	nodoEntNave->attachObject(entNave);		
	nodoNave->setPosition(0.0,0.0,0.0); 
	nodoEntNave->setScale(s,s,s);
	nodoCamara->setPosition((Ogre::Vector3(0.0f,300.0f,-1000.0f)));
	
//	nodoEntNave->showBoundingBox(true);

	Ogre::ParticleSystem* partSystem = mSceneMgr->createParticleSystem("Smoke","Examples/Smoke");
	nodoNave->attachObject(partSystem);

	Ogre::ParticleSystem* partSystem2 = mSceneMgr->createParticleSystem("Smoke2","Examples/Smoke2");
	nodoNave->attachObject(partSystem2);

	Ogre::Light* light = mSceneMgr->createLight("luz");
	light->setType(Ogre::Light::LT_POINT);
	light->setDiffuseColour(Ogre::ColourValue(1.0f,1.0f,1.0f));
	light->setDirection(Ogre::Vector3(0.0,-1.0,0.0));
	light->setDirection(Ogre::Vector3(0.0,0.0,0.0));
	nodoEntNave->attachObject(light);
	nodoCamara->attachObject(camera);


	Ogre::Animation* animDer = mSceneMgr->createAnimation("NaveAnimDer",1.0);
	animDer->setInterpolationMode(Ogre::Animation::IM_SPLINE);
	Ogre::NodeAnimationTrack* trackDer = animDer->createNodeTrack(0,nodoEntNave);

	Ogre::TransformKeyFrame* keyD;

	keyD = trackDer->createNodeKeyFrame(0.0f);
	//key->setTranslate(Ogre::Vector3(0.0,0.0,0.0));
	keyD->setScale(Ogre::Vector3(s,s,s));
	keyD->setRotation(Ogre::Quaternion(Ogre::Radian(Ogre::Degree(0.0)),Ogre::Vector3(0.0,0.0,1.0)));

	keyD = trackDer->createNodeKeyFrame(1.0f);
	//key->sdwetTranslate(Ogre::Vector3(0.0,-500,0.0));
	keyD->setScale(Ogre::Vector3(s,s,s));
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
	keyI->setScale(Ogre::Vector3(s,s,s));
	keyI->setRotation(Ogre::Quaternion(Ogre::Radian(Ogre::Degree(0.0)),Ogre::Vector3(0.0,0.0,1.0)));

	keyI = trackIzq->createNodeKeyFrame(1.0f);
	//key->setTranslate(Ogre::Vector3(0.0,-500,0.0));
	keyI->setScale(Ogre::Vector3(s,s,s));
	keyI->setRotation(Ogre::Quaternion(Ogre::Radian(Ogre::Degree(-45.0)),Ogre::Vector3(0.0,0.0,1.0)));

	animStateIzq = mSceneMgr->createAnimationState("NaveAnimIzq");
	animStateIzq->setEnabled(false);
	animStateIzq->setLoop(false);

	nodoNave->_updateBounds();

}


void Nave::moverDerecha(){
	if (entNave->getWorldBoundingBox().getCorner(Ogre::AxisAlignedBox::CornerEnum::NEAR_LEFT_BOTTOM).x <=-4975)
		return;
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
	if (entNave->getWorldBoundingBox().getCorner(Ogre::AxisAlignedBox::CornerEnum::NEAR_RIGHT_BOTTOM).x >=4975)
		return;
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
	if (entNave->getWorldBoundingBox().getCorner(Ogre::AxisAlignedBox::CornerEnum::NEAR_RIGHT_BOTTOM).z >=89975)
		return;
	z+=speed;
	nodoNave->translate(0.0,0.0,speed);
}


void Nave::moverAtras(){
	if (entNave->getWorldBoundingBox().getCorner(Ogre::AxisAlignedBox::CornerEnum::FAR_RIGHT_BOTTOM).z <=25)
		return;
	z-=speed;
	nodoNave->translate(0.0,0.0,-speed);
}

void Nave::moverArriba(){
	if (entNave->getWorldBoundingBox().getCorner(Ogre::AxisAlignedBox::CornerEnum::NEAR_RIGHT_TOP).y >=4975)
		return;
	y+=speed;
	nodoNave->translate(0.0,speed,0.0);
}

void Nave::moverAbajo(){
	if (entNave->getWorldBoundingBox().getCorner(Ogre::AxisAlignedBox::CornerEnum::NEAR_RIGHT_BOTTOM).y <=-4975)
		return;
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

Ogre::AxisAlignedBox Nave::getBox(){
	return entNave->getWorldBoundingBox();
}

Ogre::Vector3 Nave::getCenter(){
	return nodoNave->getPosition();
}