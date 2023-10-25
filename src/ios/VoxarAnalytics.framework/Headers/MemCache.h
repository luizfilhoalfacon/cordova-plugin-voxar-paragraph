//
//  MemCache.h
//  VoxarAnalytics
//
//  Created by Matheus Coelho Berger on 06/03/17.
//  Copyright © 2017 Voxar. All rights reserved.
//

#ifndef MemCache_h
#define MemCache_h

#include <stdio.h>
#include <iostream>
#include <fstream>
#include <map>
#include <string>
#include <vector>

#ifdef __APPLE__
#define KPI_FILE "/vxa-kpi-cache"
#define FEATURE_FILE "/vxa-feature-cache"
#else
#define KPI_FILE "vxa-kpi-cache"
#define FEATURE_FILE "vxa-feature-cache"
#endif

namespace vxa
{
    class MemCache
    {
        typedef std::vector<std::pair<std::string, long long>> buffer_type;
    
    private:

        static std::map<std::string, buffer_type> buffers;
        
        static void load_buffer_from_cache(const std::string &filename);
        static void load_data_from_buffer(std::map<std::string, std::vector<long long> > &data_log,
            const std::string &filename);
    
    public:
        static std::string get_cache_file_path(const std::string &filename);
        static void save_log_to_buffer(const std::string &target, long long value, const std::string &filename);
        static void save_buffer_to_file(const std::string &filename);
        static void load_cache(
            const std::vector<std::pair<std::string, std::map<std::string, std::vector<long long> >* > > &data_logs);
    };
}

#endif /* MemCache_h */
