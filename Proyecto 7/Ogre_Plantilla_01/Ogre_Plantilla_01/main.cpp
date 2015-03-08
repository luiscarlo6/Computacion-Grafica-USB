#include "stdafx.h"

Ogre::SceneNode* nM03;

class FrameListenerProyectos : public Ogre::FrameListener{
private:
	Ogre::SceneNode* nodoF01;
	Ogre::SceneNode* nodoF02;
	OIS::InputManager* _man;
	OIS::Keyboard* _key;
	OIS::Mouse* _mouse;
	Ogre::Camera* _cam;

	//Animacion
	Ogre::Entity* _ent;
	Ogre::AnimationState* _aniState;
	Ogre::AnimationState* _aniStateTop;

	float _WalkingSpeed;
	float _rotation;

public:
	bool frameStarted(const Ogre::FrameEvent& evt){
		_key->capture();
		_mouse->capture();
		
		float movSpeed = 500.0f;


		if (_key->isKeyDown(OIS::KC_ESCAPE))
			return false;

		Ogre::Vector3 t(0,0,0);
		Ogre::Vector3 t_ogro(0,0,0);

		if (_key->isKeyDown(OIS::KC_W))
			t += Ogre::Vector3(0,0,-10);

		if (_key->isKeyDown(OIS::KC_S))
			t += Ogre::Vector3(0,0,10);

		if (_key->isKeyDown(OIS::KC_A))
			t += Ogre::Vector3(-10,0,0);

		if (_key->isKeyDown(OIS::KC_D))
			t += Ogre::Vector3(10,0,0);


		t_ogro+= Ogre::Vector3(0,0,-100);
		_cam->moveRelative(t*evt.timeSinceLastFrame*movSpeed);
		float rotX = _mouse->getMouseState().X.rel * evt.timeSinceLastFrame* -1;
		float rotY = _mouse->getMouseState().Y.rel * evt.timeSinceLastFrame * -1;
		_cam->yaw(Ogre::Radian(rotX));
		_cam->pitch(Ogre::Radian(rotY));
		
		//nM03->translate(t_ogro*evt.timeSinceLastFrame);
		return true;
	}

	bool frameEnded(const Ogre::FrameEvent& evt){
		return true;
	}

	FrameListenerProyectos(Ogre::RenderWindow* win, Ogre::Camera* Cam ){

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
	}

	~FrameListenerProyectos(){
		_man->destroyInputObject(_key);
		_man->destroyInputObject(_mouse);
		OIS::InputManager::destroyInputSystem(_man);
	}

};

class OgreProyectos{

private:
	Ogre::SceneManager* _sceneManager;
	Ogre::Root* _root;
	FrameListenerProyectos* _listener;

public:
	OgreProyectos(){
		_sceneManager = NULL;
		_root = NULL;
		_listener = NULL;
	}

	 ~OgreProyectos(){
		delete _root;
		delete _listener;
	}

	 void loadResources(){
		 Ogre::ConfigFile cf;
		 cf.load("recursos_propios.cfg");

		 Ogre::ConfigFile::SectionIterator sectionIter = cf.getSectionIterator();
		 Ogre::String sectionName, typeName, dataName;

		 while (sectionIter.hasMoreElements()){
			 sectionName = sectionIter.peekNextKey();
			 Ogre::ConfigFile::SettingsMultiMap *settings = sectionIter.getNext();
			 Ogre::ConfigFile::SettingsMultiMap::iterator i;

			 for(i = settings->begin(); i !=settings->end(); i++){
				 typeName = i->first;
				 dataName = i->second;
				 Ogre::ResourceGroupManager::getSingleton().addResourceLocation(dataName, typeName, sectionName);
			 }
			 Ogre::ResourceGroupManager::getSingleton().initialiseAllResourceGroups();
		 }
	 }

	 int startup(){
		 _root = new Ogre::Root("plugins_d.cfg");
		 if(!_root->showConfigDialog()){
			 return -1;
		 }

		 Ogre::RenderWindow* window = _root->initialise(true, "Ventana Ogre");

		 _sceneManager =  _root->createSceneManager(Ogre::ST_GENERIC);

		 Ogre::Camera* camera = _sceneManager->createCamera("Camera");
		 camera->setPosition(Ogre::Vector3(1100,1100,1100));
		 camera->lookAt(Ogre::Vector3(0,0,0));
		 camera->setNearClipDistance(5);

		 Ogre::Viewport* viewport = window->addViewport(camera);
		 viewport->setBackgroundColour(Ogre::ColourValue(0.0,0.0,0.0));
		 camera->setAspectRatio(Ogre::Real(viewport->getActualWidth()/viewport->getActualHeight()));

		 _listener = new FrameListenerProyectos(window,camera);
		 _root->addFrameListener(_listener);

		 loadResources();
		 createScene();
		 _root->startRendering();

		 return 0;
	 }

	 void createScene(){
		_sceneManager->setAmbientLight(Ogre::ColourValue(1.0f,1.0f,1.0f));

		Ogre::Plane plane(Ogre::Vector3::UNIT_Y , 0.0);

		Ogre::MeshManager::getSingleton().createPlane("plane", Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME, 
						plane, 10000,20000,200,200,true, 1,10,10, Ogre::Vector3::UNIT_Z);

		Ogre::Entity* entPlano = _sceneManager->createEntity("PlanoEntity","plane");
		_sceneManager->getRootSceneNode()->createChildSceneNode()->attachObject(entPlano);
		entPlano->setMaterialName("mat02");

		Ogre::SceneNode* nodeEsfera02;
		Ogre::Light* light02;
		Ogre::Entity* entEsfera02 = _sceneManager->createEntity("EntEsfera02","sphere.mesh");
		//Ogre::SceneNode* nodeEsfera02 = mSceneMgr->createSceneNode("NodeEsfera02");
		nodeEsfera02 = _sceneManager->createSceneNode("NodeEsfera02");
		_sceneManager->getRootSceneNode()->addChild(nodeEsfera02);
		nodeEsfera02->attachObject(entEsfera02);
		
		 //NODO LUZ
		float lightScale = 0.9f;
		Ogre::SceneNode* nodeLuz02 = _sceneManager->createSceneNode("NodeLuz02");		
		light02 = _sceneManager->createLight("LuzPoint01");
		light02->setType(Ogre::Light::LT_POINT);		
		light02->setDiffuseColour(lightScale*Ogre::ColourValue(2.0f,2.0f,2.0f));	
		nodeLuz02->attachObject(light02);


		nodeEsfera02->addChild(nodeLuz02);
		nodeEsfera02->setScale(0.05f,0.05f,0.05f);
		nodeEsfera02->setPosition(0.0f,5000.0f,0.0f);


		Ogre::Entity* ent01 = _sceneManager->createEntity("MyEntity1","ejes01.mesh");
		Ogre::SceneNode* node01 = _sceneManager->createSceneNode("Node01");
		_sceneManager->getRootSceneNode()->addChild(node01);
		node01->attachObject(ent01);
		node01->setScale(100.0f,100.0f,100.0f);
	 }
};

int main(void){

	OgreProyectos app;
	app.startup();
	return 0;
}