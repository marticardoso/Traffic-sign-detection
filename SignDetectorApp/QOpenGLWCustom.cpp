#include "QOpenGLWCustom.h"


QOpenGLWCustom::QOpenGLWCustom(QObject *parent)
{
	//frame = imread("E:\\Usuario\\nuovo\\Desktop\\image-slider-2.jpg", CV_LOAD_IMAGE_COLOR);
	//Genera una imatge verda
	frame = Mat(320, 240, CV_8UC3, Scalar(0, 255, 0));
}


QOpenGLWCustom::~QOpenGLWCustom()
{
}
/**
* Funció que pinta l'escena
*/
void QOpenGLWCustom::paintGL()
{
	// Draw the scene:

	// Neteja la pantalla
	glClearColor(0.0f, 1.0f, 0.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	//Dibuixa el frame a la reguió esquerre
	double fxIni = -1, fxFi = 0.5, fyIni = -1, fyFi = 1;
	drawImage(frame, fxIni, fxFi, fyIni, fyFi);

	//Computa l'alçada que ha de tenir un senyal detectat perque hi capiguen totes (per defecte 4)
	double signHeight = 1.0 / 4.0 * 2.0; 
	if (signsDet.size() > 4)
		signHeight = 1.0 / signsDet.size() * 2.0;

	//Per cada senyal: 
	for (int i = 0; i < signsDet.size(); ++i){
		Mat m = signsDet[i].second;

		//Redimensiona a 128x128
		cv::resize(m, m, Size(128, 128));
		
		//Calcula la finestre que hauria de tenir la senyal i, i la dibuixa
		double xIni = 0.5, xFi = 1, yIni = 1 - (i + 0.9)*signHeight, yFi = 1 - (i + 0.1)*signHeight;
		drawImage(m, xIni, xFi, yIni, yFi);

		//Dibuixa una linea desde el senyal de la imatge fins el detectat.
		glBegin(GL_LINES);
			glVertex2f(xIni, yIni + (yFi-yIni)/2);
			double posX = signsDet[i].first.x + signsDet[i].first.width;
			double posY = signsDet[i].first.y + signsDet[i].first.height/2.0;
			double x = (fxFi - fxIni)*posX / double(frame.cols) + fxIni;
			double y = fyFi - (fyFi - fyIni)*posY / double(frame.rows);
			glVertex2f(x, y);
		glEnd();
	}
}
/**
* Pinta una imatge a unes coordenades
*/
void QOpenGLWCustom::drawImage(Mat& im, double& vRecMinX, double& vRecMaxX, double& vRecMinY, double& vRecMaxY){
	glEnable(GL_TEXTURE_2D);
	//Genera textura
	GLuint texFrameId2 = matToTexture(im, GL_NEAREST, GL_NEAREST, GL_CLAMP);

	//Conserva el ratio de la imatge
	double mRatio = double(im.cols) / im.rows;;
	conserveRatio(mRatio, vRecMinX, vRecMaxX, vRecMinY, vRecMaxY);

	//Dibuixa un quad amb la textura
	//glBindTexture(GL_TEXTURE_2D, texFrameId2);
	glBegin(GL_QUADS);
		glTexCoord2f(0, 1);		glVertex2f(vRecMinX, vRecMinY);
		glTexCoord2f(1, 1);		glVertex2f(vRecMaxX, vRecMinY);
		glTexCoord2f(1, 0);		glVertex2f(vRecMaxX, vRecMaxY);
		glTexCoord2f(0, 0);		glVertex2f(vRecMinX, vRecMaxY);
	glEnd();

	// Free the texture memory
	glDeleteTextures(1, &texFrameId2);

	glDisable(GL_TEXTURE_2D);
}
/*
* Donada una finestra et modifica les coordenades per mantenir un ratio.
*/
void QOpenGLWCustom::conserveRatio(double ratioIm, double& vRecMinX, double& vRecMaxX, double& vRecMinY, double& vRecMaxY){
	double height = this->height()*(vRecMaxY - vRecMinY) / 2.0;
	double width = this->width() * (vRecMaxX - vRecMinX) / 2.0;
	double prov = ratioIm;
	double ratioW = width / height;
	//Ratio W > ratio Image
	if (ratioW > ratioIm){
		double prov = height*ratioIm;
		double offset = (1.0 - prov / width)*(vRecMaxX - vRecMinX);
		vRecMinX += offset / 2.0;
		vRecMaxX -= offset / 2.0;
	}
	//Ratio W < ratio Image
	if (ratioW < ratioIm){
		double prov = width / ratioIm;
		double offset = (1 - prov / height) * (vRecMaxY - vRecMinY);
		vRecMinY += offset / 2.0;
		vRecMaxY -= offset / 2.0;
	}
}

/**
* Estableix el frame a mostrar
*/
void QOpenGLWCustom::setFrame(Mat& camFrame){
	frame = camFrame;
}

/**
* Estableix els senyals detectats
*/
void QOpenGLWCustom::setDetectedSigns(vector<pair<Rect, Mat> >& sd){
	signsDet = sd;
}

/**
* Funció que passa de mat a una textura 
*/
GLuint QOpenGLWCustom::matToTexture(cv::Mat &mat, GLenum minFilter, GLenum magFilter, GLenum wrapFilter)
{
	// Generate a number for our textureID's unique handle
	GLuint textureID;
	glGenTextures(1, &textureID);

	// Bind to our texture handle
	glBindTexture(GL_TEXTURE_2D, textureID);

	// Catch silly-mistake texture interpolation method for magnification
	if (magFilter == GL_LINEAR_MIPMAP_LINEAR ||
		magFilter == GL_LINEAR_MIPMAP_NEAREST ||
		magFilter == GL_NEAREST_MIPMAP_LINEAR ||
		magFilter == GL_NEAREST_MIPMAP_NEAREST)
	{
		magFilter = GL_LINEAR;
	}

	// Set texture interpolation methods for minification and magnification
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, minFilter);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, magFilter);

	// Set texture clamping method
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, wrapFilter);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, wrapFilter);

	// Set incoming texture format to:
	// GL_BGR       for CV_CAP_OPENNI_BGR_IMAGE,
	// GL_LUMINANCE for CV_CAP_OPENNI_DISPARITY_MAP,
	// Work out other mappings as required ( there's a list in comments in main() )
	GLenum inputColourFormat = GL_BGR;
	if (mat.channels() == 1)
	{
		inputColourFormat = GL_LUMINANCE;
	}

	// Create the texture
	glTexImage2D(GL_TEXTURE_2D,     // Type of texture
		0,                 // Pyramid level (for mip-mapping) - 0 is the top level
		GL_RGB,            // Internal colour format to convert to
		mat.cols,          // Image width  i.e. 640 for Kinect in standard mode
		mat.rows,          // Image height i.e. 480 for Kinect in standard mode
		0,                 // Border width in pixels (can either be 1 or 0)
		inputColourFormat, // Input image format (i.e. GL_RGB, GL_RGBA, GL_BGR etc.)
		GL_UNSIGNED_BYTE,  // Image data type
		mat.ptr());        // The actual image data itself

	// If we're using mipmaps then generate them. Note: This requires OpenGL 3.0 or higher
	if (minFilter == GL_LINEAR_MIPMAP_LINEAR ||
		minFilter == GL_LINEAR_MIPMAP_NEAREST ||
		minFilter == GL_NEAREST_MIPMAP_LINEAR ||
		minFilter == GL_NEAREST_MIPMAP_NEAREST)
	{
		glGenerateMipmap(GL_TEXTURE_2D);
	}

	return textureID;
}