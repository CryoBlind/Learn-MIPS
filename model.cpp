#include "model.h"
#include <vector>
#include "validityFunctions.h"
#include "Box2D/Box2D.h"
#include <iostream>

Model::Model(QObject *parent) : QObject{parent} {
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


    // TODO [Box2D]: Make a class to hold physBox data and handle creating them with a given position

    // Define the dynamic body. We set its position and call the body factory.
    b2BodyDef bodyDef;
    bodyDef.type = b2_dynamicBody;
    int labelPosX = 560;
    int labelPosY = 105;
    bodyDef.position.Set(labelPosX, labelPosY);
    physObjBody = world.CreateBody(&bodyDef);

    // Define another box shape for our dynamic body.
    b2PolygonShape dynamicBox;
    dynamicBox.SetAsBox(1.0f, 1.0f);

    // Define the dynamic body fixture.
    b2FixtureDef fixtureDef;
    fixtureDef.shape = &dynamicBox;

    // Set the box density to be non-zero, so it will be dynamic.
    fixtureDef.density = 1.0f;

    // Override the default friction.
    fixtureDef.friction = 0.3f;

    fixtureDef.restitution = 0.9f;

    // Add the shape to the body.
    physObjBody->CreateFixture(&fixtureDef);

    timer.singleShot(2000, this, &Model::updateWorld);
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

    // Now print the position and angle of the body.
    b2Vec2 position = physObjBody->GetPosition();
    float32 angle = physObjBody->GetAngle();

    emit newPosition(position.x, position.y);

    //qDebug() << position.x << position.y << angle;
    //qDebug("--finished update");
    // When the world destructor is called, all bodies and joints are freed. This can
    // create orphaned pointers, so be careful about your world management.

    timer.singleShot(80, this, &Model::updateWorld);
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


