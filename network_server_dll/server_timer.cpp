#include"server_timer.h"
namespace server
{
	std::string server_time::current_date_time_string()
	{
		return boost::posix_time::to_simple_string(boost::posix_time::second_clock::local_time());
	}

	void server_time::timer_start()
	{
		start_time_ = boost::posix_time::microsec_clock::local_time();
	}

	std::string server_time::timer_stop()
	{
		stop_time_ = boost::posix_time::microsec_clock::local_time();
		boost::int64_t res_int64_t = ( start_time_ - stop_time_).total_microseconds();
		throw;
		std::string res_str;
		return res_str;
	}
}