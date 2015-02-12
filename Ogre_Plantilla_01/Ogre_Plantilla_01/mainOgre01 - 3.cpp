#include "Ogre\ExampleApplication.h"



class Example25FrameListener : public Ogre::FrameListener
{
private:
	Ogre::SceneNode* _node;
	

public:
	Ogre::FrameListener* FrameListener01;

	Example25FrameListener(Ogre::SceneNode* node)
	{
		_node = node;
	}

	bool frameStarted(const Ogre::FrameEvent &evt)
	{
		_node->translate(Ogre::Vector3(10,0,0) * evt.timeSinceLastFrame);
		return true;
	}

	Example25FrameListener()
	{
		FrameListener01 = NULL;
	}
	~Example25FrameListener()
	{
		if(FrameListener01)
		{
			delete FrameListener01;
		}

	}

};

class Example1 : public ExampleApplication
{
private:
	Ogre::SceneNode* _SinbadNode;
	
	Ogre::FrameListener* FL;
public:	
	
	void createCamera() {

		mCamera = mSceneMgr->createCamera("MyCamera1");
		mCamera->setPosition(0,100,200);
		mCamera->lookAt(0,0,0);
		mCamera->setNearClipDistance(5);

	}

	void createFrameListener()
	{
		FL = new Example25FrameListener(_SinbadNode);
		mRoot->addFrameListener(FL);
	}


	void createScene()
	{ 
		Ogre::Plane plane(Vector3::UNIT_Y, -10);
		Ogre::MeshManager::getSingleton().createPlane("plane",
			ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME, plane,
			1500,1500,200,200,true,1,5,5,Vector3::UNIT_Z);
		Ogre::Entity* ent = mSceneMgr->createEntity("LightPlaneEntity",
			"plane");
		mSceneMgr->getRootSceneNode()->createChildSceneNode()->attachObject(ent);
		ent->setMaterialName("Examples/BeachStones");

		Ogre::Light* light = mSceneMgr->createLight("Light1");
		light->setType(Ogre::Light::LT_DIRECTIONAL);
		light->setDirection(Ogre::Vector3(1,-1,0));

		Ogre::Light* light2 = mSceneMgr->createLight("Light2");
		light2->setType(Ogre::Light::LT_DIRECTIONAL);
		light2->setDirection(Ogre::Vector3(-1,-1,0));

		Ogre::SceneNode* node = mSceneMgr->createSceneNode("Node1");
		mSceneMgr->getRootSceneNode()->addChild(node);
		Ogre::Entity* Sinbad = mSceneMgr->createEntity("Sinbad", "Sinbad.mesh");
			_SinbadNode = node->createChildSceneNode("SinbadNode");
		_SinbadNode->setScale(3.0f,3.0f,3.0f);
		_SinbadNode->setPosition(Ogre::Vector3(0.0f,4.0f,0.0f));
		_SinbadNode->attachObject(Sinbad);

		mSceneMgr->setShadowTechnique(SHADOWTYPE_STENCIL_ADDITIVE);
	}


	Example25()
	{
		FL = NULL;
	}
	~Example25()
	{
		if(FL)
		{
			delete FL;
		}
	}
};




int main (void)
{

	Example1 app;
	app.go();
	return 0;
}