#include <google/protobuf/port_def.inc>
#include <google/protobuf/message.h>
#include <unordered_map>
#include <fstream>
#include <cstdint>

struct TrackerData {
  const ::PROTOBUF_NAMESPACE_ID::Descriptor* descriptor;
  std::atomic<uint32_t>** bitmap;
  std::atomic<uint32_t>* state;
};

class DynamicTracker {
public:
  static void RegisterProto(const ::PROTOBUF_NAMESPACE_ID::Descriptor* d, std::atomic<uint32_t>** b, std::atomic<uint32_t>* s) {
    map_.insert({d->full_name(), {d, b, s}});
  }

  static void DumpStatistics(const std::string& filename) {
    std::ofstream dump_file(filename.c_str());
    for (const auto& elem: map_) {
      // each message
      std::string message_state = "not_used";
      switch(elem.second.state->load()) {
        case 1:
          message_state = "serialized";
          break;
        case 2:
        case 3:
          message_state = "get_metadata";
          break;
        case 4:
        case 5:
        case 6:
        case 7:
          message_state = "getters";
        default:
          break;
      }
      dump_file << elem.first << " " << message_state << std::endl;
      if (message_state == "not_used" || message_state == "serialized" || message_state == "get_metadata") {
        dump_file.close();
        return;
      }
      for (size_t i = 0; i < elem.second.descriptor->field_count(); ++i) {
        int index = i / 32;
        uint32_t index_in_bitmap = 1U << (i % 32);
        int is_used = ((*elem.second.bitmap)[index].load() & index_in_bitmap) >> (i % 32);
        dump_file << "\t" << elem.second.descriptor->field(i)->full_name() << "	" << is_used << std::endl;
      }
    }
    dump_file.close();
  }
  static std::unordered_map<std::string, std::string> DumpStatistics() {
    std::unordered_map<std::string, std::string> result;
    for (const auto& elem: map_) {
      for (size_t i = 0; i < elem.second.descriptor->field_count(); ++i) {
        int index = i / 32;
        uint32_t index_in_bitmap = 1U << (i % 32);
        int is_used = ((*elem.second.bitmap)[index].load() & index_in_bitmap) >> (i % 32);
        result[elem.second.descriptor->field(i)->full_name()] = is_used ? "used" : "unused";
      }
    }
    return result;
  }
private:
  static std::unordered_map<std::string, TrackerData> map_;
};

#include <google/protobuf/port_undef.inc>
