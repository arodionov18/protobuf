#include <google/protobuf/port_def.inc>
#include <google/protobuf/message.h>
#include <unordered_map>
#include <fstream>
#include <cstdint>

struct TrackerData {
  const ::PROTOBUF_NAMESPACE_ID::Descriptor* descriptor;
  std::atomic<uint32_t>** bitmap;
};

class DynamicTracker {
public:
  static void RegisterProto(const ::PROTOBUF_NAMESPACE_ID::Descriptor* d, std::atomic<uint32_t>** b) {
    map_.insert({d->full_name(), {d, b}});
  }

  static void DumpStatistics(const std::string& filename) {
    std::ofstream dump_file(filename.c_str());
    for (const auto& elem: map_) {
      // each message
      dump_file << elem.first << std::endl;
      for (size_t i = 0; i < elem.second.descriptor->field_count(); ++i) {
        int index = i / 32;
        uint32_t index_in_bitmap = 1U << (i % 32);
        int is_used = ((*elem.second.bitmap)[index].load() & index_in_bitmap) >> (i % 32);
        dump_file << "\t" << elem.second.descriptor->field(i)->full_name() << ", is used: " << is_used << std::endl;
      }
    }
    dump_file.close();
  }
private:
  static std::unordered_map<std::string, TrackerData> map_;
};

#include <google/protobuf/port_undef.inc>
