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

    static inline std::string getRelativePath(const std::string &srcPath, const std::string &targetPath) {
        if (!isValidPath(srcPath) || !isValidPath(targetPath)) {
            return "";
        }

        std::filesystem::path relative = std::filesystem::relative(targetPath, srcPath);

        return relative.string();
    }
};

} // data
} // nebula
