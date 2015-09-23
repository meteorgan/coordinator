// -*- C++ -*-
// Automatically generated from include/server.x.
// DO NOT EDIT or your changes may be overwritten

#ifndef __XDR_INCLUDE_SERVER_HH_INCLUDED__
#define __XDR_INCLUDE_SERVER_HH_INCLUDED__ 1

#include <xdrpp/types.h>

using longstring = xdr::xstring<>;

struct kvpair {
  xdr::xstring<512> key{};
  xdr::xstring<> val{};
};
namespace xdr {
template<> struct xdr_traits<::kvpair>
  : xdr_struct_base<field_ptr<::kvpair,
                              decltype(::kvpair::key),
                              &::kvpair::key>,
                    field_ptr<::kvpair,
                              decltype(::kvpair::val),
                              &::kvpair::val>> {
  template<typename Archive> static void
  save(Archive &ar, const ::kvpair &obj) {
    archive(ar, obj.key, "key");
    archive(ar, obj.val, "val");
  }
  template<typename Archive> static void
  load(Archive &ar, ::kvpair &obj) {
    archive(ar, obj.key, "key");
    archive(ar, obj.val, "val");
  }
};
}

enum ServerError : std::uint32_t {
  NONE,
  KEY_NOT_FOUND_ERROR,
  KEY_NO_PARENT,
  KEY_HAS_CHILDREN,
  KEY_MALFORMED,
  KEY_DUPLICATE,
  QUORUM_NOT_REACHED,
};
namespace xdr {
template<> struct xdr_traits<::ServerError>
  : xdr_integral_base<::ServerError, std::uint32_t> {
  static constexpr bool is_enum = true;
  static constexpr bool is_numeric = false;
  static const char *enum_name(::ServerError val) {
    switch (val) {
    case ::NONE:
      return "NONE";
    case ::KEY_NOT_FOUND_ERROR:
      return "KEY_NOT_FOUND_ERROR";
    case ::KEY_NO_PARENT:
      return "KEY_NO_PARENT";
    case ::KEY_HAS_CHILDREN:
      return "KEY_HAS_CHILDREN";
    case ::KEY_MALFORMED:
      return "KEY_MALFORMED";
    case ::KEY_DUPLICATE:
      return "KEY_DUPLICATE";
    case ::QUORUM_NOT_REACHED:
      return "QUORUM_NOT_REACHED";
    default:
      return nullptr;
    }
  }
};
}

struct Result {
private:
  std::uint32_t discriminant_;
  union {
    xdr::xstring<> val_;
    xdr::xvector<longstring> keys_;
    ServerError error_;
  };

public:
  static_assert (sizeof (unsigned) <= 4, "union discriminant must be 4 bytes");

  static constexpr int _xdr_field_number(std::uint32_t which) {
    return which == 1 ? 1
      : which == 2 ? 2
      : 3;
  }
  template<typename _F, typename...A> static bool
  _xdr_with_mem_ptr(_F &_f, std::uint32_t which, A&&...a) {
    switch (which) {
    case 1:
      _f(&Result::val_, std::forward<A>(a)...);
      return true;
    case 2:
      _f(&Result::keys_, std::forward<A>(a)...);
      return true;
    default:
      _f(&Result::error_, std::forward<A>(a)...);
      return true;
    }
  }

  std::uint32_t _xdr_discriminant() const { return discriminant_; }
  void _xdr_discriminant(std::uint32_t which, bool validate = true) {
    int fnum = _xdr_field_number(which);
    if (fnum < 0 && validate)
      throw xdr::xdr_bad_discriminant("bad value of discriminant in Result");
    if (fnum != _xdr_field_number(discriminant_)) {
      this->~Result();
      discriminant_ = which;
      _xdr_with_mem_ptr(xdr::field_constructor, discriminant_, *this);
    }
  }
  Result(std::uint32_t which = std::uint32_t{}) : discriminant_(which) {
    _xdr_with_mem_ptr(xdr::field_constructor, discriminant_, *this);
  }
  Result(const Result &source) : discriminant_(source.discriminant_) {
    _xdr_with_mem_ptr(xdr::field_constructor, discriminant_, *this, source);
  }
  Result(Result &&source) : discriminant_(source.discriminant_) {
    _xdr_with_mem_ptr(xdr::field_constructor, discriminant_, *this,
                      std::move(source));
  }
  ~Result() { _xdr_with_mem_ptr(xdr::field_destructor, discriminant_, *this); }
  Result &operator=(const Result &source) {
    if (_xdr_field_number(discriminant_) 
        == _xdr_field_number(source.discriminant_))
      _xdr_with_mem_ptr(xdr::field_assigner, discriminant_, *this, source);
    else {
      this->~Result();
      discriminant_ = std::uint32_t(-1);
      _xdr_with_mem_ptr(xdr::field_constructor, discriminant_, *this, source);
    }
    discriminant_ = source.discriminant_;
    return *this;
  }
  Result &operator=(Result &&source) {
    if (_xdr_field_number(discriminant_)
         == _xdr_field_number(source.discriminant_))
      _xdr_with_mem_ptr(xdr::field_assigner, discriminant_, *this,
                        std::move(source));
    else {
      this->~Result();
      discriminant_ = std::uint32_t(-1);
      _xdr_with_mem_ptr(xdr::field_constructor, discriminant_, *this,
                        std::move(source));
    }
    discriminant_ = source.discriminant_;
    return *this;
  }

