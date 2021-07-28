/*=============================================================================

���[�V�����L�����N�^�[�f�[�^[ MotionCharacterData.cpp ]
(Maybe-Later:Uninitialize�ŃG���[��f���Ă���)
-------------------------------------------------------------------------------

��  Create
2017/11/13
=============================================================================*/

#define _CRT_SECURE_NO_WARNINGS

/*-----------------------------------------------------------------------------
Include Files
-----------------------------------------------------------------------------*/
#include "Common.h"
#include "Debug.h"
#include "FileManager.h"
#include "RendererDirectX.h"
#include "Game.h"
#include "MotionCharacterData.h"

/*-----------------------------------------------------------------------------
Namespace
-----------------------------------------------------------------------------*/
using namespace std;

MotionCharacterData::MotionCharacterData()
{
	m_TextFileToken.push_back("SCRIPT");
	m_TextFileToken.push_back("END_SCRIPT");
	m_TextFileToken.push_back("NUM_MODEL");
	m_TextFileToken.push_back("MODEL_FILENAME");
	m_TextFileToken.push_back("CHARACTERSET");
	m_TextFileToken.push_back("END_CHARACTERSET");
	m_TextFileToken.push_back("PARTSSET");
	m_TextFileToken.push_back("END_PARTSSET");
	m_TextFileToken.push_back("INDEX");
	m_TextFileToken.push_back("PARENT");
	m_TextFileToken.push_back("POS");
	m_TextFileToken.push_back("ROT");
	m_TextFileToken.push_back("MOTIONSET");
	m_TextFileToken.push_back("END_MOTIONSET");
	m_TextFileToken.push_back("LOOP");
	m_TextFileToken.push_back("NUM_KEY");
	m_TextFileToken.push_back("KEYSET");
	m_TextFileToken.push_back("END_KEYSET");
	m_TextFileToken.push_back("FRAME");
	m_TextFileToken.push_back("KEY");
	m_TextFileToken.push_back("END_KEY");
	m_TextFileToken.push_back("���̍s�͐�Ώ����Ȃ����ƁI");
}

void MotionCharacterData::Initialize(void)
{
	Load(MOTION_PATH"Player.txt");
	Load(MOTION_PATH"Enemy.txt");
	Load(MOTION_PATH"BouHuman.txt");
}

/*-----------------------------------------------------------------------------
Function:   void MotionCharacterData::Load(string motionFilePass)
Parameter:  string motionFilePass
			  �e�N�X�`���̃p�X
Overview:   ���[�h
-----------------------------------------------------------------------------*/
void MotionCharacterData::Load(string motionFilePass)
{
	//	�����t�@�C�������݂��邩�̃`�F�b�N
	auto it = m_Motion_Map.find(motionFilePass);

	if (it != m_Motion_Map.end()) { return; }

	for(int i = 0 ; i < MAX_MOTION ; i++)
	{
		m_CharacterData.Motion[i].Loop = 0;
		m_CharacterData.Motion[i].NumKey = 0;
		m_CharacterData.Motion[i].Frame = NULL;
		m_CharacterData.Motion[i].Next = NULL;
	}

	ZeroMemory(&m_CharacterData, sizeof(CHARACTERDATA));

	ReadText(motionFilePass); // �e�L�X�g�t�@�C���̓ǂݍ���

	//	�L�[�ƒl��A��������
	m_Motion_Map[motionFilePass] = m_CharacterData;

	// �������
	//for(int i = 0 ; i < MAX_MOTION ; i++)
	//{
	//	for(int j = 0 ; j < m_CharacterData.Motion[i].NumKey ; j++)
	//	{
	//		SAFE_DELETE(m_CharacterData.Motion[i].Next[j].Position);
	//		SAFE_DELETE(m_CharacterData.Motion[i].Next[j].Rotation);
	//	}
	//}
}

