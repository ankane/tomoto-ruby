#include <DMR.h>

#include <rice/Class.hpp>
#include <rice/Module.hpp>

#include "utils.h"

void init_dmr(Rice::Module& m) {
  Rice::define_class_under<tomoto::IDMRModel, tomoto::ILDAModel>(m, "DMR")
    .define_singleton_method(
      "_new",
      *[](size_t tw, size_t k, tomoto::Float alpha, tomoto::Float sigma, tomoto::Float eta, tomoto::Float alpha_epsilon, int seed) {
        if (seed < 0) {
          seed = std::random_device{}();
        }
        return tomoto::IDMRModel::create((tomoto::TermWeight)tw, k, alpha, sigma, eta, alpha_epsilon, seed);
      })
    .define_method(
      "_add_doc",
      *[](tomoto::IDMRModel& self, std::vector<std::string> words, std::string metadata) {
        auto doc = buildDoc(words);
        doc.misc["metadata"] = metadata;
        self.addDoc(doc);
      })
    .define_method(
      "alpha_epsilon",
      *[](tomoto::IDMRModel& self) {
        return self.getAlphaEps();
      })
    .define_method(
      "alpha_epsilon=",
      *[](tomoto::IDMRModel& self, tomoto::Float value) {
        self.setAlphaEps(value);
        return value;
      })
    .define_method(
      "f",
      *[](tomoto::IDMRModel& self) {
        return self.getF();
      })
    .define_method(
      "_lambdas",
      *[](tomoto::IDMRModel& self, tomoto::Tid topic_id) {
        return self.getLambdaByTopic(topic_id);
      })
    .define_method(
      "metadata_dict",
      *[](tomoto::IDMRModel& self) {
        auto dict = self.getMetadataDict();
        Array res;
        auto utf8 = Rice::Class(rb_cEncoding).call("const_get", "UTF_8");
        for (size_t i = 0; i < dict.size(); i++) {
          res.push(to_ruby<std::string>(dict.toWord(i)).call("force_encoding", utf8));
        }
        return res;
      })
    .define_method(
      "sigma",
      *[](tomoto::IDMRModel& self) {
        return self.getSigma();
      });
}
