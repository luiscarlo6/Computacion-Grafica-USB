#include "Ogre\ExampleApplication.h"

Ogre::Light* light02;
float r=1.0;

//Animacion por Key Frames
Ogre::AnimationState* AnimacionLuz;


class FrameListenerClase : public Ogre::FrameListener {

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

	FrameListenerClase(Ogre::SceneNode* nodo01, Ogre::SceneNode* nodo02, Ogre::Entity* ent, RenderWindow* win, Ogre::Camera* Cam ){

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

		//animacion
		_ent = ent;
		_aniState = _ent->getAnimationState("RunBase");
		_aniState->setEnabled(true);
		_aniState->setLoop(false);

		_aniStateTop = _ent->getAnimationState("SliceVertical");
		_aniStateTop->setEnabled(true);
		_aniStateTop->setLoop(false);

		_WalkingSpeed = 50.0f;
		_rotation = 0.0f;

		

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


		//Walk Ogre
		bool walked = false;
		Ogre::Vector3 SinbadT(0,0,0);

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

		if (_key->isKeyDown(OIS::KC_UP)){
			SinbadT += Ogre::Vector3(0,0,-1);
			_rotation = 3.14f;
			walked = true;
		}

		if (_key->isKeyDown(OIS::KC_DOWN)){
			SinbadT += Ogre::Vector3(0,0,1);
			_rotation = 0.0f;
			walked = true;
		}

		if (_key->isKeyDown(OIS::KC_LEFT)){
			SinbadT += Ogre::Vector3(-1,0,0);
			_rotation = -1.57f;
			walked = true;
		}

		if (_key->isKeyDown(OIS::KC_RIGHT)){
			SinbadT += Ogre::Vector3(1,0,0);
			_rotation = 1.57f;
			walked = true;
		}
		
		if(walked){
			_aniState->setEnabled(true);
			_aniStateTop->setEnabled(true);
			if(_aniState->hasEnded()){
				_aniState->setTimePosition(0.0f);
			}
			if(_aniStateTop->hasEnded()){
				_aniStateTop->setTimePosition(0.0f);
			}
		}else{
			_aniState->setTimePosition(0.0f);
			_aniState->setEnabled(false);
			_aniStateTop->setTimePosition(0.0f);
			_aniStateTop->setEnabled(false);
		}

		//light02->setDiffuseColour(Ogre::ColourValue(r,1.0f,1.0f));	
		//nodoF01->translate(tOgro * evt.timeSinceLastFrame);

		float rotX = _mouse->getMouseState().X.rel * evt.timeSinceLastFrame* -1;
		float rotY = _mouse->getMouseState().Y.rel * evt.timeSinceLastFrame * -1;
		_cam->yaw(Ogre::Radian(rotX));
		_cam->pitch(Ogre::Radian(rotY));
		_cam->moveRelative(t*evt.timeSinceLastFrame*movSpeed);

		
		nodoF01->translate(SinbadT * evt.timeSinceLastFrame * _WalkingSpeed);
		nodoF01->resetOrientation();
		nodoF01->yaw(Ogre::Radian(_rotation));

		//_aniState->addTime(evt.timeSinceLastFrame*0.25);
		_aniState->addTime(evt.timeSinceLastFrame);
		_aniStateTop->addTime(evt.timeSinceLastFrame);

		// Animacion por key frame
		AnimacionLuz->addTime(evt.timeSinceLastFrame);


		return true;
	}

};



class Example1 : public ExampleApplication
{
public:
	Ogre::SceneNode* nodeSinbad;
	Ogre::SceneNode* nodeEsfera02;
	Ogre::Entity* entSinbad;
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
		FrameListener01 = new FrameListenerClase(nodeSinbad, nodeEsfera02,entSinbad, mWindow, mCamera);
		mRoot->addFrameListener(FrameListener01);
	}

	void createCamera() {

		mCamera = mSceneMgr->createCamera("MyCamera1");
		mCamera->setPosition(50,20,50);
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
		entSinbad = mSceneMgr->createEntity("MyEntitySinbad","sinbad.mesh");
		mSceneMgr->getRootSceneNode()->addChild(nodeSinbad);
		nodeSinbad->attachObject(entSinbad);
		nodeSinbad->setPosition(0.0f,5.0f,0.0f);
		nodeSinbad->setScale(1.0f,1.0f,1.0f);
		
		
		// Set Key animation		
		float duration = 4.0;
		float step = duration/4.0;
		Ogre::Animation* animation = mSceneMgr->createAnimation("LightAnim", duration);
		animation->setInterpolationMode(Animation::IM_SPLINE);
		
		Ogre::NodeAnimationTrack* track = animation->createNodeTrack(0,nodeEsfera02);

		Ogre::TransformKeyFrame* key;

		key = track->createNodeKeyFrame(0.0f);
		key->setTranslate(Vector3(-50.0f,50.0f,50.0f));
		key->setScale(Vector3(0.05f,0.05f,0.05f));

		key = track->createNodeKeyFrame(step);
		key->setTranslate(Vector3(50.0f,50.0f,50.0f));
		key->setScale(Vector3(0.05f,0.05f,0.05f));

		key = track->createNodeKeyFrame(2.0*step);
		key->setTranslate(Vector3(50.0f,50.0f,-50.0f));
		key->setScale(Vector3(0.05f,0.05f,0.05f));

		key = track->createNodeKeyFrame(3.0*step);
		key->setTranslate(Vector3(-50.0f,50.0f,-50.0f));
		key->setScale(Vector3(0.05f,0.05f,0.05f));

		key = track->createNodeKeyFrame(4.0*step);
		key->setTranslate(Vector3(-50.0f,50.0f,50.0f));
		key->setScale(Vector3(0.05f,0.05f,0.05f));

		AnimacionLuz = mSceneMgr->createAnimationState("LightAnim");
		AnimacionLuz->setEnabled(true);
		AnimacionLuz->setLoop(true);

		Ogre::Entity* sword1 = mSceneMgr->createEntity("Sword1","Sword.mesh");
		Ogre::Entity* sword2 = mSceneMgr->createEntity("Sword2","Sword.mesh");

		entSinbad->attachObjectToBone("Handle.L", sword1);
		entSinbad->attachObjectToBone("Handle.R", sword2);

	}

};


int main (void)
{

	Example1 app;
	app.go();
	return 0;
}