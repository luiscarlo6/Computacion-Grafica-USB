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

		 
	/*			
		Ogre::Entity* entMesh01 = mSceneMgr->createEntity("MyEntity1","ogrehead.mesh");
		Ogre::SceneNode* nodeMesh01 = mSceneMgr->createSceneNode("NodeMesh01");
		mSceneMgr->getRootSceneNode()->addChild(nodeMesh01);
		nodeMesh01->setPosition(0.0,0.0,0.0);
		nodeMesh01->attachObject(entMesh01);
	*/	
		
		Ogre::Entity* ent01 = mSceneMgr->createEntity("MyEntity1","ejes01.mesh");
		Ogre::SceneNode* node01 = mSceneMgr->createSceneNode("Node01");
		mSceneMgr->getRootSceneNode()->addChild(node01);
		node01->attachObject(ent01);

		Ogre::Entity* ent02 = mSceneMgr->createEntity("MyEntity2","cuadriculaX01.mesh");
		Ogre::SceneNode* node02 = mSceneMgr->createSceneNode("Node02");
		mSceneMgr->getRootSceneNode()->addChild(node02);
		node02->attachObject(ent02);

		Ogre::SceneNode* nodeSinbad = mSceneMgr->createSceneNode("NodeSinbad");
		Ogre::SceneNode* nodeEjeSinbad = mSceneMgr->createSceneNode("NodeEjeSinbad");
		Ogre::SceneNode* nodeNinja = mSceneMgr->createSceneNode("NodeNinja");

		Ogre::Entity* entSinbad = mSceneMgr->createEntity("MyEntitySinbad","sinbad.mesh");
		Ogre::Entity* entEjeSinbad = mSceneMgr->createEntity("MyEntityEjeSinbad","ejes01.mesh");
		Ogre::Entity* entNinja = mSceneMgr->createEntity("MyEntityNinja","ninja.mesh");
		
		mSceneMgr->getRootSceneNode()->addChild(nodeEjeSinbad);
		nodeEjeSinbad->attachObject(entEjeSinbad);
		nodeEjeSinbad->addChild(nodeSinbad);
		nodeEjeSinbad->addChild(nodeNinja);


		nodeSinbad->attachObject(entSinbad);
		nodeNinja->attachObject(entNinja);

		//eje
		nodeEjeSinbad->setScale(0.6,0.6,0.6);
		nodeEjeSinbad->setPosition(5.0,0.0,0.0);
		nodeEjeSinbad->translate(2.0,0.0,2.0);
		nodeEjeSinbad->yaw(Ogre::Degree(45.0f)); //rota en Y
		//nodeEjeSinbad->pitch(Ogre::Degree(45.0f));//rota en X
		//nodeEjeSinbad->roll(Ogre::Degree(45.0f));//rota en Z

		//Hijo Sinbad
		nodeSinbad->setScale(0.8,0.8,0.8);
		nodeSinbad->translate(0.0,0.0,8.0,Ogre::Node::TS_WORLD);

		//Hijo Ninja
		nodeNinja->setScale(0.04,0.04,0.04);
		nodeNinja->yaw(Ogre::Degree(180.0f));
		nodeNinja->setPosition(4.0,-4.0,5.0);

		/*nodeSinbad->attachObject(entEjeSinbad);
		nodeSinbad->attachObject(ejeSinbad);
		*/

	}

};


int main (void)
{

	Example1 app;
	app.go();
	return 0;
}