#pragma once

#include <filesystem>
#include <string>
#include <iostream>

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
        namespace fs = std::filesystem;

        try {
            fs::path src(srcPath);
            fs::path target(targetPath);

            if (src.has_filename() && src.extension() != "") {
                src = src.parent_path();
            }

            fs::path absSrc = fs::weakly_canonical(src);
            fs::path absTarget = fs::weakly_canonical(target);

            if (absSrc.root_name() != absTarget.root_name()) {
                return absTarget.string();
            }

            fs::path common;
            auto srcIt = absSrc.begin();
            auto targetIt = absTarget.begin();

            for (; srcIt != absSrc.end() && targetIt != absTarget.end() && *srcIt == *targetIt; ++srcIt, ++targetIt) {
                common /= *srcIt;
            }

            fs::path relative;
            for (; srcIt != absSrc.end(); ++srcIt) {
                relative /= "..";
            }

            for (; targetIt != absTarget.end(); ++targetIt) {
                relative /= *targetIt;
            }

            std::string rel = relative.string();

            std::replace(rel.begin(), rel.end(), '\\', '/');

            relativePath = rel;
            return relativePath;
        }
        catch (const std::exception &e) {
            std::cout << "ERROR::FILE::SETRELATIVEPATH::" << e.what() << std::endl;
            return targetPath;
        }
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
