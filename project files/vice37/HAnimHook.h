#pragma once
#include "CPatch.h"
#include <rwcore.h>
#include <rphanim.h>
#include <rtanim.h>
#include "Debug.h"

RtAnimInterpolatorInfo interpInfo;

void MyAnimFrameInterpolate(void * Out, void * In1, void * In2, RwReal time, void *customData)
{
	RpHAnimKeyFrame *key = (RpHAnimKeyFrame *)Out;
	key->prevFrame = NULL;
	key->time = 0.0f;
	key->t.x = 0.0f;
	key->t.y = 0.0f;
	key->t.z = 0.0f;
	key->q.imag.x = 0.0f;
	key->q.imag.y = 0.0f;
	key->q.imag.z = 0.0f;
	key->q.real = 1.0f;
}

RwBool MyRpHAnimPluginAttach()
{
	RwBool result = RpHAnimPluginAttach();
	interpInfo.typeID = 0xDEADBEEF;
	interpInfo.animKeyFrameSize = 36;
	interpInfo.interpKeyFrameSize = 36;
	interpInfo.keyFrameApplyCB = RpHAnimKeyFrameApply;
	interpInfo.keyFrameBlendCB = RpHAnimKeyFrameBlend;
	interpInfo.keyFrameInterpolateCB = MyAnimFrameInterpolate;
	interpInfo.keyFrameAddCB = RpHAnimKeyFrameAdd;
	interpInfo.keyFrameMulRecipCB = RpHAnimKeyFrameMulRecip;
	interpInfo.keyFrameStreamReadCB = RpHAnimKeyFrameStreamRead;
	interpInfo.keyFrameStreamWriteCB = RpHAnimKeyFrameStreamWrite;
	interpInfo.keyFrameStreamGetSizeCB = RpHAnimKeyFrameStreamGetSize;
	interpInfo.customDataSize = 0;
	RtAnimRegisterInterpolationScheme(&interpInfo);
	return result;
}

RtAnimAnimation *GtaCreateAnimAnimation(RpHAnimHierarchy *hier)
{
	if (hier)
	{
		RwInt32 numFrames = hier->numNodes * 2;
		RtAnimAnimation *animation = RtAnimAnimationCreate(1, numFrames, 0x3000, 0.0f);
		if (animation)
		{
			for (int i = 0; i < hier->numNodes; i++)
			{
				RpHAnimKeyFrame *key1 = &((RpHAnimKeyFrame *)animation->pFrames)[i];
				RpHAnimKeyFrame *key2 = &((RpHAnimKeyFrame *)animation->pFrames)[i + hier->numNodes];
				key1->prevFrame = NULL;
				key1->time = 0.0f;
				key1->t.x = 0.0f;
				key1->t.y = 0.0f;
				key1->t.z = 0.0f;
				key1->q.imag.x = 0.0f;
				key1->q.imag.y = 0.0f;
				key1->q.imag.z = 0.0f;
				key1->q.real = 1.0f;

				key2->prevFrame = NULL;
				key2->time = 1.0f;
				key2->t.x = 0.0f;
				key2->t.y = 0.0f;
				key2->t.z = 0.0f;
				key2->q.imag.x = 0.0f;
				key2->q.imag.y = 0.0f;
				key2->q.imag.z = 0.0f;
				key2->q.real = 1.0f;
			}
		}
		return animation;
	}
	else return NULL;
}

void MakeHAnimHook()
{
	CPatch::RedirectJump(0x66A9C0, MyAnimFrameInterpolate);
	CPatch::RedirectJump(0x64D970, RtAnimAnimationCreate);
	CPatch::RedirectJump(0x57F2A0, GtaCreateAnimAnimation);
	CPatch::RedirectJump(0x645C80, MyRpHAnimPluginAttach);
}