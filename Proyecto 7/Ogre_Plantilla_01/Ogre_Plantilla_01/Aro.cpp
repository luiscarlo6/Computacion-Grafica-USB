#include "stdafx.h"

Aro::Aro( Ogre::String nombre , Ogre::SceneManager* sm , float _x , float _y , float _z){

	x = _x;
	y = _y;
	z = _z;
	mSceneMgr = sm;
	Ogre::Vector3 scale = Ogre::Vector3(4.0);
	visible = true;
	nodoAro = mSceneMgr->createSceneNode("Aro"+nombre);
	mSceneMgr->getRootSceneNode()->addChild(nodoAro);
	entAro = mSceneMgr->createEntity("poly04.mesh");
	entAro->setMaterialName("mat01");
	nodoAro->rotate(Ogre::Quaternion(Ogre::Radian(Ogre::Degree(90.0)),Ogre::Vector3(1.0,0.0,0.0)));
	nodoAro->attachObject(entAro);
	nodoAro->setPosition(x,y,z); 
	nodoAro->setScale(scale);
	//nodoAro->showBoundingBox(true);
	nodoAro->_updateBounds();
	
	Ogre::AxisAlignedBox box = nodoAro->_getWorldAABB();
	Ogre::Vector3 centro = nodoAro->getPosition();
	Ogre::Vector3 corner1 = box.getCorner(Ogre::AxisAlignedBox::CornerEnum::FAR_LEFT_TOP);
	Ogre::Vector3 medium(corner1.x, centro.y, centro.z);

	radio =  medium.distance(centro);
}

Ogre::AxisAlignedBox Aro::getBox(){

	return entAro->getWorldBoundingBox();
}

bool Aro::adentro(Ogre::Vector3 point){
	Ogre::Vector3 myPos = nodoAro->getPosition();
	Ogre::Real x = point.x - myPos.x;
	Ogre::Real y = point.y - myPos.y;

	bool result = (x*x + y*y) < radio*radio;
	return result;
}

bool Aro::adentro(Ogre::AxisAlignedBox box, Ogre::Vector3 center){
	Ogre::Vector3 centroAro = nodoAro->getPosition();
	Ogre::Vector3 topRight = box.getCorner(Ogre::AxisAlignedBox::CornerEnum::FAR_RIGHT_TOP);
	Ogre::Vector3 botLeft = box.getCorner(Ogre::AxisAlignedBox::CornerEnum::FAR_LEFT_BOTTOM);

	if (abs(center.z - centroAro.z) > 10.0f)
		return false;

	if (!this->adentro(topRight)|| !this->adentro(botLeft)){
		return false;
	}
	return true;
}