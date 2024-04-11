#include "model.h"
#include <vector>
#include "validityFunctions.h"
#include "Box2D/Box2D.h"
#include "physobject.h"
#include <iostream>

Model::Model(QObject *parent) : QObject{parent} {
    connect(this,
            &Model::newPhysObj,
            this,
            &Model::spawnPhysBox);

    for(int i = 0; i < NUM_OF_SECTIONS; i++) sections->push_back(buildSection(i)); //create each section

    codeStrings = new std::string[NUM_OF_SECTIONS];
    for(int i = 0; i < NUM_OF_SECTIONS; i++) codeStrings[i] = "";

    // Box2D
    setupWorld();
}

Model::~Model(){
    delete sections;
    delete[] codeStrings;
}

void Model::changeSection(int index){
    nextSection = index;
    emit requestSaveCurrentCode();
    std::cout << "save requested" << std::endl;
}

void Model::finalizeSectionChange(){
    currSection = nextSection;
    nextSection = 0;
    QString str = codeStrings[currSection].c_str();
    std::cout << str.toStdString() << std::endl;
    emit codeUpdated(str);
}

void Model::saveCodeToCurrentIndex(std::string code){
    codeStrings[currSection] = code;
    finalizeSectionChange();
}


void Model::setupWorld() {
    // TODO [Box2D]:

    // Define the gravity vector.
    //gravity = b2Vec2(0.0f, -10.0f);

    // Construct a world object, which will hold and simulate the rigid bodies.
    //world = b2World(gravity);


    // TODO [Box2D]: set walls around the window, preferably scaled to the window size
    // Define the ground body.
    b2BodyDef groundBodyDef;
    groundBodyDef.position.Set(0.0f, 700.0f);

    // Call the body factory which allocates memory for the ground body
    // from a pool and creates the ground box shape (also from a pool).
    // The body is also added to the world.
    b2Body* groundBody = world.CreateBody(&groundBodyDef);

    // Define the ground box shape.
    b2PolygonShape groundBox;

    // The extents are the half-widths of the box.
    groundBox.SetAsBox(1000.0f, 50.0f);

    // Add the ground fixture to the ground body.
    groundBody->CreateFixture(&groundBox, 0.0f);

    //Spawn objects
    for(int num = 0; num < 20; num++) {
        int x = 560-(num*5);
        int y = 105-(num*5);
        timer.singleShot(1000, this, [this, x, y] {emit newPhysObj(x, y);});
    }

    // Start update loop
    timer.singleShot(1500, this, &Model::updateWorld);
}

void Model::updateWorld() {
    // TODO [Box2D]:

    //qDebug("--start update");
    // Prepare for simulation. Typically we use a time step of 1/60 of a
    // second (60Hz) and 10 iterations. This provides a high quality simulation
    // in most game scenarios.
    float32 timeStep = 1.0f / 60.0f;
    int32 velocityIterations = 6;
    int32 positionIterations = 2;

    // This is our little game loop.
    for (int32 i = 0; i < 60; ++i)
    {
        // Instruct the world to perform a single step of simulation.
        // It is generally best to keep the time step and iterations fixed.
        world.Step(timeStep, velocityIterations, positionIterations);
    }


    // TODO [Box2D]: This will need to be generalized to work with many different objects

    // Check for objects to spawn
    for(auto const& [id, physObjBody] : physObjBodies) {
        //if()

        // Now print the position and angle of the body.
        b2Vec2 position = physObjBody->getPosition();
        float32 angle = physObjBody->getAngle();

        emit newPosition(position.x, position.y);
    }

    //qDebug() << position.x << position.y << angle;
    //qDebug("--finished update");
    // When the world destructor is called, all bodies and joints are freed. This can
    // create orphaned pointers, so be careful about your world management.

    timer.singleShot(42, this, &Model::updateWorld);
}

void Model::spawnPhysBox(int x, int y) {
    // Define the dynamic body. We set its position and call the body factory.
    physObject body1(&world, x, y);
    physObjBodies[body1.getID()] = &body1;
}






//logic for building each section with proper validity function
Section Model::buildSection(int sectionID){
    switch(sectionID){
    case 1:
        return Section();
    case 2:
        return Section(
            Challenge(
                "", //before Code
                "", //after Code
                ValidityFunctions::section2ValidityFunction));
    case 3:
        return Section(
            Challenge(
                "", //before Code
                "", //after Code
                ValidityFunctions::section3ValidityFunction));
    case 4:
        return Section(
            Challenge(
                "", //before Code
                "", //after Code
                ValidityFunctions::section4ValidityFunction));
    case 5:
        return Section(
            Challenge(
                "", //before Code
                "", //after Code
                ValidityFunctions::section5ValidityFunction));
    case 6:
        return Section(
            Challenge(
                "", //before Code
                "", //after Code
                ValidityFunctions::section6ValidityFunction));
    case 7:
        return Section(
            Challenge(
                "", //before Code
                "", //after Code
                ValidityFunctions::section7ValidityFunction));
    case 8:
        return Section(
            Challenge(
                "", //before Code
                "", //after Code
                ValidityFunctions::section8ValidityFunction));
    case 9:
        return Section(
            Challenge(
                "", //before Code
                "", //after Code
                ValidityFunctions::section9ValidityFunction));
    case 10:
        return Section(
            Challenge(
                "", //before Code
                "", //after Code
                ValidityFunctions::section10ValidityFunction));
    case 11:
        return Section(
            Challenge(
            "", //before Code
            "", //after Code
            ValidityFunctions::section11ValidityFunction));
    case 12:
        return Section();
    default:
        return Section();
    }
}


