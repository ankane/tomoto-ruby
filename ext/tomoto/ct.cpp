#include <CT.h>

#include <rice/rice.hpp>

#include "utils.h"

void init_ct(Rice::Module& m) {
  Rice::define_class_under<tomoto::ICTModel, tomoto::ILDAModel>(m, "CT")
    .define_singleton_function(
      "_new",
      [](size_t tw, size_t k, tomoto::Float alpha, tomoto::Float eta, size_t seed) {
        tomoto::CTArgs args;
        args.k = k;
        args.alpha = {alpha};
        args.eta = eta;
        if (seed >= 0) {
          args.seed = seed;
        }
        return tomoto::ICTModel::create((tomoto::TermWeight)tw, args);
      }, Rice::Return().takeOwnership())
    .define_method(
      "_correlations",
      [](tomoto::ICTModel& self, tomoto::Tid topic_id) {
        return self.getCorrelationTopic(topic_id);
      })
    .define_method(
      "num_beta_sample",
      [](tomoto::ICTModel& self) {
        return self.getNumBetaSample();
      })
    .define_method(
      "num_beta_sample=",
      [](tomoto::ICTModel& self, size_t value) {
        self.setNumBetaSample(value);
        return value;
      })
    .define_method(
      "num_tmn_sample",
      [](tomoto::ICTModel& self) {
        return self.getNumTMNSample();
      })
    .define_method(
      "num_tmn_sample=",
      [](tomoto::ICTModel& self, size_t value) {
        self.setNumTMNSample(value);
        return value;
      })
    .define_method(
      "_prior_cov",
      [](tomoto::ICTModel& self) {
        return self.getPriorCov();
      })
    .define_method(
      "prior_mean",
      [](tomoto::ICTModel& self) {
        return self.getPriorMean();
      });
}
