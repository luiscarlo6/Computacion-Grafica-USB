		// Creacion de los nodos
		Ogre::SceneNode* node02 = mSceneMgr->getRootSceneNode()->createChildSceneNode("Node02");
		Ogre::SceneNode* node03 = mSceneMgr->createSceneNode("Node03");
		Ogre::SceneNode* node04 = mSceneMgr->createSceneNode("Node04");

//		Ogre::SceneNode* node = mSceneMgr->getRootSceneNode()->createChildSceneNode("Node1");

		// Creacion de las entedidades
		Ogre::Entity* ent02 = mSceneMgr->createEntity("prueba","usb_cilindro02.mesh");
		Ogre::Entity* ent03 = mSceneMgr->createEntity("prueba1","sphere.mesh");
		Ogre::Entity* ent04 = mSceneMgr->createEntity("prueba2","usb_cilindro.mesh");

		// attach
		ent02->setMaterialName("Torreta_text");
		node02->attachObject(ent02);
//		node02->addChild(node03);
//		node02->addChild(node04);

		node02->setPosition(50.0,0.0,0.0);
		node02->setScale(1.5,1.5,1.5);

		mSceneMgr->getRootSceneNode()->addChild(node03);
		node03->attachObject(ent03);
		node03->setPosition(50.0,10.0,0.0);
//		node03->translate(0.0,10.0,0.0,Ogre::Node::TS_PARENT);
		node03->setScale(0.05,0.05,0.05);

		mSceneMgr->getRootSceneNode()->addChild(node04);
		node04->attachObject(ent04);
		node04->roll(Ogre::Degree(90.0f));
		node04->setPosition(56.0,10.0,0.0);
//		node04->translate(6.0,10.0,0.0,Ogre::Node::TS_PARENT);
		node04->setScale(0.3,0.3,0.3);