/*-----------------------------------------------------------------------------
Function:   void MotionCharacterData::UnloadAll(void)
Overview:   ���[�V�����L�����N�^�[�f�[�^�̑S�폜
-----------------------------------------------------------------------------*/
void MotionCharacterData::UnloadAll(void)
{
	for (auto it = m_Motion_Map.begin(); it != m_Motion_Map.end(); ++it)
	{
		for(int i = 0 ; i < MAX_MOTION ; i++)
		{
			for(int j = 0 ; j < m_CharacterData.Motion[i].NumKey ; j++)
			{
//				SAFE_DELETE(it->second.Motion[i].Next[j].Position);
				if(it->second.Motion[i].Next[j].Position)
				{	//	���W

					delete it->second.Motion[i].Next[j].Position;
					it->second.Motion[i].Next[j].Position = NULL;
				}
				if(it->second.Motion[i].Next[j].Rotation)
				{	//	���W

					delete it->second.Motion[i].Next[j].Rotation;
					it->second.Motion[i].Next[j].Rotation = NULL;
				}
//				SAFE_DELETE(it->second.Motion[i].Next[j].Rotation);
				SAFE_DELETE(m_CharacterData.Motion[i].Next[j].Position);
				SAFE_DELETE(m_CharacterData.Motion[i].Next[j].Rotation);
			}

			if(m_CharacterData.Motion[i].Frame != NULL)
			{	//	���[�v���邩

				delete m_CharacterData.Motion[i].Frame;	//	���
				m_CharacterData.Motion[i].Frame = NULL;
			}

			SAFE_DELETE(it->second.Motion[i].Next);
		}

		for(int i = 0 ; i < it->second.NumModel ; i++)
		{
			for(int j = 0 ; j < (int)it->second.PartInfo[i].ModelParam.NumMaterial ; j++)
			{
				SAFE_RELEASE(it->second.PartInfo[i].ModelParam.Texture[j]);
			}

			SAFE_ARRAYDELETE(it->second.PartInfo[i].ModelParam.Texture);

			SAFE_RELEASE(it->second.PartInfo[i].ModelParam.Mesh);

			SAFE_RELEASE(it->second.PartInfo[i].ModelParam.BufferMaterial);
		}

		SAFE_ARRAYDELETE(it->second.PartInfo);
	}
	m_Motion_Map.clear(); // �S�v�f�̍폜

	m_TextFileToken.clear(); // �v�f�̉��
	vector<string>().swap(m_TextFileToken); // �������̉��
	m_Buffer.clear();
	string().swap(m_Buffer);
}

/*-----------------------------------------------------------------------------
Function:   const MotionCharacterData::CHARACTERDATA MotionCharacterData::GetCharacterData(std::string motionFilePass)const
Parameter:  string motionFilePass
			  ���[�V�����̃p�X
Overview:   ���[�V�����f�[�^�̎擾
-----------------------------------------------------------------------------*/
const MotionCharacterData::CHARACTERDATA MotionCharacterData::GetCharacterData(string motionFilePass)const
{
	//	�t�@�C�������݂��邩�̃`�F�b�N
	auto it = m_Motion_Map.find(motionFilePass);

	if (it != m_Motion_Map.end()){ return it->second; } //	���݂��Ă�����

	motionFilePass += "���擾�ł��܂���ł���";
	Debug::Assert(motionFilePass, "MotionCharacterData.cpp", "");

	CHARACTERDATA error;

	return error;
}

/*-----------------------------------------------------------------------------
Function:   void MotionCharacterData::InitCharaData(void)			  
Overview:   �L�����N�^�[�f�[�^�̏�����
-----------------------------------------------------------------------------*/
void MotionCharacterData::InitCharaData(void)
{
	for(int i = 0 ; i < m_CharacterData.NumModel ; i++)
	{	//	������

		m_CharacterData.PartInfo[i].Index = 0;
		m_CharacterData.PartInfo[i].Parent = 0;
		m_CharacterData.PartInfo[i].OffsetPosition = D3DXVECTOR3(0.0f,0.0f,0.0f);
		m_CharacterData.PartInfo[i].OffsetRotation = D3DXVECTOR3(0.0f,0.0f,0.0f);
		m_CharacterData.PartInfo[i].Position = D3DXVECTOR3(0.0f,0.0f,0.0f);
		m_CharacterData.PartInfo[i].Rotation = D3DXVECTOR3(0.0f,0.0f,0.0f);
		m_CharacterData.PartInfo[i].Scale = D3DXVECTOR3(1.0f, 1.0f, 1.0f);
		m_CharacterData.PartInfo[i].ModelParam.Texture = NULL;
		m_CharacterData.PartInfo[i].ModelParam.Mesh = NULL;
		m_CharacterData.PartInfo[i].ModelParam.BufferMaterial = NULL;
	}

	for(int i = 0; i < MAX_MOTION; i++)
	{
		m_CharacterData.Motion[i].Next = NULL;
	}
}

