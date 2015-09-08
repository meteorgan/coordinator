// -*- C++ -*-
// Automatically generated from include/participant.x.
// DO NOT EDIT or your changes may be overwritten

#ifndef __XDR_INCLUDE_PARTICIPANT_HH_INCLUDED__
#define __XDR_INCLUDE_PARTICIPANT_HH_INCLUDED__ 1

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

struct ReponseInfo {
  OpInt opNum{};
  RequestResponse response{};
  ParticipantId participantId{};
};
namespace xdr {
template<> struct xdr_traits<::ReponseInfo>
  : xdr_struct_base<field_ptr<::ReponseInfo,
                              decltype(::ReponseInfo::opNum),
                              &::ReponseInfo::opNum>,
                    field_ptr<::ReponseInfo,
                              decltype(::ReponseInfo::response),
                              &::ReponseInfo::response>,
                    field_ptr<::ReponseInfo,
                              decltype(::ReponseInfo::participantId),
                              &::ReponseInfo::participantId>> {
  template<typename Archive> static void
  save(Archive &ar, const ::ReponseInfo &obj) {
    archive(ar, obj.opNum, "opNum");
    archive(ar, obj.response, "response");
    archive(ar, obj.participantId, "participantId");
  }
  template<typename Archive> static void
  load(Archive &ar, ::ReponseInfo &obj) {
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

struct participantApi_v1 {
  static constexpr std::uint32_t program = 1074036872;
  static constexpr const char *program_name = "participant_api";
  static constexpr std::uint32_t version = 1;
  static constexpr const char *version_name = "participantApi_v1";

  struct request_vote_t {
    using interface_type = participantApi_v1;
    static constexpr std::uint32_t proc = 1;
    static constexpr const char *proc_name = "request_vote";
    using arg_type = RequestInfo;
    using arg_wire_type = RequestInfo;
    using res_type = void;
    using res_wire_type = xdr::xdr_void;
    
    template<typename C, typename...A> static auto
    dispatch(C &&c, A &&...a) ->
    decltype(c.request_vote(std::forward<A>(a)...)) {
      return c.request_vote(std::forward<A>(a)...);
    }
    
    template<typename C, typename DropIfVoid, typename...A> static auto
    dispatch_dropvoid(C &&c, DropIfVoid &&d, A &&...a) ->
    decltype(c.request_vote(std::forward<DropIfVoid>(d), std::forward<A>(a)...)) {
      return c.request_vote(std::forward<DropIfVoid>(d), std::forward<A>(a)...);
    }
  };

  struct response_vote_t {
    using interface_type = participantApi_v1;
    static constexpr std::uint32_t proc = 2;
    static constexpr const char *proc_name = "response_vote";
    using arg_type = ReponseInfo;
    using arg_wire_type = ReponseInfo;
    using res_type = void;
    using res_wire_type = xdr::xdr_void;
    
    template<typename C, typename...A> static auto
    dispatch(C &&c, A &&...a) ->
    decltype(c.response_vote(std::forward<A>(a)...)) {
      return c.response_vote(std::forward<A>(a)...);
    }
    
    template<typename C, typename DropIfVoid, typename...A> static auto
    dispatch_dropvoid(C &&c, DropIfVoid &&d, A &&...a) ->
    decltype(c.response_vote(std::forward<DropIfVoid>(d), std::forward<A>(a)...)) {
      return c.response_vote(std::forward<DropIfVoid>(d), std::forward<A>(a)...);
    }
  };

  struct request_commit_t {
    using interface_type = participantApi_v1;
    static constexpr std::uint32_t proc = 3;
    static constexpr const char *proc_name = "request_commit";
    using arg_type = CommitInfo;
    using arg_wire_type = CommitInfo;
    using res_type = void;
    using res_wire_type = xdr::xdr_void;
    
    template<typename C, typename...A> static auto
    dispatch(C &&c, A &&...a) ->
    decltype(c.request_commit(std::forward<A>(a)...)) {
      return c.request_commit(std::forward<A>(a)...);
    }
    
    template<typename C, typename DropIfVoid, typename...A> static auto
    dispatch_dropvoid(C &&c, DropIfVoid &&d, A &&...a) ->
    decltype(c.request_commit(std::forward<DropIfVoid>(d), std::forward<A>(a)...)) {
      return c.request_commit(std::forward<DropIfVoid>(d), std::forward<A>(a)...);
    }
  };

  template<typename T, typename...A> static bool
  call_dispatch(T &&t, std::uint32_t proc, A &&...a) {
    switch(proc) {
    case 1:
      t.template dispatch<request_vote_t>(std::forward<A>(a)...);
      return true;
    case 2:
      t.template dispatch<response_vote_t>(std::forward<A>(a)...);
      return true;
    case 3:
      t.template dispatch<request_commit_t>(std::forward<A>(a)...);
      return true;
    }
    return false;
  }

  template<typename _XDRBASE> struct client : _XDRBASE {
    using _XDRBASE::_XDRBASE;

    template<typename..._XDRARGS> auto
    request_vote(_XDRARGS &&..._xdr_args) ->
    decltype(this->_XDRBASE::template invoke<request_vote_t>(_xdr_args...)) {
      return this->_XDRBASE::template invoke<request_vote_t>(_xdr_args...);
    }

    template<typename..._XDRARGS> auto
    response_vote(_XDRARGS &&..._xdr_args) ->
    decltype(this->_XDRBASE::template invoke<response_vote_t>(_xdr_args...)) {
      return this->_XDRBASE::template invoke<response_vote_t>(_xdr_args...);
    }

    template<typename..._XDRARGS> auto
    request_commit(_XDRARGS &&..._xdr_args) ->
    decltype(this->_XDRBASE::template invoke<request_commit_t>(_xdr_args...)) {
      return this->_XDRBASE::template invoke<request_commit_t>(_xdr_args...);
    }
  };
};

#endif // !__XDR_INCLUDE_PARTICIPANT_HH_INCLUDED__
