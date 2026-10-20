#pragma once

#include <memory>
#include <string>

#include "engine/io_backend.h"

namespace blr {

// Linux-only backend using an ordinary io_uring ring (no SQPOLL, no cancellation).
// Liburing details are hidden behind Impl so this header stays portable.
class UringBackend : public IoBackend {
 public:
  UringBackend(const std::string& path_a, const std::string& path_b,
               unsigned queue_depth);
  ~UringBackend() override;

  bool submit(const ReadSubmission& req) override;
  size_t poll(std::vector<ReadCompletion>& out) override;
  size_t outstanding(Drive d) const override;

 private:
  struct Impl;
  std::unique_ptr<Impl> impl_;
};

}  // namespace blr
