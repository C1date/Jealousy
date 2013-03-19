
// Include OpenGL ES Engine utils
#include <es_util.h>
#include <iostream>
#include <SpriteBatch.h>
#include <SpriteSheet.h>
#include <SpriteGameObject.h>
#include <AnimatedSpriteGameObject.h>
#include <SpriteGameObject.h>
#include <Text.h>
#include <Texture.h>
#include <Input.h>
#include <Tile.h>
#include <Layer.h>
#include <Camera.h>
#include <Map.h>
#include <irrKlang.h>
#include "HitCheck.h"

float count = 0.0f;

using namespace yam2d;

namespace
{
	TmxMap* map = 0;

	HitCheck* hit = 0;
	
	SpriteGameObject* cursorObject = 0;
	AnimatedSpriteGameObject* gameObject = 0;
	// SpriteBatchGroup is used to draw Sprites and Texts.f
	//SpriteBatchGroup* batch = 0;

	Ref<SpriteSheet> spriteSheet = 0; 

	Texture* cursor = 0;

	// Texture (loaded bitmap)
	Texture* openGLTexture = 0;
	// Sprite (specifies rendering paremeters for region of texture to be rendered to screen)
	//Sprite* sprite = 0;

	// Font is series of clipping regions (SpriteSheet), which specifies font and character set.
	SpriteSheet* font = 0;
	// Texture to be used when rendering text
	Texture* fontTexture = 0;
	// Text object contain text to be rendered to the screen using given font.
	//Text* text = 0;
	Layer* layer = 0;
	Layer* topLayer = 0;



	float playerY = 16.5;
	float playerDestination = 2;
	float playerVelocity = 0;
	float playerSpeed = 15.0f;
	float difference = 0;
	int direction = 0;
	bool movingRight;
	bool movingLeft;

	bool mouseLeftReleased;

	

}

// Initialize the game
bool init ( ESContext *esContext )
{
	// Create new TmxMap object
	map = new TmxMap();

	// Load map file
	bool okay = map->loadMapFile("level.tmx");

	hit = new HitCheck(map);

	cursor = new Texture("cursor.png");
	cursorObject = new SpriteGameObject(0,cursor);

	if( okay )
	{
		// Move camera to middle of map.
		map->getCamera()->setPosition( vec2(5, map->getHeight()/2.0f-0.5f));
	}

	

	  // start the sound engine with default parameters
	irrklang::ISoundEngine* engine = irrklang::createIrrKlangDevice();  
	  
  engine->play2D("DarkestChild.wav", true);




	//texture2->setTransparentColor(255,0,255);

	//spriteSheet = SpriteSheet::generateSpriteSheet(texture2,32,68,0,0);

	//gameObject = new AnimatedSpriteGameObject(0,spriteSheet);
	//gameObject->setSize(32,68);
	//gameObject->setName("Envy2");

	

	Texture* texture = new Texture("MainSpriteSheet.png");

	texture->setTransparentColor(255,0,255);

	spriteSheet = SpriteSheet::generateSpriteSheet(texture,32,68,0,0);

	gameObject = new AnimatedSpriteGameObject(0,spriteSheet);
	gameObject->setSize(32,68);
	gameObject->setName("Envy");

	
	//for( int i=0; i<1; ++i )
	//{
		std::vector<int> indices;
		indices.resize(3);
		
		for( size_t j=0; j<indices.size(); ++j )
		{
			indices[j] = 0 + j;
		}
		gameObject->addAnimation(0, SpriteAnimation::SpriteAnimationClip(indices,2, 2.0f, true));

		for( size_t j=0; j<indices.size(); ++j )
		{
			indices[j] = 3 + j;
		}
		gameObject->addAnimation(2, SpriteAnimation::SpriteAnimationClip(indices,2, 2.0f, true));
		
		indices.resize(1);
		
		for( size_t j=0; j<indices.size(); ++j )
		{
			indices[j] = 6 + j;
		}
		gameObject->addAnimation(1, SpriteAnimation::SpriteAnimationClip(indices,2, 2.0f, true));
		
		for( size_t j=0; j<indices.size(); ++j )
		{
			indices[j] = 7 + j;
		}
		gameObject->addAnimation(3, SpriteAnimation::SpriteAnimationClip(indices,2, 2.0f, true));
	//}
	
	gameObject->setActiveAnimation(0);

	//gameObject->setSize(texture->getWidth(),texture->getHeight());

	// Create new sprite batch group. This must be deleted at deinit.
	//batch = new SpriteBatchGroup();
	
	// Load OpenGL logo to be used as texture for sprite.
	//openGLTexture = new Texture("RunSpriteSheet.png");

	// Create new sprite, with default parameters.
	//sprite = new Sprite();
	
	// Load font texture. Made with font creation tool like bitmap font builder.
	fontTexture = new Texture("Fixedsys_24_Bold.png");

	// Create font clip areas (sprite sheet), from dat file and texture. Dat-file is made with bitmap font builder.
	SpriteSheet* font = SpriteSheet::autoFindFontFromTexture(fontTexture,"Fixedsys_24_Bold.dat");


	//// Create new text-object
	//text = new Text(font);
	//// Set text.
	//text->setText("Jealousy");

	layer = new Layer(map, "Player", 1.0f, true, false);
	map->addLayer(Map::MAPLAYER9, layer);
	layer->addGameObject(gameObject);
	topLayer = new Layer(map, "Mouse", 1.0f, true, false);
	map->addLayer(Map::GUILAYER3, topLayer);
	topLayer->addGameObject(cursorObject);

	return okay;
}

