#include "Torreta.h"

Torreta::Torreta(Ogre::String nombre, Ogre::SceneManager* sm, Ogre::Real x, Ogre::Real y){

	mSceneMgr = sm;

	nodoTorreta = mSceneMgr->createSceneNode(nombre);
	Ogre::SceneNode* nodoSuperior = mSceneMgr->createSceneNode(nombre+"superior");
	Ogre::SceneNode* nodoArma = mSceneMgr->createSceneNode(nombre+"arma");

	Ogre::Entity* entTorreta = mSceneMgr->createEntity("usb_cilindro02.mesh");
	Ogre::Entity* entSuperior = mSceneMgr->createEntity("usb_dodecaedro.mesh");
	Ogre::Entity* entArma = mSceneMgr->createEntity("usb_cilindro.mesh");

	entTorreta->setMaterialName("Torreta_text");
	nodoTorreta->attachObject(entTorreta);
	entSuperior->setMaterialName("Torreta_text");
	nodoSuperior->attachObject(entSuperior);
	entArma->setMaterialName("Torreta_text");
	nodoArma->attachObject(entArma);

	nodoSuperior->setScale(0.6,0.6,0.6);
	nodoSuperior->translate(0.0,10.0,0.0);

	nodoArma->setScale(0.3,0.3,0.3);
	if(x<0){
		nodoArma->translate(6.0,10.0,0.0);
	}
	else {
		nodoArma->translate(-6.0,10.0,0.0);
	}
	nodoArma->rotate(Ogre::Vector3(0.0,0.0,1.0),Ogre::Radian(Ogre::Degree(90.0)));

	nodoTorreta->addChild(nodoSuperior);
	nodoTorreta->addChild(nodoArma);
	if (y<-18000){
		if (((x>0)&&((x<10000)||(x>20000)))||((x<-10000)&&(x>-20000))){
			nodoTorreta->rotate(Ogre::Vector3(0.0,1.0,0.0),Ogre::Radian(Ogre::Degree(90.0)));
		}
		else if (((x>10000)&&(x<20000))||((x<0)&&((x>-10000)||(x<-20000)))){
			nodoTorreta->rotate(Ogre::Vector3(0.0,1.0,0.0),Ogre::Radian(Ogre::Degree(270.0)));
		}
	}
	nodoTorreta->setPosition(x,-60,y); 
	nodoTorreta->setScale(50.0f,50.0f,50.0f);
}