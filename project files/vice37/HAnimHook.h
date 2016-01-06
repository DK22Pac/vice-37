#pragma once
#include "CPatch.h"
#include <rwcore.h>
#include <rphanim.h>
#include <rtanim.h>
#include <rplogo.h>
#include "Debug.h"

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

RwBool MyRpHAnimPluginAttach(){
    RpLogoPluginAttach();
    return RpHAnimPluginAttach();
}

void MakeHAnimHook()
{
	CPatch::RedirectJump(0x64D970, RtAnimAnimationCreate);
    CPatch::RedirectJump(0x57F2A0, GtaCreateAnimAnimation);
	CPatch::RedirectJump(0x645C80, MyRpHAnimPluginAttach);
    CPatch::RedirectJump(0x64DAD0, RtAnimInterpolatorSetCurrentAnim);
    CPatch::SetChar(0x407A47, 76);
}