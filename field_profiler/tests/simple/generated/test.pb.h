// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: test.proto

#ifndef GOOGLE_PROTOBUF_INCLUDED_test_2eproto
#define GOOGLE_PROTOBUF_INCLUDED_test_2eproto

#include <limits>
#include <string>

#include <google/protobuf/port_def.inc>
#if PROTOBUF_VERSION < 3014000
#error This file was generated by a newer version of protoc which is
#error incompatible with your Protocol Buffer headers. Please update
#error your headers.
#endif
#if 3014000 < PROTOBUF_MIN_PROTOC_VERSION
#error This file was generated by an older version of protoc which is
#error incompatible with your Protocol Buffer headers. Please
#error regenerate this file with a newer version of protoc.
#endif

#include <google/protobuf/port_undef.inc>
#include <google/protobuf/io/coded_stream.h>
#include <google/protobuf/arena.h>
#include <google/protobuf/arenastring.h>
#include <google/protobuf/generated_message_table_driven.h>
#include <google/protobuf/generated_message_util.h>
#include <google/protobuf/metadata_lite.h>
#include <google/protobuf/generated_message_reflection.h>
#include <google/protobuf/message.h>
#include <google/protobuf/repeated_field.h>  // IWYU pragma: export
#include <google/protobuf/extension_set.h>  // IWYU pragma: export
#include <google/protobuf/unknown_field_set.h>
#include "tracker.h"
// @@protoc_insertion_point(includes)
#include <google/protobuf/port_def.inc>
#define PROTOBUF_INTERNAL_EXPORT_test_2eproto
PROTOBUF_NAMESPACE_OPEN
namespace internal {
class AnyMetadata;
}  // namespace internal
PROTOBUF_NAMESPACE_CLOSE