  std::uint32_t discriminant() const { return std::uint32_t(discriminant_); }
  Result &discriminant(unsigned _xdr_d, bool _xdr_validate = true) {
    _xdr_discriminant(_xdr_d, _xdr_validate);
    return *this;
  }

  xdr::xstring<> &val() {
    if (_xdr_field_number(discriminant_) == 1)
      return val_;
    throw xdr::xdr_wrong_union("Result: val accessed when not selected");
  }
  const xdr::xstring<> &val() const {
    if (_xdr_field_number(discriminant_) == 1)
      return val_;
    throw xdr::xdr_wrong_union("Result: val accessed when not selected");
  }
  xdr::xvector<longstring> &keys() {
    if (_xdr_field_number(discriminant_) == 2)
      return keys_;
    throw xdr::xdr_wrong_union("Result: keys accessed when not selected");
  }
  const xdr::xvector<longstring> &keys() const {
    if (_xdr_field_number(discriminant_) == 2)
      return keys_;
    throw xdr::xdr_wrong_union("Result: keys accessed when not selected");
  }
  ServerError &error() {
    if (_xdr_field_number(discriminant_) == 3)
      return error_;
    throw xdr::xdr_wrong_union("Result: error accessed when not selected");
  }
  const ServerError &error() const {
    if (_xdr_field_number(discriminant_) == 3)
      return error_;
    throw xdr::xdr_wrong_union("Result: error accessed when not selected");
  }
};
namespace xdr {
template<> struct xdr_traits<::Result> : xdr_traits_base {
  static constexpr bool is_class = true;
  static constexpr bool is_union = true;
  static constexpr bool has_fixed_size = false;

  using union_type = ::Result;
  using discriminant_type = decltype(std::declval<union_type>().discriminant());

  static constexpr const char *union_field_name(std::uint32_t which) {
    return which == 1 ? "val"
      : which == 2 ? "keys"
      : "error";
  }
  static const char *union_field_name(const union_type &u) {
    return union_field_name(u._xdr_discriminant());
  }

  static std::size_t serial_size(const ::Result &obj) {
    std::size_t size = 0;
    if (!obj._xdr_with_mem_ptr(field_size, obj._xdr_discriminant(), obj, size))
      throw xdr_bad_discriminant("bad value of discriminant in Result");
    return size + 4;
  }
  template<typename Archive> static void
  save(Archive &ar, const ::Result &obj) {
    xdr::archive(ar, obj.discriminant(), "discriminant");
    if (!obj._xdr_with_mem_ptr(field_archiver, obj.discriminant(), ar, obj,
                               union_field_name(obj)))
      throw xdr_bad_discriminant("bad value of discriminant in Result");
  }
  template<typename Archive> static void
  load(Archive &ar, ::Result &obj) {
    discriminant_type which;
    xdr::archive(ar, which, "discriminant");
    obj.discriminant(which);
    obj._xdr_with_mem_ptr(field_archiver, obj.discriminant(), ar, obj,
                          union_field_name(which));
  }
};
}

struct api_v1 {
  static constexpr std::uint32_t program = 1074036870;
  static constexpr const char *program_name = "server_api";
  static constexpr std::uint32_t version = 1;
  static constexpr const char *version_name = "api_v1";

  struct create_t {
    using interface_type = api_v1;
    static constexpr std::uint32_t proc = 1;
    static constexpr const char *proc_name = "create";
    using arg_type = kvpair;
    using arg_wire_type = kvpair;
    using res_type = Result;
    using res_wire_type = Result;
    
    template<typename C, typename...A> static auto
    dispatch(C &&c, A &&...a) ->
    decltype(c.create(std::forward<A>(a)...)) {
      return c.create(std::forward<A>(a)...);
    }
    
    template<typename C, typename DropIfVoid, typename...A> static auto
    dispatch_dropvoid(C &&c, DropIfVoid &&d, A &&...a) ->
    decltype(c.create(std::forward<DropIfVoid>(d), std::forward<A>(a)...)) {
      return c.create(std::forward<DropIfVoid>(d), std::forward<A>(a)...);
    }
  };

  struct remove_t {
    using interface_type = api_v1;
    static constexpr std::uint32_t proc = 2;
    static constexpr const char *proc_name = "remove";
    using arg_type = longstring;
    using arg_wire_type = longstring;
    using res_type = Result;
    using res_wire_type = Result;
    
    template<typename C, typename...A> static auto
    dispatch(C &&c, A &&...a) ->
    decltype(c.remove(std::forward<A>(a)...)) {
      return c.remove(std::forward<A>(a)...);
    }
    
