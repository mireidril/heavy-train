#ifdef _WIN32
#include "Box2D/Box2D.h"
#else
#include <Box2D/Box2D.h>
#endif

#include "GameEngine.hpp"

void testLibrairies()
{
	std::cout<<"Hello OWLaround :)"<<std::endl;
	//-----------------SDL-------------------------------------------------

	if(SDL_Init(SDL_INIT_VIDEO) != 0) 
	{
		std::cerr << "Can't initialize SDL : " << SDL_GetError() << std::endl;
	}

	SDL_WM_SetCaption("Heavy Train", NULL);

	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);

	SDL_Surface * screen = SDL_SetVideoMode(800, 600, 32, SDL_ANYFORMAT);
	if(screen == NULL)
	{
		std::cout<<"Error at initialization screen"<<std::endl;
	}

	SDL_Surface * image = IMG_Load("../img/test.bmp");
	if(image == NULL)
	{
		std::cout<<"Error loading image"<<std::endl;
	}

	SDL_Surface * image2 = SDL_LoadBMP("../img/sol.bmp");
	if(image2 == NULL)
	{
		std::cout<<"Error loading image 2"<<std::endl;
	}
	std::cout << "How are you ?" << std::endl;
	// Indicates that the transparent color is fuschia but we don't need it now, with PNG
	//int colorkey = SDL_MapRGB(image->format, 255, 0, 255);
	//SDL_SetColorKey(image, SDL_SRCCOLORKEY, colorkey);

		
	//tinyXML
	TiXmlDocument doc( "../levels/test.xml" );
	bool loadOkay = doc.LoadFile();
	if ( !loadOkay )
	{
		printf( "Could not load test file 'demotest.xml'. Error='%s'. Exiting.\n", doc.ErrorDesc() );
	}

	doc.Print();

	//box2D
	b2Vec2 gravity(4.0f, -10.0f);

	// Construct a world object, which will hold and simulate the rigid bodies.
	b2World world(gravity);

	// Define the ground body.
	b2BodyDef groundBodyDef;
	groundBodyDef.position.Set(0.0f, -30.0f);
	SDL_Rect * posSol = new SDL_Rect;
	posSol->x = 0.0;
	posSol->y = 30 + 249/2 + 20;

	// Call the body factory which allocates memory for the ground body
	// from a pool and creates the ground box shape (also from a pool).
	// The body is also added to the world.
	b2Body* groundBody = world.CreateBody(&groundBodyDef);

	// Define the ground box shape.
	b2PolygonShape groundBox;

	// The extents are the half-widths of the box.
	groundBox.SetAsBox(800.0f, 10.0f);

	// Add the ground fixture to the ground body.
	groundBody->CreateFixture(&groundBox, 0.0f);

	// Define the dynamic body. We set its position and call the body factory.
	b2BodyDef bodyDef;
	bodyDef.type = b2_dynamicBody;
	bodyDef.position.Set(400.0f, 4.0f);
	SDL_Rect * posSprite = new SDL_Rect;
	posSprite->x = 400.f;
	b2Body* body = world.CreateBody(&bodyDef);

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

	//fixtureDef.restitution = 0.8f;

	// Add the shape to the body.
	body->CreateFixture(&fixtureDef);

	// Prepare for simulation. Typically we use a time step of 1/60 of a
	// second (60Hz) and 10 iterations. This provides a high quality simulation
	// in most game scenarios.
	float32 timeStep = 1.0f / 60.0f;
	int32 velocityIterations = 6;
	int32 positionIterations = 2;

	//SDL_ttf
	TTF_Init();
	TTF_Font * police = TTF_OpenFont("../fonts/mvboli.ttf", 50);
	SDL_Color couleurNoire = {255,255,0};
	SDL_Surface * texte = TTF_RenderText_Blended(police, "Salut les Zér0s !", couleurNoire);

	//SDL_gfx
	image = rotozoomSurface(image, 90, 1.0, 1);

	//SDL_mixer
	if( Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, MIX_DEFAULT_CHANNELS, 1024) == -1)
		std::cout<<"problem init son"<<std::endl; //Initialisation de l'API Mixer
	Mix_Music * musique = Mix_LoadMUS("../musics/fanfare.ogg");
	Mix_VolumeMusic(MIX_MAX_VOLUME/2);
	if(musique == NULL){
		std::cout<<"musique non jouée"<<std::endl;
	}
	else
	{
		Mix_PlayMusic(musique, -1);
	}

	// This is our little game loop.
	bool play = true;
	SDL_Event event;
	while (play) {
		if (SDL_PollEvent(&event)){
			switch (event.type){
			  	case SDL_KEYDOWN:
			       	switch (event.key.keysym.sym){
						case SDLK_ESCAPE:
							play=false;
							break;
						default:
							break;
					}
				default: break;
			}
		}
		// Instruct the world to perform a single step of simulation.
		// It is generally best to keep the time step and iterations fixed.
		world.Step(timeStep, velocityIterations, positionIterations);

		// Now print the position and angle of the body.
		b2Vec2 position = body->GetPosition();
		float32 angle = body->GetAngle();

		//printf("%4.2f %4.2f %4.2f\n", position.x, position.y, angle);

		/* Copy image to the screen */
		//posSprite->x = position.x +10;
		posSprite->y = -position.y +10;
		posSol->x = -position.x+10;
		SDL_FillRect( SDL_GetVideoSurface(), NULL, 0 );
		SDL_BlitSurface(image, NULL, screen, posSprite);
		SDL_BlitSurface(image2, NULL, screen, posSol);

		SDL_Rect * position1 = new SDL_Rect;
		position1->x = 50;
		position1->y = 50;
		SDL_BlitSurface(texte, NULL, screen, position1); /* Blit du texte par-dessus */
			
		// Update screen
		SDL_UpdateRect(screen, 0, 0, 0, 0);
	}
	TTF_CloseFont(police);
	TTF_Quit();
	Mix_FreeMusic(musique);
	Mix_CloseAudio();
	SDL_FreeSurface(image);
	SDL_Quit();
}

int main(int argc, char** argv)
{
	//To launch the game
	GameEngine gameEngine;
	gameEngine.run();
	
	//To test librairies
	//testLibrairies();

	return 0;
}
