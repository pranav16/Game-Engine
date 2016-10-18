#pragma once
#ifndef IACTORCONTROLLER_H
#define IACTORCONTROLLER_H
#include"IType.h"
namespace Engine
{


	class IActorController :public IType
	{
	public:
		IActorController(const HashString type) :IType(type) {};
		virtual void update(double dt) = 0;
	};



}

#endif // !IACTORCONTROLLER_H
