#include "insert_profiler.h"
#include <string>
#include <iostream>
#include <memory>
#include <unordered_set>
#include <fstream>

bool is_fields_stripped = false;
std::unordered_set<std::string> stripped_fields;
std::unordered_set<std::string> stripped_messages;

void ProccessAccessInfoMap(const std::string& filename) {
    std::ifstream input_stream(filename);
    std::string name, is_used;
    size_t field_number;

    while (input_stream >> name >> is_used >> field_number) {
        if (is_used == "not_used") {
            stripped_messages.insert(name);
        } else if (is_used == "serialized" || is_used == "get_metadata") {
            continue;
        } else if (is_used == "getters") {
            for (size_t i = 0; i < field_number; ++i) {
                input_stream >> name >> is_used;

                if (is_used == "0") {
                    stripped_fields.insert(name);
                }
            }
        } else {
            // throw error??
        }
    }
}

void GenerateTrackerFile(google::protobuf::compiler::GeneratorContext* generator_context) {
    std::unique_ptr<google::protobuf::io::ZeroCopyOutputStream> stream(generator_context->Open("tracker.h"));
    google::protobuf::io::Printer printer(stream.get(), '$');

    printer.Print("#include <google/protobuf/port_def.inc>\n");
    printer.Print("#include <google/protobuf/message.h>\n");
    printer.Print("#include <unordered_map>\n");
    printer.Print("#include <fstream>\n");
    printer.Print("#include <cstdint>\n");
    printer.Print("\n");

    printer.Print("struct TrackerData {\n");
    printer.Indent();
    printer.Print("const ::PROTOBUF_NAMESPACE_ID::Descriptor* descriptor;\n");
    printer.Print("std::atomic<uint32_t>** bitmap;\n");
    printer.Print("std::atomic<uint32_t>* state;\n");
    printer.Outdent();
    printer.Print("};\n");

    printer.Print("\n");

    printer.Print("class DynamicTracker {\n");
    printer.Print("public:\n");
    printer.Indent();
    printer.Print("static void RegisterProto(const ::PROTOBUF_NAMESPACE_ID::Descriptor* d, std::atomic<uint32_t>** b, std::atomic<uint32_t>* s) {\n");
    printer.Indent();
    printer.Print("map_.insert({d->full_name(), {d, b, s}});\n");
    printer.Outdent();
    printer.Print("}\n");
    printer.Print("\n");

    // Begin: Get statistics
    printer.Print("static void DumpStatistics(const std::string& filename) {\n");
    printer.Indent();
    printer.Print("std::ofstream dump_file(filename.c_str());\n");
    printer.Print("for (const auto& elem: map_) {\n");
    printer.Indent();
    printer.Print("// each message\n");
    //printer.Print("dump_file << elem.first << std::endl;\n");
    printer.Print("std::string message_state = \"not_used\";\n");
    printer.Print("switch(elem.second.state->load()) {\n");
    printer.Indent();
    printer.Print("case 1:\n");
    printer.Indent();
    printer.Print("message_state = \"serialized\";\n");
    printer.Print("break;\n");
    printer.Outdent();
    printer.Print("case 2:\n");
    printer.Print("case 3:\n");
    printer.Indent();
    printer.Print("message_state = \"get_metadata\";\n");
    printer.Print("break;\n");
    printer.Outdent();
    printer.Print("case 4:\n");
    printer.Print("case 5:\n");
    printer.Print("case 6:\n");
    printer.Print("case 7:\n");
    printer.Indent();
    printer.Print("message_state = \"getters\";\n");
    printer.Outdent();
    printer.Print("default:\n");
    printer.Indent();
    printer.Print("break;\n");
    printer.Outdent();
    printer.Outdent();
    printer.Print("}\n");
    printer.Print("dump_file << elem.first << \" \" << message_state << \" \" << elem.second.descriptor->field_count() << std::endl;\n");
    printer.Print("if (message_state == \"not_used\" || message_state == \"serialized\" || message_state == \"get_metadata\") {\n");
    printer.Indent();
    printer.Print("continue;\n");
    printer.Outdent();
    printer.Print("}\n");
    printer.Print("for (size_t i = 0; i < elem.second.descriptor->field_count(); ++i) {\n");
    printer.Indent();
    printer.Print("int index = i / 32;\n");
    printer.Print("uint32_t index_in_bitmap = 1U << (i % 32);\n");
    printer.Print("int is_used = ((*elem.second.bitmap)[index].load() & index_in_bitmap) >> (i % 32);\n");
    printer.Print("dump_file << \"\\t\" << elem.second.descriptor->field(i)->full_name() << \"\t\" << is_used << std::endl;\n");
    printer.Outdent();
    printer.Print("}\n");
    printer.Outdent();
    printer.Print("}\n");
    printer.Print("dump_file.close();\n");
    printer.Outdent();
    printer.Print("}\n");

    printer.Print("static std::unordered_map<std::string, std::string> DumpStatistics() {\n");
    printer.Indent();
    printer.Print("std::unordered_map<std::string, std::string> result;\n");
    printer.Print("for (const auto& elem: map_) {\n");
    printer.Indent();
    printer.Print("for (size_t i = 0; i < elem.second.descriptor->field_count(); ++i) {\n");
    printer.Indent();
    printer.Print(
        "int index = i / 32;\n"
        "uint32_t index_in_bitmap = 1U << (i % 32);\n"
        "int is_used = ((*elem.second.bitmap)[index].load() & index_in_bitmap) >> (i % 32);\n"
        "result[elem.second.descriptor->field(i)->full_name()] = is_used ? \"used\" : \"unused\";\n"
    );
    printer.Outdent();
    printer.Print("}\n");
    printer.Outdent();
    printer.Print("}\n");
    printer.Print("return result;\n");
    printer.Outdent();
    printer.Print("}\n");
    // End: Get statistics

    printer.Outdent();
    printer.Print("private:\n");
    printer.Indent();
    printer.Print("static std::unordered_map<std::string, TrackerData> map_;\n");
    printer.Outdent();
    printer.Print("};\n\n");
    printer.Print("#include <google/protobuf/port_undef.inc>\n");
}