// Deinitialize the game
void deinit ( ESContext *esContext )
{
	delete map;
	delete hit;
	/*delete sprite batch group;*/
	//delete sprite;
	//delete text;
	//delete batch;

}


// Update game
void update( ESContext* ctx, float deltaTime )
{
	//x = 54, y = 18; width = 64, height = 96;
	//(mouseXPos > getX()) && (mousxPos < (getX()+width)) && (mouseYPos > getY()) && (mouseYPos > getY()+height);

	float mouseX = float(getMouseAxisX());

	/*vec2 mouseRelativeToGameObject = gameObject->getPosition();
	esLogMessage("M: <%2.2f,%2.2f>", mouseRelativeToGameObject.x, mouseRelativeToGameObject.y);
	float rotation = atan2(mouseRelativeToGameObject.y, mouseRelativeToGameObject.x);
	gameObject->setRotation(rotation);*/
	
	//gameObject->setPosition(gameObject->getPosition().x+playerVelocity,playerY);

		//if(mouseRelativeToGameObject.x < gameObject->getPosition().x)
		//{
		//	gameObject->setActiveAnimation
		//}

	//bool mouseButtonReleased = false;
	//{
	//	//// If previously pressed and now not pressed, key has released
	//	static bool prevMouseButtonPressed = false;	
	//	if( prevMouseButtonPressed && !getMouseButtonState(MOUSE_LEFT) )
	//		mouseButtonReleased = true;
	//	
	//	// Store this frame key info to be used next frame
	//	if( getMouseButtonState(MOUSE_LEFT) )
	//		prevMouseButtonPressed = true;
	//	else
	//		prevMouseButtonPressed = false;
	//}

	//// If key released select next animation id to play
	//if(mouseButtonReleased)
	//{
	//	int nextAnimation = (gameObject->getActiveAnimation() + 1) % gameObject->getNumAnimations();
	//	gameObject->setActiveAnimation(nextAnimation);
	//}







	::SetCursor(::LoadCursor(NULL, NULL));
	/*LoadCursorFromFile()*/
//	HANDLE WINAPI LoadImage(
//  _In_      LPCTSTR thtn,
//  _In_      UINT uType,
//  _In_      int cxDesired,
//  _In_      int cyDesired,
//  _In_      UINT fuLoad
//);


	map->update(deltaTime);

	//batch->clear();

	gameObject->update(deltaTime);

	//float mouseX = float(getMouseAxisX());
	//std::cout << mouseX << std::endl;
	//float mouseY = float(getMouseAxisY());
	//std::cout << mouseY << std::endl;
	//vec2 mouseInMapCoordinates = map->screenToMapCoordinates(mouseX,mouseY);
	//gameObject->setPosition(mouseX, mouseY);
	if (!getMouseButtonState(MouseButtons::MOUSE_LEFT))
		mouseLeftReleased = true;
	else if (mouseLeftReleased)
	{
		mouseLeftReleased = false;
		float mouseX = float(getMouseAxisX());
		std::cout << mouseX << std::endl;
		float mouseY = float(getMouseAxisY());
		std::cout << mouseY << std::endl;
		vec2 mouseInMapCoordinates = map->screenToMapCoordinates(mouseX,mouseY);
		playerDestination = mouseInMapCoordinates.x;
	
		if (hit->GetNameOfObject(map->screenToMapCoordinates(getMouseAxisX(),getMouseAxisY())) == "Ligga")
		{
			std::cout << "siinä on ligga";
		}
	}
	

	
	
	
	difference = playerDestination - gameObject->getPosition().x;

	cursorObject->setPosition(map->screenToMapCoordinates(getMouseAxisX(),getMouseAxisY()));

	if (abs(difference) < playerSpeed * deltaTime)
		playerVelocity = difference;
	else
		playerVelocity = ((difference) / (abs(difference) )* playerSpeed * deltaTime);
	
	//playerVelocity *= playerSpeed * deltaTime;


	if (playerVelocity == 0 && (movingLeft || movingRight))
	{
		gameObject->setActiveAnimation(direction + 1);
		movingLeft = false;
		movingRight = false;
	}
	else if (playerVelocity>0 && !movingRight)
	{
		direction = 0;
		gameObject->setActiveAnimation(direction + 0);
		movingRight = true;
		movingLeft = false;
	}
	else if (playerVelocity<0 && !movingLeft)
	{
		direction = 2;
		gameObject->setActiveAnimation(direction + 0);
		movingLeft = true;
		movingRight = false;
	}



	gameObject->setPosition(gameObject->getPosition().x + playerVelocity,playerY);

	if (gameObject->getPosition().x < gameObject->getSize().x/map->getTileWidth()/2)
	{
		gameObject->setPosition(gameObject->getSize().x/map->getTileWidth()/2,playerY);
	}
	else if (gameObject->getPosition().x > map->getWidth() - gameObject->getSize().x/map->getTileWidth())
	{
		gameObject->setPosition(map->getWidth() - gameObject->getSize().x/map->getTileWidth(),playerY);
	}

	static float i= 0;
	i += deltaTime*50;
	// Update total time counter.
	count += deltaTime;

	map->getCamera()->setPosition(gameObject->getPosition());



	


}           


