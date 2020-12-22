#ifndef CPPLS2_SERVER_TIMESTAMPFORMATTER_H
#define CPPLS2_SERVER_TIMESTAMPFORMATTER_H

#include <chrono>
#include <ctime>
#include <filesystem>

#define fs std::filesystem;

namespace Utils {
    class TimestampConverter
    {
    public:
        static std::string ConvertFileTimestamp(const std::filesystem::file_time_type& timestamp)
        {
            std::time_t tt = FileTimeTypeToTimeT(timestamp);
            struct tm * dt;
            char buffer [30];
            dt = localtime(&tt);
            strftime(buffer, sizeof(buffer), "%Y-%m-%d %H:%M:%S", dt);
            return std::string(buffer);
        }

    private:
        static std::time_t FileTimeTypeToTimeT(const std::filesystem::file_time_type& tp)
        {
            using namespace std::chrono;
            auto sctp = time_point_cast<system_clock::duration>(tp - std::filesystem::file_time_type::clock::now()
                                                                + system_clock::now());
            return system_clock::to_time_t(sctp);
        }
    };
}

#endif //CPPLS2_SERVER_TIMESTAMPFORMATTER_H
