

#include "Terrain.h"
#include "CBMPLoader.h"

/** ���캯�� */
CTerrain::CTerrain()
{
	/** ���õ��δ�С */
	setSize(MAP_WIDTH,CELL_WIDTH);
	
		
}

/** �������� */
CTerrain::~CTerrain()
{
	
	/** ɾ�����������ռ���ڴ� */	

		m_texture.FreeImage();
	    glDeleteTextures(1,&m_texture.ID);

	
}



/** ��ʼ������ */
bool CTerrain::init()
{



	/** �������� */
	loadTexture();

	
	return true;
}

/** ���õ��δ�С */
void CTerrain::setSize(unsigned  int width, unsigned  int cell)
{
	m_nWidth = width;
	m_nCellWidth = cell; 
}


/** ����������� */
bool CTerrain::loadTexture()
{
	char* fileName= "data/terrain.bmp";	
		if(!m_texture.LoadBitmap(fileName) )                    /**< ����λͼ�ļ� */
		{
			MessageBox(NULL,"װ��λͼ�ļ�ʧ�ܣ�","����",MB_OK);       /**< �������ʧ���򵯳��Ի��� */
			exit(0);
		}
		glGenTextures(1, &m_texture.ID);                            /**< ����һ������������� */
		
			
		glBindTexture(GL_TEXTURE_2D, m_texture.ID);                 /**< ����������� */
		
		/** �����˲� */
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S,GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T,GL_REPEAT);
		
		/** �������� */
		gluBuild2DMipmaps(GL_TEXTURE_2D, GL_RGB, m_texture.imageWidth,
						m_texture.imageHeight, GL_RGB, GL_UNSIGNED_BYTE,
						m_texture.image);

  	
	return true;

}

/** ��Ⱦ���� */
void CTerrain::render()
{
		
	int X = 0, Z = 0;												
	glPushMatrix();
	glTranslatef(0.0f,0.0f,0.0f);
	glScalef(1.0f,1.0f,-1.0f);
	/** ������ */
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, m_texture.ID);
	
	for(X = -512;X<512;X+=5)
	{
		for (int Z= -512;Z<512;Z+=5)
		{
			glBegin(GL_QUADS);

			glTexCoord2f(0.0f, 0.0f); 
			glVertex3f(X, 0.0f, Z);	
			glTexCoord2f(1.0f, 0.0f); 
			glVertex3f(X+5, 0.0f, Z);	
			glTexCoord2f(1.0f, 1.0f); 
			glVertex3f(X+5, 0.0f, Z+5);	
			glTexCoord2f(0.0f, 1.0f); 
			glVertex3f(X, 0.0f, Z+5);	

			glEnd();
		}
	}

	glPopMatrix();


}