/*-----------------------------------------------------------------------------
Function:   void MotionCharacterData::InitMotionData(const int countMotion)		  
Overview:   ���[�V�����f�[�^�̏�����
-----------------------------------------------------------------------------*/
void MotionCharacterData::InitMotionData(const int countMotion)
{
	for(int i = 0; i < m_CharacterData.Motion[countMotion].NumKey; i++ )
	{	//	������
		for(int j = 0; j < m_CharacterData.NumModel; j++ )
		{	//	���f������

			m_CharacterData.Motion[countMotion].Next[i].Position[j] = D3DXVECTOR3(0.0f,0.0f,0.0f);
			m_CharacterData.Motion[countMotion].Next[i].Rotation[j] = D3DXVECTOR3(0.0f,0.0f,0.0f);
		}
	}
}

/*-----------------------------------------------------------------------------
Function:   void MotionCharacterData::ReadText(string motionFilePass)
Parameter:  string motionFilePass
			  ���[�V�����̃p�X			  
Overview:   �e�L�X�g�t�@�C���̓ǂݍ���
-----------------------------------------------------------------------------*/
void MotionCharacterData::ReadText(string motionFilePass)
{
	FileManager manager;
	m_ReadFile = manager.ReadFile(motionFilePass);

	while(!m_ReadFile.eof())
	{
		m_ReadFile >> m_Buffer;

		if( MatchFileToken(m_Buffer, m_TextFileToken[SCRIPT]) )
		{
			ReadNumModel();			// ���f�����̓ǂݍ���
			ReadModelFileName();	// ���f���t�@�C�����̓ǂݍ���
			ReadCharacterInfo();	//	�L�����N�^���̓ǂݍ���
			ReadMotion();			//	���[�V�������̓ǂݍ���
		}
	}

	m_ReadFile.close();
}

/*-----------------------------------------------------------------------------
Function:   void MotionCharacterData::ReadNumModel(void)			  
Overview:   ���f�����̓ǂݍ���
-----------------------------------------------------------------------------*/
void MotionCharacterData::ReadNumModel(void)
{
	for(;;)
	{
		m_ReadFile >> m_Buffer;

		if( MatchFileToken(m_Buffer, m_TextFileToken[NUM_MODEL]) )
		{
			m_ReadFile >> m_Buffer; // �u = �v

			m_ReadFile >> m_Buffer; // ���f����
			m_CharacterData.NumModel = stoi(m_Buffer.c_str());

			m_CharacterData.PartInfo = new PART[m_CharacterData.NumModel];

			InitCharaData(); // �L�����N�^�[�f�[�^�̏�����
			break;
		}
	}
}

/*-----------------------------------------------------------------------------
Function:   void MotionCharacterData::ReadModelFileName(void)			  
Overview:   ���f���t�@�C�����̓ǂݍ���
-----------------------------------------------------------------------------*/
void MotionCharacterData::ReadModelFileName(void)
{
	int nummodel = 0;

	while(nummodel != m_CharacterData.NumModel)
	{	//	���f������

		m_ReadFile >> m_Buffer;

		if( MatchFileToken(m_Buffer, m_TextFileToken[MODEL_FILENAME]) )
		{
			m_ReadFile >> m_Buffer;	//�u = �v

			m_ReadFile >> m_Buffer; // ���f���t�@�C����
			LoadModel(nummodel, m_Buffer); // ���f���̃��[�h
			nummodel++;
		}
	}
}

