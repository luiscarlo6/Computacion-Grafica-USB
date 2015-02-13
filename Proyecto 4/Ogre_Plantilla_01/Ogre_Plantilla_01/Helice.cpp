#include "Helice.h"

Helice::Helice(Ogre::String nombre, Ogre::SceneManager* sm, Ogre::Real x, Ogre::Real y){

	mSceneMgr = sm;

	nodoHelice = mSceneMgr->createSceneNode(nombre);
	Ogre::SceneNode* nodoTapaIzq = mSceneMgr->createSceneNode(nombre+"tapa");
	Ogre::SceneNode* nodoPala1 = mSceneMgr->createSceneNode(nombre+"pala1");
	Ogre::SceneNode* nodoPala2 = mSceneMgr->createSceneNode(nombre+"pala2");
	Ogre::SceneNode* nodoPala3 = mSceneMgr->createSceneNode(nombre+"pala3");
	Ogre::SceneNode* nodoPala4 = mSceneMgr->createSceneNode(nombre+"pala4");


	Ogre::Entity* entTapaIzq = mSceneMgr->createEntity("usb_formacurva.mesh");
	Ogre::Entity* entTapaDer = mSceneMgr->createEntity("usb_formacurva.mesh");
	Ogre::Entity* entPala1 = mSceneMgr->createEntity("usb_cubomod01.mesh");
	Ogre::Entity* entPala2 = mSceneMgr->createEntity("usb_cubomod01.mesh");
	Ogre::Entity* entPala3 = mSceneMgr->createEntity("usb_cubomod01.mesh");
	Ogre::Entity* entPala4 = mSceneMgr->createEntity("usb_cubomod01.mesh");

	entTapaIzq->setCastShadows(true);
	entTapaDer->setMaterialName("Helice_text");
	nodoHelice->attachObject(entTapaDer);	
	entTapaIzq->setMaterialName("Helice_text");
	nodoTapaIzq->attachObject(entTapaIzq);
	entPala1->setMaterialName("Helice_text");
	nodoPala1->attachObject(entPala1);
	entPala2->setMaterialName("Helice_text");
	nodoPala2->attachObject(entPala2);
	entPala3->setMaterialName("Helice_text");
	nodoPala3->attachObject(entPala3);
	entPala4->setMaterialName("Helice_text");
	nodoPala4->attachObject(entPala4);
	
	nodoPala1->setScale(1.5f,6.0f,0.5f);
	nodoPala1->rotate(Ogre::Vector3(1.0,0.0,0.0),Ogre::Radian(Ogre::Degree(-90.0)));
	nodoPala1->translate(0.0,0.0,25.0);

	nodoPala2->setScale(1.5f,6.0f,0.5f);
	nodoPala2->rotate(Ogre::Vector3(0.0,0.0,1.0),Ogre::Radian(Ogre::Degree(90.0)));
	nodoPala2->rotate(Ogre::Vector3(0.0,1.0,0.0),Ogre::Radian(Ogre::Degree(90.0)));
	nodoPala2->translate(25.0,0.0,0.0);

	nodoPala3->setScale(1.5f,6.0f,0.5f);
	nodoPala3->rotate(Ogre::Vector3(1.0,0.0,0.0),Ogre::Radian(Ogre::Degree(90.0)));
	nodoPala3->translate(0.0,0.0,-25.0);

	nodoPala4->setScale(1.5f,6.0f,0.5f);
	nodoPala4->rotate(Ogre::Vector3(0.0,0.0,1.0),Ogre::Radian(Ogre::Degree(-90.0)));
	nodoPala4->rotate(Ogre::Vector3(0.0,1.0,0.0),Ogre::Radian(Ogre::Degree(-90.0)));
	nodoPala4->translate(-25.0,0.0,0.0);
	
	nodoTapaIzq->rotate(Ogre::Vector3(0.0,0.0,1.0),Ogre::Radian(Ogre::Degree(180.0)));

	nodoHelice->addChild(nodoTapaIzq);
	nodoHelice->addChild(nodoPala1);
	nodoHelice->addChild(nodoPala2);
	nodoHelice->addChild(nodoPala3);
	nodoHelice->addChild(nodoPala4);
	nodoHelice->rotate(Ogre::Vector3(0.0,0.0,1.0),Ogre::Radian(Ogre::Degree(90.0)));
	nodoHelice->setPosition(x,1000,y); 
	nodoHelice->setScale(80.0f,80.0f,80.0f);
}