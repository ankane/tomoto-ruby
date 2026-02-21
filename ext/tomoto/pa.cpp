#include <PA.h>

#include <rice/rice.hpp>

#include "utils.h"

void init_pa(Rice::Module& m) {
  Rice::define_class_under<tomoto::IPAModel, tomoto::ILDAModel>(m, "PA")
    .define_singleton_function(
      "_new",
      [](size_t tw, size_t k1, size_t k2, tomoto::Float alpha, tomoto::Float eta, size_t seed) {
        tomoto::PAArgs args;
        args.k = k1;
        args.k2 = k2;
        args.alpha = {alpha};
        args.eta = eta;
        if (seed >= 0) {
          args.seed = seed;
        }
        return tomoto::IPAModel::create((tomoto::TermWeight)tw, args).release();
      }, Rice::Return().takeOwnership())
    .define_method(
      "k1",
      [](tomoto::IPAModel& self) {
        return self.getK();
      })
    .define_method(
      "k2",
      [](tomoto::IPAModel& self) {
        return self.getK2();
      });
}
