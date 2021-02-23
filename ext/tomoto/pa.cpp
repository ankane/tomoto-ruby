#include <PA.h>

#include <rice/Module.hpp>

#include "utils.h"

void init_pa(Rice::Module& m) {
  Rice::define_class_under<tomoto::IPAModel, tomoto::ILDAModel>(m, "PA")
    .define_singleton_method(
      "_new",
      *[](size_t tw, size_t k1, size_t k2, tomoto::Float alpha, tomoto::Float eta, int seed) {
        if (seed < 0) {
          seed = std::random_device{}();
        }
        return tomoto::IPAModel::create((tomoto::TermWeight)tw, k1, k2, alpha, eta, seed);
      })
    .define_method(
      "k1",
      *[](tomoto::IPAModel& self) {
        return self.getK();
      })
    .define_method(
      "k2",
      *[](tomoto::IPAModel& self) {
        return self.getK2();
      });
}
