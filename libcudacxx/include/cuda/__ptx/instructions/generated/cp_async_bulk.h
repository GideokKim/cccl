// This file was automatically generated. Do not edit.

#ifndef _CUDA_PTX_GENERATED_CP_ASYNC_BULK_H_
#define _CUDA_PTX_GENERATED_CP_ASYNC_BULK_H_

/*
// cp.async.bulk.dst.src.mbarrier::complete_tx::bytes [dstMem], [srcMem], size, [smem_bar]; // 1a. unicast PTX ISA 80,
SM_90
// .dst       = { .shared::cluster }
// .src       = { .global }
template <typename = void>
__device__ static inline void cp_async_bulk(
  cuda::ptx::space_cluster_t,
  cuda::ptx::space_global_t,
  void* dstMem,
  const void* srcMem,
  const uint32_t& size,
  uint64_t* smem_bar);
*/
#if __cccl_ptx_isa >= 800
extern "C" _CCCL_DEVICE void __cuda_ptx_cp_async_bulk_is_not_supported_before_SM_90__();
template <typename = void>
_CCCL_DEVICE static inline void cp_async_bulk(
  space_cluster_t,
  space_global_t,
  void* __dstMem,
  const void* __srcMem,
  const _CUDA_VSTD::uint32_t& __size,
  _CUDA_VSTD::uint64_t* __smem_bar)
{
  // __space == space_cluster (due to parameter type constraint)
  // __space == space_global (due to parameter type constraint)
  NV_IF_ELSE_TARGET(
    NV_PROVIDES_SM_90,
    (asm("cp.async.bulk.shared::cluster.global.mbarrier::complete_tx::bytes [%0], [%1], %2, [%3]; // "
         "1a. unicast" : : "r"(__as_ptr_smem(__dstMem)),
         "l"(__as_ptr_gmem(__srcMem)),
         "r"(__size),
         "r"(__as_ptr_smem(__smem_bar)) : "memory");),
    (
      // Unsupported architectures will have a linker error with a semi-decent error message
      __cuda_ptx_cp_async_bulk_is_not_supported_before_SM_90__();));
}
#endif // __cccl_ptx_isa >= 800

/*
// cp.async.bulk.dst.src.mbarrier::complete_tx::bytes [dstMem], [srcMem], size, [rdsmem_bar]; // 2.  PTX ISA 80, SM_90
// .dst       = { .shared::cluster }
// .src       = { .shared::cta }
template <typename = void>
__device__ static inline void cp_async_bulk(
  cuda::ptx::space_cluster_t,
  cuda::ptx::space_shared_t,
  void* dstMem,
  const void* srcMem,
  const uint32_t& size,
  uint64_t* rdsmem_bar);
*/
#if __cccl_ptx_isa >= 800
extern "C" _CCCL_DEVICE void __cuda_ptx_cp_async_bulk_is_not_supported_before_SM_90__();
template <typename = void>
_CCCL_DEVICE static inline void cp_async_bulk(
  space_cluster_t,
  space_shared_t,
  void* __dstMem,
  const void* __srcMem,
  const _CUDA_VSTD::uint32_t& __size,
  _CUDA_VSTD::uint64_t* __rdsmem_bar)
{
  // __space == space_cluster (due to parameter type constraint)
  // __space == space_shared (due to parameter type constraint)
  NV_IF_ELSE_TARGET(
    NV_PROVIDES_SM_90,
    (asm("cp.async.bulk.shared::cluster.shared::cta.mbarrier::complete_tx::bytes [%0], [%1], %2, [%3]; // 2. " : : "r"(
           __as_ptr_remote_dsmem(__dstMem)),
         "r"(__as_ptr_smem(__srcMem)),
         "r"(__size),
         "r"(__as_ptr_remote_dsmem(__rdsmem_bar)) : "memory");),
    (
      // Unsupported architectures will have a linker error with a semi-decent error message
      __cuda_ptx_cp_async_bulk_is_not_supported_before_SM_90__();));
}
#endif // __cccl_ptx_isa >= 800

/*
// cp.async.bulk.dst.src.bulk_group [dstMem], [srcMem], size; // 3.  PTX ISA 80, SM_90
// .dst       = { .global }
// .src       = { .shared::cta }
template <typename = void>
__device__ static inline void cp_async_bulk(
  cuda::ptx::space_global_t,
  cuda::ptx::space_shared_t,
  void* dstMem,
  const void* srcMem,
  const uint32_t& size);
*/
#if __cccl_ptx_isa >= 800
extern "C" _CCCL_DEVICE void __cuda_ptx_cp_async_bulk_is_not_supported_before_SM_90__();
template <typename = void>
_CCCL_DEVICE static inline void
cp_async_bulk(space_global_t, space_shared_t, void* __dstMem, const void* __srcMem, const _CUDA_VSTD::uint32_t& __size)
{
  // __space == space_global (due to parameter type constraint)
  // __space == space_shared (due to parameter type constraint)
  NV_IF_ELSE_TARGET(
    NV_PROVIDES_SM_90,
    (asm("cp.async.bulk.global.shared::cta.bulk_group [%0], [%1], %2; // 3. " : : "l"(__as_ptr_gmem(__dstMem)),
         "r"(__as_ptr_smem(__srcMem)),
         "r"(__size) : "memory");),
    (
      // Unsupported architectures will have a linker error with a semi-decent error message
      __cuda_ptx_cp_async_bulk_is_not_supported_before_SM_90__();));
}
#endif // __cccl_ptx_isa >= 800

#endif // _CUDA_PTX_GENERATED_CP_ASYNC_BULK_H_
