#include "Ogre\ExampleApplication.h"

class Torreta{

	public:
	Ogre::SceneManager* mSceneMgr;
	Ogre::SceneNode* nodoTorreta;
	Ogre::String nombre;
	Ogre::Real x,z;

	Torreta::Torreta(Ogre::String nombre, Ogre::SceneManager* sm, Ogre::Real x, Ogre::Real y);

};