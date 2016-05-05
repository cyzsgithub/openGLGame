

#include "3DSLoader.h"
#include "CBMPLoader.h"

/** ���캯�� */
C3DSLoader::C3DSLoader()
{
	m_CurrentChunk = new tChunk;	 /**< Ϊ��ǰ�����ռ� */
	m_TempChunk = new tChunk;		 /**< Ϊ��ʱ�����ռ� */
	m_3DModel.numOfObjects = 0;
	m_3DModel.numOfMaterials = 0;
	for (int i=0; i<MAX_TEXTURES; i++) 
		m_textures[i] = 0;
}

/** �ͷ��ڴ沢�ر��ļ� */ 
void C3DSLoader::CleanUp()
{
	fclose(m_FilePointer);			 /**< �ر��ļ� */
	delete m_CurrentChunk;		     /**< �ͷŵ�ǰ�� */
	delete m_TempChunk;				 /**< �ͷ���ʱ�� */
}

/** �������� */
C3DSLoader::~C3DSLoader()
{
	m_3DModel.numOfObjects = 0;
	m_3DModel.numOfMaterials = 0;
	m_3DModel.pObject.clear();
	m_3DModel.pMaterials.clear();
	glDeleteTextures(MAX_TEXTURES, m_textures);
}

/** ��ʱ��3DS�ļ� */
void C3DSLoader::Init(char *filename)
{	
	/** ��3ds�ļ�װ�뵽ģ�ͽṹ���� */
	Import3DS(&m_3DModel, filename);	

	for(int i =0; i<m_3DModel.numOfMaterials;i++)
	{ 
		if(strlen(m_3DModel.pMaterials[i].strFile)>0)                 /**< �ж��Ƿ���һ���ļ��� */
		   LoadTexture(m_3DModel.pMaterials[i].strFile,m_textures, i);/**< ʹ�������ļ�������װ��λͼ */		 
	   
		/** ���ò��ʵ�����ID */
		m_3DModel.pMaterials[i].texureId = i;                     
	} 
}

/** ��ʾ3dsģ�� */
void C3DSLoader::Draw() 
{
	glPushAttrib(GL_CURRENT_BIT); /**< ����������ɫ��ʵ�� */
	glDisable(GL_TEXTURE_2D);
	
	/**< ����ģ�������еĶ��� */
	for(int i = 0; i < m_3DModel.numOfObjects; i++)
	{
		if(m_3DModel.pObject.size() <= 0) 
			break;                   /**< �������Ĵ�СС��0�����˳� */
	 
		t3DObject *pObject = &m_3DModel.pObject[i];/**< ��õ�ǰ��ʾ�Ķ��� */
	 
		if(pObject->bHasTexture)                  /**< �жϸö����Ƿ�������ӳ�� */
		 {	
			 glEnable(GL_TEXTURE_2D);             /**< ������ӳ�� */
			 glBindTexture(GL_TEXTURE_2D, m_textures[pObject->materialID]);
		 } 
	 else	
		 glDisable(GL_TEXTURE_2D);                /**< �ر�����ӳ�� */
	 
	 glColor3ub(255, 255, 255);

	 /** ��ʼ���� */
	 glBegin(GL_TRIANGLES);
	 for(int j = 0; j < pObject->numOfFaces; j++)		/**< �������е��� */
	 {for(int tex = 0; tex < 3; tex++)					/**< ���������ε����е� */
		{
			int index = pObject->pFaces[j].vertIndex[tex];	/**< ������ÿ��������� */
		 
			glNormal3f(pObject->pNormals[index].x,pObject->pNormals[index].y,  
			        pObject->pNormals[index].z);		/**< ���������� */
		 
		 if(pObject->bHasTexture)						/**< �������������� */
		 {	
			 if(pObject->pTexVerts)						/**< ȷ���Ƿ���UVW�������� */
				glTexCoord2f(pObject->pTexVerts[index].x,pObject->pTexVerts[index].y);
		 }
		 else
		 {	
			 if(m_3DModel.pMaterials.size() && pObject->materialID>= 0) 
			{	
				BYTE *pColor = m_3DModel.pMaterials[pObject->materialID].color;
				glColor3ub(pColor[0],pColor[1],pColor[2]);
			}
		 }
		 glVertex3f(pObject->pVerts[index].x,pObject->pVerts[index].y,pObject->pVerts[index].z);
		}
	 }
	glEnd(); /**< ���ƽ��� */
	}
	glEnable(GL_TEXTURE_2D);
	
	glPopAttrib();   /**< �ָ�ǰһ���� */
}

