#include "DRomanCircle.h"

//------------------------------------
void DRomanCircle::update(float delta)
{

}

//------------------------------------
void DRomanCircle::draw()
{
	CHECK_START();

	ofSetColor(255);
	_tex.bind();
	_mesh.draw();
	_tex.unbind();

	//ofSetColor(0);
	//_mesh.drawWireframe();
}

//------------------------------------
void DRomanCircle::start()
{
	generate();
	_isStart = true;

}

//------------------------------------
void DRomanCircle::stop()
{
	_isStart = false;
}

//------------------------------------
void DRomanCircle::trigger()
{

}

//------------------------------------
void DRomanCircle::generate()
{
	_mesh.clear();

	float r = 100;
	float width = 20;
	float delta = 360.0 / (float)36;

	ofVec2f v(0, -1);

	for (int i = 0; i < 10; i++)
	{
		ofVec2f p1, p2;
		p1 = v * r;
		p2 = p1 + v * width;

		_mesh.addVertex(p1);
		_mesh.addTexCoord(ofVec2f(i, 0));

		_mesh.addVertex(p2);
		_mesh.addTexCoord(ofVec2f(i, 1.0));
		v.rotate(delta);

		
	}


	_mesh.enableTextures();
	_mesh.enableIndices();
	_mesh.setMode(ofPrimitiveMode::OF_PRIMITIVE_TRIANGLE_STRIP);
}