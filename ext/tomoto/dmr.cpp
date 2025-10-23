#include <string>
#include <vector>

#include <DMR.h>

#include <rice/rice.hpp>
#include <rice/stl.hpp>

#include "utils.h"

void init_dmr(Rice::Module& m) {
  Rice::define_class_under<tomoto::IDMRModel, tomoto::ILDAModel>(m, "DMR")
    .define_singleton_function(
      "_new",
      [](size_t tw, size_t k, tomoto::Float alpha, tomoto::Float sigma, tomoto::Float eta, tomoto::Float alpha_epsilon, size_t seed) {
        tomoto::DMRArgs args;
        args.k = k;
        args.alpha = {alpha};
        args.sigma = sigma;
        args.eta = eta;
        args.alphaEps = alpha_epsilon;
        if (seed >= 0) {
          args.seed = seed;
        }
        return tomoto::IDMRModel::create((tomoto::TermWeight)tw, args);
      }, Rice::Return().takeOwnership())
    .define_method(
      "_add_doc",
      [](tomoto::IDMRModel& self, std::vector<std::string> words, std::string metadata) {
        auto doc = buildDoc(words);
        doc.misc["metadata"] = metadata;
        return self.addDoc(doc);
      })
    .define_method(
      "alpha_epsilon",
      [](tomoto::IDMRModel& self) {
        return self.getAlphaEps();
      })
    .define_method(
      "alpha_epsilon=",
      [](tomoto::IDMRModel& self, tomoto::Float value) {
        self.setAlphaEps(value);
        return value;
      })
    .define_method(
      "f",
      [](tomoto::IDMRModel& self) {
        return self.getF();
      })
    .define_method(
      "_lambdas",
      [](tomoto::IDMRModel& self, tomoto::Tid topic_id) {
        return self.getLambdaByTopic(topic_id);
      })
    .define_method(
      "metadata_dict",
      [](tomoto::IDMRModel& self) {
        auto dict = self.getMetadataDict();
        Array res;
        auto utf8 = Rice::Class(rb_cEncoding).call("const_get", "UTF_8");
        for (size_t i = 0; i < dict.size(); i++) {
          VALUE value = Rice::detail::To_Ruby<std::string>().convert(dict.toWord(i));
          Object obj(value);
          res.push(obj.call("force_encoding", utf8), false);
        }
        return res;
      })
    .define_method(
      "sigma",
      [](tomoto::IDMRModel& self) {
        return self.getSigma();
      });
}
