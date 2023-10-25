//
//  Features.hpp
//  VoxarAnalytics
//
//  Created by Matheus Coelho Berger on 26/12/16.
//  Copyright © 2016 Voxar. All rights reserved.
//

#ifndef Features_h
#define Features_h

#include <map>
#include <stdio.h>
#include <iostream>
#include <string>
#include <vector>

#include "Timer.h"

#if defined _WIN32
#include "LibConfig.h"
#endif

namespace vxa
{
#if defined _WIN32
    class VXA_LIBRARY_POLICY FeatureLog
#else
    class FeatureLog
#endif
    {
    private:
        static Timer::Instant last_mode_begin;
        static std::string last_mode;
        
        static void log_current_feature(const std::string &target);         // Logs the feature and stops further recording until added again
    
    public:
        static std::map<std::string, std::vector<long long> > logs;
        static std::map<std::string, std::vector<long long> > kpis;
        
        FeatureLog() {}
        ~FeatureLog() {}
        
        static void begin_feature(const std::string &target);               // Starts recording a feature
        static void end_feature();
        static void log_feature(const std::string &target, long long value);
        static void log_event(const std::string &target);
        static void log_kpi(const std::string &target, long long value);
    };
}

#endif /* Features_h */