/** ת������ */
void C3DSLoader::LoadTexture(char* filename, GLuint textureArray[], GLuint textureID)
{

	if(!filename)
		return;
	
	/** ����λͼ */
	if(!m_BMPTexture.LoadBitmap(filename))
	{
		MessageBox(NULL,"����λͼʧ��!","����",MB_OK);
		exit(0);
	}
	glGenTextures(1,&m_textures[textureID]);
	
	glPixelStorei (GL_UNPACK_ALIGNMENT, 1);
	glBindTexture(GL_TEXTURE_2D, m_textures[textureID]);
	
	/** �����˲� */
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR_MIPMAP_LINEAR);
	
	/** �������� */
	gluBuild2DMipmaps(GL_TEXTURE_2D, 3, m_BMPTexture.imageWidth, m_BMPTexture.imageHeight, GL_RGB, 
		              GL_UNSIGNED_BYTE, m_BMPTexture.image);
		
}

/** ����3DS�ļ���ģ�ͽṹ�� */
bool C3DSLoader::Import3DS(t3DModel *pModel, char *strFileName)
{	
	char strMessage[255] = {0};
	
	/** ��һ��3ds�ļ� */
	m_FilePointer = fopen(strFileName, "rb");
	
	/**< ����ļ�ָ�� */
	if(!m_FilePointer) 
	{	
		sprintf(strMessage, "�Ҳ����ļ�: %s!", strFileName);
		MessageBox(NULL, strMessage, "Error", MB_OK);
		return false;
	}
	
	/** ���ļ��ĵ�һ��������ж��Ƿ���3ds�ļ� */
	ReadChunk(m_CurrentChunk);
	
	/** ȷ����3ds�ļ� */
	if (m_CurrentChunk->ID != PRIMARY)
	{	
		MessageBox(NULL, "���ܼ�������!", "Error", MB_OK);
		return false;
	}
	
	/** �ݹ������������ */
	ReadNextChunk(pModel, m_CurrentChunk);
	
	/** ���㶥��ķ��� */
	ComputeNormals(pModel);
	
	/** �ͷ��ڴ�ռ� */
	CleanUp();
	
	return true;
}

/**  ����һ���ַ��� */
int C3DSLoader::GetString(char *pBuffer)
{	
	int index = 0;
	
	/** ����һ���ֽڵ����� */
	fread(pBuffer, 1, 1, m_FilePointer);
	
	/** ֱ������ */
	while (*(pBuffer + index++) != 0) 
	{
		/** ����һ���ַ�ֱ��NULL */
		fread(pBuffer + index, 1, 1, m_FilePointer);
	}
	
	/** �����ַ����ĳ��� */
	return strlen(pBuffer) + 1;
}

/** ������ID�ź������ֽڳ��� */
void C3DSLoader::ReadChunk(tChunk *pChunk)
{	
	// ������ID�� */
	pChunk->bytesRead = fread(&pChunk->ID, 1, 2, m_FilePointer);
	
	/** �����ռ�õĳ��� */
	pChunk->bytesRead += fread(&pChunk->length, 1, 4, m_FilePointer);
}