void GenerateMessageTracker(google::protobuf::compiler::GeneratorContext* generator_context, const google::protobuf::Descriptor* message_type, const std::string& name, std::map<std::string, std::string>& vars) {
    std::unique_ptr<google::protobuf::io::ZeroCopyOutputStream> stream(generator_context->OpenForInsert(name + ".pb.h", "class_scope:" + message_type->full_name()));
    google::protobuf::io::Printer printer(stream.get(), '$');
    printer.Print("private:\n");
    printer.Indent();
    printer.Print("class Tracker {\n");
    printer.Print("public:\n");
    printer.Indent();
    printer.Print("Tracker() {\n");
    printer.Indent();
    printer.Print(vars, "bitmap_ = new std::atomic<uint32_t>[$message_field_number$ / 32 + ($message_field_number$ % 32 != 0)];\n");
    printer.Print(vars, "DynamicTracker::RegisterProto($message_name$::default_instance().GetDescriptor(), (std::atomic<uint32_t>**)&bitmap_, (std::atomic<uint32_t>*)&state_);\n");
    printer.Outdent();
    printer.Print("}\n\n");
    printer.Print("~Tracker() {\n");
    printer.Indent();
    printer.Print("delete [] bitmap_;\n");
    printer.Outdent();
    printer.Print("}\n");

    printer.Outdent();
    //printer.Print("private:\n");
    printer.Indent();
    // should it be static??
    printer.Print(vars, "std::atomic<uint32_t>* bitmap_;\n");
    printer.Print("std::atomic<uint32_t> state_;\n");
    printer.Outdent();
    printer.Print("};\n");

    printer.Outdent();
    printer.Print("public:\n");
    printer.Indent();

    printer.Print("static Tracker tracker_;\n");
}

bool HasMutableGetter(const google::protobuf::FieldDescriptor* field) {
    // if (field->is_repeated())
    //     return true;
    // if (field->label() == google::protobuf::FieldDescriptor::LABEL_REPEATED)
    //     return true;
    switch (field->type()) {
        case google::protobuf::FieldDescriptor::TYPE_BYTES:
        case google::protobuf::FieldDescriptor::TYPE_STRING:
        case google::protobuf::FieldDescriptor::TYPE_MESSAGE:
            return true;
        default:
            return false;
    }
}

bool HasHasGetter(const google::protobuf::FieldDescriptor* field) {
    // if (field->is_optional())
    //     return true;
    // if (field->type() == google::protobuf::FieldDescriptor::TYPE_MESSAGE)
    //     return true;
    return field->has_presence();
}