// Internal implementation detail -- do not use these members.
struct TableStruct_test_2eproto {
  static const ::PROTOBUF_NAMESPACE_ID::internal::ParseTableField entries[]
    PROTOBUF_SECTION_VARIABLE(protodesc_cold);
  static const ::PROTOBUF_NAMESPACE_ID::internal::AuxiliaryParseTableField aux[]
    PROTOBUF_SECTION_VARIABLE(protodesc_cold);
  static const ::PROTOBUF_NAMESPACE_ID::internal::ParseTable schema[1]
    PROTOBUF_SECTION_VARIABLE(protodesc_cold);
  static const ::PROTOBUF_NAMESPACE_ID::internal::FieldMetadata field_metadata[];
  static const ::PROTOBUF_NAMESPACE_ID::internal::SerializationTable serialization_table[];
  static const ::PROTOBUF_NAMESPACE_ID::uint32 offsets[];
};
extern const ::PROTOBUF_NAMESPACE_ID::internal::DescriptorTable descriptor_table_test_2eproto;
::PROTOBUF_NAMESPACE_ID::Metadata descriptor_table_test_2eproto_metadata_getter(int index);
namespace test {
class ABC;
struct ABCDefaultTypeInternal;
extern ABCDefaultTypeInternal _ABC_default_instance_;
}  // namespace test
PROTOBUF_NAMESPACE_OPEN
template<> ::test::ABC* Arena::CreateMaybeMessage<::test::ABC>(Arena*);
PROTOBUF_NAMESPACE_CLOSE
namespace test {

// ===================================================================

class ABC PROTOBUF_FINAL :
    public ::PROTOBUF_NAMESPACE_ID::Message /* @@protoc_insertion_point(class_definition:test.ABC) */ {
 public:
  inline ABC() : ABC(nullptr) {}
  virtual ~ABC();
  explicit constexpr ABC(::PROTOBUF_NAMESPACE_ID::internal::ConstantInitialized);

  ABC(const ABC& from);
  ABC(ABC&& from) noexcept
    : ABC() {
    *this = ::std::move(from);
  }

  inline ABC& operator=(const ABC& from) {
    CopyFrom(from);
    return *this;
  }
  inline ABC& operator=(ABC&& from) noexcept {
    if (GetArena() == from.GetArena()) {
      if (this != &from) InternalSwap(&from);
    } else {
      CopyFrom(from);
    }
    return *this;
  }

  static const ::PROTOBUF_NAMESPACE_ID::Descriptor* descriptor() {
    return GetDescriptor();
  }
  static const ::PROTOBUF_NAMESPACE_ID::Descriptor* GetDescriptor() {
    return GetMetadataStatic().descriptor;
  }
  static const ::PROTOBUF_NAMESPACE_ID::Reflection* GetReflection() {
    return GetMetadataStatic().reflection;
  }
  static const ABC& default_instance() {
    return *internal_default_instance();
  }
  static inline const ABC* internal_default_instance() {
    return reinterpret_cast<const ABC*>(
               &_ABC_default_instance_);
  }
  static constexpr int kIndexInFileMessages =
    0;

  friend void swap(ABC& a, ABC& b) {
    a.Swap(&b);
  }
  inline void Swap(ABC* other) {
    if (other == this) return;
    if (GetArena() == other->GetArena()) {
      InternalSwap(other);
    } else {
      ::PROTOBUF_NAMESPACE_ID::internal::GenericSwap(this, other);
    }
  }
  void UnsafeArenaSwap(ABC* other) {
    if (other == this) return;
    GOOGLE_DCHECK(GetArena() == other->GetArena());
    InternalSwap(other);
  }

  // implements Message ----------------------------------------------

  inline ABC* New() const final {
    return CreateMaybeMessage<ABC>(nullptr);
  }

  ABC* New(::PROTOBUF_NAMESPACE_ID::Arena* arena) const final {
    return CreateMaybeMessage<ABC>(arena);
  }
  void CopyFrom(const ::PROTOBUF_NAMESPACE_ID::Message& from) final;
  void MergeFrom(const ::PROTOBUF_NAMESPACE_ID::Message& from) final;
  void CopyFrom(const ABC& from);
  void MergeFrom(const ABC& from);
  PROTOBUF_ATTRIBUTE_REINITIALIZES void Clear() final;
  bool IsInitialized() const final;

  size_t ByteSizeLong() const final;
  const char* _InternalParse(const char* ptr, ::PROTOBUF_NAMESPACE_ID::internal::ParseContext* ctx) final;
  ::PROTOBUF_NAMESPACE_ID::uint8* _InternalSerialize(
      ::PROTOBUF_NAMESPACE_ID::uint8* target, ::PROTOBUF_NAMESPACE_ID::io::EpsCopyOutputStream* stream) const final;
  int GetCachedSize() const final { return _cached_size_.Get(); }

  private:
  inline void SharedCtor();
  inline void SharedDtor();
  void SetCachedSize(int size) const final;
  void InternalSwap(ABC* other);
  friend class ::PROTOBUF_NAMESPACE_ID::internal::AnyMetadata;
  static ::PROTOBUF_NAMESPACE_ID::StringPiece FullMessageName() {
    return "test.ABC";
  }
  protected:
  explicit ABC(::PROTOBUF_NAMESPACE_ID::Arena* arena);
  private:
  static void ArenaDtor(void* object);
  inline void RegisterArenaDtor(::PROTOBUF_NAMESPACE_ID::Arena* arena);
  public:

  ::PROTOBUF_NAMESPACE_ID::Metadata GetMetadata() const final;
  private:
  static ::PROTOBUF_NAMESPACE_ID::Metadata GetMetadataStatic() {
    return ::descriptor_table_test_2eproto_metadata_getter(kIndexInFileMessages);
  }

  public:

  // nested types ----------------------------------------------------

  // accessors -------------------------------------------------------

  enum : int {
    kBFieldNumber = 2,
    kAFieldNumber = 1,
  };
  // string b = 2;
  bool has_b() const;
  private:
  bool _internal_has_b() const;
  public:
  void clear_b();
  const std::string& b() const;
  void set_b(const std::string& value);
  void set_b(std::string&& value);
  void set_b(const char* value);
  void set_b(const char* value, size_t size);
  std::string* mutable_b();
  std::string* release_b();
  void set_allocated_b(std::string* b);
  private:
  const std::string& _internal_b() const;
  void _internal_set_b(const std::string& value);
  std::string* _internal_mutable_b();
  public:

  // int64 a = 1;
  void clear_a();
  ::PROTOBUF_NAMESPACE_ID::int64 a() const;
  void set_a(::PROTOBUF_NAMESPACE_ID::int64 value);
  private:
  ::PROTOBUF_NAMESPACE_ID::int64 _internal_a() const;
  void _internal_set_a(::PROTOBUF_NAMESPACE_ID::int64 value);
  public:

  private:
    class Tracker {
    public:
      Tracker() {
        bitmap_ = new std::atomic<uint32_t>[2 / 32 + (2 % 32 != 0)];
        DynamicTracker::RegisterProto(ABC::default_instance().GetDescriptor(), (std::atomic<uint32_t>**)&bitmap_);
      }
  
      ~Tracker() {
        delete [] bitmap_;
      }
      std::atomic<uint32_t>* bitmap_;
    };
  public:
    static Tracker tracker_;
  // @@protoc_insertion_point(class_scope:test.ABC)
 private:
  class _Internal;

  template <typename T> friend class ::PROTOBUF_NAMESPACE_ID::Arena::InternalHelper;
  typedef void InternalArenaConstructable_;
  typedef void DestructorSkippable_;
  ::PROTOBUF_NAMESPACE_ID::internal::HasBits<1> _has_bits_;
  mutable ::PROTOBUF_NAMESPACE_ID::internal::CachedSize _cached_size_;
  ::PROTOBUF_NAMESPACE_ID::internal::ArenaStringPtr b_;
  ::PROTOBUF_NAMESPACE_ID::int64 a_;
  friend struct ::TableStruct_test_2eproto;
};
// ===================================================================


// ===================================================================

#ifdef __GNUC__
  #pragma GCC diagnostic push
  #pragma GCC diagnostic ignored "-Wstrict-aliasing"
#endif  // __GNUC__
// ABC

// int64 a = 1;
inline void ABC::clear_a() {
  a_ = PROTOBUF_LONGLONG(0);
}
inline ::PROTOBUF_NAMESPACE_ID::int64 ABC::_internal_a() const {
  return a_;
}
inline ::PROTOBUF_NAMESPACE_ID::int64 ABC::a() const {
  tracker_.bitmap_[0].store((tracker_.bitmap_[0].load()) | (1U << 0));
  // @@protoc_insertion_point(field_get:test.ABC.a)
  return _internal_a();
}
inline void ABC::_internal_set_a(::PROTOBUF_NAMESPACE_ID::int64 value) {
  
  a_ = value;
}
inline void ABC::set_a(::PROTOBUF_NAMESPACE_ID::int64 value) {
  _internal_set_a(value);
  // @@protoc_insertion_point(field_set:test.ABC.a)
}

// string b = 2;
inline bool ABC::_internal_has_b() const {
  bool value = (_has_bits_[0] & 0x00000001u) != 0;
  return value;
}
inline bool ABC::has_b() const {
  tracker_.bitmap_[0].store((tracker_.bitmap_[0].load()) | (1U << 1));
  // @@protoc_insertion_point(field_has:test.ABC.b)
  return _internal_has_b();
}
inline void ABC::clear_b() {
  b_.ClearToEmpty();
  _has_bits_[0] &= ~0x00000001u;
}
inline const std::string& ABC::b() const {
  tracker_.bitmap_[0].store((tracker_.bitmap_[0].load()) | (1U << 1));
  // @@protoc_insertion_point(field_get:test.ABC.b)
  return _internal_b();
}
inline void ABC::set_b(const std::string& value) {
  _internal_set_b(value);
  // @@protoc_insertion_point(field_set:test.ABC.b)
}
inline std::string* ABC::mutable_b() {
  tracker_.bitmap_[0].store((tracker_.bitmap_[0].load()) | (1U << 1));
  // @@protoc_insertion_point(field_mutable:test.ABC.b)
  return _internal_mutable_b();
}
inline const std::string& ABC::_internal_b() const {
  return b_.Get();
}
inline void ABC::_internal_set_b(const std::string& value) {
  _has_bits_[0] |= 0x00000001u;
  b_.Set(::PROTOBUF_NAMESPACE_ID::internal::ArenaStringPtr::EmptyDefault{}, value, GetArena());
}
inline void ABC::set_b(std::string&& value) {
  _has_bits_[0] |= 0x00000001u;
  b_.Set(
    ::PROTOBUF_NAMESPACE_ID::internal::ArenaStringPtr::EmptyDefault{}, ::std::move(value), GetArena());
  // @@protoc_insertion_point(field_set_rvalue:test.ABC.b)
}
inline void ABC::set_b(const char* value) {
  GOOGLE_DCHECK(value != nullptr);
  _has_bits_[0] |= 0x00000001u;
  b_.Set(::PROTOBUF_NAMESPACE_ID::internal::ArenaStringPtr::EmptyDefault{}, ::std::string(value), GetArena());
  // @@protoc_insertion_point(field_set_char:test.ABC.b)
}
inline void ABC::set_b(const char* value,
    size_t size) {
  _has_bits_[0] |= 0x00000001u;
  b_.Set(::PROTOBUF_NAMESPACE_ID::internal::ArenaStringPtr::EmptyDefault{}, ::std::string(
      reinterpret_cast<const char*>(value), size), GetArena());
  // @@protoc_insertion_point(field_set_pointer:test.ABC.b)
}
inline std::string* ABC::_internal_mutable_b() {
  _has_bits_[0] |= 0x00000001u;
  return b_.Mutable(::PROTOBUF_NAMESPACE_ID::internal::ArenaStringPtr::EmptyDefault{}, GetArena());
}
inline std::string* ABC::release_b() {
  // @@protoc_insertion_point(field_release:test.ABC.b)
  if (!_internal_has_b()) {
    return nullptr;
  }
  _has_bits_[0] &= ~0x00000001u;
  return b_.ReleaseNonDefault(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited(), GetArena());
}
inline void ABC::set_allocated_b(std::string* b) {
  if (b != nullptr) {
    _has_bits_[0] |= 0x00000001u;
  } else {
    _has_bits_[0] &= ~0x00000001u;
  }
  b_.SetAllocated(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited(), b,
      GetArena());
  // @@protoc_insertion_point(field_set_allocated:test.ABC.b)
}

#ifdef __GNUC__
  #pragma GCC diagnostic pop
#endif  // __GNUC__

// @@protoc_insertion_point(namespace_scope)

}  // namespace test

// @@protoc_insertion_point(global_scope)

#include <google/protobuf/port_undef.inc>
#endif  // GOOGLE_PROTOBUF_INCLUDED_GOOGLE_PROTOBUF_INCLUDED_test_2eproto
