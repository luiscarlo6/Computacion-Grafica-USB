#include "stdafx.h"
bool freemoving = false;
int num_monedas = 45;
Moneda* moneda[45];
Banderin* banderin[2];
Nave* nave;

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

		if (_key->isKeyDown(OIS::KC_W))
			if (freemoving)
				t += Ogre::Vector3(0,0,-10);
			else
				nave->moverAdelante();
		if (_key->isKeyDown(OIS::KC_S))
			if (freemoving)
				t += Ogre::Vector3(0,0,10);
			else
				nave->moverAtras();

		if (_key->isKeyDown(OIS::KC_A))
			if (freemoving)
				t += Ogre::Vector3(-10,0,0);
			else
				nave->moverIzquierda();

		if (_key->isKeyDown(OIS::KC_D))
			if (freemoving)
				t += Ogre::Vector3(10,0,0);
			else
				nave->moverDerecha();
		if (_key->isKeyDown(OIS::KC_UP))
			nave->moverArriba();

		if (_key->isKeyDown(OIS::KC_DOWN))
			nave->moverAbajo();

		if (!_key->isKeyDown(OIS::KC_A) && !_key->isKeyDown(OIS::KC_D))
			nave->reset();

		if(_key->isKeyDown(OIS::KC_I))
			std::cout<<"CAMARA:"<<_cam->getPosition()<<std::endl
					 <<"NAVE:"<<nave->nodoNave->getPosition()<<std::endl;

		_cam->moveRelative(t*evt.timeSinceLastFrame*movSpeed);
		if (freemoving){
			float rotX = _mouse->getMouseState().X.rel * evt.timeSinceLastFrame* -1;
			float rotY = _mouse->getMouseState().Y.rel * evt.timeSinceLastFrame * -1;
		
			_cam->yaw(Ogre::Radian(rotX));
			_cam->pitch(Ogre::Radian(rotY));
		}
		for (int i = 0; i < num_monedas; i++)
		{
			moneda[i]->animState->addTime(evt.timeSinceLastFrame);
		}
		
		nave->animStateDer->addTime(evt.timeSinceLastFrame);
		nave->animStateIzq->addTime(evt.timeSinceLastFrame);
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
		 /*
		 if(!_root->showConfigDialog()){
			 return -1;
		 }
		 */

		 Ogre::RenderSystem* _rs = _root->getRenderSystemByName("Direct3D9 Rendering Subsystem");
		// or use "OpenGL Rendering Subsystem"
		_root->setRenderSystem(_rs);
		_rs->setConfigOption("Full Screen", "No");
		_rs->setConfigOption("Video Mode", "800 x 600 @ 32-bit colour");
		_rs->setConfigOption("FSAA", "0");
		_rs->setConfigOption("Floating-point mode", "Fastest");
		_rs->setConfigOption("Use Multihead", "Auto");
		_rs->setConfigOption("VSync", "No");
		_rs->setConfigOption("VSync Interval", "1");

		 Ogre::RenderWindow* window = _root->initialise(true, "Ventana Ogre");

		 _sceneManager =  _root->createSceneManager(Ogre::ST_GENERIC);

		 Ogre::Camera* camera = _sceneManager->createCamera("Camera");
		 camera->setPosition(Ogre::Vector3(0.0f,500.0f,-3000.0f));
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
		_sceneManager->setShadowTechnique(Ogre::SHADOWTYPE_STENCIL_ADDITIVE);

		_sceneManager->setSkyBox(true, "OMV/SkyBoxUnderwater1");

		Ogre::Plane plane(Ogre::Vector3::UNIT_Y , -5000.0);

		Ogre::MeshManager::getSingleton().createPlane("plane", Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME, 
						plane, 60000,100000,200,200,true, 1,10,10, Ogre::Vector3::UNIT_Z);
		Ogre::SceneNode* nodePlano;
		Ogre::Entity* entPlano = _sceneManager->createEntity("PlanoEntity","plane");
		nodePlano = _sceneManager->createSceneNode("NodePlano");
		nodePlano->attachObject(entPlano);
		_sceneManager->getRootSceneNode()->addChild(nodePlano);
		entPlano->setMaterialName("plano");
		nodePlano->translate(Ogre::Vector3(0.0f,0.0f,45000.0f));
		
		
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

		banderin[0] = new Banderin("Inicio",_sceneManager, 1105.0, 0.0, 0.0);
		_sceneManager->getRootSceneNode()->addChild(banderin[0]->nodoBanderin);
		banderin[1] = new Banderin("Fin",_sceneManager, 1105.0, 0.0, 90000.0);
		_sceneManager->getRootSceneNode()->addChild(banderin[1]->nodoBanderin);

		nave = new Nave(_sceneManager, _sceneManager->getCamera("Camera"));

		for (int i = 0; i < num_monedas; i++)
		{
			moneda[i] = new Moneda(std::to_string(i),_sceneManager,0.0,pow(-1,i)*250.0,i*2000.0);
		}

		//Aro* aro = new Aro("1",_sceneManager,0.0,0.0,1000.0);

		//Obstaculo obs = Obstaculo("1",1,_sceneManager,0.0,0.0,2000.0);
	 }
};

int main(void){

	OgreProyectos app;
	app.startup();
	return 0;
}
