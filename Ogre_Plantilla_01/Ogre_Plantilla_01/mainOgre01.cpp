#include "Ogre\ExampleApplication.h"

class Example1 : public ExampleApplication
{
public:


	void createCamera() {

		mCamera = mSceneMgr->createCamera("MyCamera1");
		mCamera->setPosition(60,10,60);
		mCamera->lookAt(0,0,0);
		mCamera->setNearClipDistance(5);

	}

	void createScene()
	{ 

		 mSceneMgr->setAmbientLight(Ogre::ColourValue(1.0, 1.0, 1.0));

		 
				
		Ogre::Entity* entMesh01 = mSceneMgr->createEntity("MyEntity1","ogrehead.mesh");
		Ogre::SceneNode* nodeMesh01 = mSceneMgr->createSceneNode("NodeMesh01");
		mSceneMgr->getRootSceneNode()->addChild(nodeMesh01);
		nodeMesh01->setPosition(0.0,0.0,0.0);
		nodeMesh01->attachObject(entMesh01);

		

	

	}

};


int main (void)
{

	Example1 app;
	app.go();
	return 0;
}