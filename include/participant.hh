// -*- C++ -*-
// Automatically generated from include/participant.x.
// DO NOT EDIT or your changes may be overwritten

#ifndef __XDR_INCLUDE_PARTICIPANT_HH_INCLUDED__
#define __XDR_INCLUDE_PARTICIPANT_HH_INCLUDED__ 1

#include <xdrpp/types.h>

 #include "two_phrase_commit_common.hh"

struct participant_api_v1 {
  static constexpr std::uint32_t program = 1074036872;
  static constexpr const char *program_name = "participant_api";
  static constexpr std::uint32_t version = 1;
  static constexpr const char *version_name = "participant_api_v1";

  struct request_vote_t {
    using interface_type = participant_api_v1;
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

  struct request_response_t {
    using interface_type = participant_api_v1;
    static constexpr std::uint32_t proc = 2;
    static constexpr const char *proc_name = "request_response";
    using arg_type = ResponseInfo;
    using arg_wire_type = ResponseInfo;
    using res_type = void;
    using res_wire_type = xdr::xdr_void;
    
    template<typename C, typename...A> static auto
    dispatch(C &&c, A &&...a) ->
    decltype(c.request_response(std::forward<A>(a)...)) {
      return c.request_response(std::forward<A>(a)...);
    }
    
    template<typename C, typename DropIfVoid, typename...A> static auto
    dispatch_dropvoid(C &&c, DropIfVoid &&d, A &&...a) ->
    decltype(c.request_response(std::forward<DropIfVoid>(d), std::forward<A>(a)...)) {
      return c.request_response(std::forward<DropIfVoid>(d), std::forward<A>(a)...);
    }
  };

  struct request_commit_t {
    using interface_type = participant_api_v1;
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
      t.template dispatch<request_response_t>(std::forward<A>(a)...);
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
    request_response(_XDRARGS &&..._xdr_args) ->
    decltype(this->_XDRBASE::template invoke<request_response_t>(_xdr_args...)) {
      return this->_XDRBASE::template invoke<request_response_t>(_xdr_args...);
    }

    template<typename..._XDRARGS> auto
    request_commit(_XDRARGS &&..._xdr_args) ->
    decltype(this->_XDRBASE::template invoke<request_commit_t>(_xdr_args...)) {
      return this->_XDRBASE::template invoke<request_commit_t>(_xdr_args...);
    }
  };
};

#endif // !__XDR_INCLUDE_PARTICIPANT_HH_INCLUDED__
