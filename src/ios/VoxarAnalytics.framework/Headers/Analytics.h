//
//  Analytics.hpp
//  VoxarAnalytics
//
//  Created by Matheus Coelho Berger on 22/12/16.
//  Copyright © 2016 Voxar. All rights reserved.
//

#ifndef Analytics_h
#define Analytics_h

#include <stdio.h>
#include <iostream>

#include "Timer.h"
#include "Features.h"
#include "Request.h"
#include "MemCache.h"

#if defined __APPLE__

#define PLATAFORM "ios"
#include "boost/thread.hpp"

#elif defined _WIN32

#define PLATAFORM "win"
#include "LibConfig.h"

#include <thread>

#endif

#include <list>
#include <map>
#include <mutex>
#include <string>
#include <vector>

namespace vxa
{
#if defined _WIN32
    class VXA_LIBRARY_POLICY Analytics
#else
    class Analytics
#endif
    {
#if defined __APPLE__
        typedef boost::thread thread_type;
#else
        typedef std::thread thread_type;
#endif

    private:
        static std::mutex lock;
        static std::map<thread_type::id, thread_type*> thread_map;
        static std::list<thread_type::id> dead_threads;
        static std::string tech_identifier;
        static Timer::Instant usage_timer;
        
        static std::string host;
        static std::string path;

		static std::string tid;
		static std::string cid;
        
        static void remove_dead_threads();

        static void process_logged_data(std::map<std::string, 
            std::vector<long long> > &map, void(*const log_fn)(const std::string&, long long), 
            const std::string &cache_filename);

        static void send_logged_data(const std::string name, long long value, const std::string &category,
            const std::string &cache_filename);

    public:
        static bool session_is_active;
        static bool session_should_be_active;
        
        static void init(const std::string& tech_name,
						 const std::string& t_id = "UA-92277227-1",
						 const std::string& c_id = "406a108e-10d2-438c-bdda-120e044b3607")    //handle tech usage begin
        {
			tid = t_id;
			cid = c_id;

			Analytics::tech_identifier = tech_name;
            Analytics::internal_init();
        }
        
        static void internal_init();
        
        static void end_session();             //handle tech usage's end, uploads all logs to google analytics
        static void resume_session();          //handle application comming to foreground, resume analytics
        static void pause_session();           //handle application going background, uploads all logs to google analytics
        static void update_session();
        static std::string get_tech_name();
        
        static void send_logged_feature(const std::string &event_name, const long long event_value);    //uploads event with double parameter to google
        static void send_logged_kpi(const std::string &kpi_name, const long long kpi_value);            //uploads kpi measure to google
    };
}

#endif /* Analytics_h */
