#include <string>
#include <vector>
#include <utility>

namespace vxa
{
    bool clean_file(const std::string &url);

    bool read_file(const std::string &url,
        std::vector<std::pair<std::string, long long> > &mem_data);

    bool write_file(const std::string &url,
        const std::vector<std::pair<std::string, long long> > &mem_data);
}

