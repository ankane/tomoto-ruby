#include <HLDA.h>

#include <rice/rice.hpp>

#include "utils.h"

void init_hlda(Rice::Module& m) {
  Rice::define_class_under<tomoto::IHLDAModel, tomoto::ILDAModel>(m, "HLDA")
    .define_singleton_function(
      "_new",
      [](size_t tw, size_t levelDepth, tomoto::Float alpha, tomoto::Float eta, tomoto::Float gamma, size_t seed) {
        tomoto::HLDAArgs args;
        args.k = levelDepth;
        args.alpha = {alpha};
        args.eta = eta;
        args.gamma = gamma;
        if (seed >= 0) {
          args.seed = seed;
        }
        return tomoto::IHLDAModel::create((tomoto::TermWeight)tw, args).release();
      }, Rice::Return().takeOwnership())
    .define_method(
      "alpha",
      [](tomoto::IHLDAModel& self) {
        Array res;
        for (size_t i = 0; i < self.getLevelDepth(); i++) {
          res.push(self.getAlpha(i), false);
        }
        return res;
      })
    .define_method(
      "_children_topics",
      [](tomoto::IHLDAModel& self, tomoto::Tid topic_id) {
        return self.getChildTopicId(topic_id);
      })
    .define_method(
      "depth",
      [](tomoto::IHLDAModel& self) {
        return self.getLevelDepth();
      })
    .define_method(
      "gamma",
      [](tomoto::IHLDAModel& self) {
        return self.getGamma();
      })
    .define_method(
      "_level",
      [](tomoto::IHLDAModel& self, tomoto::Tid topic_id) {
        return self.getLevelOfTopic(topic_id);
      })
    .define_method(
      "live_k",
      [](tomoto::IHLDAModel& self) {
        return self.getLiveK();
      })
    .define_method(
      "_live_topic?",
      [](tomoto::IHLDAModel& self, tomoto::Tid topic_id) {
        return self.isLiveTopic(topic_id);
      })
    .define_method(
      "_num_docs_of_topic",
      [](tomoto::IHLDAModel& self, tomoto::Tid topic_id) {
        return self.getNumDocsOfTopic(topic_id);
      })
    .define_method(
      "_parent_topic",
      [](tomoto::IHLDAModel& self, tomoto::Tid topic_id) {
        return self.getParentTopicId(topic_id);
      });
}
