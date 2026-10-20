#include "policy/hedge_fixed.h"

#include "policy/selector.h"

namespace blr {

Drive HedgeFixed::choose_primary(const IoBackend& backend) {
  return choose_less_busy(backend, rr_);
}

bool HedgeFixed::try_hedge(const LogicalRead& read, const IoBackend&, uint64_t now_ns) {
  // TODO: also require that the primary is still unfinished (completion race)
  // and that no duplicate exists yet.
  return !read.duplicate.has_value() &&
         now_ns >= read.primary.submit_ns + delay_ns_;
}

}  // namespace blr