/*-----------------------------------------------------------------------------
Function:   void MotionCharacterData::LoadModel(const int nummodel, string modelfilename)
Parameter:  const int nummodel
              ���f���̃C���f�b�N�X
            string modelfilename
              ���f���̃t�@�C����
Overview:   ���f���t�@�C�����̓ǂݍ���
-----------------------------------------------------------------------------*/
void MotionCharacterData::LoadModel(const int nummodel, string modelfilename)
{
	//	�f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 Device = RendererDirectX::GetDevice();

	HRESULT hr;

	// �ǂݍ���
	hr = D3DXLoadMeshFromX(		modelfilename.c_str(),		//	�t�@�C����
								D3DXMESH_SYSTEMMEM,
								Device,				//	�f�o�C�X
								NULL,					//	�אڃo�b�t�@
								&m_CharacterData.PartInfo[nummodel].ModelParam.BufferMaterial,	//	�}�e���A�������i�[
								NULL,
								&m_CharacterData.PartInfo[nummodel].ModelParam.NumMaterial,	//	�}�e���A����
								&m_CharacterData.PartInfo[nummodel].ModelParam.Mesh );	//	���b�V��

	//	���f���̃G���[�`�F�b�N
	if(FAILED(hr))
	{
		MessageBox( NULL , modelfilename.c_str() , "Motion.cpp" , MB_OK | MB_ICONHAND );
	}

	//	�}�e���A�����̃|�C���^�Ƃ��ăo�b�t�@�̃A�h���X���擾
	m_CharacterData.PartInfo[nummodel].ModelParam.Material = ( D3DXMATERIAL* )m_CharacterData.PartInfo[nummodel].ModelParam.BufferMaterial->GetBufferPointer();

	//	�e�N�X�`���̓��I�m��
	m_CharacterData.PartInfo[nummodel].ModelParam.Texture = new LPDIRECT3DTEXTURE9[m_CharacterData.PartInfo[nummodel].ModelParam.NumMaterial];


	for(int j = 0 ; j < (int)m_CharacterData.PartInfo[nummodel].ModelParam.NumMaterial ; j++)
	{

		m_CharacterData.PartInfo[nummodel].ModelParam.Texture[j] = NULL;

		if(m_CharacterData.PartInfo[nummodel].ModelParam.Material[j].pTextureFilename)
		{

			char filePath[MAX_PATH];
			strcpy(filePath, TEXTURE_PATH);
			strcat(filePath, m_CharacterData.PartInfo[nummodel].ModelParam.Material[j].pTextureFilename);

			hr = D3DXCreateTextureFromFile( Device, filePath, &m_CharacterData.PartInfo[nummodel].ModelParam.Texture[j]);

			//	�e�N�X�`���̃G���[�`�F�b�N
			if(FAILED(hr))
			{
				MessageBox( NULL , "���f���̃e�N�X�`���p�X�����������ł�" , "MotionCharacterData.cpp" , MB_OK | MB_ICONHAND );
			}
		}
	}
}

/*-----------------------------------------------------------------------------
Function:   void MotionCharacterData::ReadCharacterInfo(void)		  
Overview:   �L�����N�^���̓ǂݍ���
-----------------------------------------------------------------------------*/
void MotionCharacterData::ReadCharacterInfo(void)
{
	while( MisMatchFileToken(m_Buffer, m_TextFileToken[END_CHARACTERSET]) )
	{
		m_ReadFile >> m_Buffer;

		if( MatchFileToken(m_Buffer, m_TextFileToken[CHARACTERSET]) )
		{	//	CHARACTERSET�̌���

			ReadPartsSet(); //	�L�����N�^�̃p�[�c���̓ǂݍ���
		}
	}
}

