/*=============================================================================

���[�V�����L�����N�^�[�f�[�^[ MotionCharacterData.h ]
(Maybe-Later:Uninitialize�ŃG���[��f���Ă���)
-------------------------------------------------------------------------------

��  Create
2017/11/13
=============================================================================*/

#ifndef _MOTIONCHARACTERDATA_H_
#define _MOTIONCHARACTERDATA_H_

/*-----------------------------------------------------------------------------
Include Files
-----------------------------------------------------------------------------*/
#include <fstream>
#include "ModelManagerDirectX.h"

/*-----------------------------------------------------------------------------
Macro
-----------------------------------------------------------------------------*/
#define MAX_MOTION (10)	//	�ő僂�[�V������

/*-----------------------------------------------------------------------------
Class
-----------------------------------------------------------------------------*/
class MotionCharacterData
{
public:
	struct KEYINFO
	{
		D3DXVECTOR3* Position;
		D3DXVECTOR3* Rotation;
	};

	struct PART
	{
		int			Index;			//	�p�[�c�ԍ�
		int			Parent;			//	�e�q�\��
		D3DXVECTOR3	OffsetPosition;	//	�������W
		D3DXVECTOR3	OffsetRotation;	//	������]
		D3DXVECTOR3	Position;		//	��ԍ��W
		D3DXVECTOR3	Rotation;		//	��ԉ�]
		D3DXVECTOR3	Scale;			//	�g��
		D3DXMATRIX	MatrixWorld;	//	���[���h�}�g���N�X
		D3DXMATRIX	MatrixRotation;	//	��]�}�g���N�X
		D3DXMATRIX	MatrixPosition;	//	���W�}�g���N�X
		D3DXMATRIX	MatrixScale;	//	�g��}�g���N�X		
		MODEL_PARAM	ModelParam; // ���f�����
	};

	struct MOTION
	{
		int Loop;		//	���[�v���邩
		int NumKey;		//	�L�[��
		int* Frame; // �t���[����
		KEYINFO *Next;	//	���̏ꏊ
	};

	struct CHARACTERDATA
	{
		PART* PartInfo; // �p�[�c���
		MOTION Motion[MAX_MOTION]; // ���[�V�������
		int NumModel; // ���f����
	};

public:
	MotionCharacterData();

	void Initialize(void);
	void Uninitialize(void){ UnloadAll(); }

	// Getter
	const CHARACTERDATA GetCharacterData(std::string motionFilePass)const;

private:
	void Load(std::string motionFilePass);		// ���[�V�����f�[�^���[�h
	void UnloadAll(void);						// ���[�V�����L�����N�^�[�f�[�^�̑S�폜
	void InitCharaData(void);					// �L�����N�^�[�f�[�^�̏�����
	void InitMotionData(const int countMotion);	// ���[�V�����f�[�^�̏�����

	void ReadText(std::string motionFilePass);							//	�e�L�X�g�t�@�C���̓ǂݍ���
	void ReadNumModel(void);											//	���f�����̓ǂݍ���
	void ReadModelFileName(void);										// ���f���t�@�C�����̓ǂݍ���
	void LoadModel(const int nummodel, std::string modelfilename);		//	���f���̃��[�h
	void ReadCharacterInfo(void);										//	�L�����N�^���̓ǂݍ���
	void ReadPartsSet(void);											//	�L�����N�^�̃p�[�c���̓ǂݍ���
	void ReadMotion(void);												//	���[�V�������̓ǂݍ���

	bool MatchFileToken(std::string buffer, std::string fileToken);		// �t�@�C���g�[�N���̈�v
	bool MisMatchFileToken(std::string buffer, std::string fileToken); // �t�@�C���g�[�N���̕s��v

private:
	enum TOKEN
	{
		SCRIPT = 0,
		END_SCRIPT,
		NUM_MODEL,
		MODEL_FILENAME,
		CHARACTERSET,
		END_CHARACTERSET,
		PARTSSET,
		END_PARTSSET,
		INDEX,
		PARENT,
		POS,
		ROT,
		MOTIONSET,
		END_MOTIONSET,
		LOOP,
		NUMKEY,
		KEYSET,
		END_KEYSET,
		FRAME,
		KEY,
		END_KEY,
		LAST_WORD,
		MAX_TOKEN
	};

	CHARACTERDATA m_CharacterData; // �L�����N�^�[���

	std::string m_Buffer;
	std::vector<std::string> m_TextFileToken;	// �t�@�C���g�[�N��
	std::ifstream m_ReadFile;					// �t�@�C����ǂݍ���
	std::unordered_map< std::string, CHARACTERDATA > m_Motion_Map;
};

#endif
