#ifndef _RGENGINE_H_
#define _RGENGINE_H_

// �������� int main����
#pragma comment(linker, "/ENTRY:mainCRTStartup")

#ifdef _DEBUG
#pragma comment(linker, "/SUBSYSTEM:CONSOLE") // ������Ͻ� �ܼ�âǥ��
#pragma comment(lib, "Debug_RGEngine_2016")
#else
#pragma comment(linker, "/SUBSYSTEM:WINDOWS") // �������Ͻ� �ܼ�â����
#pragma comment(lib, "Release_RGEngine_2016")
#endif

#include "RGApplication.h"
#include "RGGameObject.h"
#include "RGComponent.h"
#include "RGTypes.h"
#include "RGMath.h"

#include "RGComponentBoxCollider.h"
#include "RGComponentCircleCollider.h"
#include "RGComponentSpriteRenderer.h"
#include "RGComponentAnimationRenderer.h"
#include "RGComponentTextRenderer.h"
#include "RGComponentAudioSource.h"
#include "RGComponentAudioListener.h"

#include "RGDataStreamFile.h"
#include "RGDataStreamJSON.h"
#include "RGDataStreamXML.h"

#endif //_RGENGINE_H_