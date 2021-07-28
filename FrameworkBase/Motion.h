/*=============================================================================

���[�V����[ Motion.h ]

-------------------------------------------------------------------------------

��  Create
	2017/08/07
=============================================================================*/

#ifndef _MOTION_H_
#define _MOTION_H_

/*-----------------------------------------------------------------------------
Include Files
-----------------------------------------------------------------------------*/
#include <stdio.h>

/*-----------------------------------------------------------------------------
Macro
-----------------------------------------------------------------------------*/
#define MAX_MOTION (10)	//	�ő僂�[�V������

/*-----------------------------------------------------------------------------

-----------------------------------------------------------------------------*/
class MotionCharacterData;
class VertexShader;
class PixelShader;

/*-----------------------------------------------------------------------------
	Class
-----------------------------------------------------------------------------*/
class Motion:public Object
{
public:
	Motion(int Priolity);

	static Motion *Create(const int Priolity, char* TextFileName);

	void Initialize(void)override;
	void Uninitialize(void)override;
	void Update(void)override;
	void Draw(void)override;

	//	Setter
	void SetTextFileName(char *data) { m_TextFileName = data; }
	void SetMotionIndex(const int index);
	void SetRotation(const D3DXVECTOR3 rot) { m_Rotation = rot; }
	void SetPartsRotation(const int index, const D3DXVECTOR3 rot){ m_CharacterData.PartInfo[index].OffsetRot = rot; }

	//	Getter
	D3DXVECTOR3 GetRotation(void) { return m_Rotation; }
	D3DXVECTOR3 GetPartsPosition(const int index){ return m_CharacterData.PartInfo[index].OffsetPos; }
	D3DXVECTOR3 GetPartsRotation(const int index){ return m_CharacterData.PartInfo[index].OffsetRot; }
	D3DXMATRIX GetPartsMatrix(const int index){ return m_CharacterData.PartInfo[index].MatrixWorld; }
	bool GetMotionEnd(void) { return m_MotionEnd; }
	D3DXMATRIX GetMatrix(void){return m_MtxWorld;}

private:
	void MotionInterpolation(void);	//	���[�V�������
	void MotionBlend(void);	//	���[�V�����u�����h
	void WorldTransform(LPDIRECT3DDEVICE9 Device);//	���[���h���W�ϊ�
	void PartWorldTransform(const int cntmodel, LPDIRECT3DDEVICE9 Device);	//	�p�[�c���Ƃ̃��[���h���W�ϊ�
	void ReadText(void);											//	�e�L�X�g�t�@�C���̓ǂݍ���
	void ReadNumModel(FILE *fp);									//	���f�����̓ǂݍ���
	void ReadModelFileName(FILE *fp);								//	���f���t�@�C�����̓ǂݍ���
	void LoadModel(const int nummodel, char *modelfilename);		//	���f���̃��[�h
	void ReadCharacterInfo(FILE *fp);								//	�L�����N�^���̓ǂݍ���
	void ReadPartsSet(FILE *fp);									//	�L�����N�^�̃p�[�c���̓ǂݍ���
	void ReadMotion(FILE *fp);										//	���[�V�������̓ǂݍ���
	void InitializePartsData(void);
	void InitializeMotionData(int countMotion);
	bool MatchFileToken(char* buffer, char* fileToken);		// �t�@�C���g�[�N���̈�v
	bool MisMatchFileToken(char* buffer, char* fileToken); // �t�@�C���g�[�N���̕s��v
	virtual void ConfigShader(LPDIRECT3DDEVICE9 device);


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
		EQUAL,
		LAST_WORD,
		MAX_TOKEN
	};

	struct KEYINFO
	{
		D3DXVECTOR3 *Pos;
		D3DXVECTOR3 *Rot;
	};

	struct PART
	{
		int					Index;		//	�p�[�c�ԍ�
		int					Parent;		//	�e�q�\��
		D3DXVECTOR3			OffsetPos;	//	�������W
		D3DXVECTOR3			OffsetRot;	//	������]
		D3DXVECTOR3			Pos;		//	��ԍ��W
		D3DXVECTOR3			Rot;		//	��ԉ�]
		D3DXVECTOR3			Scale;
		D3DXMATRIX			MatrixWorld;	//	���[���h�}�g���N�X
		D3DXMATRIX			MatrixScl;		//	�g��}�g���N�X
		D3DXMATRIX			MatrixRot;		//	��]�}�g���N�X
		D3DXMATRIX			MatrixPos;		//	���W�}�g���N�X
		MODEL_PARAM			ModelParam;
	};

	struct MOTION
	{
		int Loop;		//	���[�v���邩
		int NumKey;		//	�L�[��
		int *Frame;		//	�t���[����
		KEYINFO *Next;	//	���̏ꏊ
	};

	struct CHARACTERDATA
	{
		PART* PartInfo; // �p�[�c���
		MOTION Motion[MAX_MOTION]; // ���[�V�������
		int NumModel; // ���f����
	};

	D3DXMATRIX	m_MtxWorld;	//	���[���h�}�g���N�X

	D3DXVECTOR3 m_Rotation;	//	��]
	D3DXVECTOR3 m_Scale;	//	�g��

	int m_MotionIndex;	//	���[�V�����ԍ�
	int m_NumKeyCount;	//	�L�[��
	int m_MotionCount;	//	���[�V�����J�E���^

	static char* m_FileToken[MAX_TOKEN];	//	�g�[�N��
	static char m_Buffer[256];		//	�e�L�X�g�f�[�^�ǂݍ��݂̃o�b�t�@
	char* m_TextFileName;	//	�e�L�X�g�̃t�@�C����

	CHARACTERDATA m_CharacterData; // �L�����N�^�[���

	bool m_MotionEnd;

	int m_BlendMotionIndex;
	int m_BlendNumKey;
	int m_BlendUpdateCount;
	int m_MotionBlendFrame;
	MOTION m_BlendMotion[MAX_MOTION];

	VertexShader* m_VertexShader;
	PixelShader* m_PixelShader;

	LPDIRECT3DVERTEXDECLARATION9 m_VertexDeclaration;
};

#endif