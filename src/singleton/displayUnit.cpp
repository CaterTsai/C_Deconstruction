#include "displayUnit.h"

#pragma region Basic
//------------------------------
displayUnit::displayUnit()
	:_isSetup(false)
	, _startDraw(false)
{
}

//------------------------------
void displayUnit::setup(int width, int height , const stDisplayParam & param)
{
	_canvas.allocate(width, height, GL_RGBA);
	_canvas.getTextureReference().setTextureWrap(GL_REPEAT, GL_REPEAT);

	for (int i = 0; i < cCtrlPointNum; i++)
	{
		_ctrlPos[i].set(param.ctrlPos[i]);
	}

	setupPlane(width, height);

	_isSetup = true;
}

//------------------------------
void displayUnit::drawBegin(bool needClear)
{
	_startDraw = true;
	_canvas.begin();
	if (needClear)
	{
		ofClear(0);
	}	
}

//------------------------------
void displayUnit::drawEnd()
{
	_canvas.end();
	_startDraw = false;
}

//------------------------------
void displayUnit::drawCanvas(int x, int y, int w, int h)
{
	if (!_isSetup || _startDraw)
	{
		return;
	}

	ofSetColor(255);
	_canvas.draw(x, y, w, h);
}

//------------------------------
ofRectangle displayUnit::getSize()
{
	return ofRectangle(0, 0, _canvas.getWidth(), _canvas.getHeight());
}

//------------------------------
ofVec2f displayUnit::getCtrlPos(int id)
{
	return _ctrlPos[id];
}


#pragma endregion


#pragma region Projection
//------------------------------
void displayUnit::drawOnProjection()
{
	ofPushStyle();
	ofSetColor(255);
	{
		_canvas.getTextureReference().bind();
		{
			_plane.draw();
		}
		_canvas.getTextureReference().unbind();
	}
	ofPopStyle();
}

//------------------------------
void displayUnit::mousePress(int x, int y)
{
	ofVec2f mousePos(x, y);
	float minDist = cCtrlPointMaxDist;
	int index = -1;
	for (int i = 0; i < cCtrlPointNum; i++)
	{
		float dist = _ctrlPos[i].distance(mousePos);
		if (dist < minDist)
		{
			minDist = dist;
			index = i;
		}
	}

	if (index != -1)
	{
		_selectCtrlIndex = index;
	}
}

//------------------------------
void displayUnit::mouseDrag(int x, int y)
{
	if (_selectCtrlIndex >= 0 && _selectCtrlIndex < cCtrlPointNum)
	{
		_ctrlPos[_selectCtrlIndex].set(x, y);
	}
}

//------------------------------
void displayUnit::mouseRelease(int x, int y)
{
	if (_selectCtrlIndex >= 0 && _selectCtrlIndex < cCtrlPointNum)
	{
		_plane.setVertex(_selectCtrlIndex, _ctrlPos[_selectCtrlIndex]);
	}
}


//------------------------------
void displayUnit::drawCtrlPos()
{
	ofPushStyle();
	{
		ofNoFill();
		ofSetLineWidth(3);
		ofSetColor(255, 0, 0);
		for (auto& pos : _ctrlPos)
		{
			ofCircle(pos, cCtrlPointCircleRadius);
		}
	}
	ofPopStyle();
}

//------------------------------
void displayUnit::setupPlane(int width, int height)
{
	_plane.setMode(ofPrimitiveMode::OF_PRIMITIVE_TRIANGLE_STRIP);
	_plane.enableTextures();

	for (int i = 0; i < cCtrlPointNum; i++)
	{
		_plane.addVertex(_ctrlPos[i]);
	}

	_plane.addTriangle(0, 1, 3);
	_plane.addTriangle(1, 2, 3);
	_plane.addTexCoord(ofVec2f(0.0, 0.0));
	_plane.addTexCoord(ofVec2f(width, 0.0));
	_plane.addTexCoord(ofVec2f(width, height));
	_plane.addTexCoord(ofVec2f(0.0, height));

	
}
#pragma endregion