/** ����3ds�ļ�����Ҫ���� */
void C3DSLoader::ReadNextChunk(t3DModel *pModel, tChunk *pPreChunk)
{	
	t3DObject newObject = {0};					/**< ������ӵ��������� */
	tMatInfo newTexture = {0};				    /**< ������ӵ��������� */
	unsigned int version = 0;					/**< �����ļ��汾 */
	int buffer[50000] = {0};					/**< ������������Ҫ������ */
	m_CurrentChunk = new tChunk;				/**< Ϊ�µĿ����ռ�		 */
	
	/** ���������ӿ� */
	while (pPreChunk->bytesRead < pPreChunk->length)
	{	
		/** ������һ���� */
		ReadChunk(m_CurrentChunk);
		
		/** �жϿ��ID�� */
		switch (m_CurrentChunk->ID)
		{
		
		/** �ļ��汾�� */
		case VERSION:							
			
			/** �����ļ��İ汾�� */
			m_CurrentChunk->bytesRead += fread(&version, 1, m_CurrentChunk->length - m_CurrentChunk->bytesRead, m_FilePointer);
			
			/** ����ļ��汾�Ŵ���3������һ��������Ϣ */
			if (version > 0x03)
				MessageBox(NULL, " ��3DS�ļ��汾����3.0,���ܲ�����ȷ��ȡ", "����", MB_OK);
			break;
		
			/** ����汾��Ϣ */
		case OBJECTINFO:						
			
			/** ������һ���� */
			ReadChunk(m_TempChunk);
			
			/** �������İ汾�� */
			m_TempChunk->bytesRead += fread(&version, 1, m_TempChunk->length - m_TempChunk->bytesRead, m_FilePointer);
			
			/** ���Ӷ�����ֽ��� */
			m_CurrentChunk->bytesRead += m_TempChunk->bytesRead;
			
			/** ������һ���� */
			ReadNextChunk(pModel, m_CurrentChunk);
			break;
		
		/** ������Ϣ */
		case MATERIAL:							
			
			/** ���ʵ���Ŀ���� */
			pModel->numOfMaterials++;
			
			/** ���������������һ���հ�����ṹ */
			pModel->pMaterials.push_back(newTexture);
			
			/** �������װ�뺯�� */
			ReadNextMatChunk(pModel, m_CurrentChunk);
			break;

		/** �������� */
		case OBJECT:							
			
			/** ���������� */
			pModel->numOfObjects++;
			
			/** ���һ���µ�tObject�ڵ㵽���������� */
			pModel->pObject.push_back(newObject);
			
			/** ��ʼ������������������ݳ�Ա */
			memset(&(pModel->pObject[pModel->numOfObjects - 1]), 0, sizeof(t3DObject));
			
			/** ��ò������������ƣ�Ȼ�����Ӷ�����ֽ��� */
			m_CurrentChunk->bytesRead += GetString(pModel->pObject[pModel->numOfObjects - 1].strName);
			
			/** ��������Ķ�����Ϣ�Ķ��� */
			ReadNextObjChunk(pModel, &(pModel->pObject[pModel->numOfObjects - 1]), m_CurrentChunk);
			break;
		
		/** �ؼ�֡ */
		case EDITKEYFRAME:
			
			/** �����ؼ�֡��Ķ��� */
			m_CurrentChunk->bytesRead += fread(buffer, 1, m_CurrentChunk->length - m_CurrentChunk->bytesRead, m_FilePointer);
			break;
		default: 
			
			/**  �������к��ԵĿ�����ݵĶ��� */
			m_CurrentChunk->bytesRead += fread(buffer, 1, m_CurrentChunk->length - m_CurrentChunk->bytesRead, m_FilePointer);
			break;
		}
		
		/** ���Ӵ����������ֽ��� */
		pPreChunk->bytesRead += m_CurrentChunk->bytesRead;
	}
	
	/** �ͷŵ�ǰ����ڴ�ռ� */
	delete m_CurrentChunk;
	m_CurrentChunk = pPreChunk;

}
/** �������е��ļ��ж������Ϣ */
void C3DSLoader::ReadNextObjChunk(t3DModel *pModel, t3DObject *pObject, tChunk *pPreChunk)
{	
	int buffer[50000] = {0};					/** ���ڶ��벻��Ҫ������ */
	
	/** ���µĿ����洢�ռ� */
	m_CurrentChunk = new tChunk;
	
	/** ��������������ֱ�����ӿ���� */
	while (pPreChunk->bytesRead < pPreChunk->length)
	{	
		/** ������һ���� */
		ReadChunk(m_CurrentChunk);
		
		/** ������������ֿ� */
		switch (m_CurrentChunk->ID)
		{
		case OBJ_MESH:					/**< ���������һ���¿� */
			
			/** ʹ�õݹ麯�����ã�������¿� */
			ReadNextObjChunk(pModel, pObject, m_CurrentChunk);
			break;
		case OBJ_VERTICES:				/**< �����Ƕ��󶥵� */
			ReadVertices(pObject, m_CurrentChunk);
			break;
		case OBJ_FACES:					/**< ������Ƕ������ */
			ReadVertexIndices(pObject, m_CurrentChunk);
			break;
		case OBJ_MATERIAL:				/**< ������Ƕ���Ĳ������� */
			
			/** �������Ĳ������� */
			ReadObjMat(pModel, pObject, m_CurrentChunk);			
			break;
		case OBJ_UV:						/**< ��������UV�������� */
			/** ��������UV�������� */
			ReadUVCoordinates(pObject, m_CurrentChunk);
			break;
		default:  
			/** �Թ�����Ҫ����Ŀ� */
			m_CurrentChunk->bytesRead += fread(buffer, 1, m_CurrentChunk->length - m_CurrentChunk->bytesRead, m_FilePointer);
			break;
		}
		/** ��Ӵ������ж�����ֽ�����ǰ��Ķ�����ֽ��� */
		pPreChunk->bytesRead += m_CurrentChunk->bytesRead;
	}
	/** �ͷŵ�ǰ����ڴ�ռ䣬���ѵ�ǰ������Ϊǰ��� */
	delete m_CurrentChunk;
	m_CurrentChunk = pPreChunk;
}
/** �������еĲ�����Ϣ */
void C3DSLoader::ReadNextMatChunk(t3DModel *pModel, tChunk *pPreChunk)
{	
	int buffer[50000] = {0};					/**< ���ڶ��벻��Ҫ������ */
	/** ����ǰ�����洢�ռ� */
	m_CurrentChunk = new tChunk;
	/** ����������Щ�� */
	while (pPreChunk->bytesRead < pPreChunk->length)
	{	
		/** ������һ�� */
		ReadChunk(m_CurrentChunk);
		/** �ж϶������ʲô�� */
		switch (m_CurrentChunk->ID)
		{
		case MATNAME:							/**< ���ʵ����� */
			/** ������ʵ����� */
			m_CurrentChunk->bytesRead += fread(pModel->pMaterials[pModel->numOfMaterials - 1].strName, 1, m_CurrentChunk->length - m_CurrentChunk->bytesRead, m_FilePointer);
			break;
		case MATDIFFUSE:						/**< �����R G B��ɫ */
			ReadColor(&(pModel->pMaterials[pModel->numOfMaterials - 1]), m_CurrentChunk);
			break;
		case MATMAP:							/**< ������Ϣ��ͷ�� */
			/** ��һ�����ʿ���Ϣ */
			ReadNextMatChunk(pModel, m_CurrentChunk);
			break;
		case MATMAPFILE:						/**< �����ļ������� */
			/** ������ʵ��ļ����� */
			m_CurrentChunk->bytesRead += fread(pModel->pMaterials[pModel->numOfMaterials - 1].strFile, 1, m_CurrentChunk->length - m_CurrentChunk->bytesRead, m_FilePointer);
			break;
		default:  
			/** ��������Ҫ����Ŀ� */
			m_CurrentChunk->bytesRead += fread(buffer, 1, m_CurrentChunk->length - m_CurrentChunk->bytesRead, m_FilePointer);
			break;
		}
		/** ��Ӵ������ж�����ֽ��� */
		pPreChunk->bytesRead += m_CurrentChunk->bytesRead;
	}
	/** ɾ����ǰ�飬������ǰ������Ϊǰ��Ŀ� */
	delete m_CurrentChunk;
	m_CurrentChunk = pPreChunk;
}


