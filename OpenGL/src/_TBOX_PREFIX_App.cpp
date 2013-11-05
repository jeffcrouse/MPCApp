#include "cinder/app/AppNative.h"
#include "cinder/gl/gl.h"
#include "cinder/Timer.h"
#include "cinder/params/Params.h"
#include "cinder/Rand.h"

using namespace ci;
using namespace ci::app;
using namespace std;

class _TBOX_PREFIX_App : public AppNative {
  public:
	void prepareSettings( AppBasic::Settings *settings ) override;
	void setup() override;
	void update() override;
	void draw() override;
	void resize() override;
	void mouseMove( MouseEvent event ) override;
	void mouseDown( MouseEvent event ) override;
	void mouseDrag( MouseEvent event ) override;
	void mouseWheel( MouseEvent event ) override;
	void mouseUp( MouseEvent event ) override;
	void keyDown( KeyEvent event ) override;
	void keyUp( KeyEvent event ) override;
	void shutdown() override;

	params::InterfaceGl mParams;
	Timer mTimer;
	float mFrameRate;
};

void _TBOX_PREFIX_App::prepareSettings( AppBasic::Settings *settings )
{
	settings->setFrameRate(60);
	settings->setWindowSize(1024, 768);
	//settings->setAlwaysOnTop();
	//settings->setBorderless();
	//settings->setWindowPos( 0, 0 );
	//settings->setFullScreen();
}


void _TBOX_PREFIX_App::setup()
{
	Rand::randomize();

	getWindow()->setTitle("MPCDigital App");
	mParams = params::InterfaceGl( "Settings", Vec2i( 300, 200 ) );
	mParams.addParam( "Framerate", &mFrameRate, "", true );


	gl::enable( GL_POLYGON_SMOOTH );
	glHint( GL_POLYGON_SMOOTH_HINT, GL_NICEST );
	
	gl::enable( GL_LINE_SMOOTH );
	glHint( GL_LINE_SMOOTH_HINT, GL_NICEST );
}

void _TBOX_PREFIX_App::update()
{
	float deltaTime = mTimer.getSeconds();
	mTimer.start();

	mFrameRate = getAverageFps();
}

void _TBOX_PREFIX_App::draw()
{
	// clear out the window with black
	gl::clear( Color( 0, 0, 0 ) ); 

	// Draw the interface
	mParams.draw();
}

void _TBOX_PREFIX_App::resize()
{
	console() << getWindowBounds();
}

void _TBOX_PREFIX_App::mouseDown( MouseEvent event )
{
}

void _TBOX_PREFIX_App::mouseMove( MouseEvent event )
{
}

void _TBOX_PREFIX_App::mouseDrag( MouseEvent event )
{
}

void _TBOX_PREFIX_App::mouseUp( MouseEvent event )
{
}

void _TBOX_PREFIX_App::mouseWheel( MouseEvent event )
{
}

void _TBOX_PREFIX_App::keyDown( KeyEvent event )
{
}

void _TBOX_PREFIX_App::keyUp( KeyEvent event ) 
{
	if( event.getChar() == 'f' ) {
		app::setFullScreen( !app::isFullScreen() );
	} else if(event.getChar()==KeyEvent::KEY_SPACE) {
		mParams.maximize( !mParams.isMaximized() );
	}
}

void _TBOX_PREFIX_App::shutdown()
{
}

CINDER_APP_NATIVE( _TBOX_PREFIX_App, RendererGl )
