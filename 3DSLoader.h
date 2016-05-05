

//�ļ�����:  3DS�ļ�������  


#ifndef __3DSLOADER_H__
#define __3DSLOADER_H__

#include "vector.h"
#include "CBMPLoader.h"
#include <math.h>
#include <vector>                    /** ������������ */
using namespace std;         

/** �����Ƕ���һЩ���ID�� */

/**  ������(Primary Chunk)��λ���ļ��Ŀ�ʼ */
#define PRIMARY       0x4D4D

/**  ����(Main Chunks) */
#define OBJECTINFO    0x3D3D		/**< �������İ汾�� */
#define VERSION       0x0002		/**< .3ds�ļ��İ汾 */
#define EDITKEYFRAME  0xB000		/**< ���йؼ�֡��Ϣ��ͷ�� */

/**<  ����Ĵμ����� */
#define MATERIAL	  0xAFFF		/** ������Ϣ */
#define OBJECT		  0x4000		/** ������桢�������Ϣ */

/**  ���ʵĴμ����� */
#define MATNAME       0xA000		/**< �������� */
#define MATDIFFUSE    0xA020		/**< ����/���ʵ���ɫ */
#define MATMAP        0xA200		/**< �²��ʵ�ͷ�� */
#define MATMAPFILE    0xA300		/**< ����������ļ��� */
#define OBJ_MESH	  0x4100		/**< �µ�������� */


/** �������Ĵμ����� */
#define OBJ_VERTICES  0x4110		/**< ���󶥵� */
#define OBJ_FACES	  0x4120		/**< ������� */
#define OBJ_MATERIAL  0x4130		/**< ����Ĳ��� */
#define OBJ_UV		  0x4140		/**< �����UV�������� */


/** ��Ľṹ���� */
struct tFace		
{	
	int vertIndex[3];			    /**< �������� */
	int coordIndex[3];			    /**< ������������ */
};

/** ������Ϣ�ṹ�� */
struct tMatInfo
{	
	char  strName[255];			   /**< �������� */
	char  strFile[255];			   /**< �����ļ����� */
	BYTE  color[3];				   /**< �����RGB��ɫ */
	int   texureId;				   /**< ����ID */
	float uTile;				   /**< u �ظ� */
	float vTile;				   /**< v �ظ� */
	float uOffset;			       /**< u ����ƫ�� */
	float vOffset;				   /**< v ����ƫ�� */
} ;

/** ������Ϣ�ṹ�� */
struct t3DObject	
{	
	int  numOfVerts;		      /**<	ģ���ж������Ŀ */
	int  numOfFaces;			  /**< ģ���������Ŀ */
	int  numTexVertex;			  /**< ģ���������������Ŀ */
	int  materialID;			  /**< ����ID */
	bool bHasTexture;			  /**< �Ƿ��������ӳ�� */
	char strName[255];			  /**< ��������� */
	Vector3  *pVerts;			  /**< ����Ķ��� */
	Vector3  *pNormals;		      /**< ����ķ����� */
	Vector2  *pTexVerts;		  /**< ����UV���� */
	tFace *pFaces;				  /**< ���������Ϣ */
};

/** ģ����Ϣ�ṹ�� */
struct t3DModel	
{	int numOfObjects;			  /**< ģ���ж������Ŀ */
	int numOfMaterials;			  /**< ģ���в��ʵ���Ŀ */
	vector<tMatInfo>pMaterials;	  /**< ����������Ϣ */
	vector<t3DObject> pObject;	  /**< ģ���ж���������Ϣ */
};

/** ����Ϣ�Ľṹ */
struct tChunk	
{	
	unsigned short int ID;		  /**< ���ID */
	unsigned int length;		  /**< ��ĳ��� */
	unsigned int bytesRead;		  /**< ��Ҫ���Ŀ����ݵ��ֽ��� */
};

#define MAX_TEXTURES  100

/** 3DS�ļ������� */
class C3DSLoader
{
public:
	/** ���캯�� */
	C3DSLoader();								
	virtual ~C3DSLoader();
	void Draw();//��ʾ3dsģ��
	void Init(char *filename);

private:
	/** ��һ���ַ��� */
	int  GetString(char *);								
	
	/** װ��3ds�ļ���ģ�ͽṹ�� */
	bool Import3DS(t3DModel *pModel, char *strFileName);

	void LoadTexture(char* filename, GLuint textureArray[], GLuint textureID);//  ���ļ��д�������
	
	/** ��ȡһ���� */
	void ReadChunk(tChunk *);		

	/** ��ȡ��һ���� */
	void ReadNextChunk(t3DModel *pModel, tChunk *);

	/** ��ȡ��һ������ */
	void ReadNextObjChunk(t3DModel *pModel,t3DObject *pObject,tChunk *);

	/** ��ȡ��һ�����ʿ� */
	void ReadNextMatChunk(t3DModel *pModel, tChunk *);	

	/** ��ȡ������ɫ��RGBֵ */
	void ReadColor(tMatInfo *pMaterial, tChunk *pChunk);

	/** ��ȡ����Ķ�����Ϣ */
	void ReadVertices(t3DObject *pObject, tChunk *);

	/** ��ȡ���������Ϣ */
	void ReadVertexIndices(t3DObject *pObject,tChunk *);

	/** ��ȡ������������� */
	void ReadUVCoordinates(t3DObject *pObject,tChunk *);

	/** ��ȡ�������Ĳ��� */
	void ReadObjMat(t3DModel *pModel,t3DObject *pObject,tChunk *pPreChunk);

	/** ������󶥵�ķ����� */
	void ComputeNormals(t3DModel *pModel);	

	/** �ͷ��ڴ�,�ر��ļ� */
	void CleanUp();										

	FILE	     *m_FilePointer;			  /**< �ļ�ָ�� */					
	tChunk	     *m_CurrentChunk;             /**< ��ȡ�����е�ǰ�� */
	tChunk	     *m_TempChunk;                /**< ��ʱ�� */
    CBMPLoader   m_BMPTexture;                /**< ����λͼ */
	GLuint       m_textures[MAX_TEXTURES];    /**< ���� */
	t3DModel     m_3DModel;                   /**< ģ�� */
};

#endif