#pragma once

#include <filesystem>
#include <string>

namespace nebula {
    namespace data {

class File {
public:
    static inline bool isValidPath(const std::string &path) {
        try {
            if (std::filesystem::exists(path)) {
                if (std::filesystem::is_directory(path)) {
                    return true;
                } else {
                    std::filesystem::path p(path);
                    return true;
                }
            }
        } catch (const std::exception& e) {
            return false;
        }
        return false;
    }

    static inline std::string setRelativePath(const std::string &srcPath, const std::string &targetPath) {
        if (!isValidPath(srcPath) || !isValidPath(targetPath)) {
            return "";
        }

        std::filesystem::path relative = std::filesystem::relative(targetPath, srcPath);
        relativePath = relative.string();

        return relativePath;
    }

    static inline std::string getRelativePath(std::string &target) {
        if (relativePath.size() == 0) {
            return std::string("").append(target);
        }
        std::string copy = relativePath;
        return copy.append("\\").append(target);
    }

    static inline std::string getRelativePath(const char *target) {
        if (relativePath.size() == 0) {
            return std::string("").append(std::string(target));
        }
        std::string copy = relativePath;
        return copy.append("\\").append(std::string(target));
    }

private:
    static inline std::string relativePath {};
};

} // data
} // nebula
