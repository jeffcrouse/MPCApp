#include "cinder/app/AppNative.h"
#include "cinder/gl/gl.h"
#include "cinder/Timer.h"
#include "cinder/params/Params.h"
#include "cinder/Rand.h"
#include "cinder/MayaCamUI.h"

using namespace ci;
using namespace ci::app;
using namespace std;

class _TBOX_PREFIX_App : public AppNative {
public:
	void prepareSettings( AppBasic::Settings *settings ) override;
	void setup() override;
	void resize() override;
	void update() override;
	void draw() override;
	void mouseMove( MouseEvent event ) override;
	void mouseDown( MouseEvent event ) override;
	void mouseDrag( MouseEvent event ) override;
	void mouseWheel( MouseEvent event ) override;
	void mouseUp( MouseEvent event ) override;
	void keyDown( KeyEvent event ) override;
	void keyUp( KeyEvent event ) override;
	void shutdown() override;
private:
	params::InterfaceGl mParams;
	Timer mTimer;
	float mFrameRate;
	MayaCamUI mMayaCam;
	Vec2f mMousePos;
};

void _TBOX_PREFIX_App::prepareSettings( AppBasic::Settings *settings )
{
	settings->setFrameRate(60);
	settings->setWindowSize(1024, 768);
	//	settings->enableHighDensityDisplay();
	//	settings->setAlwaysOnTop();
	//	settings->setBorderless();
	//	settings->setWindowPos( 0, 0 );
	//	settings->setFullScreen();
}

void _TBOX_PREFIX_App::setup()
{
	Rand::randomize();
	
	getWindow()->setTitle("MPCDigital App");
	mParams = params::InterfaceGl( "Settings", Vec2i( 300, 200 ) );
	mParams.addParam( "Framerate", &mFrameRate, "", true );
	
	
	// enable the depth buffer (for 3D)
	gl::enableDepthRead();
	gl::enableDepthWrite();
	
	gl::enable( GL_POLYGON_SMOOTH );
	glHint( GL_POLYGON_SMOOTH_HINT, GL_NICEST );
	
	gl::enable( GL_LINE_SMOOTH );
	glHint( GL_LINE_SMOOTH_HINT, GL_NICEST );
}

void _TBOX_PREFIX_App::resize()
{
	console() << getWindowBounds();
	CameraPersp cam = mMayaCam.getCamera();
	cam.setAspectRatio( getWindowAspectRatio() );
	mMayaCam.setCurrentCam( cam );
	gl::enableDepthRead();
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
	
	// set up the camera
	gl::pushMatrices();
	gl::setMatrices( mMayaCam.getCamera() );
	
	Vec3f size = 5.0f * Vec3f::one();
	gl::drawColorCube( 0.5f * size, size );
	gl::drawCoordinateFrame( 6.0f );
	
	gl::popMatrices();
	
	// Draw the interface
	mParams.draw();
}

void _TBOX_PREFIX_App::mouseDown( MouseEvent event )
{
	mMousePos = event.getPos();
	mMayaCam.mouseDown( mMousePos );
}

void _TBOX_PREFIX_App::mouseMove( MouseEvent event )
{
	mMousePos = event.getPos();
}

void _TBOX_PREFIX_App::mouseDrag( MouseEvent event )
{
	mMousePos = event.getPos();
	
	// Added/hacked support for international mac laptop keyboards.
	bool middle = event.isMiddleDown() || ( event.isMetaDown() && event.isLeftDown() );
	bool right = event.isRightDown() || ( event.isControlDown() && event.isLeftDown() );
	mMayaCam.mouseDrag( event.getPos(), event.isLeftDown() && !middle && !right, middle, right );}

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
