#include <HPA.h>

#include <rice/Module.hpp>

#include "utils.h"

void init_hpa(Rice::Module& m) {
  Rice::define_class_under<tomoto::IHPAModel, tomoto::IPAModel>(m, "HPA")
    .define_singleton_method(
      "_new",
      *[](size_t tw, size_t k1, size_t k2, tomoto::Float alpha, tomoto::Float eta, int seed) {
        if (seed < 0) {
          seed = std::random_device{}();
        }
        return tomoto::IHPAModel::create((tomoto::TermWeight)tw, false, k1, k2, alpha, eta, seed);
      })
    .define_method(
      "alpha",
      *[](tomoto::IHPAModel& self) {
        Array res;
        // use <= to return k+1 elements
        for (size_t i = 0; i <= self.getK(); i++) {
          res.push(self.getAlpha(i));
        }
        return res;
      });
}
