#include "policy/selector.h"

namespace blr {

Drive choose_less_busy(const IoBackend& backend, int& rr_state) {
  size_t a = backend.outstanding(Drive::A);
  size_t b = backend.outstanding(Drive::B);
  if (a < b) return Drive::A;
  if (b < a) return Drive::B;
  Drive d = static_cast<Drive>(rr_state);
  rr_state ^= 1;
  return d;
}

Drive NoDupRoundRobin::choose_primary(const IoBackend&) {
  Drive d = static_cast<Drive>(next_);
  next_ ^= 1;
  return d;
}

Drive NoDupLessBusy::choose_primary(const IoBackend& backend) {
  return choose_less_busy(backend, next_);
}

}  // namespace blr
