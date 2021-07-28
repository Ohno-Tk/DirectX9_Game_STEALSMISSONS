/*=============================================================================

���ʕ���[ Common.h ]
( ����g�p����Renderer.h�̎��ɃC���N���[�h����
 ���������[�N���o��d3dxmath.h�̑O�ɋL�q����ƃG���[�����o)
-------------------------------------------------------------------------------

��  Create
2017/11/11
=============================================================================*/

#ifndef _COMMON_H_
#define _COMMON_H_

/*-----------------------------------------------------------------------------
Include Files
-----------------------------------------------------------------------------*/
#ifdef _DEBUG
	#include <crtdbg.h>
#endif
#include <string>
#include <vector>
#include <list>
#include <algorithm>
#include <windows.h>

/*-----------------------------------------------------------------------------
Macro
-----------------------------------------------------------------------------*/
//#define new ::new(_NORMAL_BLOCK, __FILE__, __LINE__)	//	���������[�N���o(�o�̓f�o�b�O�ɕ\�������)

#define SCREEN_WIDTH   ( 800 ) // ��ʃT�C�Y(��)
#define SCREEN_HEIGHT  ( 600 ) // ��ʃT�C�Y(�c)

#define TEXTURE_PATH "data/TEXTURE/" // �e�N�X�`���̃p�X
#define MODEL_PATH   "data/MODEL/"   // ���f���̃p�X
#define MOTION_PATH  "data/MOTION/"	 //	���[�V�����̃p�X
#define SHADER_PATH  "data/SHADER/"  // �V�F�[�_�[�̃p�X

#define SAFE_UNINIT(p)      if(p){ p->Uninitialize(); delete p; p = NULL; }// �|�C���^�̏I�������}�N��
#define SAFE_DELETE(p)      if(p){ delete p; p = NULL; }             // �|�C���^�̉�������}�N��
#define SAFE_ARRAYDELETE(p) if(p){ delete[] p; p = NULL; }           // �z��̉���}�N��

#define ENABLE_SOUND
#undef ENABLE_SOUND

#define ENABLE_XINPUT
//#undef ENABLE_XINPUT

#endif
