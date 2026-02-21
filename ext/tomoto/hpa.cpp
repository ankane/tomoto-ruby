#include <HPA.h>

#include <rice/rice.hpp>

#include "utils.h"

void init_hpa(Rice::Module& m) {
  Rice::define_class_under<tomoto::IHPAModel, tomoto::IPAModel>(m, "HPA")
    .define_singleton_function(
      "_new",
      [](size_t tw, size_t k1, size_t k2, tomoto::Float alpha, tomoto::Float eta, size_t seed) {
        tomoto::HPAArgs args;
        args.k = k1;
        args.k2 = k2;
        args.alpha = {alpha};
        args.eta = eta;
        if (seed >= 0) {
          args.seed = seed;
        }
        return tomoto::IHPAModel::create((tomoto::TermWeight)tw, false, args).release();
      }, Rice::Return().takeOwnership())
    .define_method(
      "alpha",
      [](tomoto::IHPAModel& self) {
        Array res;
        // use <= to return k+1 elements
        for (size_t i = 0; i <= self.getK(); i++) {
          res.push(self.getAlpha(i), false);
        }
        return res;
      });
}
