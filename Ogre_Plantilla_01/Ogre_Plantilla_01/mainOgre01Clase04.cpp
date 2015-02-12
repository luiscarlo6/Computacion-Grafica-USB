#include "Ogre\ExampleApplication.h"

Ogre::Light* light02;
float r=1.0;

class FrameListenerClase : public Ogre::FrameListener {

private:
	Ogre::SceneNode* nodoF01;
	Ogre::SceneNode* nodoF02;
	OIS::InputManager* _man;
	OIS::Keyboard* _key;
	OIS::Mouse* _mouse;
	Ogre::Camera* _cam;

public:

	FrameListenerClase(Ogre::SceneNode* nodo01, Ogre::SceneNode* nodo02, RenderWindow* win, Ogre::Camera* Cam ){

		//Conf captura teclado y mouse
		size_t windowHnd = 0;
		std::stringstream windowsHndStr;
		win->getCustomAttribute("WINDOW", &windowHnd);
		windowsHndStr << windowHnd;

		OIS::ParamList pl;
		pl.insert(std::make_pair(std::string("WINDOW"), windowsHndStr.str()));

		//Eventos
		_man = OIS::InputManager::createInputSystem(pl);
		_key = static_cast<OIS::Keyboard*>(_man->createInputObject(OIS::OISKeyboard,false));
		_mouse = static_cast<OIS::Mouse*>(_man->createInputObject(OIS::OISMouse,false));
		// Fin eventos
		

		_cam = Cam;
		nodoF01 = nodo01;
		nodoF02 = nodo02;
	}

	~FrameListenerClase(){
		_man->destroyInputObject(_key);
		_man->destroyInputObject(_mouse);
		OIS::InputManager::destroyInputSystem(_man);
	}

	bool frameStarted(const Ogre::FrameEvent &evt){		
		//nodoF01->translate(Ogre::Vector3(10.f,0.0f,0.0f) * evt.timeSinceLastFrame);
		//nodoF02->translate(Ogre::Vector3(10.f,0.0f,-10.0f) * evt.timeSinceLastFrame);

		_key->capture();
		_mouse->capture();
		
		float movSpeed = 10.0f;

		if (_key->isKeyDown(OIS::KC_ESCAPE))
			return false;

		Ogre::Vector3 t(0,0,0);
		Ogre::Vector3 tOgro(0,0,0);

		if (_key->isKeyDown(OIS::KC_W))
			t += Ogre::Vector3(0,0,-10);

		if (_key->isKeyDown(OIS::KC_S))
			t += Ogre::Vector3(0,0,10);

		if (_key->isKeyDown(OIS::KC_A))
			t += Ogre::Vector3(-10,0,0);

		if (_key->isKeyDown(OIS::KC_D))
			t += Ogre::Vector3(10,0,0);

		if (_key->isKeyDown(OIS::KC_T))
			tOgro += Ogre::Vector3(0,0,-10);

		if (_key->isKeyDown(OIS::KC_G))
			tOgro += Ogre::Vector3(0,0,10);

		if (_key->isKeyDown(OIS::KC_F))
			tOgro += Ogre::Vector3(-10,0,0);

		if (_key->isKeyDown(OIS::KC_H))
			tOgro += Ogre::Vector3(10,0,0);

		if (_key->isKeyDown(OIS::KC_1))
			r += 0.05;

		if (_key->isKeyDown(OIS::KC_2))
			r -= 0.05;

		light02->setDiffuseColour(Ogre::ColourValue(r,1.0f,1.0f));	

		float rotX = _mouse->getMouseState().X.rel * evt.timeSinceLastFrame* -1;
		float rotY = _mouse->getMouseState().Y.rel * evt.timeSinceLastFrame * -1;
		_cam->yaw(Ogre::Radian(rotX));
		_cam->pitch(Ogre::Radian(rotY));
		_cam->moveRelative(t*evt.timeSinceLastFrame*movSpeed);

		nodoF01->translate(tOgro * evt.timeSinceLastFrame);

		return true;
	}

};



class Example1 : public ExampleApplication
{
public:
	Ogre::SceneNode* nodeSinbad;
	Ogre::SceneNode* nodeEsfera02;
	
	Ogre::FrameListener* FrameListener01;

	Example1(){
		FrameListener01 = NULL;
	}

	~Example1(){
		if(FrameListener01){
			delete FrameListener01;
		}
	}

	void createFrameListener(){
		FrameListener01 = new FrameListenerClase(nodeSinbad, nodeEsfera02, mWindow, mCamera);
		mRoot->addFrameListener(FrameListener01);
	}

	void createCamera() {

		mCamera = mSceneMgr->createCamera("MyCamera1");
		mCamera->setPosition(100,50,100);
		mCamera->lookAt(0,0,0);
		mCamera->setNearClipDistance(5);

	}

