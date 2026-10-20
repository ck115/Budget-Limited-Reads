#pragma once

#include "policy/policy.h"

namespace blr {

// No-duplicate baseline: alternate drives.
class NoDupRoundRobin : public Policy {
 public:
  const char* name() const override { return "nodup-roundrobin"; }
  Drive choose_primary(const IoBackend& backend) override;
  bool try_hedge(const LogicalRead&, const IoBackend&, uint64_t) override { return false; }
  void on_pair_drained(const LogicalRead&) override {}

 private:
  int next_ = 0;
};

// No-duplicate baseline: fewer outstanding reads first, round-robin on ties.
class NoDupLessBusy : public Policy {
 public:
  const char* name() const override { return "nodup-lessbusy"; }
  Drive choose_primary(const IoBackend& backend) override;
  bool try_hedge(const LogicalRead&, const IoBackend&, uint64_t) override { return false; }
  void on_pair_drained(const LogicalRead&) override {}

 private:
  int next_ = 0;
};

// Shared primary-selection rule used by the hedging policies.
Drive choose_less_busy(const IoBackend& backend, int& rr_state);

}  // namespace blr
