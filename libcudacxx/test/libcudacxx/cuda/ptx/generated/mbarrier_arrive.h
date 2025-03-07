// This file was automatically generated. Do not edit.

// We use a special strategy to force the generation of the PTX. This is mainly
// a fight against dead-code-elimination in the NVVM layer.
//
// The reason we need this strategy is because certain older versions of ptxas
// segfault when a non-sensical sequence of PTX is generated. So instead, we try
// to force the instantiation and compilation to PTX of all the overloads of the
// PTX wrapping functions.
//
// We do this by writing a function pointer of each overload to the kernel
// parameter `fn_ptr`.
//
// Because `fn_ptr` is possibly visible outside this translation unit, the
// compiler must compile all the functions which are stored.

__global__ void test_mbarrier_arrive(void** fn_ptr)
{
#if __cccl_ptx_isa >= 700
  NV_IF_TARGET(
    NV_PROVIDES_SM_80,
    (
        // mbarrier.arrive.shared.b64                                  state,  [addr];           // 1.
        * fn_ptr++ = reinterpret_cast<void*>(static_cast<uint64_t (*)(uint64_t*)>(cuda::ptx::mbarrier_arrive));));
#endif // __cccl_ptx_isa >= 700

#if __cccl_ptx_isa >= 780
  NV_IF_TARGET(NV_PROVIDES_SM_90,
               (
                   // mbarrier.arrive.shared::cta.b64                             state,  [addr], count;    // 2.
                   * fn_ptr++ = reinterpret_cast<void*>(
                     static_cast<uint64_t (*)(uint64_t*, const uint32_t&)>(cuda::ptx::mbarrier_arrive));));
#endif // __cccl_ptx_isa >= 780

#if __cccl_ptx_isa >= 800
  NV_IF_TARGET(
    NV_PROVIDES_SM_90,
    (
        // mbarrier.arrive.release.cta.shared::cta.b64                   state,  [addr];           // 3a.
        * fn_ptr++ = reinterpret_cast<void*>(
          static_cast<uint64_t (*)(
            cuda::ptx::sem_release_t, cuda::ptx::scope_cta_t, cuda::ptx::space_shared_t, uint64_t*)>(
            cuda::ptx::mbarrier_arrive));
          // mbarrier.arrive.release.cluster.shared::cta.b64                   state,  [addr];           // 3a.
            * fn_ptr++ = reinterpret_cast<void*>(
              static_cast<uint64_t (*)(
                cuda::ptx::sem_release_t, cuda::ptx::scope_cluster_t, cuda::ptx::space_shared_t, uint64_t*)>(
                cuda::ptx::mbarrier_arrive));));
#endif // __cccl_ptx_isa >= 800

#if __cccl_ptx_isa >= 800
  NV_IF_TARGET(
    NV_PROVIDES_SM_90,
    (
        // mbarrier.arrive.release.cta.shared::cta.b64                   state,  [addr], count;    // 3b.
        * fn_ptr++ = reinterpret_cast<void*>(
          static_cast<uint64_t (*)(
            cuda::ptx::sem_release_t, cuda::ptx::scope_cta_t, cuda::ptx::space_shared_t, uint64_t*, const uint32_t&)>(
            cuda::ptx::mbarrier_arrive));
          // mbarrier.arrive.release.cluster.shared::cta.b64                   state,  [addr], count;    // 3b.
            * fn_ptr++ = reinterpret_cast<void*>(
              static_cast<uint64_t (*)(cuda::ptx::sem_release_t,
                                       cuda::ptx::scope_cluster_t,
                                       cuda::ptx::space_shared_t,
                                       uint64_t*,
                                       const uint32_t&)>(cuda::ptx::mbarrier_arrive));));
#endif // __cccl_ptx_isa >= 800

#if __cccl_ptx_isa >= 800
  NV_IF_TARGET(
    NV_PROVIDES_SM_90,
    (
        // mbarrier.arrive.release.cluster.shared::cluster.b64                   _, [addr];                // 4a.
        * fn_ptr++ = reinterpret_cast<void*>(
          static_cast<void (*)(
            cuda::ptx::sem_release_t, cuda::ptx::scope_cluster_t, cuda::ptx::space_cluster_t, uint64_t*)>(
            cuda::ptx::mbarrier_arrive));));
#endif // __cccl_ptx_isa >= 800

#if __cccl_ptx_isa >= 800
  NV_IF_TARGET(
    NV_PROVIDES_SM_90,
    (
        // mbarrier.arrive.release.cluster.shared::cluster.b64                   _, [addr], count;         // 4b.
        * fn_ptr++ = reinterpret_cast<void*>(
          static_cast<void (*)(
            cuda::ptx::sem_release_t, cuda::ptx::scope_cluster_t, cuda::ptx::space_cluster_t, uint64_t*, const uint32_t&)>(
            cuda::ptx::mbarrier_arrive));));
#endif // __cccl_ptx_isa >= 800
}
