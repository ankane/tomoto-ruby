#pragma once

#include <rice/Array.hpp>

using Rice::Array;
using Rice::Object;

template<>
inline
Object to_ruby<std::vector<tomoto::Float>>(std::vector<tomoto::Float> const & x)
{
  Array res;
  for (auto const& v : x) {
    res.push(v);
  }
  return res;
}

template<>
inline
Object to_ruby<std::vector<uint32_t>>(std::vector<uint32_t> const & x)
{
  Array res;
  for (auto const& v : x) {
    res.push(v);
  }
  return res;
}

template<>
inline
Object to_ruby<std::vector<uint64_t>>(std::vector<uint64_t> const & x)
{
  Array res;
  for (auto const& v : x) {
    res.push(v);
  }
  return res;
}

template<>
inline
std::vector<std::string> from_ruby<std::vector<std::string>>(Object x)
{
  Array a = Array(x);
  std::vector<std::string> res;
  res.reserve(a.size());
  for (auto const& v : a) {
    res.push_back(from_ruby<std::string>(v));
  }
  return res;
}

template<>
inline
std::vector<tomoto::Float> from_ruby<std::vector<tomoto::Float>>(Object x)
{
  Array a = Array(x);
  std::vector<tomoto::Float> res;
  res.reserve(a.size());
  for (auto const& v : a) {
    res.push_back(from_ruby<tomoto::Float>(v));
  }
  return res;
}

template<>
inline
std::vector<uint64_t> from_ruby<std::vector<uint64_t>>(Object x)
{
  Array a = Array(x);
  std::vector<uint64_t> res;
  res.reserve(a.size());
  for (auto const& v : a) {
    res.push_back(from_ruby<uint64_t>(v));
  }
  return res;
}

inline tomoto::RawDoc buildDoc(std::vector<std::string>& words) {
  tomoto::RawDoc doc;
  doc.rawWords = words;
  return doc;
}
