#include <rice/rice.hpp>

void init_lda(Rice::Module& m);
void init_ct(Rice::Module& m);
void init_dmr(Rice::Module& m);
void init_dt(Rice::Module& m);
void init_gdmr(Rice::Module& m);
void init_hdp(Rice::Module& m);
void init_hlda(Rice::Module& m);
void init_pa(Rice::Module& m);
void init_hpa(Rice::Module& m);
void init_mglda(Rice::Module& m);
void init_llda(Rice::Module& m);
void init_plda(Rice::Module& m);
void init_slda(Rice::Module& m);

extern "C"
void Init_ext()
{
  auto m = Rice::define_module("Tomoto")
    .define_singleton_function(
      "isa",
      []() {
        #ifdef __AVX2__
          return Rice::String("avx2");
        #elif defined(__AVX__)
          return Rice::String("avx");
        #elif defined(__SSE2__) || defined(__x86_64__) || defined(_WIN64)
          return Rice::String("sse2");
        #else
          return Rice::String("none");
        #endif
      });

  init_lda(m);
  init_ct(m);
  init_dmr(m);
  init_dt(m);
  init_gdmr(m);
  init_hdp(m);
  init_hlda(m);
  init_pa(m);
  init_hpa(m);
  init_mglda(m);
  init_llda(m);
  init_plda(m);
  init_slda(m);
}
