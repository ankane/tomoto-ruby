#pragma once

#include <string>
#include <vector>

#include <rice/rice.hpp>
#include <rice/stl.hpp>

using Rice::Array;
using Rice::Object;

namespace Rice::detail {
  template<typename T>
  class To_Ruby<std::vector<T>> {
  public:
    To_Ruby() = default;

    explicit To_Ruby(Arg* arg) : arg_(arg) { }

    VALUE convert(std::vector<T> const & x) {
      auto a = rb_ary_new2(x.size());
      for (const auto& v : x) {
        detail::protect(rb_ary_push, a, To_Ruby<T>().convert(v));
      }
      return a;
    }

  private:
    Arg* arg_ = nullptr;
  };
} // namespace Rice::detail

inline tomoto::RawDoc buildDoc(std::vector<std::string>& words) {
  tomoto::RawDoc doc;
  doc.rawWords = words;
  return doc;
}
