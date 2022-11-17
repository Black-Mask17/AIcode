#include "Scene1.h"
#include "VMath.h"
#include "KinematicWander.h"
#include "KinematicArrive.h"


Scene1::Scene1(SDL_Window* sdlWindow_, GameManager* game_){
	window = sdlWindow_;
    game = game_;
	renderer = SDL_GetRenderer(window);
	xAxis = 25.0f;
	yAxis = 15.0f;

	// create a NPC
	blinky = nullptr;
	myNPC = NULL;
	clyde = nullptr;
}

Scene1::~Scene1(){
	if (blinky) 
	{
		blinky->OnDestroy();
		delete blinky;
	}

	if (clyde)
	{
		clyde->OnDestroy();
		delete clyde;
	}
}

bool Scene1::OnCreate() {
	int w, h;
	SDL_GetWindowSize(window,&w,&h);
	
	Matrix4 ndc = MMath::viewportNDC(w, h);
	Matrix4 ortho = MMath::orthographic(0.0f, xAxis, 0.0f, yAxis, 0.0f, 1.0f);
	projectionMatrix = ndc * ortho;
	
	/// Turn on the SDL imaging subsystem
	IMG_Init(IMG_INIT_PNG);

	// Set player image to PacMan

	SDL_Surface* image;
	SDL_Texture* texture;

	image = IMG_Load("pacman.png");
	texture = SDL_CreateTextureFromSurface(renderer, image);
	game->getPlayer()->setImage(image);
	game->getPlayer()->setTexture(texture);

	// Set up characters, choose good values for the constructor
	// or use the defaults, like this
	blinky = new Character();
	
	if (!blinky->OnCreate(this))
	{
		return false;
	}
	blinky->setPos(Vec3(0.0, 1.0, 0.0));
	clyde = new Character();
	
	if (!clyde->OnCreate(this))
	{
		return false;
	}
	clyde->setPos(Vec3(15.0, 10.0, 0.0));

	Vec3 position = Vec3();
	float orienation = 0.0f;
	float maxSpeed = 3.5f;
	float maxRotation = 1.0f;
	myNPC = new StaticBody{
		position,
		orienation,
		maxSpeed,
		maxRotation
	};


	image = IMG_Load("Blinky.png");
	texture = SDL_CreateTextureFromSurface(renderer, image);
	if (image == nullptr) {
		std::cerr << "Can't open the image" << std::endl;
		return false;
	}
	else {
		blinky->setTexture(texture);
		SDL_FreeSurface(image);
	}

	

	image = IMG_Load("Clyde.png");
	texture = SDL_CreateTextureFromSurface(renderer, image);
	if (image == nullptr) {
		std::cerr << "Can't open the image" << std::endl;
		return false;
	}
	else {
		clyde->setTexture(texture);
		SDL_FreeSurface(image);
	}
	// end of character set ups

	return true;
}

void Scene1::OnDestroy() {}

void Scene1::Update(const float deltaTime) {
	// Calculate and apply any steering for npc's
	blinky->Update(deltaTime);
	clyde->Update(deltaTime);

	Body* player = game->getPlayer();
	KinematicWander* steering_algorithm;
	steering_algorithm = new KinematicWander(myNPC);
	KinematicSteeringOutput* steering;
	steering = steering_algorithm->getSteering();
	myNPC->Update(deltaTime, steering);


	// Update player
	game->getPlayer()->Update(deltaTime);
}

void Scene1::Render() {
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
	SDL_RenderClear(renderer);

	// render any npc's
	blinky->render(0.15f);
	clyde->render(0.15f);

	SDL_Rect square;
	Vec3 screenCoords;
	int w, h;
	float scale = 0.15f;

	SDL_QueryTexture(myNPC->getTexture(), nullptr, nullptr, &w, &h);
	w = static_cast<int>(w * scale);
	h = static_cast<int>(h * scale);
	screenCoords = projectionMatrix * myNPC->getPos();
	square.x = static_cast<int>(screenCoords.x - 0.5f * w);
	square.y = static_cast<int>(screenCoords.y - 0.5f * h);
	square.w = w;
	square.h = h;

	float orientation = myNPC->getOrientation() * 180.0f / M_PI; 
	SDL_RenderCopyEx(renderer, myNPC->getTexture(), nullptr, &square, orientation, nullptr, SDL_FLIP_NONE);
	// render the player
	game->RenderPlayer(0.10f);

	SDL_RenderPresent(renderer);
}

void Scene1::HandleEvents(const SDL_Event& event)
{
	// send events to npc's as needed

	// send events to player as needed
	game->getPlayer()->HandleEvents(event);
}
