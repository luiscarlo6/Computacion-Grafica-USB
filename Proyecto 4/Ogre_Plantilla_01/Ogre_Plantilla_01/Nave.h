#include "Ogre\ExampleApplication.h"

class Nave{

	public:
	Ogre::SceneManager* mSceneMgr;
	Ogre::SceneNode* nodoNave;
	Ogre::String nombre;
	Ogre::Real x,z;

	Nave::Nave(Ogre::String nombre, Ogre::SceneManager* sm, Ogre::Real x, Ogre::Real y);

};