    template<typename C, typename DropIfVoid, typename...A> static auto
    dispatch_dropvoid(C &&c, DropIfVoid &&d, A &&...a) ->
    decltype(c.remove(std::forward<DropIfVoid>(d), std::forward<A>(a)...)) {
      return c.remove(std::forward<DropIfVoid>(d), std::forward<A>(a)...);
    }
  };

  struct set_t {
    using interface_type = api_v1;
    static constexpr std::uint32_t proc = 3;
    static constexpr const char *proc_name = "set";
    using arg_type = kvpair;
    using arg_wire_type = kvpair;
    using res_type = Result;
    using res_wire_type = Result;
    
    template<typename C, typename...A> static auto
    dispatch(C &&c, A &&...a) ->
    decltype(c.set(std::forward<A>(a)...)) {
      return c.set(std::forward<A>(a)...);
    }
    
    template<typename C, typename DropIfVoid, typename...A> static auto
    dispatch_dropvoid(C &&c, DropIfVoid &&d, A &&...a) ->
    decltype(c.set(std::forward<DropIfVoid>(d), std::forward<A>(a)...)) {
      return c.set(std::forward<DropIfVoid>(d), std::forward<A>(a)...);
    }
  };

  struct get_t {
    using interface_type = api_v1;
    static constexpr std::uint32_t proc = 4;
    static constexpr const char *proc_name = "get";
    using arg_type = longstring;
    using arg_wire_type = longstring;
    using res_type = Result;
    using res_wire_type = Result;
    
    template<typename C, typename...A> static auto
    dispatch(C &&c, A &&...a) ->
    decltype(c.get(std::forward<A>(a)...)) {
      return c.get(std::forward<A>(a)...);
    }
    
    template<typename C, typename DropIfVoid, typename...A> static auto
    dispatch_dropvoid(C &&c, DropIfVoid &&d, A &&...a) ->
    decltype(c.get(std::forward<DropIfVoid>(d), std::forward<A>(a)...)) {
      return c.get(std::forward<DropIfVoid>(d), std::forward<A>(a)...);
    }
  };

  struct list_t {
    using interface_type = api_v1;
    static constexpr std::uint32_t proc = 5;
    static constexpr const char *proc_name = "list";
    using arg_type = longstring;
    using arg_wire_type = longstring;
    using res_type = Result;
    using res_wire_type = Result;
    
    template<typename C, typename...A> static auto
    dispatch(C &&c, A &&...a) ->
    decltype(c.list(std::forward<A>(a)...)) {
      return c.list(std::forward<A>(a)...);
    }
    
    template<typename C, typename DropIfVoid, typename...A> static auto
    dispatch_dropvoid(C &&c, DropIfVoid &&d, A &&...a) ->
    decltype(c.list(std::forward<DropIfVoid>(d), std::forward<A>(a)...)) {
      return c.list(std::forward<DropIfVoid>(d), std::forward<A>(a)...);
    }
  };

  template<typename T, typename...A> static bool
  call_dispatch(T &&t, std::uint32_t proc, A &&...a) {
    switch(proc) {
    case 1:
      t.template dispatch<create_t>(std::forward<A>(a)...);
      return true;
    case 2:
      t.template dispatch<remove_t>(std::forward<A>(a)...);
      return true;
    case 3:
      t.template dispatch<set_t>(std::forward<A>(a)...);
      return true;
    case 4:
      t.template dispatch<get_t>(std::forward<A>(a)...);
      return true;
    case 5:
      t.template dispatch<list_t>(std::forward<A>(a)...);
      return true;
    }
    return false;
  }

  template<typename _XDRBASE> struct client : _XDRBASE {
    using _XDRBASE::_XDRBASE;

    template<typename..._XDRARGS> auto
    create(_XDRARGS &&..._xdr_args) ->
    decltype(this->_XDRBASE::template invoke<create_t>(_xdr_args...)) {
      return this->_XDRBASE::template invoke<create_t>(_xdr_args...);
    }

    template<typename..._XDRARGS> auto
    remove(_XDRARGS &&..._xdr_args) ->
    decltype(this->_XDRBASE::template invoke<remove_t>(_xdr_args...)) {
      return this->_XDRBASE::template invoke<remove_t>(_xdr_args...);
    }

    template<typename..._XDRARGS> auto
    set(_XDRARGS &&..._xdr_args) ->
    decltype(this->_XDRBASE::template invoke<set_t>(_xdr_args...)) {
      return this->_XDRBASE::template invoke<set_t>(_xdr_args...);
    }

    template<typename..._XDRARGS> auto
    get(_XDRARGS &&..._xdr_args) ->
    decltype(this->_XDRBASE::template invoke<get_t>(_xdr_args...)) {
      return this->_XDRBASE::template invoke<get_t>(_xdr_args...);
    }

    template<typename..._XDRARGS> auto
    list(_XDRARGS &&..._xdr_args) ->
    decltype(this->_XDRBASE::template invoke<list_t>(_xdr_args...)) {
      return this->_XDRBASE::template invoke<list_t>(_xdr_args...);
    }
  };
};

#endif // !__XDR_INCLUDE_SERVER_HH_INCLUDED__
