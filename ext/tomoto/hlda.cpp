#include <HLDA.h>

#include <rice/Module.hpp>

#include "utils.h"

void init_hlda(Rice::Module& m) {
  Rice::define_class_under<tomoto::IHLDAModel, tomoto::ILDAModel>(m, "HLDA")
    .define_singleton_method(
      "_new",
      *[](size_t tw, size_t levelDepth, tomoto::Float alpha, tomoto::Float eta, tomoto::Float gamma, int seed) {
        if (seed < 0) {
          seed = std::random_device{}();
        }
        return tomoto::IHLDAModel::create((tomoto::TermWeight)tw, levelDepth, alpha, eta, gamma, seed);
      })
    .define_method(
      "alpha",
      *[](tomoto::IHLDAModel& self) {
        Array res;
        for (size_t i = 0; i < self.getLevelDepth(); i++) {
          res.push(self.getAlpha(i));
        }
        return res;
      })
    .define_method(
      "_children_topics",
      *[](tomoto::IHLDAModel& self, tomoto::Tid topic_id) {
        return self.getChildTopicId(topic_id);
      })
    .define_method(
      "depth",
      *[](tomoto::IHLDAModel& self) {
        return self.getLevelDepth();
      })
    .define_method(
      "gamma",
      *[](tomoto::IHLDAModel& self) {
        return self.getGamma();
      })
    .define_method(
      "_level",
      *[](tomoto::IHLDAModel& self, tomoto::Tid topic_id) {
        return self.getLevelOfTopic(topic_id);
      })
    .define_method(
      "live_k",
      *[](tomoto::IHLDAModel& self) {
        return self.getLiveK();
      })
    .define_method(
      "_live_topic?",
      *[](tomoto::IHLDAModel& self, tomoto::Tid topic_id) {
        return self.isLiveTopic(topic_id);
      })
    .define_method(
      "_num_docs_of_topic",
      *[](tomoto::IHLDAModel& self, tomoto::Tid topic_id) {
        return self.getNumDocsOfTopic(topic_id);
      })
    .define_method(
      "_parent_topic",
      *[](tomoto::IHLDAModel& self, tomoto::Tid topic_id) {
        return self.getParentTopicId(topic_id);
      });
}
