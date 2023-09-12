/**
 * @file svc.h
 * @brief Wrappers for kernel syscalls.
 * @copyright libnx Authors
 */
#pragma once

extern "C" {

/**
 * @brief Outputs debug text, if used during debugging.
 * @param[in] str Text to output.
 * @param[in] size Size of the text in bytes.
 * @return Result code.
 * @note Syscall number 0x27.
 */
Result svcOutputDebugString(const char *str, u64 size);


}