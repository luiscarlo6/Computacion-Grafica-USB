#include "Ogre\ExampleApplication.h"
#include "Torreta.h"
#include "Nave.h"
#include "Helice.h"

Ogre::Light* light02;
float r=1.0;
Torreta* torre[8];
Nave* nave;
Helice* heli[2];
float movi = -23500;


class MyFrameListener :public Ogre::FrameListener{

private:
	OIS::InputManager* _man;
	OIS::Keyboard* _key;
	OIS::Mouse* _mouse;
	Ogre::Camera* _cam;

public:

	MyFrameListener(RenderWindow* win, Ogre::Camera* Cam ){

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

	~MyFrameListener(){
		_man->destroyInputObject(_key);
		_man->destroyInputObject(_mouse);
		OIS::InputManager::destroyInputSystem(_man);
	}

	bool frameStarted(const Ogre::FrameEvent &evt){		
		_key->capture();
		_mouse->capture();

		float movSpeed = 1000.0f;

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
			t += Ogre::Vector3(0,0,-1);

		if (_key->isKeyDown(OIS::KC_G))
			t += Ogre::Vector3(0,0,1);

		if (_key->isKeyDown(OIS::KC_F))
			t += Ogre::Vector3(-1,0,0);

		if (_key->isKeyDown(OIS::KC_H))
			t += Ogre::Vector3(1,0,0);

		if (_key->isKeyDown(OIS::KC_1))
			r += 0.05;

		if (_key->isKeyDown(OIS::KC_2))
			r -= 0.05;

		float rotX = _mouse->getMouseState().X.rel * evt.timeSinceLastFrame* -1;
		float rotY = _mouse->getMouseState().Y.rel * evt.timeSinceLastFrame * -1;
		_cam->yaw(Ogre::Radian(rotX));
		_cam->pitch(Ogre::Radian(rotY));
		_cam->moveRelative(t*evt.timeSinceLastFrame*movSpeed);

		heli[0]->nodoHelice->rotate(Ogre::Vector3(0.0,1.0,0.0),Ogre::Radian(Ogre::Degree(-1.0)));
		heli[1]->nodoHelice->rotate(Ogre::Vector3(0.0,1.0,0.0),Ogre::Radian(Ogre::Degree(-1.0)));

		return true;
	}


};

class Example1 : public ExampleApplication
{

public:
	FrameListener* FrameListener01;

	Example1(){
		FrameListener01 = NULL;
	}

	~Example1(){
		if(FrameListener01){
			delete FrameListener01;
		}
	}

	void createFrameListener(){
		FrameListener01 = new MyFrameListener(mWindow, mCamera);
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

		mSceneMgr->setAmbientLight(Ogre::ColourValue(1.0, 1.0, 1.0));
		mSceneMgr->setShadowTechnique(Ogre::SHADOWTYPE_STENCIL_ADDITIVE);	

		/*
		Ogre::Entity* ent01 = mSceneMgr->createEntity("MyEntity1","ejes01.mesh");
		Ogre::SceneNode* node01 = mSceneMgr->createSceneNode("Node01");
		mSceneMgr->getRootSceneNode()->addChild(node01);
		node01->attachObject(ent01);
		*/

		mSceneMgr->setSkyBox(true, "MySkyBox1");

		Ogre::Entity* entEscenario01 = mSceneMgr->createEntity("EscenarioBase01","proyectoOgreI.mesh");
		Ogre::SceneNode* nodeEscenario01 = mSceneMgr->createSceneNode("NodeMesh01");		
		mSceneMgr->getRootSceneNode()->addChild(nodeEscenario01);
		nodeEscenario01->attachObject(entEscenario01);


		nave = new Nave("nave", mSceneMgr,0,-1000);
		mSceneMgr->getRootSceneNode()->addChild(nave->nodoNave);

		heli[0] = new Helice("helice1", mSceneMgr, 15300, -23750);
		mSceneMgr->getRootSceneNode()->addChild(heli[0]->nodoHelice);

		heli[1] = new Helice("helice2", mSceneMgr, -13300, -23750);
		mSceneMgr->getRootSceneNode()->addChild(heli[1]->nodoHelice);

		//Naves
		torre[0] = new Torreta("torre0",mSceneMgr, -1700, -8600);
		torre[1] = new Torreta("torre1",mSceneMgr, 1700, -15300);
		torre[2] = new Torreta("torre2",mSceneMgr, 15500, -18900);
		torre[3] = new Torreta("torre3",mSceneMgr, 24000, -23500);
		torre[4] = new Torreta("torre4",mSceneMgr, 8300, -23500);
		torre[5] = new Torreta("torre5",mSceneMgr, -9980, -23500);
		torre[6] = new Torreta("torre6",mSceneMgr, -23110, -23500);
		torre[7] = new Torreta("torre7",mSceneMgr, -17050, -18900);


		mSceneMgr->getRootSceneNode()->addChild(torre[0]->nodoTorreta);
		mSceneMgr->getRootSceneNode()->addChild(torre[1]->nodoTorreta);
		mSceneMgr->getRootSceneNode()->addChild(torre[2]->nodoTorreta);
		mSceneMgr->getRootSceneNode()->addChild(torre[3]->nodoTorreta);
		mSceneMgr->getRootSceneNode()->addChild(torre[4]->nodoTorreta);
		mSceneMgr->getRootSceneNode()->addChild(torre[5]->nodoTorreta);
		mSceneMgr->getRootSceneNode()->addChild(torre[6]->nodoTorreta);
		mSceneMgr->getRootSceneNode()->addChild(torre[7]->nodoTorreta);
		//Fin naves
	}

};


int main (void)
{

	Example1 app;
	app.go();
	return 0;
}