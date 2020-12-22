#ifndef CPPLS2_CLIENT_TIMESTAMPFORMATTER_H
#define CPPLS2_CLIENT_TIMESTAMPFORMATTER_H

#include <chrono>
#include <ctime>
#include <filesystem>

#define fs std::filesystem;

namespace Utils {
    class TimestampConverter
    {
    public:
        static std::string convertFileTimestamp(const std::filesystem::file_time_type& timestamp)
        {
            std::time_t tt = fileTimeTypeToTimeT(timestamp);
            struct tm * dt;
            char buffer [30];
            dt = localtime(&tt);
            strftime(buffer, sizeof(buffer), "%Y-%m-%d %H:%M:%S", dt);
            return std::string(buffer);
        }

        static std::time_t convertStringToTimeT(const std::string& str)
        {
            struct std::tm tm{};
            std::istringstream ss{str};
            ss >> std::get_time(&tm, "%Y-%m-%d %H:%M:%S");
            return mktime(&tm);
        }

    private:
        static std::time_t fileTimeTypeToTimeT(const std::filesystem::file_time_type& tp)
        {
            using namespace std::chrono;
            auto sctp = time_point_cast<system_clock::duration>(tp - std::filesystem::file_time_type::clock::now()
                                                                + system_clock::now());
            return system_clock::to_time_t(sctp);
        }
    };
}

#endif //CPPLS2_CLIENT_TIMESTAMPFORMATTER_H
