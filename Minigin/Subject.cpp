#include "Subject.h"
#include "Observer.h"
#include "Event.h"

namespace dae
{
    void Subject::AddObserver(Observer* observer)
    {
		m_observers.push_back(observer);
    }

    void Subject::RemoveObserver(Observer* observer)
    {
		std::erase(m_observers, observer);
    }

    void Subject::NotifyObservers(Event event, Subject* gameActor)
    {
		for (auto observer : m_observers)
		{
			observer->Notify(event, gameActor);
		}
    }
}