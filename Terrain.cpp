

#include "Terrain.h"
#include "CBMPLoader.h"

/** 构造函数 */
CTerrain::CTerrain()
{
	/** 设置地形大小 */
	setSize(MAP_WIDTH,CELL_WIDTH);
	
		
}

/** 析构函数 */
CTerrain::~CTerrain()
{
	
	/** 删除纹理对象及其占用内存 */	

		m_texture.FreeImage();
	    glDeleteTextures(1,&m_texture.ID);

	
}



/** 初始化地形 */
bool CTerrain::init()
{



	/** 载入纹理 */
	loadTexture();

	
	return true;
}

/** 设置地形大小 */
void CTerrain::setSize(unsigned  int width, unsigned  int cell)
{
	m_nWidth = width;
	m_nCellWidth = cell; 
}


/** 载入地面纹理 */
bool CTerrain::loadTexture()
{
	char* fileName= "data/terrain.bmp";	
		if(!m_texture.LoadBitmap(fileName) )                    /**< 载入位图文件 */
		{
			MessageBox(NULL,"装载位图文件失败！","错误",MB_OK);       /**< 如果载入失败则弹出对话框 */
			exit(0);
		}
		glGenTextures(1, &m_texture.ID);                            /**< 生成一个纹理对象名称 */
		
			
		glBindTexture(GL_TEXTURE_2D, m_texture.ID);                 /**< 创建纹理对象 */
		
		/** 控制滤波 */
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S,GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T,GL_REPEAT);
		
		/** 创建纹理 */
		gluBuild2DMipmaps(GL_TEXTURE_2D, GL_RGB, m_texture.imageWidth,
						m_texture.imageHeight, GL_RGB, GL_UNSIGNED_BYTE,
						m_texture.image);

  	
	return true;

}

/** 渲染地形 */
void CTerrain::render()
{
		
	int X = 0, Z = 0;												
	glPushMatrix();
	glTranslatef(0.0f,0.0f,0.0f);
	glScalef(1.0f,1.0f,-1.0f);
	/** 绑定纹理 */
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

