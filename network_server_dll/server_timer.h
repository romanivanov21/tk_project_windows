/*******************************************************************
* Файл: server_timer.h											   *
* Описание:содержит обяъявление функций таймера					   *
* Автор: Иванов Роман Витальевич (c)							   *
* Год: 2014														   *
*																   *
********************************************************************/

#ifndef _SERVER_TIMER_
#define _SERVER_TIMER_

#include <boost/date_time/posix_time/posix_time.hpp>
#include <boost/date_time/posix_time/posix_time_types.hpp>


namespace server
{
	class server_time : private boost::noncopyable
	{
	public:
		std::string current_date_time_string();
		void timer_start();
		boost::int64_t timer_stop();
	private:
		boost::posix_time::ptime start_time_;
		boost::posix_time::ptime stop_time_;
	};
}
#endif