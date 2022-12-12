#ifndef DELTATIME_H
#define DELTATIME_H

#include "AppDataStore.h"

namespace BOG {

	class delTime {
	//members
	private:
		BOG::fltPoint m_framTime = 0.f, m_framCurrentTime = 0.f, m_framPrevTime = 0.f;

	//constructor
	public:
		delTime() = default;
		~delTime() {
			m_framTime = 0.f; m_framCurrentTime = 0.f; m_framPrevTime = 0.f;
		}
	//setters and getters
	public:
		inline BOG::fltPoint getFramTm() {
			return m_framTime;
		}
		inline BOG::fltPoint getFps() {
			return (1 / m_framTime);
		}
	//methods
	public:
		void update()
		{
			m_framCurrentTime = glfwGetTime();
			m_framTime = m_framCurrentTime - m_framPrevTime;
			m_framPrevTime = m_framCurrentTime;
		}

	};
}



#endif //DELTIME_H