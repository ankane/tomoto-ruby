#include <SLDA.h>

#include <rice/Module.hpp>

#include "utils.h"

void init_slda(Rice::Module& m) {
  Rice::define_class_under<tomoto::ISLDAModel, tomoto::ILDAModel>(m, "SLDA")
    .define_singleton_method(
      "_new",
      *[](size_t tw, size_t k, Array rb_vars, tomoto::Float alpha, tomoto::Float eta, std::vector<tomoto::Float> mu, std::vector<tomoto::Float> nu_sq, std::vector<tomoto::Float> glm_param, int seed) {
        if (seed < 0) {
          seed = std::random_device{}();
        }
        std::vector<tomoto::ISLDAModel::GLM> vars;
        vars.reserve(rb_vars.size());
        for (auto const& v : rb_vars) {
          vars.push_back((tomoto::ISLDAModel::GLM) from_ruby<int>(v));
        }
        return tomoto::ISLDAModel::create((tomoto::TermWeight)tw, k, vars, alpha, eta, mu, nu_sq, glm_param, seed);
      })
    .define_method(
      "_add_doc",
      *[](tomoto::ISLDAModel& self, std::vector<std::string> words, std::vector<tomoto::Float> y) {
        auto doc = buildDoc(words);
        doc.misc["y"] = y;
        return self.addDoc(doc);
      })
    .define_method(
      "f",
      *[](tomoto::ISLDAModel& self) {
        return self.getF();
      })
    .define_method(
      "_var_type",
      *[](tomoto::ISLDAModel& self, size_t var_id) {
        if (var_id >= self.getF()) throw std::runtime_error{ "'var_id' must be < 'f'" };
        return self.getTypeOfVar(var_id) == tomoto::ISLDAModel::GLM::linear ? "l" : "b";
      });
}
