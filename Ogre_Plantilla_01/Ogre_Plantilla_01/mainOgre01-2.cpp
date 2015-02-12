#include "Ogre\ExampleApplication.h"

class Example1 : public ExampleApplication
{
public:


	void createCamera() {

		mCamera = mSceneMgr->createCamera("MyCamera1");
		mCamera->setPosition(80,30,80);
		mCamera->lookAt(0,0,0);
		mCamera->setNearClipDistance(5);

	}

	void createScene()
	{ 

		 //mSceneMgr->setAmbientLight(Ogre::ColourValue(1.0, 0.0, 0.0));
		 mSceneMgr->setAmbientLight(Ogre::ColourValue(1.0, 1.0, 1.0));
		 mSceneMgr->setShadowTechnique(Ogre::SHADOWTYPE_STENCIL_ADDITIVE);

		 
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

		Ogre::Plane plane(Vector3::UNIT_Y,0.0);
		Ogre::MeshManager::getSingleton().createPlane("plane",ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME,plane,1500,1500,20,20,true,1,5,5,Vector3::UNIT_Z);

		Ogre::Entity* entPlano = mSceneMgr->createEntity("PlanoEntity","plane");
		mSceneMgr->getRootSceneNode()->createChildSceneNode()->attachObject(entPlano);
		entPlano->setMaterialName("Examples/BeachStones");

		
		Ogre::SceneNode* node02 = mSceneMgr->createSceneNode("NodeLuz");
		mSceneMgr->getRootSceneNode()->addChild(node02);
		
		Ogre::Light* Luz01 = mSceneMgr->createLight("Luz01");
		Luz01->setType(Ogre::Light::LT_POINT);
		Luz01->setPosition(-20,20,0);
		Luz01->setDiffuseColour(1.0f,1.0f,1.0f);
		Luz01->setCastShadows(false);

		Ogre::Entity* spLight01 = mSceneMgr->createEntity("MyEntitySphereLuz","sphere.mesh");
		Ogre::SceneNode* node04 = node02->createChildSceneNode("node04");
		node04->setScale(0.01f,0.01f,0.01f);
		node04->setPosition(-20,20,0);
		node04->attachObject(spLight01);

		
		Ogre::Light* Luz02 = mSceneMgr->createLight("Luz02");
		Luz02->setType(Ogre::Light::LT_POINT);
		Luz02->setPosition(20,20,0);
		Luz02->setDiffuseColour(1.0f,0.0f,0.0f);

		Ogre::Entity* spLight02 = mSceneMgr->createEntity("MyEntitySphereLuz","sphere.mesh");
		Ogre::SceneNode* node05 = node02->createChildSceneNode("node05");
		node05->setScale(0.01f,0.01f,0.01f);
		node05->setPosition(20,20,0);
		node05->attachObject(spLight02);


		Ogre::SceneNode* nodeSinbad = mSceneMgr->createSceneNode("NodeSinbad");
		Ogre::Entity* entSinbad = mSceneMgr->createEntity("MyEntitySinbad","sinbad.mesh");
		mSceneMgr->getRootSceneNode()->addChild(nodeSinbad);
		nodeSinbad->attachObject(entSinbad);

		nodeSinbad->setPosition(0.0f,5.0f,0.0f);
		nodeSinbad->setScale(1.0f,1.0f,1.0f);
		entSinbad->setCastShadows(false);

		/*
		Ogre::Light* Luz03 = mSceneMgr->createLight("Luz03");
		Luz03->setType(Ogre::Light::LT_SPOTLIGHT);
		Luz03->setPosition(0,40,0);
		Luz03->setDirection(Ogre::Vector3(0,-1,0));
		Luz03->setSpotlightInnerAngle(Ogre::Degree(5.0f));
		Luz03->setSpotlightOuterAngle(Ogre::Degree(45.0f));
		Luz03->setSpotlightFalloff(0.0f);

		Luz03->setDiffuseColour(1.0f,1.0f,1.0f);
		node02->attachObject(Luz03);
		*/
	}

};


int main (void)
{

	Example1 app;
	app.go();
	return 0;
}