#include <MGLDA.h>

#include <rice/Module.hpp>

#include "utils.h"

void init_mglda(Rice::Module& m) {
  Rice::define_class_under<tomoto::IMGLDAModel, tomoto::ILDAModel>(m, "MGLDA")
    .define_singleton_method(
      "_new",
      *[](size_t tw, size_t k_g, size_t k_l, size_t t, tomoto::Float alpha_g, tomoto::Float alpha_l, tomoto::Float alpha_mg, tomoto::Float alpha_ml, tomoto::Float eta_g) {
        return tomoto::IMGLDAModel::create((tomoto::TermWeight)tw, k_g, k_l, t, alpha_g, alpha_l, alpha_mg, alpha_ml, eta_g);
      })
    .define_method(
      "_add_doc",
      *[](tomoto::IMGLDAModel& self, std::vector<std::string> words, std::string delimiter) {
        auto doc = buildDoc(words);
        doc.misc["delimiter"] = delimiter;
        self.addDoc(doc);
      })
    .define_method(
      "alpha_g",
      *[](tomoto::IMGLDAModel& self) {
        return self.getAlpha();
      })
    .define_method(
      "alpha_l",
      *[](tomoto::IMGLDAModel& self) {
        return self.getAlphaL();
      })
    .define_method(
      "alpha_mg",
      *[](tomoto::IMGLDAModel& self) {
        return self.getAlphaM();
      })
    .define_method(
      "alpha_ml",
      *[](tomoto::IMGLDAModel& self) {
        return self.getAlphaML();
      })
    .define_method(
      "eta_g",
      *[](tomoto::IMGLDAModel& self) {
        return self.getEta();
      })
    .define_method(
      "eta_l",
      *[](tomoto::IMGLDAModel& self) {
        return self.getEtaL();
      })
    .define_method(
      "gamma",
      *[](tomoto::IMGLDAModel& self) {
        return self.getGamma();
      })
    .define_method(
      "k_g",
      *[](tomoto::IMGLDAModel& self) {
        return self.getK();
      })
    .define_method(
      "k_l",
      *[](tomoto::IMGLDAModel& self) {
        return self.getKL();
      })
    .define_method(
      "t",
      *[](tomoto::IMGLDAModel& self) {
        return self.getT();
      });
}
