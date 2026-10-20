#include "accounting/counters.h"

namespace blr {

double Counters::duplicate_fraction() const {
  return logical_submitted ? static_cast<double>(duplicates_issued) / logical_submitted : 0.0;
}

double Counters::replica_reads_per_logical() const {
  return logical_succeeded ? static_cast<double>(replica_issued) / logical_succeeded : 0.0;
}

}  // namespace blr
