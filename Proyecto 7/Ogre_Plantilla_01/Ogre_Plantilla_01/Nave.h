#pragma  once
#include "stdafx.h"


class Nave{

	public:
		Ogre::Camera* camera;
		Ogre::SceneManager* mSceneMgr;
		Ogre::SceneNode* nodoNave;
		Ogre::SceneNode* nodoEntNave;
		Ogre::SceneNode* nodoCamara;
		Ogre::AnimationState* animStateDer;
		Ogre::AnimationState* animStateIzq;
		float x;
		float y;
		float z;
		int lastMove;
		Ogre::Real speed;

		Nave::Nave(Ogre::String nombre, Ogre::SceneManager* sm, Ogre::Real x, Ogre::Real y);
		Ogre::ManualObject* Nave::crearAla(Ogre::String nombre, Ogre::SceneManager* sm);

		Nave::Nave(Ogre::SceneManager* sm, Ogre::Camera* cam);

		void Nave::moverDerecha();

		void Nave::moverAtras();

		void Nave::reset();

		Ogre::Quaternion Nave::girarDerecha();

		void Nave::moverIzquierda();

		Ogre::Quaternion Nave::girarIzquierda();

		void Nave::moverAdelante();

		void Nave::moverArriba();

		void Nave::moverAbajo();

		void Nave::rotarDerecha();

};
