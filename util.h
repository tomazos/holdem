#pragma once

#include <experimental/filesystem>
#include <optional>
#include <fstream>

//namespace std {
//    template<typename T>
//    using optional = experimental::optional<T>;
////    auto nullopt = experimental::nullopt;
//}

#define DEFINE_STANARD_OPS(type, memfun, memtype) \
inline std::ostream& operator<<(std::ostream& os, type t) { return os << t.string(); } \
inline bool operator==(type a, type b) { return a.memfun() == b.memfun(); } \
inline bool operator!=(type a, type b) { return a.memfun() != b.memfun(); } \
inline bool operator< (type a, type b) { return a.memfun() <  b.memfun(); } \
inline bool operator> (type a, type b) { return a.memfun() >  b.memfun(); } \
inline bool operator<=(type a, type b) { return a.memfun() <= b.memfun(); } \
inline bool operator>=(type a, type b) { return a.memfun() >= b.memfun(); } \
namespace std { template<> struct hash<type> { \
    typedef type argument_type; \
    typedef std::size_t result_type; \
    result_type operator()(argument_type const& s) const noexcept \
    { return std::hash<memtype>{}(s.memfun()); } \
}; \
}

using FilesystemPath = std::experimental::filesystem::path;

class OutputFileStream : public std::ofstream {
public:
    OutputFileStream(OutputFileStream&& writer) : std::ofstream(std::move(writer)) {}

    OutputFileStream& operator=(OutputFileStream&& writer) {
        ((std::ofstream&)(*this)) = std::move(writer);
        return *this;
    }

    static OutputFileStream truncate(const FilesystemPath& path) {
        return {
                path,
                std::ios_base::out | std::ios_base::trunc | std::ios_base::binary
        };
    }

    static OutputFileStream append(const FilesystemPath& path) {
        return {
                path,
                std::ios_base::out | std::ios_base::app | std::ios_base::binary
        };
    }

private:
    OutputFileStream(const std::experimental::filesystem::path& file_path, std::ios_base::openmode mode) {
        exceptions(std::ios_base::failbit | std::ios_base::badbit);
        open(file_path.c_str(), mode);
    }
};

template<typename... T>
std::string stringify(const T&... values) {
    std::ostringstream oss;
    ((oss << values), ...);
    return oss.str();
}