/** ����RGB��ɫ */
void C3DSLoader::ReadColor(tMatInfo *pMaterial, tChunk *pChunk)
{	
	/** ������ɫ����Ϣ */
	ReadChunk(m_TempChunk);
	/** ����RGB��ɫ */
	m_TempChunk->bytesRead += fread(pMaterial->color, 1, m_TempChunk->length - m_TempChunk->bytesRead, m_FilePointer);
	/** ���Ӷ�����ֽ��� */
	pChunk->bytesRead += m_TempChunk->bytesRead;
}
/** ���붥������ */
void C3DSLoader::ReadVertexIndices(t3DObject *pObject, tChunk *pPreChunk)
{	
	unsigned short index = 0;					/**< ���ڶ��뵱ǰ������� */
	/** ����ö����������Ŀ */
	pPreChunk->bytesRead += fread(&pObject->numOfFaces, 1, 2, m_FilePointer);
	/** ����������Ĵ洢�ռ䣬����ʼ���ṹ */
	pObject->pFaces = new tFace [pObject->numOfFaces];
	memset(pObject->pFaces, 0, sizeof(tFace) * pObject->numOfFaces);
	/** �������������е��� */
	for(int i = 0; i < pObject->numOfFaces; i++)
	{	for(int j = 0; j < 4; j++)
		{	
			/** ���뵱ǰ��ĵ�һ����  */
			pPreChunk->bytesRead += fread(&index, 1, sizeof(index), m_FilePointer);
			if(j < 3)
			{	
				/** ��������������Ľṹ�� */
				pObject->pFaces[i].vertIndex[j] = index;
			}
		}
	}
}

