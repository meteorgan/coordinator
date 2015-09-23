// -*- C++ -*-
// Automatically generated from include/two_phrase_commit_common.x.
// DO NOT EDIT or your changes may be overwritten

#ifndef __XDR_INCLUDE_TWO_PHRASE_COMMIT_COMMON_HH_INCLUDED__
#define __XDR_INCLUDE_TWO_PHRASE_COMMIT_COMMON_HH_INCLUDED__ 1

#include <xdrpp/types.h>

 #include "server.hh"

using ParticipantId = std::uint64_t;
using OpInt = std::uint64_t;

enum OpType : std::uint32_t {
  CREATE,
  SET,
  REMOVE,
};
namespace xdr {
template<> struct xdr_traits<::OpType>
  : xdr_integral_base<::OpType, std::uint32_t> {
  static constexpr bool is_enum = true;
  static constexpr bool is_numeric = false;
  static const char *enum_name(::OpType val) {
    switch (val) {
    case ::CREATE:
      return "CREATE";
    case ::SET:
      return "SET";
    case ::REMOVE:
      return "REMOVE";
    default:
      return nullptr;
    }
  }
};
}

enum RequestResponse : std::uint32_t {
  VOTE_COMMIT,
  VOTE_ABORT,
};
namespace xdr {
template<> struct xdr_traits<::RequestResponse>
  : xdr_integral_base<::RequestResponse, std::uint32_t> {
  static constexpr bool is_enum = true;
  static constexpr bool is_numeric = false;
  static const char *enum_name(::RequestResponse val) {
    switch (val) {
    case ::VOTE_COMMIT:
      return "VOTE_COMMIT";
    case ::VOTE_ABORT:
      return "VOTE_ABORT";
    default:
      return nullptr;
    }
  }
};
}

enum CommitOp : std::uint32_t {
  GLOABL_COMMIT,
  GLOBAL_ABORT,
};
namespace xdr {
template<> struct xdr_traits<::CommitOp>
  : xdr_integral_base<::CommitOp, std::uint32_t> {
  static constexpr bool is_enum = true;
  static constexpr bool is_numeric = false;
  static const char *enum_name(::CommitOp val) {
    switch (val) {
    case ::GLOABL_COMMIT:
      return "GLOABL_COMMIT";
    case ::GLOBAL_ABORT:
      return "GLOBAL_ABORT";
    default:
      return nullptr;
    }
  }
};
}

struct CommitRequest {
  kvpair kv{};
  OpType opType{};
};
namespace xdr {
template<> struct xdr_traits<::CommitRequest>
  : xdr_struct_base<field_ptr<::CommitRequest,
                              decltype(::CommitRequest::kv),
                              &::CommitRequest::kv>,
                    field_ptr<::CommitRequest,
                              decltype(::CommitRequest::opType),
                              &::CommitRequest::opType>> {
  template<typename Archive> static void
  save(Archive &ar, const ::CommitRequest &obj) {
    archive(ar, obj.kv, "kv");
    archive(ar, obj.opType, "opType");
  }
  template<typename Archive> static void
  load(Archive &ar, ::CommitRequest &obj) {
    archive(ar, obj.kv, "kv");
    archive(ar, obj.opType, "opType");
  }
};
}

struct RequestInfo {
  kvpair kv{};
  OpType opType{};
  OpInt opNum{};
  ParticipantId participantId{};
};
namespace xdr {
template<> struct xdr_traits<::RequestInfo>
  : xdr_struct_base<field_ptr<::RequestInfo,
                              decltype(::RequestInfo::kv),
                              &::RequestInfo::kv>,
                    field_ptr<::RequestInfo,
                              decltype(::RequestInfo::opType),
                              &::RequestInfo::opType>,
                    field_ptr<::RequestInfo,
                              decltype(::RequestInfo::opNum),
                              &::RequestInfo::opNum>,
                    field_ptr<::RequestInfo,
                              decltype(::RequestInfo::participantId),
                              &::RequestInfo::participantId>> {
  template<typename Archive> static void
  save(Archive &ar, const ::RequestInfo &obj) {
    archive(ar, obj.kv, "kv");
    archive(ar, obj.opType, "opType");
    archive(ar, obj.opNum, "opNum");
    archive(ar, obj.participantId, "participantId");
  }
  template<typename Archive> static void
  load(Archive &ar, ::RequestInfo &obj) {
    archive(ar, obj.kv, "kv");
    archive(ar, obj.opType, "opType");
    archive(ar, obj.opNum, "opNum");
    archive(ar, obj.participantId, "participantId");
  }
};
}

struct ResponseInfo {
  OpInt opNum{};
  RequestResponse response{};
  ParticipantId participantId{};
};
namespace xdr {
template<> struct xdr_traits<::ResponseInfo>
  : xdr_struct_base<field_ptr<::ResponseInfo,
                              decltype(::ResponseInfo::opNum),
                              &::ResponseInfo::opNum>,
                    field_ptr<::ResponseInfo,
                              decltype(::ResponseInfo::response),
                              &::ResponseInfo::response>,
                    field_ptr<::ResponseInfo,
                              decltype(::ResponseInfo::participantId),
                              &::ResponseInfo::participantId>> {
  template<typename Archive> static void
  save(Archive &ar, const ::ResponseInfo &obj) {
    archive(ar, obj.opNum, "opNum");
    archive(ar, obj.response, "response");
    archive(ar, obj.participantId, "participantId");
  }
  template<typename Archive> static void
  load(Archive &ar, ::ResponseInfo &obj) {
    archive(ar, obj.opNum, "opNum");
    archive(ar, obj.response, "response");
    archive(ar, obj.participantId, "participantId");
  }
};
}

struct CommitInfo {
  CommitOp commitOp{};
  OpInt opNum{};
  ParticipantId participantId{};
};
namespace xdr {
template<> struct xdr_traits<::CommitInfo>
  : xdr_struct_base<field_ptr<::CommitInfo,
                              decltype(::CommitInfo::commitOp),
                              &::CommitInfo::commitOp>,
                    field_ptr<::CommitInfo,
                              decltype(::CommitInfo::opNum),
                              &::CommitInfo::opNum>,
                    field_ptr<::CommitInfo,
                              decltype(::CommitInfo::participantId),
                              &::CommitInfo::participantId>> {
  template<typename Archive> static void
  save(Archive &ar, const ::CommitInfo &obj) {
    archive(ar, obj.commitOp, "commitOp");
    archive(ar, obj.opNum, "opNum");
    archive(ar, obj.participantId, "participantId");
  }
  template<typename Archive> static void
  load(Archive &ar, ::CommitInfo &obj) {
    archive(ar, obj.commitOp, "commitOp");
    archive(ar, obj.opNum, "opNum");
    archive(ar, obj.participantId, "participantId");
  }
};
}

#endif // !__XDR_INCLUDE_TWO_PHRASE_COMMIT_COMMON_HH_INCLUDED__
