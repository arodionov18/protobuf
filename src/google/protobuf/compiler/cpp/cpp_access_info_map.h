#ifndef GOOGLE_PROTOBUF_COMPILER_CPP_ACCESS_INFO_MAP_H__
#define GOOGLE_PROTOBUF_COMPILER_CPP_ACCESS_INFO_MAP_H__

#include <string>
#include <memory>
#include <unordered_set>
#include <fstream>

namespace google {
namespace protobuf {
namespace compiler {

namespace cpp {

class AccessInfoMap {
public:
    AccessInfoMap(const std::string& filename) {
        std::ifstream input_stream(filename);
        std::string name, is_used;
        size_t field_number;

        while (input_stream >> name >> is_used >> field_number) {
            if (is_used == "not_used") {
                continue;
            } else if (is_used == "serialized" || is_used == "get_metadata") {
                accessed_messages_.insert(name);
            } else if (is_used == "getters") {
                for (size_t i = 0; i < field_number; ++i) {
                    input_stream >> name >> is_used;

                    if (is_used == "1") {
                        accessed_.insert(name);
                    }
                }
            } else {
                // throw error??
            }
        }
    }

    bool IsAccessed(const std::string& name) {
        return accessed_.find(name) != accessed_.end();
    }

    bool IsParentMessageAccessed(const std::string& full_name, const std::string field_name) {
        std::string message_name = full_name.substr(0, full_name.find(field_name) - 1);
        return accessed_messages_.find(message_name) != accessed_messages_.end();
    }

private:
    std::unordered_set<std::string> accessed_;
    std::unordered_set<std::string> accessed_messages_;
};

}  // namespace cpp
}  // namespace compiler
}  // namespace protobuf
}  // namespace google



#endif  // GOOGLE_PROTOBUF_COMPILER_CPP_ACCESS_INFO_MAP_H__
