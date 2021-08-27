#include <SLDA.h>

#include <rice/rice.hpp>

#include "utils.h"

void init_slda(Rice::Module& m) {
  Rice::define_class_under<tomoto::ISLDAModel, tomoto::ILDAModel>(m, "SLDA")
    .define_singleton_function(
      "_new",
      [](size_t tw, size_t k, Array rb_vars, tomoto::Float alpha, tomoto::Float eta, std::vector<tomoto::Float> mu, std::vector<tomoto::Float> nu_sq, std::vector<tomoto::Float> glm_param, size_t seed) {
        std::vector<tomoto::ISLDAModel::GLM> vars;
        vars.reserve(rb_vars.size());
        for (auto const& v : rb_vars) {
          vars.push_back((tomoto::ISLDAModel::GLM) Rice::detail::From_Ruby<int>().convert(v.value()));
        }
        tomoto::SLDAArgs args;
        args.k = k;
        args.vars = vars;
        args.alpha = {alpha};
        args.eta = eta;
        args.mu = mu;
        args.nuSq = nu_sq;
        args.glmParam = glm_param;
        if (seed >= 0) {
          args.seed = seed;
        }
        return tomoto::ISLDAModel::create((tomoto::TermWeight)tw, args);
      }, Rice::Return().takeOwnership())
    .define_method(
      "_add_doc",
      [](tomoto::ISLDAModel& self, std::vector<std::string> words, std::vector<tomoto::Float> y) {
        auto doc = buildDoc(words);
        doc.misc["y"] = y;
        return self.addDoc(doc);
      })
    .define_method(
      "f",
      [](tomoto::ISLDAModel& self) {
        return self.getF();
      })
    .define_method(
      "_var_type",
      [](tomoto::ISLDAModel& self, size_t var_id) {
        if (var_id >= self.getF()) throw std::runtime_error{ "'var_id' must be < 'f'" };
        return self.getTypeOfVar(var_id) == tomoto::ISLDAModel::GLM::linear ? "l" : "b";
      });
}