// Draw game
void draw ( ESContext *esContext )
{

	// Set OpenGL clear color
	glClearColor( 0.1f, 0.1f, 0.1f, 0.0f );

	// Clear the color buffer
	glClear ( GL_COLOR_BUFFER_BIT );
	
	// Set the viewport to be full window area.
	glViewport( 0, 0, esContext->width, esContext->height );
	
	// Set projection to identity
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
		
	// Calculate half screen size
	float left = -0.5f*esContext->width;
	float right = 0.5f*esContext->width;
	float bottom = -0.5f*esContext->height;
	float top = 0.5f*esContext->height;
	
	// Set OpenGL orthogonal projection for screen size <esContext->width,esContext->height>
	glOrthof( float(int(left)), float(int(right)), float(int(bottom)), float(int(top)), -1.0, 1.0f);
	
	// Enable back face culling
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);
	
	// Enable depth test
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);
	
	// Enable alpha blending (transparency)
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);
	
	// Set model view matrix to identity
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();






	map->getCamera()->setScreenSize(esContext->width,esContext->height); 

	// Render map and all of its layers containing GameObjects to screen.
	
	map->render();

	// Add sprite. Rotate it according to total time. We need also scale font a bit (100 times, so the sprite is 100x100 pixels).
	//batch->addSprite(openGLTexture, sprite, vec2(0,0), 0, vec2(48,87) );
	

	// Add text to position 0,0
	/*batch->addText(fontTexture, text, vec2(0,20), 0);*/

	
	// Draw batched objects to screen.
	//batch->render();
	
	gameObject->render(layer);
}



int main ( int argc, char *argv[] )
{
	ESContext esContext;
	esInitContext ( &esContext );
	esCreateWindow( &esContext, "Green-Eyed Jealousy", 1280, 720, ES_WINDOW_DEFAULT );
   
	if ( !init ( &esContext ) )
		return 0;                                                      

	esRegisterDrawFunc( &esContext, draw );
	esRegisterUpdateFunc( &esContext, update );
	esRegisterDeinitFunc( &esContext, deinit);

	esMainLoop ( &esContext );
	return 0;

}

