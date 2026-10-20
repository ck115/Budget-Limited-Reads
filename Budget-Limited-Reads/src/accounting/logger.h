#pragma once

#include <fstream>
#include <string>

#include "mirror/request.h"

namespace blr {

// CSV logs: one row per logical read and one row per replica read (losers
// included). Plots are generated from these files, not from live counters.
class Logger {
 public:
  bool open(const std::string& logical_path, const std::string& replica_path);

  // TODO: finalize columns (ids, timestamps, drive, outcome, winner, permit state).
  void log_logical(const LogicalRead& read, bool ok);
  void log_replica(LogicalId logical, const ReplicaRead& replica, bool winner);

 private:
  std::ofstream logical_;
  std::ofstream replica_;
};

}  // namespace blr