/** ��������UV���� */
void C3DSLoader::ReadUVCoordinates(t3DObject *pObject, tChunk *pPreChunk)
{	
	/** ����UV��������� */
	pPreChunk->bytesRead += fread(&pObject->numTexVertex, 1, 2, m_FilePointer);
	
	/** ���䱣��UV������ڴ�ռ� */
	pObject->pTexVerts = new Vector2 [pObject->numTexVertex];
	
	/** ������������ */
	pPreChunk->bytesRead += fread(pObject->pTexVerts, 1, pPreChunk->length - pPreChunk->bytesRead, m_FilePointer);
}

/**  �������Ķ��� */
void C3DSLoader::ReadVertices(t3DObject *pObject, tChunk *pPreChunk)
{	
	/** ���붥�����Ŀ */
	pPreChunk->bytesRead += fread(&(pObject->numOfVerts), 1, 2, m_FilePointer);
	
	/** ���䶥��Ĵ洢�ռ䣬Ȼ���ʼ���ṹ�� */
	pObject->pVerts = new Vector3 [pObject->numOfVerts];
	memset(pObject->pVerts, 0, sizeof(Vector3) * pObject->numOfVerts);
	
	/** ���붥������ */
	pPreChunk->bytesRead += fread(pObject->pVerts, 1, pPreChunk->length - pPreChunk->bytesRead, m_FilePointer);
	
	/** �������еĶ��㽫Y���Z�ύ����Ȼ��Z�ᷴ�� */
	for(int i = 0; i < pObject->numOfVerts; i++)
	{	
		/** ����Y���ֵ */
		float fTempY = pObject->pVerts[i].y;
		/** ����Y���ֵ����Z���ֵ */
		pObject->pVerts[i].y = pObject->pVerts[i].z;
		/** ����Z���ֵ����-Y���ֵ  */
		pObject->pVerts[i].z = -fTempY;
	}
}