/*-----------------------------------------------------------------------------
Function:   void MotionCharacterData::ReadPartsSet(void)		  
Overview:   �L�����N�^�̃p�[�c���̓ǂݍ���
-----------------------------------------------------------------------------*/
void MotionCharacterData::ReadPartsSet(void)
{
	int nummodel = 0;

	while( nummodel != m_CharacterData.NumModel )
	{	//	���f������

		m_ReadFile >> m_Buffer;

		if( MatchFileToken(m_Buffer, m_TextFileToken[PARTSSET]) )
		{	//	PARTSSET�̌���

			for(;;)
			{
				m_ReadFile >> m_Buffer;

				if( MatchFileToken(m_Buffer, m_TextFileToken[INDEX]) )
				{
					m_ReadFile >> m_Buffer;	//�u = �v

					m_ReadFile >> m_Buffer; // �p�[�c�ԍ�
					m_CharacterData.PartInfo[nummodel].Index = stoi(m_Buffer.c_str());
				}

				else if( MatchFileToken(m_Buffer, m_TextFileToken[PARENT]) )
				{
					m_ReadFile >> m_Buffer;//�u = �v

					m_ReadFile >> m_Buffer;//	�e�q�\��
					m_CharacterData.PartInfo[nummodel].Parent = stoi(m_Buffer.c_str());
				}

				else if( MatchFileToken(m_Buffer, m_TextFileToken[POS]) )
				{
					m_ReadFile >> m_Buffer;//�u = �v

					//	���W�̓ǂݍ���
					m_ReadFile >> m_Buffer;
					m_CharacterData.PartInfo[nummodel].OffsetPosition.x = stof(m_Buffer.c_str());

					m_ReadFile >> m_Buffer;
					m_CharacterData.PartInfo[nummodel].OffsetPosition.y = stof(m_Buffer.c_str());

					m_ReadFile >> m_Buffer;
					m_CharacterData.PartInfo[nummodel].OffsetPosition.z = stof(m_Buffer.c_str());
				}

				else if( MatchFileToken(m_Buffer, m_TextFileToken[ROT]) )
				{
					m_ReadFile >> m_Buffer;//�u = �v

					//	��]�̓ǂݍ���
					m_ReadFile >> m_Buffer;
					m_CharacterData.PartInfo[nummodel].OffsetRotation.x = stof(m_Buffer.c_str());

					m_ReadFile >> m_Buffer;
					m_CharacterData.PartInfo[nummodel].OffsetRotation.y = stof(m_Buffer.c_str());

					m_ReadFile >> m_Buffer;
					m_CharacterData.PartInfo[nummodel].OffsetRotation.z = stof(m_Buffer.c_str());
					break;
				}
			}
		}

		//	END_PARTSSET�̌���
		if( MatchFileToken(m_Buffer, m_TextFileToken[END_PARTSSET]) ){ nummodel++; }
	}
}