void ProccessMessage(google::protobuf::compiler::GeneratorContext* generator_context, const google::protobuf::Descriptor* message, const std::string& filename, const std::string& name) {
    std::map<std::string, std::string> vars;
    vars["message_name"] = name;
    vars["message_field_number"] = std::to_string(message->field_count());

    GenerateMessageTracker(generator_context, message, filename, vars);

    {
        std::unique_ptr<google::protobuf::io::ZeroCopyOutputStream> out_cc_namespace_scope(generator_context->OpenForInsert(filename + ".pb.cc", "namespace_scope"));
        google::protobuf::io::Printer pb_namespace_scope_printer(out_cc_namespace_scope.get(), '$');
        pb_namespace_scope_printer.Print((name + "::Tracker " + name + "::tracker_ = {};\n").c_str());
    }

    if (stripped_messages.find(message->full_name()) != stripped_messages.end()) {
        return;
    }

    { // InternalSerialize
        std::unique_ptr<google::protobuf::io::ZeroCopyOutputStream> out_h_getters(generator_context->OpenForInsert(filename + ".pb.cc", "serialize_to_array_start:" + message->full_name()));
        google::protobuf::io::Printer pb_includes(out_h_getters.get(), '$');
        pb_includes.Print("tracker_.state_.fetch_or(1);\n");
    }

    for (size_t j = 0; j < message->field_count(); ++j) {
        auto field = message->field(j);

        if (stripped_fields.find(field->full_name()) != stripped_fields.end()) {
            continue;
        }

        std::vector<std::string> points;

        if (field->is_map()) {
            points.push_back("field_map:");
        } else {
            points.push_back("field_get:");
        }

        if (HasMutableGetter(field)) {
            if (field->is_map()) {
                points.push_back("field_mutable_map:");
            } else {
                points.push_back("field_mutable:");
            }
        }

        if (HasHasGetter(field)) {
            points.push_back("field_has:");
        }

        if (field->is_repeated()) {
            if (!field->is_map()) {
                points.push_back("field_list:");
            }
            points.push_back("field_size:");
        }

        std::string field_name_has_point = field->full_name();
        const auto oneof_desc = field->real_containing_oneof();
        if (oneof_desc) {
            auto pos = field_name_has_point.find_last_of('.') + 1;
            field_name_has_point[pos] = std::toupper(field_name_has_point[pos]);
        }

        for (const auto &point : points) {
            std::unique_ptr<google::protobuf::io::ZeroCopyOutputStream> out_h_getters;
            if (point == "field_has:" && oneof_desc) {
                out_h_getters.reset(generator_context->OpenForInsert(filename + ".pb.h", point + field_name_has_point));
            } else {
                out_h_getters.reset(generator_context->OpenForInsert(filename + ".pb.h", point + field->full_name()));
            }
            google::protobuf::io::Printer pb_includes(out_h_getters.get(), '$');

            vars["array_index"] = std::to_string(j / 32);
            vars["shift_index"] = std::to_string(j % 32);

            pb_includes.Print(vars, "tracker_.bitmap_[$array_index$].fetch_or(1U << $shift_index$);\n");
            pb_includes.Print(vars, "tracker_.state_.fetch_or(4);\n");
        }
    }
}

void AddMessage(std::map<std::string, std::pair<const google::protobuf::Descriptor*, std::string>>& messages, const google::protobuf::Descriptor* message, const std::string& prefix) {
    for (size_t j = 0; j < message->field_count(); ++j) {
        auto field = message->field(j);

        const auto inner_message = field->message_type();

        if (inner_message && !field->is_map()) {
            std::string inner_name = prefix + "_" + inner_message->name();
            messages.insert({inner_message->full_name(), {inner_message, inner_name}});
            AddMessage(messages, inner_message, inner_name);
        }
    }
}

bool ProfilerGenerator::Generate(const google::protobuf::FileDescriptor *file,
                          const std::string &parameter,
                          google::protobuf::compiler::GeneratorContext *generator_context,
                          std::string *error) const
{
    std::vector<std::pair<std::string, std::string> > options;
    google::protobuf::compiler::ParseGeneratorParameter(parameter, &options);

    std::string access_info_map_path;
    for (int i = 0; i < options.size(); i++) {
        if (options[i].first == "unused_field_stripping") {
            is_fields_stripped = true;
        } else if (options[i].first == "access_info_map") {
            access_info_map_path = options[i].second;
        }
    }

    if (is_fields_stripped) {
        ProccessAccessInfoMap(access_info_map_path);
    }

    auto filename = file->name();
    filename = filename.substr(0, filename.size() - 6);

    GenerateTrackerFile(generator_context);

    {
        std::unique_ptr<google::protobuf::io::ZeroCopyOutputStream> out_global_include_h(generator_context->OpenForInsert(filename + ".pb.h", "includes"));
        google::protobuf::io::Printer include_scope_printer(out_global_include_h.get(), '$');
        include_scope_printer.Print("#include \"tracker.h\"\n");
    }

    std::map<std::string, std::pair<const google::protobuf::Descriptor*, std::string>> messages;

    for (size_t i = 0; i < file->message_type_count(); ++i) {
        auto message = file->message_type(i);
        messages.insert({message->full_name(), {message, message->name()}});
        AddMessage(messages, message, message->name());
    }

    for (const auto& message: messages) {
        ProccessMessage(generator_context, message.second.first, filename, message.second.second);
    }

    return true;
}

uint64_t ProfilerGenerator::GetSupportedFeatures() const {
    // Indicate that this code generator supports proto3 optional fields.
    // (Note: don't release your code generator with this flag set until you
    // have actually added and tested your proto3 support!)
    return FEATURE_PROTO3_OPTIONAL;
}