/** �������Ĳ������� */
void C3DSLoader::ReadObjMat(t3DModel *pModel, t3DObject *pObject, tChunk *pPreChunk)
{	
	char strMaterial[255] = {0};			/**< �����������Ĳ������� */
	int buffer[50000] = {0};				/**< �������벻��Ҫ������ */
	
	/** ���븳�赱ǰ����Ĳ������� */
	pPreChunk->bytesRead += GetString(strMaterial);
	
	/** �������е����� */
	for(int i = 0; i < pModel->numOfMaterials; i++)
	{	
		/** �������������뵱ǰ����������ƥ�� */
		if(strcmp(strMaterial, pModel->pMaterials[i].strName) == 0)
		{	
			/** ���ò���ID */
			pObject->materialID = i;
			
			/** �ж��Ƿ�������ӳ�� */
			if(strlen(pModel->pMaterials[i].strFile) > 0) {
				
				/** ���ö��������ӳ���־ */
				pObject->bHasTexture = true;
			}	
			break;
		}
		else
		{	
			/** ����ö���û�в��ʣ�������IDΪ-1 */
			pObject->materialID = -1;
		}
	}
	pPreChunk->bytesRead += fread(buffer, 1, pPreChunk->length - pPreChunk->bytesRead, m_FilePointer);
}


/** �������ķ����� */
void C3DSLoader::ComputeNormals(t3DModel *pModel)
{	
	Vector3 vVector1, vVector2, vNormal, vPoly[3];
	
	/** ���ģ����û�ж����򷵻� */
	if(pModel->numOfObjects <= 0)
		return;
	
	/** ����ģ�������еĶ��� */
	for(int index = 0; index < pModel->numOfObjects; index++)
	{	
		/** ��õ�ǰ�Ķ��� */
		t3DObject *pObject = &(pModel->pObject[index]);
		
		/** ������Ҫ�Ĵ洢�ռ� */
		Vector3 *pNormals		= new Vector3 [pObject->numOfFaces];
		Vector3 *pTempNormals	= new Vector3 [pObject->numOfFaces];
		pObject->pNormals		= new Vector3 [pObject->numOfVerts];
		
		/** ��������������� */
		for(int i=0; i < pObject->numOfFaces; i++)
		{	vPoly[0] = pObject->pVerts[pObject->pFaces[i].vertIndex[0]];
			vPoly[1] = pObject->pVerts[pObject->pFaces[i].vertIndex[1]];
			vPoly[2] = pObject->pVerts[pObject->pFaces[i].vertIndex[2]];
			
			/** ������ķ����� */
			vVector1 = vPoly[0] - vPoly[2];		        /**< ��ö���ε�ʸ�� */
			vVector2 = vPoly[2] - vPoly[1];		        /**< ��ö���εĵڶ���ʸ�� */
			vNormal  = vVector1.crossProduct(vVector2);	/**< ��������ʸ���Ĳ�� */
			pTempNormals[i] = vNormal;					
			vNormal  = vNormal.normalize();				/**< ��һ����� */
			pNormals[i] = vNormal;						/**< ����������ӵ��������б��� */
		}
		
		/** ���㶥�㷨���� */
		Vector3 vSum(0.0,0.0,0.0);
		Vector3 vZero = vSum;
		int shared=0;
		
		/** �������еĶ��� */
		for (int i = 0; i < pObject->numOfVerts; i++)			
		{	for (int j = 0; j < pObject->numOfFaces; j++)	/**< �������е��������� */
			{												/**< �жϸõ��Ƿ����������湲�� */
				if (pObject->pFaces[j].vertIndex[0] == i || 
					pObject->pFaces[j].vertIndex[1] == i || 
					pObject->pFaces[j].vertIndex[2] == i)
				{	
					vSum = vSum + pTempNormals[j];
					shared++;								
				}
			}      
			pObject->pNormals[i] = vSum / float(-shared);
			
			/** ��һ�����㷨�� */
			pObject->pNormals[i] = pObject->pNormals[i].normalize();	
			vSum = vZero;								
			shared = 0;										
		}
		/** �ͷŴ洢�ռ䣬��ʼ��һ������ */
		delete [] pTempNormals;
		delete [] pNormals;
	}
}








