#include "Track.h"


CTrack::CTrack(void)
{
	setSize(100,10);
}


CTrack::~CTrack(void)
{
	/** ɾ�����������ռ���ڴ� */	
	m_texture.FreeImage();
	glDeleteTextures(1,&m_texture.ID);
}

bool CTrack::init()
{
	/** �������� */
	loadTexture();

	return true;
}

void CTrack::setSize(unsigned  int width, unsigned  int cell)
{
	m_nWidth = width;
	m_nCellWidth = cell; 
}


bool CTrack::loadTexture()
{
	char* fileName = "data/track.bmp";	

	if(!m_texture.LoadBitmap(fileName) )                    /**< ����λͼ�ļ� */
	{
		MessageBox(NULL,"װ��λͼ�ļ�ʧ�ܣ�","����",MB_OK);       /**< �������ʧ���򵯳��Ի��� */
		exit(0);
	}
	glGenTextures(1, &m_texture.ID);                            /**< ����һ������������� */


	glBindTexture(GL_TEXTURE_2D, m_texture.ID);                 /**< ����������� */

	/** �����˲� */
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S,GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T,GL_REPEAT);

	/** �������� */
	gluBuild2DMipmaps(GL_TEXTURE_2D, GL_RGB, m_texture.imageWidth,
		m_texture.imageHeight, GL_RGB, GL_UNSIGNED_BYTE,
		m_texture.image);

	return true;
}

void CTrack::render()
{
	float X = 0, Z = 0;	

	float angle = PI/180;
	/** ���� sin ��cosֵ */
	float cosTheta = (float)cos(angle);
	float sinTheta = (float)sin(angle);

	float x1,z1,x2,z2,x3,z3,x4,z4;
	float rx,rz;

	glPushMatrix();
	glTranslatef(0.0f,0.0f,0.0f);
	//glRotatef(180,1.0f,1.0f,0.0f);
	glScalef(1.0f,1.0f,-1.0f);
	/** ������ */
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, m_texture.ID);


	for(X = 0;X<10;X+=10)
	{
		for (Z= -100;Z<100;Z+=10)
		{
			glBegin(GL_QUADS);

			glTexCoord2f(0.0f, 0.0f); glVertex3f(X, 0.01f, Z);	
			glTexCoord2f(1.0f, 0.0f); glVertex3f(X+10, 0.01f, Z);	
			glTexCoord2f(1.0f, 1.0f); glVertex3f(X+10, 0.01f, Z+10);	
			glTexCoord2f(0.0f, 1.0f); glVertex3f(X, 0.01f, Z+10);	

			glEnd();
		}
	}

	x4 = X-10; z4 = Z;
	x3 = X;z3 = Z;
	rx = X-60;rz = Z;

	for (int i =0 ;i<180;i++)
	{
		x1=x4;
		z1=z4;
		x2=x3;
		z2=z3;

		x3=(x2-rx)*cosTheta-(z2-rz)*sinTheta+rx;
		z3=(x2-rx)*sinTheta+(z2-rz)*cosTheta+rz;

		x4=(x1-rx)*cosTheta-(z1-rz)*sinTheta+rx;
		z4=(x1-rx)*sinTheta+(z1-rz)*cosTheta+rz;

		glBegin(GL_QUADS);

		glTexCoord2f(0.0f, 0.0f); glVertex3f(x1, 0.01f, z1);	
		glTexCoord2f(1.0f, 0.0f); glVertex3f(x2, 0.01f, z2);	
		glTexCoord2f(1.0f, 1.0f); glVertex3f(x3, 0.01f, z3);	
		glTexCoord2f(0.0f, 1.0f); glVertex3f(x4, 0.01f, z4);	

		glEnd();

	}

	X = -100;
	
	for (Z= 100;Z>-100;Z-=10)
	{
		glBegin(GL_QUADS);

		glTexCoord2f(0.0f, 0.0f); glVertex3f(X, 0.01f, Z);	
		glTexCoord2f(1.0f, 0.0f); glVertex3f(X-10, 0.01f, Z);	
		glTexCoord2f(1.0f, 1.0f); glVertex3f(X-10, 0.01f, Z-10);	
		glTexCoord2f(0.0f, 1.0f); glVertex3f(X, 0.01f, Z-10);	

		glEnd();
	}

	angle = (PI/180);

	cosTheta = (float)cos(angle);
	sinTheta = (float)sin(angle);


	x3 = X-10; z3 = Z;
	x4 = X;z4 = Z;
	rx = X+50;rz = Z;

	for (int i =0 ;i<180;i++)
	{
		x1=x4;
		z1=z4;
		x2=x3;
		z2=z3;

		x3=(x2-rx)*cosTheta-(z2-rz)*sinTheta+rx;
		z3=(x2-rx)*sinTheta+(z2-rz)*cosTheta+rz;

		x4=(x1-rx)*cosTheta-(z1-rz)*sinTheta+rx;
		z4=(x1-rx)*sinTheta+(z1-rz)*cosTheta+rz;

		glBegin(GL_QUADS);

		glTexCoord2f(0.0f, 0.0f); glVertex3f(x1, 0.01f, z1);	
		glTexCoord2f(1.0f, 0.0f); glVertex3f(x2, 0.01f, z2);	
		glTexCoord2f(1.0f, 1.0f); glVertex3f(x3, 0.01f, z3);	
		glTexCoord2f(0.0f, 1.0f); glVertex3f(x4, 0.01f, z4);	

		glEnd();

	}

	glPopMatrix();
}