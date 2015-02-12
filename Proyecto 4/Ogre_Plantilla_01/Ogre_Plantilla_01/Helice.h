#include "Ogre\ExampleApplication.h"

class Helice{

	public:
	Ogre::SceneManager* mSceneMgr;
	Ogre::SceneNode* nodoHelice;
	Ogre::String nombre;
	Ogre::Real x,z;

	Helice::Helice(Ogre::String nombre, Ogre::SceneManager* sm, Ogre::Real x, Ogre::Real y);

};