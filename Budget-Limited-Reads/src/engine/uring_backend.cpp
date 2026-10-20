#include "engine/uring_backend.h"

#include <liburing.h>

namespace blr {

struct UringBackend::Impl {
  // TODO: struct io_uring ring; file descriptors (O_DIRECT) for both drives;
  // per-drive outstanding counters.
  size_t outstanding[2] = {0, 0};
};

UringBackend::UringBackend(const std::string&, const std::string&, unsigned)
    : impl_(new Impl) {
  // TODO: io_uring_queue_init, open both files read-only.
}

UringBackend::~UringBackend() = default;

bool UringBackend::submit(const ReadSubmission&) {
  // TODO: io_uring_get_sqe, io_uring_prep_read, set user_data = replica id.
  return false;
}

size_t UringBackend::poll(std::vector<ReadCompletion>&) {
  // TODO: io_uring_peek_cqe / io_uring_cqe_seen loop.
  return 0;
}

size_t UringBackend::outstanding(Drive d) const {
  return impl_->outstanding[static_cast<int>(d)];
}

}  // namespace blr
