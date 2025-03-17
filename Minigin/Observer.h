#pragma once
#include "Event.h"
#include "Subject.h"

namespace dae
{
	class Observer
	{
	public:
		virtual ~Observer() = default;
		virtual void Notify(Event event, Subject* subject) = 0;
	};
}