/*-----------------------------------------------------------------------------
Function:   void MotionCharacterData::ReadMotion(void)	  
Overview:   ���[�V�������̓ǂݍ���
-----------------------------------------------------------------------------*/
void MotionCharacterData::ReadMotion(void)
{
	int cntMotion = 0;

	while(cntMotion != MAX_MOTION)
	{
		m_ReadFile >> m_Buffer;

		if( MatchFileToken(m_Buffer, m_TextFileToken[MOTIONSET]) )
		{
			for(;;)
			{
				m_ReadFile >> m_Buffer;

				if( MatchFileToken(m_Buffer, m_TextFileToken[LOOP]) )
				{
					m_ReadFile >> m_Buffer;	//�u = �v

					m_ReadFile >> m_Buffer; // ���[�v���邩
					m_CharacterData.Motion[cntMotion].Loop = stoi(m_Buffer.c_str());
				}
				else if( MatchFileToken(m_Buffer, m_TextFileToken[NUMKEY]) )
				{
					m_ReadFile >> m_Buffer;	//�u = �v

					m_ReadFile >> m_Buffer; // �L�[��
					m_CharacterData.Motion[cntMotion].NumKey = stoi(m_Buffer.c_str());

					m_CharacterData.Motion[cntMotion].Frame = new int[m_CharacterData.Motion[cntMotion].NumKey];

					m_CharacterData.Motion[cntMotion].Next = new KEYINFO[ m_CharacterData.Motion[cntMotion].NumKey ];

					for(int i = 0 ; i < m_CharacterData.Motion[cntMotion].NumKey ; i++ )
					{	//	�L�[����
						m_CharacterData.Motion[cntMotion].Next[i].Position = new D3DXVECTOR3[m_CharacterData.NumModel];
						m_CharacterData.Motion[cntMotion].Next[i].Rotation = new D3DXVECTOR3[m_CharacterData.NumModel];
					}

					InitMotionData(cntMotion); // ���[�V�����f�[�^�̏�����
					break;
				}
			}

			int numKey = 0;

			while(numKey != m_CharacterData.Motion[cntMotion].NumKey)
			{	//	�L�[����

				m_ReadFile >> m_Buffer;

				if( MatchFileToken(m_Buffer, m_TextFileToken[KEYSET]) )
				{	//	KEYSET�̌���

					int numModel = 0;

					while( numModel != m_CharacterData.NumModel )
					{	//	���f������

						m_ReadFile >> m_Buffer;

						if( MatchFileToken(m_Buffer, m_TextFileToken[FRAME]) )
						{
							m_ReadFile >> m_Buffer;	//�u = �v

							m_ReadFile >> m_Buffer;// �t���[����
							m_CharacterData.Motion[cntMotion].Frame[numKey] = stoi(m_Buffer.c_str());
						}

						else if( MatchFileToken(m_Buffer, m_TextFileToken[POS]) )
						{	//	POS�̌���
							m_ReadFile >> m_Buffer;	//�u = �v

							//	���W�̓ǂݍ���
							m_ReadFile >> m_Buffer;
							m_CharacterData.Motion[cntMotion].Next[numKey].Position[numModel].x = stof(m_Buffer.c_str());

							m_ReadFile >> m_Buffer;
							m_CharacterData.Motion[cntMotion].Next[numKey].Position[numModel].y = stof(m_Buffer.c_str());

							m_ReadFile >> m_Buffer;
							m_CharacterData.Motion[cntMotion].Next[numKey].Position[numModel].z = stof(m_Buffer.c_str());
						}

						else if( MatchFileToken(m_Buffer, m_TextFileToken[ROT]) )
						{	//	ROT�̌���
							m_ReadFile >> m_Buffer;	//�u = �v
							
							//	��]�̓ǂݍ���
							m_ReadFile >> m_Buffer;
							m_CharacterData.Motion[cntMotion].Next[numKey].Rotation[numModel].x = stof(m_Buffer.c_str());

							m_ReadFile >> m_Buffer;
							m_CharacterData.Motion[cntMotion].Next[numKey].Rotation[numModel].y = stof(m_Buffer.c_str());

							m_ReadFile >> m_Buffer;
							m_CharacterData.Motion[cntMotion].Next[numKey].Rotation[numModel].z = stof(m_Buffer.c_str());
						}

						else if( MatchFileToken(m_Buffer, m_TextFileToken[END_KEY]) ){ numModel++; }//	END_KEY�̌���
					}
				}

				else if( MatchFileToken(m_Buffer, m_TextFileToken[END_KEYSET]) ){ numKey++; }//	END_KEYSET�̌���
			}
		}
	
		if( MatchFileToken(m_Buffer, m_TextFileToken[END_MOTIONSET]) ){	cntMotion++; } //	END_MOTIONSET�̌���

		//	END_SCRIPT�̌���
		if ( MatchFileToken(m_Buffer, m_TextFileToken[END_SCRIPT]) )
		{
			for (UINT j = 0; j < (UINT)m_CharacterData.NumModel; j++)
			{
				m_CharacterData.PartInfo[j].Position = m_CharacterData.Motion[0].Next[0].Position[j];
				m_CharacterData.PartInfo[j].Rotation = m_CharacterData.Motion[0].Next[0].Rotation[j];
			}
			break;
		}
	}
}

/*-----------------------------------------------------------------------------
Function:   bool MotionCharacterData::MatchFileToken(string buffer, string fileToken)	  
Overview:   �t�@�C���g�[�N���̈�v
-----------------------------------------------------------------------------*/
bool MotionCharacterData::MatchFileToken(string buffer, string fileToken)
{
	if(strcmp(buffer.c_str() , fileToken.c_str()) == 0){ return true; }

	return false;
}

/*-----------------------------------------------------------------------------
Function:   bool MotionCharacterData::MisMatchFileToken(string buffer, string fileToken)	  
Overview:   �t�@�C���g�[�N���̕s��v
-----------------------------------------------------------------------------*/
bool MotionCharacterData::MisMatchFileToken(string buffer, string fileToken)
{
	if(strcmp(buffer.c_str() , fileToken.c_str()) != 0){ return true; }

	return false;
}