	void createScene()
	{

		mSceneMgr->setAmbientLight(Ogre::ColourValue(1.0f, 1.0f, 1.0f));
		mSceneMgr->setShadowTechnique(Ogre::SHADOWTYPE_STENCIL_ADDITIVE);
 
		//Plano
		Ogre::Plane plane(Vector3::UNIT_Y, 0.0);
		Ogre::MeshManager::getSingleton().createPlane("plane", ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME, 
						plane, 1500,1500,200,200,true, 1,10,10, Vector3::UNIT_Z);

		Ogre::Entity* entPlano = mSceneMgr->createEntity("PlanoEntity","plane");
		mSceneMgr->getRootSceneNode()->createChildSceneNode()->attachObject(entPlano);
		entPlano->setMaterialName("Examples/BeachStones");
		
		Ogre::Entity* entEsfera02 = mSceneMgr->createEntity("EntEsfera02","sphere.mesh");
		//Ogre::SceneNode* nodeEsfera02 = mSceneMgr->createSceneNode("NodeEsfera02");
		nodeEsfera02 = mSceneMgr->createSceneNode("NodeEsfera02");
		mSceneMgr->getRootSceneNode()->addChild(nodeEsfera02);
		nodeEsfera02->attachObject(entEsfera02);

		//NODO LUZ
		float lightScale = 0.9f;
		Ogre::SceneNode* nodeLuz02 = mSceneMgr->createSceneNode("NodeLuz02");		
		light02 = mSceneMgr->createLight("LuzPoint01");
		light02->setType(Ogre::Light::LT_POINT);		
		light02->setDiffuseColour(lightScale*Ogre::ColourValue(1.0f,1.0f,1.0f));	
		nodeLuz02->attachObject(light02);


		nodeEsfera02->addChild(nodeLuz02);
		nodeEsfera02->setScale(0.05f,0.05f,0.05f);
		nodeEsfera02->setPosition(-50.0f,50.0f,50.0f);

		//Eje
		Ogre::Entity* ent01 = mSceneMgr->createEntity("MyEntity1","ejes01.mesh");
		Ogre::SceneNode* node01 = mSceneMgr->createSceneNode("Node01");
		mSceneMgr->getRootSceneNode()->addChild(node01);
		node01->attachObject(ent01);
		
		
		// Objetos
		nodeSinbad = mSceneMgr->createSceneNode("NodeSinbad");
		Ogre::Entity* entSinbad = mSceneMgr->createEntity("MyEntitySinbad","sinbad.mesh");
		mSceneMgr->getRootSceneNode()->addChild(nodeSinbad);
		nodeSinbad->attachObject(entSinbad);
		nodeSinbad->setPosition(0.0f,5.0f,0.0f);
		nodeSinbad->setScale(1.0f,1.0f,1.0f);
		



		/*
		Ogre::Entity* ent02 = mSceneMgr->createEntity("MyEntity2","cuadriculaX01.mesh");
		Ogre::SceneNode* node02 = mSceneMgr->createSceneNode("Node02");
		mSceneMgr->getRootSceneNode()->addChild(node02);
		node02->attachObject(ent02);

		// Objetos
		Ogre::SceneNode* nodeEjeSinbad = mSceneMgr->createSceneNode("NodeEjeSinbad");
		Ogre::SceneNode* nodeSinbad = mSceneMgr->createSceneNode("NodeSinbad");
		Ogre::SceneNode* nodeNinja = mSceneMgr->createSceneNode("NodeNinja");
		
		Ogre::Entity* entEjeSinbad = mSceneMgr->createEntity("MyEntityEjeSinbad","ejes01.mesh");
		Ogre::Entity* entSinbad = mSceneMgr->createEntity("MyEntitySinbad","sinbad.mesh");
		Ogre::Entity* entNinja = mSceneMgr->createEntity("MyEntityNinja","ninja.mesh");

		
		mSceneMgr->getRootSceneNode()->addChild(nodeEjeSinbad);
		nodeEjeSinbad->attachObject(entEjeSinbad);
		nodeEjeSinbad->addChild(nodeSinbad);
		nodeEjeSinbad->addChild(nodeNinja);

		nodeSinbad->attachObject(entSinbad);
		nodeNinja->attachObject(entNinja);
		
		//Eje
		nodeEjeSinbad->setScale(0.6,0.6,0.6);
		nodeEjeSinbad->setPosition(5.0,0.0,0.0);
		nodeEjeSinbad->translate(2.0,0.0,2.0);
		nodeEjeSinbad->yaw(Ogre::Degree(45.0f));//Rota en Y
		//nodeEjeSinbad->pitch(Ogre::Degree(45.0f));//Rota en X
		//nodeEjeSinbad->roll(Ogre::Degree(45.0f));//Rota en Z


		//Hijo Sinbad
		nodeSinbad->setScale(0.8,0.8,0.8);
		nodeSinbad->translate(0.0,0.0,8.0,Ogre::Node::TS_WORLD);
	
		//Hijo Ninja
		nodeNinja->setScale(0.04,0.04,0.04);
		nodeNinja->yaw(Ogre::Degree(180.0f));//Rota en Y
		nodeNinja->setPosition(4.0,-2.0,5.0);
		*/

		//node03->attachObject(ent03);
		//node03->attachObject(ent04);
		//node03->setScale(0.6,0.6,0.6);
		//node03->setPosition(5.0,0.0,0.0);












		/*Ogre::Entity* entMesh01 = mSceneMgr->createEntity("MyEntity1","ogrehead.mesh");
		Ogre::SceneNode* nodeMesh01 = mSceneMgr->createSceneNode("NodeMesh01");
		mSceneMgr->getRootSceneNode()->addChild(nodeMesh01);
		nodeMesh01->setPosition(0.0,0.0,0.0);
		nodeMesh01->attachObject(entMesh01);*/


		/*
		 mSceneMgr->setAmbientLight(Ogre::ColourValue(0.0, 0.0, 0.0));

		//Plano
		Ogre::Plane plane(Vector3::UNIT_Y,-6.0);
		Ogre::MeshManager::getSingleton().createPlane("plane",ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME,plane,500,500,20,20,true,1,20,20,Vector3::UNIT_Z);

		Ogre::Entity* entPlano01 = mSceneMgr->createEntity("PlaneEntity","plane");
		mSceneMgr->getRootSceneNode()->createChildSceneNode()->attachObject(entPlano01);

		entPlano01->setMaterialName("Examples/BeachStones");


		Ogre::Entity* entMesh01 = mSceneMgr->createEntity("MyEntity1","Sinbad.mesh");
		Ogre::SceneNode* nodeMesh01 = mSceneMgr->createSceneNode("NodeMesh01");
		mSceneMgr->getRootSceneNode()->addChild(nodeMesh01);
		//node01->addChild(nodeMesh01);
		//mSceneMgr->getRootSceneNode()->addChild(nodeMesh01);		
		nodeMesh01->setPosition(0.0,0.0,0.0);
		nodeMesh01->attachObject(entMesh01);

		

		
		//Creamos el nodo para Luz Puntual
		Ogre::SceneNode* nodeluzP01 = mSceneMgr->createSceneNode("nodeLuzPoint01");
		mSceneMgr->getRootSceneNode()->addChild(nodeluzP01);

		//EsferaPuntual
		Ogre::Entity* entLuzEsfera01 = mSceneMgr->createEntity("EntLuzEsfera01","sphere.mesh");

		//Luz puntual
		Ogre::Light* LuzPuntual01 = mSceneMgr->createLight("Luz01");
		LuzPuntual01->setType(Ogre::Light::LT_POINT);
		LuzPuntual01->setDiffuseColour(1.0,0.0,0.0);

		Ogre::MaterialPtr matEsf01 = entLuzEsfera01->getSubEntity(0)->getMaterial();
		matEsf01->setLightingEnabled(true);
		matEsf01->setDiffuse(Ogre::ColourValue(0.0, 0.0, 0.0));
		matEsf01->setAmbient(Ogre::ColourValue(0.0, 0.0, 0.0));
		matEsf01->setSelfIllumination(LuzPuntual01->getDiffuseColour());

		nodeluzP01->setScale(0.01f,0.01f,0.01f);
		nodeluzP01->setPosition(20.0,10.0,0.0);
		nodeluzP01->attachObject(entLuzEsfera01);
		nodeluzP01->attachObject(LuzPuntual01);
		
		
		
		//Creamos el nodo para Luz Puntual
		Ogre::SceneNode* nodeluzP02 = mSceneMgr->createSceneNode("nodeLuzPoint02");
		mSceneMgr->getRootSceneNode()->addChild(nodeluzP02);

		//EsferaPuntual
		Ogre::Entity* entLuzEsfera02 = mSceneMgr->createEntity("EntLuzEsfera02","sphere.mesh");

		//Luz puntual
		Ogre::Light* LuzPuntual02 = mSceneMgr->createLight("Luz02");
		LuzPuntual02->setType(Ogre::Light::LT_POINT);
		LuzPuntual02->setDiffuseColour(1.0,0.0,1.0);


		Ogre::MaterialPtr matEsf02 = entLuzEsfera02->getSubEntity(0)->getMaterial();
		matEsf02->setLightingEnabled(true);
		matEsf02->setDiffuse(Ogre::ColourValue(0.0, 0.0, 0.0));		
		matEsf02->setAmbient(Ogre::ColourValue(0.0, 0.0, 0.0));
		matEsf02->setSelfIllumination(LuzPuntual02->getDiffuseColour());
		//entLuzEsfera02->getSubEntity(0)->setMaterial();


		nodeluzP02->setScale(0.01f,0.01f,0.01f);
		nodeluzP02->setPosition(-20.0,10.0,10.0);
		nodeluzP02->attachObject(entLuzEsfera02);
		nodeluzP02->attachObject(LuzPuntual02);


		

	*/


	}

};


int main (void)
{

	Example1 app;
	app.go();
	return 0;
}